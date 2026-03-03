# Quine-McCluskey Method

## Overview
The Quine-McCluskey Method is a systematic approach used for minimization of boolean functions. It provides an efficient way to simplify propositional logic expressions and is especially useful when dealing with multiple variables.

## Purpose
The main purpose of this project is to implement the Quine-McCluskey Method in a programming environment, allowing users to easily minimize boolean expressions and gain insights into the logical structures of their problems.

## How It Works
The method works by identifying and eliminating redundant terms in boolean expressions through a tabular method of grouping minterms. It systematically reduces the complexity of the boolean function while maintaining its logical equivalence.

## Getting Started Guide
To get started with this project, follow these steps:
1. Clone the repository: `git clone https://github.com/AbdulRafy8601/Quine-McCluskey-Method`
2. Navigate to the project directory: `cd Quine-McCluskey-Method`
3. Install any necessary dependencies (if applicable).
4. Run the application using the provided scripts or commands.

## Example Usage
Here’s a basic example of how to use the Quine-McCluskey Method implementation:
```python
# Example code snippet
from quine_mccluskey import minimize

# Input boolean function in canonical form
function = [0b111, 0b100, 0b011]  # Example minterms

# Call the minimize function
result = minimize(function)

print("Minimized Expression:", result)
```

## Program Structure
The project consists of the following key components:
- `main.py`: The main script to run the program.
- `minimizer.py`: Contains the logic for the Quine-McCluskey algorithm.
- `utils.py`: Helper functions for various operations.

## Features
- Systematic reduction of boolean expressions.
- Handling of multi-variable expressions.
- Output of minimized logical expressions.

## Algorithm Steps
1. Identify all minterms and maxterms from the boolean function.
2. Create a prime implicant chart.
3. Find the essential prime implicants.
4. Reduce the function to its simplest form.

## Educational Value
This project serves as a valuable educational resource for those studying digital logic design, helping users understand the importance of boolean minimization and its applications in computer science.

## Input/Output Format
Input should be provided in the form of a list of minterms. Output will be the minimized boolean expression in string format.

## System Requirements
- Python 3.x
- Any standard library dependencies (as per the implementation).

## Notes
This implementation assumes that the input function will be in canonical form and within reasonable limits for practical use.

## References
- Quine, W.V.: "Mathematical Logic".
- McCluskey, E.J.: "Minimization of Boolean Functions".

## Author Information
**Name**: Abdul Rafy
**GitHub**: [AbdulRafy8601](https://github.com/AbdulRafy8601)
