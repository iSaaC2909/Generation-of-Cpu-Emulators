#include <iostream>
#include <vector>
#include <map>
#include <random>
#include <algorithm>

// CPU Variant struct
struct CPUVariant {
    double clockSpeed;  // Clock speed in MHz
    std::vector<std::string> opcodes;  // List of opcodes
    int memorySize;  // Total memory size in bytes
    std::map<std::string, int> memoryMap;  // Memory map (e.g., RAM and ROM)
};

// Rule-based generation class
class RuleBasedGenerator {
public:
    // Generate CPU variant following the rules
    CPUVariant generateVariant() {
        double clockSpeed = generateClockSpeed();
        std::vector<std::string> opcodes = generateOpcodes();
        int memorySize = generateMemorySize();
        std::map<std::string, int> memoryMap = generateMemoryMap(memorySize);
        
        return {clockSpeed, opcodes, memorySize, memoryMap};
    }

private:
    // Generate clock speed within a specific range
    double generateClockSpeed() {
        return randomDouble(1.5, 2.5);  // Rule: Clock speed between 1.5 MHz and 2.5 MHz
    }
    
    // Generate opcodes, ensuring essential ones are always included
    std::vector<std::string> generateOpcodes() {
        std::vector<std::string> possibleOpcodes = {"LDA", "STA", "ADC", "SBC", "NOP"};
        
        // Rule: Must always include "LDA" and "STA"
        std::vector<std::string> opcodes = {"LDA", "STA"};
        
        // Randomly select other opcodes (with rules like max number of opcodes)
        int additionalOpcodesCount = randomInt(1, 3);  // Rule: Max 3 extra opcodes
        std::sample(possibleOpcodes.begin(), possibleOpcodes.end(), std::back_inserter(opcodes),
                    additionalOpcodesCount, std::mt19937{std::random_device{}()});
        
        return opcodes;
    }
    
    // Generate memory size within specific bounds
    int generateMemorySize() {
        // Rule: Memory size must be between 8 KB and 64 KB
        return randomInt(8192, 65536);
    }
    
    // Generate memory map with a specific rule (RAM < half of memory)
    std::map<std::string, int> generateMemoryMap(int memorySize) {
        // Rule: RAM must be less than half of the total memory
        int ramSize = randomInt(512, memorySize / 2);
        int romSize = memorySize - ramSize;
        
        std::map<std::string, int> memoryMap = {{"RAM", ramSize}, {"ROM", romSize}};
        return memoryMap;
    }
    
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
};

int main() {
    // Create the rule-based generator
    RuleBasedGenerator generator;
    
    // Generate a CPU variant following the rules
    CPUVariant variant = generator.generateVariant();
    
    // Display the generated CPU variant
    std::cout << "Generated CPU Variant\n";
    std::cout << "Clock Speed: " << variant.clockSpeed << " MHz\n";
    std::cout << "Opcodes: ";
    for (const auto& opcode : variant.opcodes) {
        std::cout << opcode << " ";
    }
    std::cout << "\nMemory Size: " << variant.memorySize << " bytes\n";
    std::cout << "Memory Map: RAM = " << variant.memoryMap.at("RAM") 
              << " bytes, ROM = " << variant.memoryMap.at("ROM") << " bytes\n";
    
    return 0;
}
