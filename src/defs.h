#pragma once
#include <Eigen/Dense>
#include <cmath>
#include <complex>
using Mat2 = Eigen::Matrix<std::complex<double>, 2, 2>;
using Vec2 = Eigen::Matrix<std::complex<double>, 2, 1>;
using namespace std::complex_literals;
inline const Vec2 ZERO = {1, 0};
inline const Vec2 ONE = {0, 1};
namespace Gates {
inline const Mat2 I{{1, 0}, {0, 1}};
inline const Mat2 X{{0, 1}, {1, 0}};
inline const Mat2 Y{{0, -1i}, {1i, 0}};
inline const Mat2 Z{{1, 0}, {0, -1}};
inline const double root2 = 1 / std::sqrt(2.0);
inline const Mat2 H{{root2, root2}, {root2, -root2}};
}; // namespace Gates
inline double Prob(std::complex<double> c) {
  return c.real() * c.real() + c.imag() * c.imag();
}