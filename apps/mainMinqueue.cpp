#include "../include/includeMinqueue.hpp"
#include <iostream>
#include <iterator>
#include <sstream>

uint32_t seed;
#define R UINT32_MAX
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
    auto X = RngNext();
    (X % 10) < P ? m.enqueue(X) : m.dequeue();
    auto lpos = m.m_minimumVec[0].pos;
    std::cout << m.m_minimumVec.size() << std::distance(m.m_curVec.cbegin(),lpos->cbegin()) << '\n';
  };
}
