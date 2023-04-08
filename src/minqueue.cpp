#include "../include/minqueue.hpp"

uint32_t Minqueue::minElem() { return _minimumVec->at(0); }

void Minqueue::dequeue() {
  auto initialElem = _curVec->at(0);
  _curVec->erase(_curVec->begin());
  if (initialElem == _minimumVec->at(0)) {
    _minimumVec->erase(_minimumVec->begin());
  }
}

void Minqueue::enqueue(const uint32_t& x_k) {
  _curVec->push_back(x_k);
  while (_minimumVec->back() > x_k) {
    _minimumVec->pop_back();
  }
  _minimumVec->push_back(x_k);
}