#include "Circuit.h"
#include <stdio.h>

void printState(const Eigen::VectorXcd &state) {
  for (size_t i = 0; i < state.size(); i++) {
    printf("%zu: %0.02f\n", i, Prob(state[i]));
  }
}
int main() {
  Circuit c{};
  c.addWire(Vec2{ZERO});
  c.addOp(Gate{Gates::H, 0, {}});
  c.initalizeState();
  printState(c.compute());
}