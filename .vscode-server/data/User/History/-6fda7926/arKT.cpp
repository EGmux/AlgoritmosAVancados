#include "../include/sparsetable.hpp"
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <istream>
#include <sstream>
#include <string>

uint32_t seed;
#define R UINT32_MAX
#define A 1664525
#define C 1013904223

uint32_t RngNext() {
    seed = (A * seed + C) % R;
    return seed;
}

int main(int argc, char* argv[]) {
    uint32_t sparseTableWidth {0};
    std::string op;         // operation that can be MIN, MAX or SUM
    uint32_t numOps {0};    // total number of operations
    uint32_t freqRangeQuery {0};
    uint32_t freqRangeUpdt {0};
    std::string curLine;     // current testset in a testcase;
    uint32_t curIter {0};    // current testcase

    while (std::getline(std::cin, curLine), !curLine.empty()) {
        std::stringstream ss(curLine);
        ss >> seed >> sparseTableWidth >> op >> numOps >> freqRangeQuery >>
            freqRangeUpdt;    // parse testset
        std::vector<uint32_t> zerothRow;
        zerothRow.reserve(
            sparseTableWidth);    // https://stackoverflow.com/questions/13029299/stdvectorresize-vs-stdvectorreserve
        auto m = (sparseTableWidth << 2);

        /*
         * We use pushback here because reserve only allocates memory, but won't create the
         * necessary indexes until needed.
         */
         zerothRow.push_back(seed); // Na primeira chamada, essa função deve retornar X[0]=S.
        for (auto i {0}; i < sparseTableWidth; ++i) {
            zerothRow.push_back(curSeed % m);
            curSeed = RNG(curSeed);
        };
        uint32_t (*function)(const uint32_t, const uint32_t);
        uint32_t id;
        if (op == "MIN") {
            function = [](const uint32_t X, const uint32_t Y) {
                return X > Y ? Y : X;
            };
            id = UINT32_MAX;
        } else if (op == "MAX") {
            function = [](const uint32_t X, const uint32_t Y) {
                return X > Y ? X : Y;
            };
            id = 0;
        } else {
            function = [](const uint32_t X, const uint32_t Y) {
                return X + Y;
            };
            id = 0;
        }
        SparseTable st {zerothRow, function, id};
        uint32_t result;
        std::cout << "caso"
                  << " " << curIter << '\n';
        for (uint32_t curOp {0}; curOp < numOps; ++curOp) {
            if (curSeed % (freqRangeQuery + freqRangeUpdt) < freqRangeQuery) {
                auto lower = curSeed % sparseTableWidth;
                auto higher = lower + 1 + (curSeed % (sparseTableWidth - lower));
                result = st.Query(lower, higher);
            } else {
                auto targetIndex = curSeed % sparseTableWidth;
                auto newValue = curSeed % m;
                st.Upd(targetIndex, newValue);
                result = st.Query(targetIndex, sparseTableWidth);
            }
            std::cout << result << '\n';
            curSeed = RNG(curSeed);
        };
        std::cout << '\n';    // blank line, signals end of current testcase
        curIter = curIter + 1;
    }
};
