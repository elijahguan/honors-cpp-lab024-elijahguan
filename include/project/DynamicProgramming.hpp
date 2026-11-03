#pragma once

#include <string>
#include <vector>

struct MatrixChainResult {
    long long minimumCost;
    std::vector<std::vector<int>> split;
    std::string parenthesization;
};

// Matrix A_i has dimensions dimensions[i-1] x dimensions[i].
// Returns the minimum number of scalar multiplications required.
MatrixChainResult matrixChainOrder(
    const std::vector<int>& dimensions);

// Global alignment using dynamic programming.
// matchScore is added for a match, mismatchScore for a mismatch,
// and gapScore for inserting a gap.
struct AlignmentResult {
    int score;
    std::string alignedFirst;
    std::string alignedSecond;
};

AlignmentResult globalSequenceAlignment(
    const std::string& first,
    const std::string& second,
    int matchScore = 1,
    int mismatchScore = -1,
    int gapScore = -2);

// Reconstruct the optimal matrix-chain parenthesization.
std::string buildParenthesization(
    const std::vector<std::vector<int>>& split,
    int i,
    int j);
