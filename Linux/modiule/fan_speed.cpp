#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <dirent.h>
#include <unistd.h> // For sleep function

// Function to set fan speed in RPM
void setFanSpeedRPM(const std::string& fanPath, int rpm) {
    // Convert RPM to PWM value (if necessary)
    int pwmValue = rpm * 255 / 5000; // Example conversion, adjust as needed

    // Write PWM value to fan control file
    std::ofstream file(fanPath);
    if (file.is_open()) {
        file << pwmValue;
        file.close();
        std::cout << "Fan speed set to " << rpm << " RPM for fan: " << fanPath << std::endl;
    } else {
        std::cerr << "Unable to open fan control file for fan: " << fanPath << std::endl;
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
    const int targetFanRPM = 2000; // Example target fan speed in RPM

    // Find fan control files
    std::vector<std::string> fanPaths = findFanControlFiles(baseDir);

    // Set fan speed for each fan
    for (const auto& fanPath : fanPaths) {
        setFanSpeedRPM(fanPath, targetFanRPM);
    }

    return 0;
}
