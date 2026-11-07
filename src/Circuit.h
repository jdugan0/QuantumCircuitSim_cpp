#pragma once
#include "defs.h"
#include <random>
#include <unsupported/Eigen/KroneckerProduct>
#include <variant>
#include <vector>

struct Gate {
  Mat2 u;
  int target;
  std::vector<int> controls{};
};
struct Measure {
  int target;
};
struct RunResult {
  Eigen::VectorXcd state{};
  std::vector<int> measurements{};
};
using Op = std::variant<Gate, Measure>;
struct Circuit {
  Eigen::VectorXcd initalState{};
  std::vector<Op> ops{};
  void addWire(const Vec2 &w);
  void addWire(const std::vector<Vec2> &w);
  void addWire(const Vec2 &w, int amount);
  void addOp(const Op &op);
  void addOp(const std::vector<Op> &op);
  RunResult compute();
};

namespace Circuits {
const std::vector<Op> U_f0(int x, int y);
const std::vector<Op> U_f1(int x, int y);
const std::vector<Op> U_f2(int x, int y);
const std::vector<Op> U_f3(int x, int y);

const std::vector<Op> Deutsch(int x, int y, std::vector<Op> U_f);
}; // namespace Circuits