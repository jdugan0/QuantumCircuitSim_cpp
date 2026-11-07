#pragma once
#include "defs.h"
#include <unsupported/Eigen/KroneckerProduct>
#include <variant>
#include <vector>

struct Gate {
  Mat2 u;
  int target;
  std::vector<int> controls;
};
struct Measure {
  int target;
  int cbit;
};
using Op = std::variant<Gate, Measure>;
struct Circuit {
  Eigen::VectorXcd initalState{};
  std::vector<Op> ops{};
  void addWire(const Vec2 &w);
  void addOp(const Op &op);
  Eigen::VectorXcd compute();
};