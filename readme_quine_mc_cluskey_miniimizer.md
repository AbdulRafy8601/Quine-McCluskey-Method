# Quine–McCluskey Boolean Minimizer

A high-performance **C++ implementation** of the **Quine–McCluskey (Tabular) Method** for simplifying Boolean expressions into a minimal **Sum of Products (SOP)** form.

This project is designed as an academic and practical demonstration of digital logic minimization. It implements the complete minimization pipeline, including prime implicant generation, coverage analysis, and essential prime implicant selection.

---

## Abstract

Boolean function minimization is a fundamental topic in **Digital Logic Design (DLD)** and computer engineering. The Quine–McCluskey method provides a systematic, tabular approach to reducing Boolean expressions, especially when the number of variables makes manual simplification inefficient.

This repository contains a C++ program that automates the Quine–McCluskey method using dynamic memory management and bitwise representation of minterms. The implementation performs iterative pairing of adjacent minterms, identifies prime implicants, constructs coverage relationships, and extracts the essential prime implicants that produce the final minimized SOP expression.

---

## Objectives

The primary objectives of this project are:

- To implement the Quine–McCluskey method in C++ without relying heavily on STL containers.
- To demonstrate the relationship between minterms, binary representation, and implicant formation.
- To identify all prime implicants through iterative comparison.
- To separate essential prime implicants from non-essential ones using coverage analysis.
- To provide both console-based tracing and a file-based final result.

---

## Features

- **Custom memory management** using dynamic regrow and shrink logic for 1D and 2D arrays.
- **Runtime scalability** for variable input sizes and minterm counts.
- **Binary conversion engine** for representing minterms according to the number of variables.
- **Bit-level implicant comparison** using `-1` to denote a “don’t care” position.
- **Two-stage minimization workflow**:
  - Stage 1: Prime implicant generation by iterative adjacency comparison.
  - Stage 2: Essential prime implicant selection through minterm coverage analysis.
- **Dual output mode**:
  - Step-by-step trace in the console.
  - Final minimized Boolean expression written to `result.txt`.

---

## Theoretical Background

The Quine–McCluskey method is a tabular Boolean minimization technique used to reduce the number of literals in a logic expression. It is particularly useful when a Karnaugh map becomes impractical due to a larger number of variables.

The algorithm works in two major phases:

### 1. Prime Implicant Generation
Minterms are grouped according to the number of 1s in their binary forms. Terms from adjacent groups are compared. If two terms differ by exactly one bit, they can be combined into a more general implicant where the differing bit is replaced by a don’t-care symbol.

This process repeats until no further combination is possible.

### 2. Essential Prime Implicant Selection
Each prime implicant is analyzed to determine which original minterms it covers. A prime implicant is considered **essential** if it covers at least one minterm that is not covered by any other implicant. The final minimized SOP expression is formed from the selected implicants.

---

## Algorithm Overview

Given a set of minterms, the program follows these steps:

1. Convert each decimal minterm into binary form.
2. Group minterms according to the number of set bits.
3. Compare adjacent groups to form valid pairs.
4. Replace the differing bit with `-1` to represent elimination of one variable.
5. Repeat pairing on the newly formed table until no more combinations exist.
6. Collect all prime implicants.
7. Determine the coverage of each prime implicant over the original minterms.
8. Remove non-essential implicants.
9. Output the final simplified expression.

---

## Example

### Input Scenario
- Number of variables: `3`
- Minterms: `0, 2, 5, 6, 7`

### Internal Process
The program converts the minterms into binary, compares adjacent terms, and progressively eliminates variables through valid pairings.

### Final Expression
```text
A'C' + AC
```

---

## Project Structure

- `Quine-McCluskey-Method.cpp`  
  Main source file containing the full algorithm implementation.

- `Documentation.pdf`  
  Full technical documentation with supporting explanation of the theory, gray-code relationships, and DLD background.

- `Intersection Idea quine Mc cluskey.png`  
  Logic diagram illustrating the intersection idea used during prime implicant selection.

---

## Function Reference

The implementation is organized into modular functions, each responsible for a specific part of the minimization process.

### Core Utilities

- `findbinary()`  
  Converts decimal minterms into binary arrays of fixed length.

- `checkones()`  
  Counts the number of `1`s in a binary row.

- `compare()`  
  Performs the adjacency comparison between grouped minterms to identify pairable terms.

- `regrow()` / `shrink()`  
  Custom 1D dynamic array resizing functions.

- `regrow2d()` / `shrink2d()`  
  Custom 2D dynamic array resizing functions.

### Prime Implicant Processing

- `eliminating()`  
  Builds the next-level table by combining paired minterms and replacing differing bits with `-1`.

- `CheckingTermsUsed()`  
  Detects minterms that do not participate in any pairing and stores them as prime implicants.

- `RemovingDuplication()`  
  Removes repeated implicant rows from the prime implicant table.

### Coverage and Essentiality

- `findingTermsCoveredByEactPrimeImplicant()`  
  Determines which original minterms are covered by each prime implicant.

- `SeparatingEssentialfromNonEssentialPrimeImplicants()`  
  Selects the essential prime implicants by testing whether all minterms remain covered without a given implicant.

---

## Prerequisites

To compile and run this project, you need:

- A C++ compiler such as **GCC/G++**, **Clang**, or **MSVC**.
- Basic knowledge of **Digital Logic Design**.
- Familiarity with dynamic arrays and pointer-based programming in C++.

---

## Build Instructions

### Using GCC/G++
```bash
g++ Quine-McCluskey-Method.cpp -o qm_minimizer
```

### Using Clang
```bash
clang++ Quine-McCluskey-Method.cpp -o qm_minimizer
```

### Using MSVC
```bash
cl Quine-McCluskey-Method.cpp
```

---

## Usage

1. Run the compiled executable.
2. Enter the number of variables when prompted.
3. Enter each minterm one by one.
4. Enter `-1` to indicate the end of input.
5. Review the console trace and the generated `result.txt` file for the simplified expression.

Example:
```text
Enter the number of variables: 3
Enter Min No. 1: 0
Enter Min No. 2: 2
Enter Min No. 3: 5
Enter Min No. 4: 6
Enter Min No. 5: 7
Enter Min No. 6: -1
```

---

## Output

The program provides:

- A step-by-step trace of the minimization process in the console.
- A final minimized SOP expression written to `result.txt`.

The result is expressed in standard Boolean notation, for example:

```text
A'C' + AC
```

---

## Academic Note

This repository is suitable for:

- Digital Logic Design coursework
- Boolean algebra and logic minimization demonstrations
- Academic presentations on tabular minimization techniques
- Learning pointer-based dynamic memory handling in C++

The implementation is intentionally educational in style, showing how the Quine–McCluskey algorithm can be built from first principles using arrays and custom memory operations.

---

## Limitations

- The implementation uses manual dynamic memory management instead of STL containers.
- The approach is most practical for a moderate number of variables and minterms.
- The Quine–McCluskey method can become computationally expensive for large input sizes.

---

## Future Improvements

Possible enhancements include:

- Replacing raw arrays with safer modern C++ containers.
- Adding input validation for duplicate or out-of-range minterms.
- Supporting don’t-care terms explicitly.
- Producing a more formal prime implicant chart.
- Exporting results in a richer formatted report.

---

## License

Add a license of your choice here, such as MIT, GPL, or Apache 2.0.

---

## Acknowledgment

This project is based on the classical Quine–McCluskey method used in digital logic minimization and was developed as an academic implementation for understanding prime implicants, coverage tables, and Boolean expression reduction.

