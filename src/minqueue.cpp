#include "../include/minqueue.hpp"

minimum Minqueue::minElem() { return _minimumVec->at(0); }

void Minqueue::dequeue() {
  auto initialElem = _curVec->at(0);
  _curVec->erase(_curVec->begin());
  if (initialElem == _minimumVec->at(0).elem) {
    _minimumVec->erase(_minimumVec->begin());
  }
}

void Minqueue::enqueue(const uint32_t& x_k) {
  _curVec->push_back(x_k);
  while (_minimumVec->back().elem > x_k) {
    _minimumVec->pop_back();
  }
  // track _curVec elem position in _minimumVec
  _minimumVec->push_back(minimum(x_k,&_curVec->back()));
}

uint32_t Minqueue::sizeOfMinVec() { return _minimumVec->size(); }