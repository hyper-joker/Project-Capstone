#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <numeric>
#include "Include/graph.hpp"
#include "Include/data_handler.hpp"
#include "Include/simulation.hpp"

int main() {
    const int ITERATIONS = 50;
    const double MAP_LENGTH = 10.0; // 10km minimum as per requirement

    // SFML Configuration
    const int graphWidth = 300;
    const int graphHeight = 200;
    const int graphSpacing = 50;
    const int graphsPerRow = 3;
    const int xOffset = 50;
    const int yOffset = 50;

    std::vector<std::pair<int, int>> configurations = {
            {100, 10}, {100, 20}, {100, 30}, {100, 40}, {100, 50},
            {200, 10}, {200, 20}, {200, 30}, {200, 40}, {200, 50},
            {300, 10}, {300, 20}, {300, 30}, {300, 40}, {300, 50},
            {400, 10}, {400, 20}, {400, 30}, {400, 40}, {400, 50},
            {500, 10}, {500, 20}, {500, 30}, {500, 40}, {500, 50}
    };

    // Data storage for visualization
    std::vector<std::vector<double>> pathLossValuesForGraphs;

    // Initialize CSV files
    std::string avgResultsCsv = "C:\\Users\\badre\\AGH\\Project-Capstone\\Results\\average_results.csv";
    std::string detailedResultsCsv = "C:\\Users\\badre\\AGH\\Project-Capstone\\Results\\detailed_results.csv";

    // Save headers
    saveCSVHeader(avgResultsCsv);
    saveDetailedCSVHeader(detailedResultsCsv);

    // Process each configuration
    for (const auto& config : configurations) {
        double totalAvgPathLoss = 0;
        double totalUnlinkedVehicles = 0;
        double totalUnusedAntennas = 0;
        std::vector<double> allPathLossValues;
        std::vector<double> avgPathLossesPerIteration;

        // Run 50 iterations for each configuration
        for (int i = 0; i < ITERATIONS; ++i) {
            Simulation sim(config.first, config.second, MAP_LENGTH);
            sim.runSimulation();

            double iterationPathLoss = sim.getAvgPathLoss();
            totalAvgPathLoss += iterationPathLoss;
            totalUnlinkedVehicles += sim.getUnlinkedVehicles();
            totalUnusedAntennas += sim.getUnusedAntennas();

            // Save detailed results for each iteration
            saveDetailedCSVData(detailedResultsCsv, config.first, config.second, i + 1,
                                iterationPathLoss, sim.getUnlinkedVehicles(),
                                sim.getUnusedAntennas());

            avgPathLossesPerIteration.push_back(iterationPathLoss);
        }

        // Calculate final averages
        double finalAvgPathLoss = totalAvgPathLoss / ITERATIONS;
        double finalAvgUnlinkedVehicles = totalUnlinkedVehicles / ITERATIONS;
        double finalAvgUnusedAntennas = totalUnusedAntennas / ITERATIONS;

        // Save averaged results
        saveCSVData(avgResultsCsv, config.first, config.second,
                    finalAvgPathLoss, finalAvgUnlinkedVehicles,
                    finalAvgUnusedAntennas);

        // Store the first 5 path loss values for visualization
        pathLossValuesForGraphs.push_back(
                std::vector<double>(avgPathLossesPerIteration.begin(),
                                    avgPathLossesPerIteration.begin() +
                                    std::min(size_t(5), avgPathLossesPerIteration.size())));
    }

    /*// SFML Visualization
    int totalGraphs = configurations.size();
    int textureWidth = xOffset + (graphWidth + graphSpacing) *
                                 std::min(graphsPerRow, totalGraphs);
    int textureHeight = yOffset + (graphHeight + graphSpacing) *
                                  ((totalGraphs + graphsPerRow - 1) / graphsPerRow);

    sf::RenderTexture renderTexture;
    if (!renderTexture.create(textureWidth, textureHeight)) {
        throw std::runtime_error("Failed to create render texture");
    }

    Graph graph(graphWidth, graphHeight);
    renderTexture.clear(sf::Color::White);

    int currentColumn = 0;
    int currentRow = 0;

    // Draw graphs
    for (size_t i = 0; i < configurations.size(); ++i) {
        std::ostringstream title;
        title << configurations[i].first << " Vehicles, "
              << configurations[i].second << " Antennas";

        int xPos = xOffset + currentColumn * (graphWidth + graphSpacing);
        int yPos = yOffset + currentRow * (graphHeight + graphSpacing);

        if (xPos + graphWidth + graphSpacing <= textureWidth &&
            yPos + graphHeight + graphSpacing <= textureHeight) {
            graph.drawGraph(renderTexture, pathLossValuesForGraphs[i],
                            xPos, yPos, title.str());

            currentColumn++;
            if (currentColumn >= graphsPerRow) {
                currentColumn = 0;
                currentRow++;
            }
        }
    }

    // Save screenshot
    renderTexture.display();
    sf::Image screenshot = renderTexture.getTexture().copyToImage();
    if (!screenshot.saveToFile("C:\\Users\\badre\\AGH\\Methodology finalProject\\simulation_graphs.png")) {
        throw std::runtime_error("Failed to save the screenshot");
    }

    std::cout << "Screenshot saved as simulation_graphs.png" << std::endl;//*/
    std::cout << "Results saved in " << avgResultsCsv << " and "
              << detailedResultsCsv << std::endl;

    return 0;
}