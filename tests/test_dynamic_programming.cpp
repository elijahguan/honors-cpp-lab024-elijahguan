#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "project/DynamicProgramming.hpp"

#include <stdexcept>
#include <string>
#include <vector>

TEST_CASE("Matrix chain product computes classic optimal cost") {
    std::vector<int> dimensions = {30, 35, 15, 5, 10, 20, 25};

    MatrixChainResult result = matrixChainOrder(dimensions);

    REQUIRE(result.minimumCost == 15125);
    REQUIRE(result.parenthesization == "((A1 x (A2 x A3)) x ((A4 x A5) x A6))");
}

TEST_CASE("Matrix chain product handles two matrices") {
    std::vector<int> dimensions = {10, 20, 30};

    MatrixChainResult result = matrixChainOrder(dimensions);

    REQUIRE(result.minimumCost == 6000);
    REQUIRE(result.parenthesization == "(A1 x A2)");
}

TEST_CASE("Matrix chain product rejects invalid dimensions") {
    REQUIRE_THROWS_AS(
        matrixChainOrder({}),
        std::invalid_argument);

    REQUIRE_THROWS_AS(
        matrixChainOrder({10}),
        std::invalid_argument);

    REQUIRE_THROWS_AS(
        matrixChainOrder({10, 0, 20}),
        std::invalid_argument);
}

TEST_CASE("Sequence alignment rewards identical sequences") {
    AlignmentResult result =
        globalSequenceAlignment("ACGT", "ACGT");

    REQUIRE(result.score == 4);
    REQUIRE(result.alignedFirst == "ACGT");
    REQUIRE(result.alignedSecond == "ACGT");
}

TEST_CASE("Sequence alignment supports gaps") {
    AlignmentResult result =
        globalSequenceAlignment("GATTACA", "GCATGCU");

    REQUIRE(result.alignedFirst.size() == result.alignedSecond.size());
    REQUIRE((result.alignedFirst.find('-') != std::string::npos ||
             result.alignedSecond.find('-') != std::string::npos));
}

TEST_CASE("Sequence alignment preserves original characters") {
    AlignmentResult result =
        globalSequenceAlignment("ACG", "AG");

    REQUIRE(result.alignedFirst.size() == result.alignedSecond.size());

    std::string firstWithoutGaps;
    std::string secondWithoutGaps;

    for (char c : result.alignedFirst) {
        if (c != '-') {
            firstWithoutGaps += c;
        }
    }

    for (char c : result.alignedSecond) {
        if (c != '-') {
            secondWithoutGaps += c;
        }
    }

    REQUIRE(firstWithoutGaps == "ACG");
    REQUIRE(secondWithoutGaps == "AG");
}

TEST_CASE("Sequence alignment supports custom scoring") {
    AlignmentResult result =
        globalSequenceAlignment("AA", "AA", 2, -1, -2);

    REQUIRE(result.score == 4);
    REQUIRE(result.alignedFirst == "AA");
    REQUIRE(result.alignedSecond == "AA");
}
