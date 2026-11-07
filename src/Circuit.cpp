#include "Circuit.h"
void Circuit::addWire(const Vec2 &w) {
  if (initalState.size() == 0) {
    initalState = w;
    return;
  }
  initalState = Eigen::kroneckerProduct(w, initalState).eval();
}
void Circuit::addWire(const Vec2 &w, int amount) {
  for (int i = 0; i < amount; i++) {
    addWire(w);
  }
}
void Circuit::addWire(const std::vector<Vec2> &w) {
  for (size_t i = 0; i < w.size(); i++) {
    addWire(w[i]);
  }
}
void Circuit::addOp(const Op &op) { ops.push_back(op); }
void Circuit::addOp(const std::vector<Op> &op) {
  for (size_t i = 0; i < op.size(); i++) {
    addOp(op[i]);
  }
}

RunResult Circuit::compute() {
  Eigen::VectorXcd state = initalState;
  std::vector<int> measurements{};
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
        bool skip = false;
        for (size_t t = 0; t < gate.controls.size(); t++) {
          if (((1 << gate.controls[t]) & j0) == 0) {
            skip = true;
            break;
          }
        }
        if (skip) {
          continue;
        }
        Vec2 temp_state{state[j0], state[j1]};
        Vec2 Utemp_state = gate.u * temp_state;

        state[j0] = Utemp_state[0];
        state[j1] = Utemp_state[1];
      }
    } else {
      const Measure &m = std::get<Measure>(op);
      int mask = 1 << m.target;
      double prob = 0;
      for (size_t k = 0; k < state.size(); k++) {
        if (mask & k) {
          prob += Prob(state[k]);
        }
      }
      // generate value
      std::random_device rd;
      std::mt19937 gen(rd());
      std::uniform_real_distribution<double> dist(0.0, 1.0);
      double random_num = dist(gen);
      if (random_num < prob) {
        for (size_t k = 0; k < state.size(); k++) {
          if (!(mask & k)) {
            state[k] = 0;
          }
        }
        measurements.push_back(1);
        state /= std::sqrt(prob);
      } else {
        for (size_t k = 0; k < state.size(); k++) {
          if ((mask & k)) {
            state[k] = 0;
          }
        }
        measurements.push_back(0);
        state /= std::sqrt(1 - prob);
      }
    }
  }
  return RunResult{state, measurements};
}


const std::vector<Op> Circuits::U_f0(int x, int y) { return {}; };
const std::vector<Op> Circuits::U_f1(int x, int y) { return {Gate{Gates::X, y, {x}}}; }
const std::vector<Op> Circuits::U_f2(int x, int y) {
  return {Gate{Gates::X, y, {}}, Gate{Gates::X, y, {x}}};
}
const std::vector<Op> Circuits::U_f3(int x, int y) { return {Gate{Gates::X, y, {}}}; }

const std::vector<Op> Circuits::Deutsch(int x, int y, std::vector<Op> U_f) {
  std::vector<Op> v = {{Gate{Gates::H, x}}, {Gate{Gates::H, y}}};
  v.insert(v.end(), U_f.begin(), U_f.end());
  v.push_back({Gate{Gates::H, x}});
  v.push_back({Gate{Gates::H, y}});
  v.push_back({Measure{x}});
  return v;
}