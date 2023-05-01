#include "../include/includeMinqueue.hpp"
#include <cstdint>


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
