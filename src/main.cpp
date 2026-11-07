#include "Circuit.h"

void printState(const Eigen::VectorXcd &state) {
  for (size_t i = 0; i < state.size(); i++) {
    printf("%zu: %0.02f + %0.02fi\n", i, state[i].real(), state[i].imag());
  }
}
int main() {
  Circuit c{};
  c.addWire(ZERO);
  c.addWire(ONE);
  c.addOp(Circuits::Deutsch(0, 1, Circuits::U_f3(0, 1)));
  RunResult r = c.compute();
  printf("Result: %d\n", r.measurements[0]);
}