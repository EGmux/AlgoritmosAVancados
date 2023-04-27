#include "../include/includeSkipList.hpp"
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

uint32_t RngNext() {
    seed = (A * seed + C) % R;
    return seed;
}

int main(int argc, char *argv[]){
    uint32_t S{0};
    uint32_t U{0};
    uint32_t B{0};
    uint32_t N{0};
    uint32_t F{0};
    uint32_t I{0};
    uint32_t D {0};
    uint32_t P{0};
    std::string curLine;

    while(std::getline(std::cin, curLine), !curLine.empty()){
        std::stringstream ss(curLine);
        ss >> S >> U >> B >> N >> F >> I >> D >> P;

        seed = S;
        auto L = new USkipList(1);
        L->Insert(&L, seed % U, RngNext);
        for(auto i{1}; i < B; ++i){
            L->Insert(&L, RngNext()%U ,RngNext);
        }
        for(auto curOp{0}; curOp < N; ++curOp){
            auto X = RngNext() % (F + I +D);
            if(X < F){
                /* FND */
                X = RngNext() % U;
                auto [ammount, height] = L->Search(L, X);
                if(curOp%P==0){
                    std::cout << "F " << ammount << " " << height;
                }
            }
            else if((F <= X) && (X < (F + I))){
                /* INS */
                X = RngNext() % U;
                auto r = L->Insert(&L, X, RngNext);
                if(curOp%P == 0){
                    std::cout << "I " << (r==true?1 :0);
                }
            }
            else {
                /* DEL */
                X = RngNext() % U;
                auto r = L->Delete(&L, X);
                if(curOp %P == 0){
                    std::cout << "D " << (r==true?1:0);
                }
            }
            std::cout << '\n';
        }
    }
}

