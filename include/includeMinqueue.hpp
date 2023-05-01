#ifndef MINQUEUE_H
#define MINQUEUE_H
#include <vector>
#include <cstdint>

struct minimum {
  uint32_t elem;
  std::vector<uint32_t>* pos;
  minimum(uint32_t e, std::vector<uint32_t>* p) : elem(e), pos(p){};
};

struct Minqueue {
  void enqueue(uint32_t x_k);
  void dequeue();
  uint32_t sizeOfMinVec();

  std::vector<uint32_t> m_curVec;
  std::vector<minimum> m_minimumVec;
};

#endif  // MINQUE_H