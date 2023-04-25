
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
    ss >> seed >> universeSize >> burnIn >> numOps >> freqInsertion >>
        freqSucc >> freqRemoval >> freqPrint;    // parse testset

    VEBTree* root;
    VanEndeBoas vebTree(universeSize, root);
    
    vebTree.Insertion(root, seed%universeSize);
    for(uint32_t insertionNum{1}; insertionNum < burnIn; ++insertionNum){
        vebTree.Insertion( root, RngNext()%universeSize);
    }

    uint32_t result;
    for (uint32_t curOp {0}; curOp < numOps; ++curOp) {
        auto choiceOfOperation = (RngNext() % (freqInsertion + freqSucc + freqRemoval));
        if (choiceOfOperation < freqInsertion) {
            /* OP == "INS" */
            auto valueToInsert = RngNext() % universeSize;
            int32_t depth = vebTree.Insertion(root, valueToInsert); 
            if(curOp%freqPrint==0)
                std::cout << "I" << ' ' << depth << '\n';
        } else if(choiceOfOperation < (freqInsertion + freqSucc)) {
            /* OP == "SUCC" */
            auto valueToFind = RngNext() % universeSize;
            auto succ = vebTree.Succ(root, valueToFind);
            if(curOp%freqPrint==0)
                std::cout << "S" << ' ' << succ << '\n';
        }
        else {
            /* OP == "DEL" */
            /* IMPORTANTE: Caso a vEBT T não contenha o valor X antes dessa operação, consideramos L=0. */
            auto valueToFind = RngNext() % universeSize;
            auto succ = vebTree.Succ(root, valueToFind);
            valueToFind = succ != -1? succ : valueToFind; 
            int32_t depth = vebTree.Removal(valueToFind, root);
            if(curOp%freqPrint==0)
                std::cout << "D" << ' ' << depth << '\n';
        }
    };
};
