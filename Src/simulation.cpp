#include "../Include/simulation.hpp"

double Simulation::calculateCostHataPathLoss(double distance, double antennaHeight) {
    // COST-Hata model for urban environment
    double a_hm = (1.1 * log10(frequency) - 0.7) * vehicleHeight
                  - (1.56 * log10(frequency) - 0.8);

    // Basic path loss for urban areas
    double L = 69.55 + 26.16 * log10(frequency)
               - 13.82 * log10(antennaHeight)
               - a_hm
               + (44.9 - 6.55 * log10(antennaHeight)) * log10(distance);

    return L;
}

Simulation::Simulation(int v, int a, double l) : vehicles(v), antennas(a), mapLength(l) {
    pathLossValues.clear();
}

void Simulation::runSimulation() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, mapLength);
    std::uniform_real_distribution<> height_dis(0.01, 0.04); // 10m to 40m in km

    std::vector<std::tuple<double, double, double>> vehiclePositions;
    std::vector<std::tuple<double, double, double>> antennaPositions;

    // Generate positions
    for (int i = 0; i < vehicles; ++i) {
        vehiclePositions.push_back({dis(gen), dis(gen), 0.001}); // 1m height in km
    }

    for (int i = 0; i < antennas; ++i) {
        antennaPositions.push_back({dis(gen), dis(gen), height_dis(gen)});
    }

    double totalPathLoss = 0;
    std::vector<bool> antennaUsed(antennas, false);
    int linkedVehicles = 0;

    // Process each vehicle
    for (int i = 0; i < vehicles; ++i) {
        auto [vx, vy, vz] = vehiclePositions[i];
        double minDistance = maxLinkDistance;
        double bestPathLoss = -1;
        int bestAntennaIndex = -1;

        // Find closest antenna within range
        for (int j = 0; j < antennas; ++j) {
            auto [ax, ay, az] = antennaPositions[j];
            double distance = sqrt(pow(vx - ax, 2) + pow(vy - ay, 2));

            if (distance < maxLinkDistance && distance < minDistance) {
                minDistance = distance;
                double pathLoss = calculateCostHataPathLoss(distance, az * 1000); // Convert km to m
                bestPathLoss = pathLoss;
                bestAntennaIndex = j;
            }
        }

        // If vehicle is linked
        if (bestAntennaIndex != -1) {
            linkedVehicles++;
            antennaUsed[bestAntennaIndex] = true;
            totalPathLoss += bestPathLoss;
            pathLossValues.push_back(bestPathLoss);
        }
    }

    // Calculate results
    unlinkedVehicles = vehicles - linkedVehicles;
    unusedAntennas = antennas - std::count(antennaUsed.begin(), antennaUsed.end(), true);
    avgPathLoss = linkedVehicles > 0 ? totalPathLoss / linkedVehicles : 0;
}

double Simulation::getAvgPathLoss() const{
    return avgPathLoss;
}

int Simulation::getUnlinkedVehicles() const {
    return unlinkedVehicles;
}

int Simulation::getUnusedAntennas() const {
    return unusedAntennas;
}

const std::vector<double>& Simulation::getPathLossValues() const {
    return pathLossValues;
}