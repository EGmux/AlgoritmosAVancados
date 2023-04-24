
#include "../include/vanendeboas.hpp"
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
    uint32_t universeSize {0};
    uint32_t burnIn{0};         // operation that can be MIN, MAX or SUM
    uint32_t numOps {0};    // total number of operations
    uint32_t freqInsertion {0};
    uint32_t freqSucc {0};
    uint32_t freqRemoval{0};     
    uint32_t freqPrint{0};    
    std::string curLine;

    std::getline(std::cin, curLine);
    std::stringstream ss(curLine);
    ss >> seed >> burnIn >> numOps >> numOps >> freqInsertion >>
        freqSucc >> freqRemoval >> freqPrint;    // parse testset

    uint32_t result;
    for (uint32_t curOp {0}; curOp < numOps; ++curOp) {
        auto choiceOfOperation = (RngNext() % (freqInsertion + freqSucc + freqRemoval));
        if (choiceOfOperation < freqInsertion) {
            /* OP == "INS" */
        } else if(choiceOfOperation < (freqInsertion + freqSucc)) {
            /* OP == "SUCC" */
        }
        else {
            /* OP == "DEL" */
        }
        std::cout << result << '\n';
    };
    std::cout << '\n';    // blank line, signals end of current testcase
    }
};
