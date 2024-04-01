#include <cstdlib>

int main() {
    // Set fan speed using smcFanControl command-line interface
    int fanSpeed = 3000; // Example fan speed in RPM
    std::string command = "smc -k F0Mn -w " + std::to_string(fanSpeed);
    int status = std::system(command.c_str());
    
    if (status == 0) {
        std::cout << "Fan speed set successfully." << std::endl;
    } else {
        std::cerr << "Failed to set fan speed." << std::endl;
    }

    return 0;
}
