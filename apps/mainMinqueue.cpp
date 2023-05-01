#include "../include/includeMinqueue.hpp"
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <iterator>
#include <sstream>
#include <sys/types.h>

uint32_t seed;
#define R 4294967296
#define A 1664525
#define C 1013904223

uint32_t RngNext() {
    seed = (A * seed + C) % R;
    return seed;
}

int main() {
  uint32_t S;  // X_k(0)
  uint32_t B;  // Burn in , first set of push() operations
  uint32_t N;  // Total number of operations after the burn in
  uint32_t P;  // frequency of operatons for pop() and push()
  std::string curline;
  std::getline(std::cin, curline);
  std::stringstream ss(curline);
  ss >> S >> B >> N >> P;

  seed = S;
  Minqueue m;
  if(B>0){
    m.enqueue(S);
    for (auto i = 0; i < B; ++i) {
        m.enqueue(RngNext());
    }
  }
  
  for (auto i = 0; i < N; ++i) {
    auto X = (seed == S)?seed:RngNext();
    if((X % 10) < P){
      auto X = RngNext();
      m.enqueue((X));
    } 
    else{m.dequeue();}
    auto pos = m.m_minimumVec[0].pos - (m.g_timer - m.m_minimumVec[0].g_timer);
    std::cout << m.m_minimumVec.size() << ' ' << pos << '\n';
  };
}
