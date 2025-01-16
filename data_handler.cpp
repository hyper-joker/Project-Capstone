#include "data_handler.hpp"
#include <fstream>
#include <iostream>

void saveCSVHeader(const std::string& filename) {
    std::ofstream file(filename, std::ios::trunc);
    if (file.is_open()) {
        file << "Vehicles,Antennas,AvgPathLoss,AvgUnlinkedVehicles,AvgUnusedAntennas\n";
        file.close();
    } else {
        std::cerr << "Unable to open file for writing header: " << filename << std::endl;
    }
}

void saveDetailedCSVHeader(const std::string& filename) {
    std::ofstream file(filename, std::ios::trunc);
    if (file.is_open()) {
        file << "Vehicles,Antennas,Iteration,PathLoss,UnlinkedVehicles,UnusedAntennas\n";
        file.close();
    } else {
        std::cerr << "Unable to open file for writing header: " << filename << std::endl;
    }
}

void saveCSVData(const std::string& filename, int vehicles, int antennas,
                 double avgPathLoss, double avgUnlinkedVehicles,
                 double avgUnusedAntennas) {
    std::ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        file << vehicles << ","
             << antennas << ","
             << avgPathLoss << ","
             << avgUnlinkedVehicles << ","
             << avgUnusedAntennas << "\n";
        file.close();
    } else {
        std::cerr << "Unable to open file for writing data: " << filename << std::endl;
    }
}

void saveDetailedCSVData(const std::string& filename, int vehicles, int antennas,
                         int iteration, double pathLoss, int unlinkedVehicles,
                         int unusedAntennas) {
    std::ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        file << vehicles << ","
             << antennas << ","
             << iteration << ","
             << pathLoss << ","
             << unlinkedVehicles << ","
             << unusedAntennas << "\n";
        file.close();
    } else {
        std::cerr << "Unable to open file for writing data: " << filename << std::endl;
    }
}