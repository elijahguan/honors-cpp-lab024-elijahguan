# Lab 024: Dynamic Programming — Matrix Chain Product and Sequence Alignment

## Description

This lab introduces dynamic programming through two important applications:

1. **Matrix Chain-Product**
2. **DNA and Text Sequence Alignment**

Both problems demonstrate how a large optimization problem can be divided into overlapping subproblems, solved once, and combined to obtain an optimal solution.

You will implement dynamic programming algorithms rather than relying on library implementations.

## Learning Objectives

By completing this lab, you should be able to:

- Identify overlapping subproblems and optimal substructure.
- Design a bottom-up dynamic programming solution.
- Build and interpret a dynamic programming table.
- Solve the Matrix Chain-Product optimization problem.
- Recover an optimal matrix multiplication order.
- Analyze the time and space complexity of matrix-chain dynamic programming.
- Formulate sequence alignment as an optimization problem.
- Compute a global alignment using a dynamic programming table.
- Reconstruct an optimal alignment from the table.
- Explain how scoring choices affect an alignment.

## Student Implementation

The starter repository intentionally contains incomplete functions marked with `TODO`.

You must implement these three functions in `src/DynamicProgramming.cpp`:

- `matrixChainOrder()` — compute the minimum matrix multiplication cost and split table.
- `buildParenthesization()` — reconstruct an optimal matrix-chain parenthesization.
- `globalSequenceAlignment()` — compute the optimal alignment score and reconstruct both aligned sequences.

Do not hard-code the sample answers. The unit tests include additional cases and custom scoring.

## Part 1: Matrix Chain-Product

Suppose matrices are multiplied as:

    A1 A2 A3 ... An

The matrices cannot be arbitrarily reordered, but the parentheses can be changed.

For example:

    ((A1 x A2) x A3)

and

    (A1 x (A2 x A3))

produce the same mathematical result but may require very different numbers of scalar multiplications.

If the dimensions are:

    p0 x p1, p1 x p2, ..., p(n-1) x pn

then multiplying:

    Ai ... Ak

with:

    A(k+1) ... Aj

requires:

    p(i-1) * pk * pj

scalar multiplications.

Your implementation must use dynamic programming to determine the minimum cost and recover an optimal parenthesization.

### Requirements

Implement:

    MatrixChainResult matrixChainOrder(
        const std::vector<int>& dimensions);

Your implementation must:

- Use bottom-up dynamic programming.
- Compute the minimum multiplication cost.
- Store the split position for each subproblem.
- Reconstruct the optimal parenthesization.
- Reject invalid matrix dimensions.

### Complexity

Determine and explain:

- Time complexity
- Space complexity

## Part 2: DNA and Text Sequence Alignment

Sequence alignment is a classic dynamic programming problem used for comparing strings and biological sequences.

Given two sequences, characters can be:

- matched,
- mismatched, or
- aligned with a gap.

The implementation uses a scoring system:

- Match: +1
- Mismatch: -1
- Gap: -2

For example, an alignment may contain:

    ACGT
    A-GT

The goal is to find an alignment with the maximum score.

### Requirements

Implement:

    AlignmentResult globalSequenceAlignment(
        const std::string& first,
        const std::string& second,
        int matchScore,
        int mismatchScore,
        int gapScore);

Your implementation must:

- Build the dynamic programming table.
- Correctly initialize the first row and column.
- Consider diagonal, vertical, and horizontal transitions.
- Compute the optimal alignment score.
- Backtrack through the table.
- Return both aligned sequences.
- Use `-` to represent gaps.
- Support custom scoring values.

### Complexity

Determine and explain:

- Time complexity in terms of the two sequence lengths.
- Space complexity.
- How the complexity changes as sequence lengths increase.

## Important Implementation Requirement

Do not replace the dynamic programming algorithms with:

- brute-force enumeration,
- recursion without memoization,
- library alignment algorithms, or
- hard-coded answers.

The purpose of this lab is to implement and understand dynamic programming.

## Testing

Run:

    make

Then:

    make run

Finally:

    make test

All provided unit tests should pass.

## Discussion Questions

Answer the following questions in your notes or during discussion:

1. Why does Matrix Chain-Product have optimal substructure?
2. Why would trying every possible parenthesization become impractical?
3. What information must be stored to reconstruct the optimal parenthesization?
4. What are the dimensions of the sequence-alignment dynamic programming table?
5. Why must the first row and first column be initialized before filling the table?
6. What do the diagonal, vertical, and horizontal transitions represent?
7. How can different match, mismatch, and gap scores change the resulting alignment?
8. Why are DNA sequence alignment and ordinary text comparison structurally similar dynamic programming problems?

## Deliverable

Your GitHub repository must contain:

- Working Matrix Chain-Product implementation.
- Working sequence-alignment implementation.
- Unit tests.
- A working `main.cpp` demonstration.
- Code that compiles with C++17.
- All automated tests passing.
