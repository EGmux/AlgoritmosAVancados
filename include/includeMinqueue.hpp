#ifndef MINQUEUE_H
#define MINQUEUE_H
#include <vector>
#include <cstdint>

struct Minqueue {
  void enqueue(uint32_t x_k);
  void dequeue();
  uint32_t sizeOfMinVec();

  std::vector<uint32_t> m_curVec;
  std::vector<uint32_t> m_minimumVec;
};

#endif  // MINQUE_H