#include "../include/includeMinqueue.hpp"
#include <cstdint>


void Minqueue::dequeue() {
  auto initialElem = m_curVec.at(0);
  m_curVec.erase(m_curVec.begin());
  if (initialElem == m_minimumVec[0]) {
    m_minimumVec.erase(m_minimumVec.begin());
  }
}

void Minqueue::enqueue(uint32_t x) {
  m_curVec.push_back(x);
  if(!m_minimumVec.empty()){
    while (!m_minimumVec.empty() && m_minimumVec.back()> x) {
      m_minimumVec.pop_back();
    }
  }
  m_minimumVec.push_back(x);
}
