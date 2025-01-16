#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>

class Graph {
public:
    Graph(int width, int height);

    void drawGraph(sf::RenderTarget &target, const std::vector<double> &pathLossValues, int xPos, int yPos, const std::string &title);
    int graphWidth;
    int graphHeight;
};

#endif
