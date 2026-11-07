#include "Circuit.h"

void Circuit::addWire(const Vec2 &w) {
  if (initalState.size() == 0) {
    initalState = w;
    return;
  }
  initalState = Eigen::kroneckerProduct(initalState, w).eval();
}
void Circuit::addOp(const Op &op) { ops.push_back(op); }
Eigen::VectorXcd Circuit::compute() {
  Eigen::VectorXcd state = initalState;
  size_t count = state.size();
  for (size_t i = 0; i < ops.size(); i++) {
    const Op &op = ops[i];
    if (std::holds_alternative<Gate>(op)) {
      const Gate &gate = std::get<Gate>(op);
      int target = gate.target;
      // iterate over all pairs of qbits
      for (int p = 0; p < count >> 1; p++) {
        size_t mask = (size_t(1) << target) - 1;     // ones in bits 0..target-1
        size_t j0 = ((p & ~mask) << 1) | (p & mask); // bit target = 0
        size_t j1 = j0 | (size_t(1) << target);      // bit target = 1
        Vec2 temp_state{state[j0], state[j1]};
        Vec2 Utemp_state = gate.u * temp_state;

        state[j0] = Utemp_state[0];
        state[j1] = Utemp_state[1];
      }
    } else {
      const Measure &gate = std::get<Measure>(op);
    }
  }
  return state;
}