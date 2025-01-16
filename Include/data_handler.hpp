#ifndef DATA_HANDLER_HPP
#define DATA_HANDLER_HPP
#include <string>

void saveCSVHeader(const std::string& filename);
void saveDetailedCSVHeader(const std::string& filename);
void saveCSVData(const std::string& filename, int vehicles, int antennas,
                 double avgPathLoss, double avgUnlinkedVehicles,
                 double avgUnusedAntennas);
void saveDetailedCSVData(const std::string& filename, int vehicles, int antennas,
                         int iteration, double pathLoss, int unlinkedVehicles,
                         int unusedAntennas);

#endif // DATA_HANDLER_HPP