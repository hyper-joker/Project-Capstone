#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>

class Graph {
public:
    Graph(int width, int height);

    void drawGraph(sf::RenderTarget& target, const std::vector<double>& values, int xPos, int yPos, const std::string& title, const sf::Color& barColor = sf::Color::Blue);
    void drawMultipleGraphs(sf::RenderTexture& renderTexture, const std::vector<std::vector<double>>& data, const std::vector<std::string>& titles, int graphsPerRow, int xOffset, int yOffset, int graphWidth, int graphHeight, int graphSpacing);

private:
    int graphWidth;
    int graphHeight;
};

#endif