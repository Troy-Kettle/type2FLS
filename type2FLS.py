import numpy as np
import matplotlib.pyplot as plt

class Type2FuzzySystem:
    def __init__(self):
        # Define the temperature ranges for fuzzy sets
        self.temp_ranges = {
            'Cold': [0, 10, 20],
            'Neutral': [15, 25, 35],
            'Hot': [30, 40, 50]
        }
        
        # Define the fan speed fuzzy sets
        self.fan_speed_ranges = {
            'Slow': [0, 25, 50],
            'Medium': [25, 50, 75],
            'Fast': [50, 75, 100]
        }
        
        # Define Footprint of Uncertainty (FOU) for Type-2 Fuzzy Sets
        self.fou = {
            'Cold': [0.2, 0.3],
            'Neutral': [0.3, 0.4],
            'Hot': [0.2, 0.3]
        }
    
    def membership_function(self, x, fuzzy_set):
        a, b, c = self.temp_ranges[fuzzy_set]
        if x <= a or x >= c:
            return 0
        elif a < x < b:
            return (x - a) / (b - a)
        elif b <= x < c:
            return (c - x) / (c - b)
    
    def fuzzy_set(self, x, fuzzy_set):
        primary_membership = self.membership_function(x, fuzzy_set)
        f_min, f_max = self.fou[fuzzy_set]
        return [max(0, min(primary_membership + f_max, 1)), max(0, min(primary_membership - f_min, 1))]
    
    def apply_rules(self, temp):
        fan_speeds = {'Slow': 0, 'Medium': 0, 'Fast': 0}
        
        cold_fuzzy = self.fuzzy_set(temp, 'Cold')
        neutral_fuzzy = self.fuzzy_set(temp, 'Neutral')
        hot_fuzzy = self.fuzzy_set(temp, 'Hot')
        
        if cold_fuzzy[0] > 0:
            fan_speeds['Slow'] += cold_fuzzy[0]
        
        if neutral_fuzzy[0] > 0:
            fan_speeds['Medium'] += neutral_fuzzy[0]
        
        if hot_fuzzy[0] > 0:
            fan_speeds['Fast'] += hot_fuzzy[0]
        
        return fan_speeds

    def defuzzify(self, fan_speeds):
        weighted_sum = 0
        total_weight = 0
        for speed, value in fan_speeds.items():
            if value > 0:
                midpoint = np.mean(self.fan_speed_ranges[speed])
                weighted_sum += midpoint * value
                total_weight += value
        return weighted_sum / total_weight if total_weight > 0 else 0

    def run(self, temperature):
        fan_speeds = self.apply_rules(temperature)
        return self.defuzzify(fan_speeds)

# Example Usage
fuzzy_system = Type2FuzzySystem()

# Define temperature input
temperature_input = 28

# Get the fan speed output
fan_speed = fuzzy_system.run(temperature_input)
print(f"Recommended Fan Speed: {fan_speed:.2f}")

# Plot the fuzzy membership functions and the result
x = np.linspace(0, 50, 100)
y_cold = [fuzzy_system.membership_function(val, 'Cold') for val in x]
y_neutral = [fuzzy_system.membership_function(val, 'Neutral') for val in x]
y_hot = [fuzzy_system.membership_function(val, 'Hot') for val in x]

plt.plot(x, y_cold, label='Cold')
plt.plot(x, y_neutral, label='Neutral')
plt.plot(x, y_hot, label='Hot')
plt.xlabel('Temperature')
plt.ylabel('Membership Degree')
plt.title('Temperature Fuzzy Sets')
plt.legend()
plt.grid(True)
plt.show()
