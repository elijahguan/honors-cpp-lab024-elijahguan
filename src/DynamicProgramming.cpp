#include "project/DynamicProgramming.hpp"

#include <stdexcept>

std::string buildParenthesization(
    const std::vector<std::vector<int>>& split,
    int i,
    int j) {

    // TODO: Implement recursive reconstruction of the optimal
    // matrix-chain parenthesization using the split table.
    // Base case: if i == j, return "A" + std::to_string(i).
    // Recursive case: split at split[i][j] and combine both subchains.

    (void)split;
    (void)i;
    (void)j;
    throw std::logic_error("TODO: implement buildParenthesization");
}

MatrixChainResult matrixChainOrder(
    const std::vector<int>& dimensions) {

    // TODO: Implement Matrix Chain-Product using bottom-up dynamic programming.
    // dimensions = {p0, p1, ..., pn} represents n matrices.
    // Create a cost table and a split table, evaluate increasing chain lengths,
    // store the best split, and reconstruct the optimal parenthesization.
    // Validate that at least one matrix exists and all dimensions are positive.
    // Do not hard-code the sample answer.

    (void)dimensions;
    throw std::logic_error("TODO: implement matrixChainOrder");
}

AlignmentResult globalSequenceAlignment(
    const std::string& first,
    const std::string& second,
    int matchScore,
    int mismatchScore,
    int gapScore) {

    // TODO: Implement global sequence alignment using dynamic programming.
    // Build and initialize the DP table, evaluate diagonal/up/left transitions,
    // then backtrack from the final cell to reconstruct both aligned strings.
    // Use '-' for gaps and support arbitrary scoring parameters.
    // Do not hard-code the DNA/text examples.

    (void)first;
    (void)second;
    (void)matchScore;
    (void)mismatchScore;
    (void)gapScore;
    throw std::logic_error("TODO: implement globalSequenceAlignment");
}
