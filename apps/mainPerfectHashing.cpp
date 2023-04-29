#include "../include/includePerfectHashing.hpp"
#include <cstdint>
#include <sstream>
#include <string>
#include <sys/types.h>
#include <iostream>
#include <iterator>

uint32_t seed;
#define R UINT32_MAX
#define A 1664525
#define C 1013904223
#define P (2<<30 - 1)

uint32_t RngNext() {
    seed = (A * seed + C) % R;
    return seed;
}

int main(int argc, char *argv[]){
    uint32_t S{0};
    uint32_t U{0};
    uint32_t M0{0};
    uint32_t I{0};
    uint32_t Q{0};
    uint32_t Pi{0};
    uint32_t Pq {0};
    std::string curLine;

    while(std::getline(std::cin, curLine), !curLine.empty()){
        std::stringstream ss(curLine);
        ss >> S >> U >> M0 >> I >> Q >> Pi >> Pq;

        seed = S;
        auto T = PerfectHashTable(U, M0, P, RngNext);
        
        for(auto curInsertion{0}; curInsertion < I; ++curInsertion){
            auto K = (seed == S?seed:RngNext()) % (U);
            auto [i, j] = T.Set(K);
            if(curInsertion % Pi==0){
                std::cout << I << K << i << j << '\n';
                // same as below but strictly for T0 only   
            }
        }
        // T.BuildPerfectHashing();
        for(auto curQuery{0}; curQuery < Q; ++curQuery){
            /* do some querying 🖥️ */
            if(curQuery % Pq == 0){
                // std::cout << Q << K << i << j << '\n';
                // K := key val, i := position in T0 that become T1, j := position in the linked list T0 that become T1 
            }
        }
    }
}

