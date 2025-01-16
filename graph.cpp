#include "graph.hpp"

Graph::Graph(int width, int height) : graphWidth(width), graphHeight(height) {}

void Graph::drawGraph(sf::RenderTarget &target, const std::vector<double> &pathLossValues, int xPos, int yPos, const std::string &title) {
    const int barWidth = 40;
    const int spaceBetweenBars = 10;

    // Load font
    sf::Font font;
    if (!font.loadFromFile("C:\\Users\\badre\\AGH\\Methodology finalProject\\Arialn.ttf")) {
        throw std::runtime_error("Failed to load font");
    }

    // Draw title
    sf::Text graphTitle;
    graphTitle.setFont(font);
    graphTitle.setString(title);
    graphTitle.setCharacterSize(18);
    graphTitle.setFillColor(sf::Color::Black);
    graphTitle.setPosition(xPos, yPos - 30); // Position title above the graph

    target.draw(graphTitle);

    // Draw bars for each path loss value
    for (size_t i = 0; i < pathLossValues.size(); ++i) {
        double pathLoss = pathLossValues[i];
        // Scale the height of the bar based on the path loss
        int barHeight = static_cast<int>((pathLoss - 20) * (graphHeight / 10.0)); // Assuming path loss between 20 to 30 dB

        // Create the bar (RectangleShape)
        sf::RectangleShape bar(sf::Vector2f(barWidth, barHeight));
        bar.setFillColor(sf::Color::Blue);
        bar.setPosition(xPos + i * (barWidth + spaceBetweenBars), yPos + graphHeight - barHeight); // Adjust bar position

        target.draw(bar);
    }

    // Draw axes
    sf::Vertex xAxis[] = {
            sf::Vertex(sf::Vector2f(xPos, yPos + graphHeight), sf::Color::Black),
            sf::Vertex(sf::Vector2f(xPos + pathLossValues.size() * (barWidth + spaceBetweenBars), yPos + graphHeight), sf::Color::Black)
    };

    sf::Vertex yAxis[] = {
            sf::Vertex(sf::Vector2f(xPos, yPos), sf::Color::Black),
            sf::Vertex(sf::Vector2f(xPos, yPos + graphHeight), sf::Color::Black)
    };

    target.draw(xAxis, 2, sf::Lines);
    target.draw(yAxis, 2, sf::Lines);
}
