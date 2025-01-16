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
    const double maxLinkDistance = 0.8; // 0.8 km as per requirement
    const double vehicleHeight = 1.0;   // 1m as per requirement
    const double frequency = 1500.0;    // MHz (maximum frequency for urban environment)

    // Results storage
    double avgPathLoss = 0;
    int unlinkedVehicles = 0;
    int unusedAntennas = 0;
    std::vector<double> pathLossValues;

    double calculateCostHataPathLoss(double distance, double antennaHeight);

public:
    Simulation(int v, int a, double l);

    void runSimulation();

    // Getters
    double getAvgPathLoss() const;
    int getUnlinkedVehicles() const;
    int getUnusedAntennas() const;
    const std::vector<double>& getPathLossValues() const;
};

#endif
