#ifndef MINQUEUE_H
#define MINQUEUE_H
#include <vector>
#include <cstdint>
#include <tuple>

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

#endif  // MINQUE_H