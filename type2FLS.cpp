#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

class Type2FuzzySystem {
public:
    Type2FuzzySystem() {
        // Define temperature ranges for fuzzy sets
        tempRanges["Cold"] = {0, 10, 20};
        tempRanges["Neutral"] = {15, 25, 35};
        tempRanges["Hot"] = {30, 40, 50};
        
        // Define Footprint of Uncertainty (FOU) for Type-2 Fuzzy Sets
        fou["Cold"] = {0.2, 0.3};
        fou["Neutral"] = {0.3, 0.4};
        fou["Hot"] = {0.2, 0.3};
        
        // Define fan speed fuzzy sets
        fanSpeedRanges["Slow"] = {0, 25, 50};
        fanSpeedRanges["Medium"] = {25, 50, 75};
        fanSpeedRanges["Fast"] = {50, 75, 100};
    }

    // Membership function for temperature fuzzy sets
    double membershipFunction(double x, const std::string& fuzzySet) {
        const auto& range = tempRanges[fuzzySet];
        double a = range[0], b = range[1], c = range[2];

        if (x <= a || x >= c) return 0;
        if (x > a && x < b) return (x - a) / (b - a);
        if (x >= b && x < c) return (c - x) / (c - b);
        return 0;
    }

    // Compute fuzzy set values considering FOU
    std::vector<double> fuzzySet(double x, const std::string& fuzzySet) {
        double primaryMembership = membershipFunction(x, fuzzySet);
        double fMin = fou[fuzzySet][0];
        double fMax = fou[fuzzySet][1];

        return {std::max(0.0, std::min(primaryMembership + fMax, 1.0)),
                std::max(0.0, std::min(primaryMembership - fMin, 1.0))};
    }

    // Apply fuzzy rules and compute fan speed
    std::vector<double> applyRules(double temp) {
        std::vector<double> fanSpeeds = {0, 0, 0}; // Slow, Medium, Fast

        auto coldFuzzy = fuzzySet(temp, "Cold");
        auto neutralFuzzy = fuzzySet(temp, "Neutral");
        auto hotFuzzy = fuzzySet(temp, "Hot");

        if (coldFuzzy[0] > 0) fanSpeeds[0] += coldFuzzy[0]; // Slow
        if (neutralFuzzy[0] > 0) fanSpeeds[1] += neutralFuzzy[0]; // Medium
        if (hotFuzzy[0] > 0) fanSpeeds[2] += hotFuzzy[0]; // Fast

        return fanSpeeds;
    }

    // Defuzzification
    double defuzzify(const std::vector<double>& fanSpeeds) {
        double weightedSum = 0;
        double totalWeight = 0;

        auto addToSum = [&](const std::string& speed, double value) {
            if (value > 0) {
                auto midPoint = (fanSpeedRanges[speed][0] + fanSpeedRanges[speed][2]) / 2.0;
                weightedSum += midPoint * value;
                totalWeight += value;
            }
        };

        addToSum("Slow", fanSpeeds[0]);
        addToSum("Medium", fanSpeeds[1]);
        addToSum("Fast", fanSpeeds[2]);

        return totalWeight > 0 ? weightedSum / totalWeight : 0;
    }

    // Run the fuzzy system
    double run(double temperature) {
        auto fanSpeeds = applyRules(temperature);
        return defuzzify(fanSpeeds);
    }

private:
    std::map<std::string, std::vector<double>> tempRanges;
    std::map<std::string, std::vector<double>> fou;
    std::map<std::string, std::vector<double>> fanSpeedRanges;
};

int main() {
    Type2FuzzySystem fuzzySystem;

    // Define temperature input
    double temperatureInput = 28;

    // Get the fan speed output
    double fanSpeed = fuzzySystem.run(temperatureInput);
    std::cout << "Recommended Fan Speed: " << fanSpeed << std::endl;

    return 0;
}
