#include <iostream>

#include "../include/minqueue.hpp"

// #define R 2 ^ 32  
#define A 1664525
#define C 1013904223

#define X_k(k) (A * k + C) // because 0 <= lhs <= 2^32, no rhs is neeeded, % R.

int main() {
  uint32_t S;  // X_k(0)
  uint32_t B;  // Burn in , first set of push() operations
  uint32_t N;  // Total number of operations after the burn in
  uint32_t P;  // frequency of operatons for pop() and push()
  Minqueue M;
  uint32_t x_k;
  std::cin >> S >> B >> N >> P;
  x_k = S;
  for (auto i = 0; i < B; ++i) {
    M.enqueue(X_k(x_k));
    x_k = X_k(x_k);
  }
  for (auto i = 0; i < N; ++i) {
    (x_k % 10) < P ? M.enqueue(X_k(x_k)) : M.dequeue();

  }
}
