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

    if (i == j) {
        return "A" + std::to_string(i);
    }
    int k = split[i][j];
    return "(" + buildParenthesization(split, i, k) + " x " + buildParenthesization(split, k + 1, j) + ")";
}

MatrixChainResult matrixChainOrder(
    const std::vector<int>& dimensions) {

    // TODO: Implement Matrix Chain-Product using bottom-up dynamic programming.
    // dimensions = {p0, p1, ..., pn} represents n matrices.
    // Create a cost table and a split table, evaluate increasing chain lengths,
    // store the best split, and reconstruct the optimal parenthesization.
    // Validate that at least one matrix exists and all dimensions are positive.
    // Do not hard-code the sample answer.

    int n = static_cast<int>(dimensions.size()) - 1;
    if (n <= 0) {
        throw std::invalid_argument("At least one matrix must exist");
    }
    for (int i = 0; i <= n; ++i) {
        if (dimensions[i] <= 0) {
            throw std::invalid_argument("All dimensions must be positive");
        }
    }

    std::vector<std::vector<int>> m(n + 1, std::vector<int>(n + 1, 0));
    std::vector<std::vector<int>> s(n + 1, std::vector<int>(n + 1, 0));

    for (int len = 2; len <= n; ++len) {
        for (int i = 1; i <= n - len + 1; ++i) {
            int j = i + len - 1;
            m[i][j] = std::numeric_limits<int>::max();
            for (int k = i; k < j; ++k) {
                int q = m[i][k] + m[k + 1][j] + dimensions[i - 1] * dimensions[k] * dimensions[j];
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }

    std::string parenthesization = buildParenthesization(s, 1, n);
    return {m[1][n], s, parenthesization};
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

    int m = static_cast<int>(first.size());
    int n = static_cast<int>(second.size());
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));
    for (int i = 0; i <= m; ++i) {
        dp[i][0] = i * gapScore;
    }
    for (int j = 0; j <= n; ++j) {
        dp[0][j] = j * gapScore;
    }
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            int match = (first[i - 1] == second[j - 1]) ? matchScore : mismatchScore;
            dp[i][j] = std::max({
                dp[i - 1][j - 1] + match,
                dp[i - 1][j] + gapScore,
                dp[i][j - 1] + gapScore
            });
        }
    }

    // Backtrack to reconstruct the aligned strings
    std::string alignedFirst;
    std::string alignedSecond;
    int i = m;
    int j = n;
    while (i > 0 || j > 0) {
        if (i > 0 && j > 0 && dp[i][j] == dp[i - 1][j - 1] + ((first[i - 1] == second[j - 1]) ? matchScore : mismatchScore)) {
            alignedFirst.push_back(first[i - 1]);
            alignedSecond.push_back(second[j - 1]);
            --i;
            --j;
        } else if (i > 0 && dp[i][j] == dp[i - 1][j] + gapScore) {
            alignedFirst.push_back(first[i - 1]);
            alignedSecond.push_back('-');
            --i;
        } else {
            alignedFirst.push_back('-');
            alignedSecond.push_back(second[j - 1]);
            --j;
        }
    }
    std::reverse(alignedFirst.begin(), alignedFirst.end());
    std::reverse(alignedSecond.begin(), alignedSecond.end());
    return {dp[m][n], alignedFirst, alignedSecond};
}
