#include "../Include/graph.hpp"

Graph::Graph(int width, int height) : graphWidth(width), graphHeight(height) {}

void Graph::drawGraph(sf::RenderTarget& target, const std::vector<double>& values, int xPos, int yPos, const std::string& title, const sf::Color& barColor) {
    const int barWidth = 30;
    const int spaceBetweenBars = 20;
    const int padding = 20;

    sf::Font font;
    if (!font.loadFromFile("C:\\Users\\badre\\AGH\\Project-Capstone\\Assets\\Arialn.ttf")) {
        throw std::runtime_error("Failed to load font");
    }

    sf::Text graphTitle;
    graphTitle.setFont(font);
    graphTitle.setString(title);
    graphTitle.setCharacterSize(16);
    graphTitle.setFillColor(sf::Color::Black);
    graphTitle.setPosition(xPos + padding, yPos - 30);
    target.draw(graphTitle);

    double maxValue = *std::max_element(values.begin(), values.end());
    if (maxValue == 0) maxValue = 1; // Avoid division by zero

    for (size_t i = 0; i < values.size(); ++i) {
        double value = values[i];
        int barHeight = static_cast<int>((value / maxValue) * (graphHeight - 2 * padding));

        sf::RectangleShape bar(sf::Vector2f(barWidth, barHeight));
        bar.setFillColor(barColor);
        bar.setPosition(xPos + padding + i * (barWidth + spaceBetweenBars), yPos + graphHeight - padding - barHeight);
        target.draw(bar);

        sf::Text valueLabel;
        valueLabel.setFont(font);
        valueLabel.setString(std::to_string(static_cast<int>(value)));
        valueLabel.setCharacterSize(12);
        valueLabel.setFillColor(sf::Color::Black);
        valueLabel.setPosition(xPos + padding + i * (barWidth + spaceBetweenBars) + barWidth / 2 - 10, yPos + graphHeight - padding - barHeight - 20);
        target.draw(valueLabel);
    }

    sf::Vertex xAxis[] = {
            sf::Vertex(sf::Vector2f(xPos + padding, yPos + graphHeight - padding), sf::Color::Black),
            sf::Vertex(sf::Vector2f(xPos + padding + values.size() * (barWidth + spaceBetweenBars), yPos + graphHeight - padding), sf::Color::Black)
    };

    sf::Vertex yAxis[] = {
            sf::Vertex(sf::Vector2f(xPos + padding, yPos + padding), sf::Color::Black),
            sf::Vertex(sf::Vector2f(xPos + padding, yPos + graphHeight - padding), sf::Color::Black)
    };

    target.draw(xAxis, 2, sf::Lines);
    target.draw(yAxis, 2, sf::Lines);
}

void Graph::drawMultipleGraphs(sf::RenderTexture& renderTexture, const std::vector<std::vector<double>>& data, const std::vector<std::string>& titles, int graphsPerRow, int xOffset, int yOffset, int graphWidth, int graphHeight, int graphSpacing) {
    int currentColumn = 0;
    int currentRow = 0;

    for (size_t i = 0; i < data.size(); ++i) {
        int xPos = xOffset + currentColumn * (graphWidth + graphSpacing);
        int yPos = yOffset + currentRow * (graphHeight + graphSpacing);

        drawGraph(renderTexture, data[i], xPos, yPos, titles[i]);

        currentColumn++;
        if (currentColumn >= graphsPerRow) {
            currentColumn = 0;
            currentRow++;
        }
    }
}
