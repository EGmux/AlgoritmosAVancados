#include "../include/includeScapeGoatTree.hpp"
#include <cstdint>
#include <sstream>
#include <string>
#include <sys/types.h>
#include <iostream>
#include <iterator>

uint32_t seed;
#define R 4294967296
#define A 1664525
#define C 1013904223

uint32_t RngNext() {
    seed = (A * seed + C) % R;
    return seed;
}

int main(int argc, char *argv[]){
    uint32_t S{0};
    uint32_t U{0};
    uint32_t A{0};
    uint32_t B{0};
    uint32_t N{0};
    uint32_t I{0};
    uint32_t Q{0};
    uint32_t P{0};
    std::string curLine;

    while(std::getline(std::cin, curLine), !curLine.empty()){
        std::stringstream ss(curLine);
        ss >> S >> U >> A >>B >> N  >> I >> Q >> P;

        seed = S;
        auto sG = new ScapeGoatTree();
        if(B>0){
            sG->insert(seed % U);
            for(auto i{1}; i < B; ++i){
                sG->insert(RngNext()%U);
            }
        }
        
        for(auto curOp{0}; curOp < N; ++curOp){
            auto X = (seed == S?seed:RngNext()%(I+Q));
            if(X<I){
                /* INS */
                auto K = RngNext() % U;
                auto [Lo, Lf] = sG->insert(K);
                if(curOp%P==0){
                    std::cout << "I " << K << ' ' << Lo << ' ' << Lf '\n';
                }
            }else{
                /* QUERY */
                auto K = RngNext() % U;
                auto L = sT->query(K);
                if(curOp%P == 0){
                    std::cout << "Q " << K << ' ' << L << '\n'; 
                }
            }
        }
    }
}

