#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <numeric>
#include "Include/graph.hpp"
#include "Include/data_handler.hpp"
#include "Include/simulation.hpp"

std::vector<std::vector<double>> readAverageResults(const std::string& filename) {
    std::vector<std::vector<double>> data;
    std::ifstream file(filename);
    std::string line;

    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string cell;
        std::vector<double> row;

        while (std::getline(ss, cell, ',')) {
            row.push_back(std::stod(cell));
        }

        data.push_back(row);
    }

    return data;
}

int main() {
    const int ITERATIONS = 50;
    const double MAP_LENGTH = 10.0;

    std::string avgResultsCsv = "C:\\Users\\badre\\AGH\\Project-Capstone\\Results\\average_results.csv";
    std::string detailedResultsCsv = "C:\\Users\\badre\\AGH\\Project-Capstone\\Results\\detailed_results.csv";

    saveCSVHeader(avgResultsCsv);
    saveDetailedCSVHeader(detailedResultsCsv);

    std::vector<std::pair<int, int>> configurations = {
            {100, 10}, {100, 20}, {100, 30}, {100, 40}, {100, 50},
            {200, 10}, {200, 20}, {200, 30}, {200, 40}, {200, 50},
            {300, 10}, {300, 20}, {300, 30}, {300, 40}, {300, 50},
            {400, 10}, {400, 20}, {400, 30}, {400, 40}, {400, 50},
            {500, 10}, {500, 20}, {500, 30}, {500, 40}, {500, 50}
    };

    for (const auto& config : configurations) {
        double totalAvgPathLoss = 0;
        double totalUnlinkedVehicles = 0;
        double totalUnusedAntennas = 0;

        for (int i = 0; i < ITERATIONS; ++i) {
            Simulation sim(config.first, config.second, MAP_LENGTH);
            sim.runSimulation();

            totalAvgPathLoss += sim.getAvgPathLoss();
            totalUnlinkedVehicles += sim.getUnlinkedVehicles();
            totalUnusedAntennas += sim.getUnusedAntennas();

            saveDetailedCSVData(detailedResultsCsv, config.first, config.second, i + 1,
                                sim.getAvgPathLoss(), sim.getUnlinkedVehicles(),
                                sim.getUnusedAntennas());
        }

        double finalAvgPathLoss = totalAvgPathLoss / ITERATIONS;
        double finalAvgUnlinkedVehicles = totalUnlinkedVehicles / ITERATIONS;
        double finalAvgUnusedAntennas = totalUnusedAntennas / ITERATIONS;

        saveCSVData(avgResultsCsv, config.first, config.second,
                    finalAvgPathLoss, finalAvgUnlinkedVehicles,
                    finalAvgUnusedAntennas);
    }

    std::vector<std::vector<double>> averageResults = readAverageResults(avgResultsCsv);

    std::vector<std::vector<double>> pathLossData;
    std::vector<std::vector<double>> unlinkedVehiclesData;
    std::vector<std::vector<double>> unusedAntennasData;

    std::vector<std::string> pathLossTitles;
    std::vector<std::string> unlinkedVehiclesTitles;
    std::vector<std::string> unusedAntennasTitles;

    for (int vehicles = 100; vehicles <= 500; vehicles += 100) {
        std::vector<double> pathLossValues;
        std::vector<double> unlinkedVehiclesValues;
        std::vector<double> unusedAntennasValues;

        for (const auto& row : averageResults) {
            if (row[0] == vehicles) {
                pathLossValues.push_back(row[2]);
                unlinkedVehiclesValues.push_back(row[3]);
                unusedAntennasValues.push_back(row[4]);
            }
        }

        pathLossData.push_back(pathLossValues);
        unlinkedVehiclesData.push_back(unlinkedVehiclesValues);
        unusedAntennasData.push_back(unusedAntennasValues);

        pathLossTitles.push_back(std::to_string(vehicles) + " Vehicles - Path Loss");
        unlinkedVehiclesTitles.push_back(std::to_string(vehicles) + " Vehicles - Unlinked Vehicles");
        unusedAntennasTitles.push_back(std::to_string(vehicles) + " Vehicles - Unused Antennas");
    }

    // SFML Visualization
    const int graphWidth = 400;
    const int graphHeight = 300;
    const int graphSpacing = 50;
    const int graphsPerRow = 3;
    const int xOffset = 50;
    const int yOffset = 50;

    Graph graph(graphWidth, graphHeight);

    sf::RenderTexture pathLossTexture;
    if (!pathLossTexture.create(xOffset + (graphWidth + graphSpacing) * graphsPerRow,
                                yOffset + (graphHeight + graphSpacing) * ((pathLossData.size() + graphsPerRow - 1) / graphsPerRow))) {
        throw std::runtime_error("Failed to create render texture for path loss graphs");
    }
    pathLossTexture.clear(sf::Color::White);
    graph.drawMultipleGraphs(pathLossTexture, pathLossData, pathLossTitles, graphsPerRow, xOffset, yOffset, graphWidth, graphHeight, graphSpacing);
    pathLossTexture.display();
    sf::Image pathLossImage = pathLossTexture.getTexture().copyToImage();
    if (!pathLossImage.saveToFile("C:\\Users\\badre\\AGH\\Project-Capstone\\Results\\path_loss_graphs.png")) {
        throw std::runtime_error("Failed to save path loss graphs");
    }

    sf::RenderTexture unlinkedVehiclesTexture;
    if (!unlinkedVehiclesTexture.create(xOffset + (graphWidth + graphSpacing) * graphsPerRow,
                                        yOffset + (graphHeight + graphSpacing) * ((unlinkedVehiclesData.size() + graphsPerRow - 1) / graphsPerRow))) {
        throw std::runtime_error("Failed to create render texture for unlinked vehicles graphs");
    }
    unlinkedVehiclesTexture.clear(sf::Color::White);
    graph.drawMultipleGraphs(unlinkedVehiclesTexture, unlinkedVehiclesData, unlinkedVehiclesTitles, graphsPerRow, xOffset, yOffset, graphWidth, graphHeight, graphSpacing);
    unlinkedVehiclesTexture.display();
    sf::Image unlinkedVehiclesImage = unlinkedVehiclesTexture.getTexture().copyToImage();
    if (!unlinkedVehiclesImage.saveToFile("C:\\Users\\badre\\AGH\\Project-Capstone\\Results\\unlinked_vehicles_graphs.png")) {
        throw std::runtime_error("Failed to save unlinked vehicles graphs");
    }

    sf::RenderTexture unusedAntennasTexture;
    if (!unusedAntennasTexture.create(xOffset + (graphWidth + graphSpacing) * graphsPerRow,
                                      yOffset + (graphHeight + graphSpacing) * ((unusedAntennasData.size() + graphsPerRow - 1) / graphsPerRow))) {
        throw std::runtime_error("Failed to create render texture for unused antennas graphs");
    }
    unusedAntennasTexture.clear(sf::Color::White);
    graph.drawMultipleGraphs(unusedAntennasTexture, unusedAntennasData, unusedAntennasTitles, graphsPerRow, xOffset, yOffset, graphWidth, graphHeight, graphSpacing);
    unusedAntennasTexture.display();
    sf::Image unusedAntennasImage = unusedAntennasTexture.getTexture().copyToImage();
    if (!unusedAntennasImage.saveToFile("C:\\Users\\badre\\AGH\\Project-Capstone\\Results\\unused_antennas_graphs.png")) {
        throw std::runtime_error("Failed to save unused antennas graphs");
    }

    std::cout << "Results saved in " << avgResultsCsv << " and " << detailedResultsCsv << std::endl;
    std::cout << "Graphs saved as:\n"
              << "- path_loss_graphs.png\n"
              << "- unlinked_vehicles_graphs.png\n"
              << "- unused_antennas_graphs.png" << std::endl;

    return 0;
}