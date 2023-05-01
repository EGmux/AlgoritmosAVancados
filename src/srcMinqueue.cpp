#include "../include/includeMinqueue.hpp"


void Minqueue::dequeue() {
  auto initialElem = m_curVec.at(0);
  m_curVec.erase(m_curVec.begin());
  if (initialElem == m_minimumVec.at(0).elem) {
    m_minimumVec.erase(m_minimumVec.begin());
  }
}

void Minqueue::enqueue(uint32_t x) {
  m_curVec.push_back(x);
  while (m_minimumVec.back().elem > x) {
    m_minimumVec.pop_back();
  }
  // track m_curVec elem position in m_minimumVec
  m_minimumVec.push_back(minimum(x,&m_curVec));
}
