#include "Circuit.h"

void printState(const Eigen::VectorXcd &state) {
  for (size_t i = 0; i < state.size(); i++) {
    printf("%zu: %0.02f + %0.02fi\n", i, state[i].real(), state[i].imag());
  }
}
int main() {
  // Deutsch example code, replace with your circuit.
  Circuit c{};
  // adds 2 wires, in states |0> and |1>.
  c.addWire(std::vector<Vec2>{ZERO, ONE});
  // adds the operators to perform Deutsch's algorith, with input Qbit 0 and output Qbit 1.
  c.addOp(Circuits::Deutsch(0, 1, Circuits::U_f3(0, 1)));
  // computes the circuit
  RunResult r = c.compute();
  // prints the first (and only) measurement performed.
  printf("Result: %d\n", r.measurements[0]);
}