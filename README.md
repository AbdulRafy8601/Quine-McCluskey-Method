# Quine-McCluskey Method

## Overview
The Quine-McCluskey method is a widely-used algorithm for simplifying Boolean functions. It provides a systematic approach to finding the minimal sum of products representation for a given Boolean expression.

## Getting Started
To run the Quine-McCluskey method in C++, ensure you have a C++ compiler installed. You can use any IDE of your choice, such as Visual Studio, Code::Blocks, or online compilers like repl.it.

### Prerequisites
- C++11 or later

## Example Usage
To use the Quine-McCluskey method, you can include the following code snippet in your C++ program:
```cpp
#include "QuineMcCluskey.h"

int main() {
    // Initialize a Boolean function
    std::vector<int> minterms = {1, 2, 5, 6};

    // Create an instance of the Quine-McCluskey class
    QuineMcCluskey qm(minterms);

    // Simplify the Boolean function
    qm.simplify();

    // Display the minimized expression
    qm.displayMinimizedExpression();
    return 0;
}
```

## Program Structure
The Quine-McCluskey method is typically structured in the following way:
- **Main Class**: Handles the simplification logic.
- **Helper Functions**: Manage Boolean operations and data processing.

## Features
- Systematic method for Boolean function simplification
- Handles multiple variables
- Can produce essential prime implicants

## Algorithm Steps
1. **List Minterms**: Start with the minterms of the function.
2. **Group Minterms**: Group minterms based on the number of 1's in their binary representation.
3. **Combine Minterms**: Merge pairs of minterms to eliminate variables, iterating until no further combinations are possible.
4. **Prime Implicants**: Identify the prime implicants from the combinations.
5. **Select Essential Prime Implicants**: Construct the simplified expression using selected essential prime implicants.

## Educational Value
The Quine-McCluskey method is not only practical for engineers and computer scientists but also serves as a great educational tool. It provides insights into Boolean algebra, logic design, and systematic problem-solving techniques.

## Author Information
- **Name**: Abdul Rafy
- **Email**: [example@example.com](mailto:example@example.com)
- **Date**: 2026-03-03 14:30:21 (UTC)
