#ifndef SIMULATION_H
#define SIMULATION_H

#include <cmath>
#include <random>
#include <vector>
#include <algorithm>
#include <iostream>

class Simulation {
private:
    int vehicles;
    int antennas;
    double mapLength;
    const double maxLinkDistance = 0.8;
    const double vehicleHeight = 1.0;
    const double frequency = 1500.0;

    double avgPathLoss = 0;
    int unlinkedVehicles = 0;
    int unusedAntennas = 0;
    std::vector<double> pathLossValues;

    double calculateCostHataPathLoss(double distance, double antennaHeight);

public:
    Simulation(int v, int a, double l);

    void runSimulation();

    double getAvgPathLoss() const;
    int getUnlinkedVehicles() const;
    int getUnusedAntennas() const;
    const std::vector<double>& getPathLossValues() const;
};

#endif
