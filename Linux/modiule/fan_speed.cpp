#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <dirent.h>

// Function to set fan speed
void setFanSpeed(const std::string& fanPath, int speed) {
    std::ofstream file(fanPath); // Open the fan control file
    if (file.is_open()) {
        file << speed; // Set the fan speed
        file.close();
        std::cout << "Fan speed set to " << speed << " for fan: " << fanPath << std::endl;
    } else {
        std::cerr << "Unable to open fan speed control file for fan: " << fanPath << std::endl;
    }
}

// Function to find fan control files
std::vector<std::string> findFanControlFiles(const std::string& baseDir) {
    std::vector<std::string> fanPaths;
    DIR* dir;
    struct dirent* ent;
    if ((dir = opendir(baseDir.c_str())) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            std::string name(ent->d_name);
            if (name.find("pwm") != std::string::npos) {
                std::string fanPath = baseDir + "/" + name;
                fanPaths.push_back(fanPath);
            }
        }
        closedir(dir);
    } else {
        std::cerr << "Unable to open directory: " << baseDir << std::endl;
    }
    return fanPaths;
}

int main() {
    const std::string baseDir = "/sys/class/hwmon"; // Base directory for fan control files
    const int fanSpeed = 80; // Example fan speed (percentage)

    // Find fan control files
    std::vector<std::string> fanPaths = findFanControlFiles(baseDir);

    // Set fan speed for each fan
    for (const auto& fanPath : fanPaths) {
        setFanSpeed(fanPath, fanSpeed);
    }

    return 0;
} 
