#include <vector>
#include <cstdint>
#include <tuple>
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <iterator>
#include <sstream>
#include <sys/types.h>

struct minimumData{
  uint32_t val;
  uint32_t g_timer;
  uint32_t pos;

  minimumData(uint32_t v, uint32_t g, uint32_t p):val(v),g_timer(g),pos(p){};
};

struct Minqueue {
  void enqueue(uint32_t x_k);
  void dequeue();
  uint32_t sizeOfMinVec();

  std::vector<uint32_t> m_curVec;
  std::vector<minimumData> m_minimumVec;
  uint32_t g_timer{0};
};

void Minqueue::dequeue() {
  auto initialElem = m_curVec.at(0);
  m_curVec.erase(m_curVec.begin());
  if (initialElem == m_minimumVec[0].val) {
    m_minimumVec.erase(m_minimumVec.begin());
  }
  g_timer++;
}

void Minqueue::enqueue(uint32_t x) {
  m_curVec.push_back(x);
  if(!m_minimumVec.empty()){
    while (!m_minimumVec.empty() && m_minimumVec.back().val > x) {
      m_minimumVec.pop_back();
    }
  }
  auto p = minimumData(x,g_timer,m_curVec.size());
  m_minimumVec.push_back(p);
}

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
