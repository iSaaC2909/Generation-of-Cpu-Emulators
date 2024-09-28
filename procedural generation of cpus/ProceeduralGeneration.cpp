#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <map>

// CPU Variant struct
struct CPUVariant {
    double clockSpeed;  // Clock speed in MHz
    std::vector<std::string> opcodes;  // List of opcodes
    int memorySize;  // Total memory size in bytes
    std::map<std::string, int> memoryMap;  // Memory map (e.g., RAM and ROM)
};

// Emulator class
class Emulator {
public:
    Emulator(const CPUVariant& variant) : cpuVariant(variant) {}
    void display() const {
        std::cout << "Clock Speed: " << cpuVariant.clockSpeed << " MHz\n";
        std::cout << "Opcodes: ";
        for (const auto& opcode : cpuVariant.opcodes) {
            std::cout << opcode << " ";
        }
        std::cout << "\nMemory Size: " << cpuVariant.memorySize << " bytes\n";
        std::cout << "Memory Map: RAM = " << cpuVariant.memoryMap.at("RAM")
                  << " bytes, ROM = " << cpuVariant.memoryMap.at("ROM") << " bytes\n";
    }
private:
    CPUVariant cpuVariant;
};

// Helper function to generate random double
double randomDouble(double min, double max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(min, max);
    return dis(gen);
}

// Helper function to generate random integer
int randomInt(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

// Randomly generate a CPU variant
CPUVariant generateRandomVariant() {
    // Define possible opcodes
    std::vector<std::string> POSSIBLE_OPCODES = {"LDA", "STA", "ADC", "SBC", "NOP"};
    
    // Random clock speed between 1.0 MHz and 3.0 MHz
    double clockSpeed = randomDouble(1.0, 3.0);
    
    // Randomly select a subset of opcodes
    int opcodeCount = randomInt(3, POSSIBLE_OPCODES.size());
    std::vector<std::string> opcodes;
    std::sample(POSSIBLE_OPCODES.begin(), POSSIBLE_OPCODES.end(), std::back_inserter(opcodes),
                opcodeCount, std::mt19937{std::random_device{}()});
    
    // Random memory size between 2 KB and 64 KB
    std::vector<int> memorySizes = {2048, 4096, 8192, 16384, 32768, 65536};
    int memorySize = memorySizes[randomInt(0, memorySizes.size() - 1)];
    
    // Random memory map
    int ramSize = randomInt(512, memorySize / 2);
    int romSize = memorySize - ramSize;
    
    std::map<std::string, int> memoryMap = {
        {"RAM", ramSize},
        {"ROM", romSize}
    };
    
    return {clockSpeed, opcodes, memorySize, memoryMap};
}

int main() {
    // Generate a random variant of the CPU
    CPUVariant randomVariant = generateRandomVariant();
    
    // Create an emulator with this random variant
    Emulator emulator(randomVariant);
    
    // Display the emulator's properties
    emulator.display();
    
    return 0;
}
