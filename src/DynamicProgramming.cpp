#include "project/DynamicProgramming.hpp"

#include <stdexcept>

std::string buildParenthesization(
    const std::vector<std::vector<int>>& split,
    int i,
    int j) {

    if (i == j) {
        return "A" + std::to_string(i);
    }

    int k = split[i][j];
    return "(" + buildParenthesization(split, i, k)
        + " x " + buildParenthesization(split, k + 1, j) + ")";
}

MatrixChainResult matrixChainOrder(
    const std::vector<int>& dimensions) {

    if (dimensions.size() < 2) {
        throw std::invalid_argument("At least one matrix must exist");
    }

    int n = static_cast<int>(dimensions.size()) - 1;

    for (int dimension : dimensions) {
        if (dimension <= 0) {
            throw std::invalid_argument("All dimensions must be positive");
        }
    }

    std::vector<std::vector<int>> cost(
        n + 1, std::vector<int>(n + 1, 0));
    std::vector<std::vector<int>> split(
        n + 1, std::vector<int>(n + 1, 0));

    for (int length = 2; length <= n; ++length) {
        for (int i = 1; i <= n - length + 1; ++i) {
            int j = i + length - 1;

            // Use the first split to initialize the best cost.
            int k = i;
            int bestCost = cost[i][k] + cost[k + 1][j]
                + dimensions[i - 1] * dimensions[k] * dimensions[j];

            split[i][j] = k;

            for (k = i + 1; k < j; ++k) {
                int currentCost = cost[i][k] + cost[k + 1][j]
                    + dimensions[i - 1] * dimensions[k] * dimensions[j];

                if (currentCost < bestCost) {
                    bestCost = currentCost;
                    split[i][j] = k;
                }
            }

            cost[i][j] = bestCost;
        }
    }

    std::string parenthesization = buildParenthesization(split, 1, n);
    return {cost[1][n], split, parenthesization};
}

AlignmentResult globalSequenceAlignment(
    const std::string& first,
    const std::string& second,
    int matchScore,
    int mismatchScore,
    int gapScore) {

    int m = static_cast<int>(first.size());
    int n = static_cast<int>(second.size());

    std::vector<std::vector<int>> dp(
        m + 1, std::vector<int>(n + 1, 0));

    for (int i = 1; i <= m; ++i) {
        dp[i][0] = dp[i - 1][0] + gapScore;
    }

    for (int j = 1; j <= n; ++j) {
        dp[0][j] = dp[0][j - 1] + gapScore;
    }

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            int characterScore =
                (first[i - 1] == second[j - 1])
                    ? matchScore
                    : mismatchScore;

            int diagonal = dp[i - 1][j - 1] + characterScore;
            int up = dp[i - 1][j] + gapScore;
            int left = dp[i][j - 1] + gapScore;

            int best = diagonal;
            if (up > best) {
                best = up;
            }
            if (left > best) {
                best = left;
            }

            dp[i][j] = best;
        }
    }

    std::string alignedFirst;
    std::string alignedSecond;
    int i = m;
    int j = n;

    while (i > 0 || j > 0) {
    // Prefer a gap when it preserves the optimal score.
    if (i > 0 && dp[i][j] == dp[i - 1][j] + gapScore) {
        alignedFirst += first[i - 1];
        alignedSecond += '-';
        --i;
    } 
    else if (j > 0 && dp[i][j] == dp[i][j - 1] + gapScore) {
        alignedFirst += '-';
        alignedSecond += second[j - 1];
        --j;
    } 
    else {
        // If neither gap move matches the optimal score, take the diagonal.
        alignedFirst += first[i - 1];
        alignedSecond += second[j - 1];
        --i;
        --j;
    }
}

    // The strings were built backwards during backtracking; reverse them
    // with loops so no additional header is needed.
    std::string resultFirst;
    std::string resultSecond;

    for (int index = static_cast<int>(alignedFirst.size()) - 1;
         index >= 0; --index) {
        resultFirst += alignedFirst[index];
        resultSecond += alignedSecond[index];
    }

    return {dp[m][n], resultFirst, resultSecond};
}