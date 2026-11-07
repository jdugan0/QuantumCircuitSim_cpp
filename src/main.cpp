#include "Circuit.h"
#include "Examples.h"
void printState(const Eigen::VectorXcd &state) {
  for (size_t i = 0; i < state.size(); i++) {
    printf("%zu: %0.02f + %0.02fi\n", i, state[i].real(), state[i].imag());
  }
}
int main() {
  // Add your circuit here:
  printf("Result: %d\n", DeutschExample().measurements[0]);
}