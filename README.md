Type-2 Fuzzy System for Fan Speed Control
# Type2FLS

This repository contains a Python implementation of a Type-2 Fuzzy Logic System designed to control fan speed based on temperature input. The system uses fuzzy logic principles to handle uncertainty and make decisions about the appropriate fan speed.

## Overview
The Type-2 Fuzzy System evaluates temperature inputs and recommends an appropriate fan speed using fuzzy sets and rules. This system can be particularly useful for applications in climate control where precise temperature management is necessary.

## Features
- Temperature Fuzzy Sets: Defines fuzzy sets for 'Cold', 'Neutral', and 'Hot' temperature ranges.
- Fan Speed Fuzzy Sets: Defines fuzzy sets for 'Slow', 'Medium', and 'Fast' fan speeds.
- Type-2 Fuzzy Logic: Incorporates Footprint of Uncertainty (FOU) to handle imprecision in fuzzy sets.
- Defuzzification: Converts fuzzy outputs to a crisp fan speed recommendation.
- Visualization: Plots the membership functions for different temperature ranges.

## Installation
To run this code, you need Python and the following packages:

- numpy
- matplotlib

You can install these packages using pip:

```bash
pip install numpy matplotlib
```

## Usage
Initialize the Fuzzy System

```python
from fuzzy_system import Type2FuzzySystem
fuzzy_system = Type2FuzzySystem()
```

Run the Fuzzy System

Define a temperature input and get the recommended fan speed:

```python
temperature_input = 28
fan_speed = fuzzy_system.run(temperature_input)
print(f"Recommended Fan Speed: {fan_speed:.2f}")
```

Plot Membership Functions

To visualize the fuzzy membership functions for temperature sets, use the following code:

```python
import numpy as np
import matplotlib.pyplot as plt

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
```

## Code Explanation
- Initialization: The Type2FuzzySystem class initializes fuzzy sets for temperature and fan speed, along with the FOU values for type-2 fuzzy logic.
- Membership Function: Calculates the membership degree for a given temperature based on the fuzzy set definitions.
- Fuzzy Set: Applies the FOU to the primary membership degree to account for uncertainty.
- Apply Rules: Determines fan speed recommendations based on the evaluated fuzzy sets.
- Defuzzify: Converts the fuzzy fan speed recommendations into a crisp value using weighted averages.
- Run Method: Integrates the fuzzy logic operations and returns the final fan speed recommendation.

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments
Inspired by principles of fuzzy logic and control systems.
