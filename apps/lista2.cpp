#include "../include/sparsetable.hpp"
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <istream>
#include <string>
#include <sstream>

#define R           (1 << 31);
#define A           1664525
#define C           1013904223
#define RNG(curGen) (A * curGen) % R;

int main() {
    uint32_t sparseTableWidth;
    uint32_t seed;
    std::string op;     // operation that can be MIN, MAX or SUM
    uint32_t numOps;    // total number of operations
    uint32_t freqRangeQuery;
    uint32_t freqRangeUpdt;
    std::string curLine;    // current testset in a testcase;
    uint32_t curIter; // current testcase

    while (std::getline(std::cin, curLine), !curLine.empty()) {
        std::stringstream ss(curLine);
        ss >> seed >> sparseTableWidth >> op >> numOps >> freqRangeQuery >> freqRangeUpdt; //parse testset
        std::vector<uint32_t> zerothRow;
        zerothRow.reserve(sparseTableWidth);
        auto curSeed = RNG(seed);
        auto m = (sparseTableWidth << 2);

        for (auto &i : zerothRow) {
            i = curSeed % m;
            curSeed = RNG(curSeed);
        };
        uint32_t (*function)(const uint32_t, const uint32_t);
        if (op == "MIN") {
            function = [](const uint32_t X, const uint32_t Y) {
                return X > Y ? Y : X;
            };
        } else if (op == "MAX") {
            function = [](const uint32_t X, const uint32_t Y) {
                return X > Y ? X : Y;
            };
        } else {
            function = [](const uint32_t X, const uint32_t Y) {
                return X + Y;
            };
        }
        SparseTable st {zerothRow, function};
        uint32_t result;
        std::cout << "caso" << " " << curIter << '\n';
        for (uint32_t curOp {0}; curOp < numOps; ++curOp) {
            if (curSeed % (freqRangeQuery + freqRangeUpdt) < freqRangeQuery) {
                auto lower = curSeed % sparseTableWidth;
                auto higher = lower + 1 + (curSeed % (sparseTableWidth - lower));
                result =st.Query(lower, higher);
            } else {
                auto targetIndex = curSeed % sparseTableWidth;
                auto newValue = curSeed % m;
                st.Upd(targetIndex, newValue);
                result = st.Query(targetIndex , sparseTableWidth);
            }
            std::cout << result << '\n';
            curSeed = RNG(curSeed);
        };
        std::cout << '\n'; // blank line, signals end of current testcase
    }
};
