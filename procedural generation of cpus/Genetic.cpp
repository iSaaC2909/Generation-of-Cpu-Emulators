#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <map>

// CPU Variant struct
struct CPUVariant {
    double clockSpeed;  // Clock speed in MHz
    int memorySize;     // Total memory size in bytes
};

// Random helpers
double randomDouble(double min, double max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(min, max);
    return dis(gen);
}

int randomInt(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

// Generate random CPU variant
CPUVariant generateRandomVariant() {
    return {randomDouble(1.0, 3.0), randomInt(2048, 65536)};
}

// Evaluate fitness (dummy evaluation function)
double evaluateFitness(const CPUVariant& variant) {
    // Example fitness function: higher clock speed and larger memory size are better
    return variant.clockSpeed * variant.memorySize;
}

// Mutate a CPU variant
CPUVariant mutate(const CPUVariant& variant) {
    CPUVariant mutated = variant;
    mutated.clockSpeed *= randomDouble(0.9, 1.1);  // Mutate clock speed ±10%
    mutated.memorySize += randomInt(-1024, 1024);  // Mutate memory size by ±1 KB
    return mutated;
}

// Select the best variants
std::vector<CPUVariant> selectBestVariants(const std::vector<CPUVariant>& population, int numBest) {
    // Sort by fitness and select the top variants
    std::vector<std::pair<double, CPUVariant>> fitnessPairs;
    for (const auto& variant : population) {
        fitnessPairs.emplace_back(evaluateFitness(variant), variant);
    }
    std::sort(fitnessPairs.begin(), fitnessPairs.end(), std::greater<>());
    
    std::vector<CPUVariant> bestVariants;
    for (int i = 0; i < numBest; ++i) {
        bestVariants.push_back(fitnessPairs[i].second);
    }
    return bestVariants;
}

// Breed new population
std::vector<CPUVariant> breedPopulation(const std::vector<CPUVariant>& bestVariants, int populationSize) {
    std::vector<CPUVariant> newPopulation;
    for (int i = 0; i < populationSize; ++i) {
        newPopulation.push_back(mutate(bestVariants[randomInt(0, bestVariants.size() - 1)]));
    }
    return newPopulation;
}

int main() {
    const int populationSize = 10;
    const int generations = 5;
    const int numBest = 3;
    
    // Initialize population
    std::vector<CPUVariant> population;
    for (int i = 0; i < populationSize; ++i) {
        population.push_back(generateRandomVariant());
    }

    // Run genetic algorithm
    for (int generation = 0; generation < generations; ++generation) {
        std::cout << "Generation " << generation + 1 << std::endl;
        
        // Select the best variants
        auto bestVariants = selectBestVariants(population, numBest);
        
        // Breed new population
        population = breedPopulation(bestVariants, populationSize);
    }

    // Display final best variant
    auto bestVariant = selectBestVariants(population, 1)[0];
    std::cout << "Best Variant - Clock Speed: " << bestVariant.clockSpeed << " MHz, "
              << "Memory Size: " << bestVariant.memorySize << " bytes" << std::endl;
    
    return 0;
}
