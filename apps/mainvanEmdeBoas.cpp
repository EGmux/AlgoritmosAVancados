#include "../include/includevanEmdeBoas.hpp"
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
    uint32_t M{0};
    uint32_t B{0};
    uint32_t N{0};
    uint32_t I{0};
    uint32_t F{0};
    uint32_t D {0};
    uint32_t P{0};
    std::string curLine;

    while(std::getline(std::cin, curLine), !curLine.empty()){
        std::stringstream ss(curLine);
        ss >> S >> M >> B >> N >> F >> I >> D >> P;

        seed = S;
        auto U = 1<<(1<<(M-1));
        auto veb = new vanEmdeBoas();
        if(B>0){
            veb.insert(seed);
            for(auto i{1}; i < B; ++i){
                veb.Insert(RngNext()%U);
            }
        }
        
        for(auto curOp{0}; curOp < N; ++curOp){
            auto X = (seed == S?seed:RngNext()) % (F + I +D);
            if(X < I){
                /* INS */
                X = RngNext() % U;
                auto [I,L ] = veb.insert(X);
                if(curOp%P==0){
                    std::cout << "F " << I << " " << L << '\n';
                }
            }
            else if((X < (F + I))){
                /* SUC */
                X = RngNext() % U;
                auto X_ = veb.suc(X)q
                if(curOp%P == 0){
                    std::cout << "S " << X_ << '\n';
                }
            }
            else {
                /* DEL */
                X = RngNext() % U;
                auto X_ = veb.suc(X);
                auto L = veb.delete(X_!=U?X_:X);
                if(curOp %P == 0){
                    std::cout << "D " << L << '\n';
                }
            }
        }
    }
}

