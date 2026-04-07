#ifndef SJTU_COMPLEX_HPP
#define SJTU_COMPLEX_HPP

#include <cmath>     // 数学函数
#include <iomanip>   // 控制输出格式
#include <iostream>  // 输入输出
#include <stdexcept> // 异常处理
// 你不可以使用任何其他的头文件!

namespace sjtu {

class divided_by_zero final : public std::exception {
public:
  divided_by_zero() = default;
  ~divided_by_zero() = default;
  const char *what() const noexcept override {
    return "complex divided by zero!";
  }
};

// 用于判断浮点数的符号.
inline int sign(double x) {
  const double eps = 1e-6;
  return (x > eps) - (x < -eps);
}

class complex {
private:
  double a, b; // a + bi
public:
  complex() : a(0), b(0) {}
  complex(double a) : a(a), b(0) {}
  complex(double a, double b) : a(a), b(b) {}

  double &real() { return a; }
  double &imag() { return b; }

  complex operator-() const { return complex(-a, -b); }
  complex operator~() const { return complex(a, -b); }

  complex operator+(const complex &rhs) const { return complex(a + rhs.a, b + rhs.b); }
  complex operator-(const complex &rhs) const { return complex(a - rhs.a, b - rhs.b); }
  complex operator*(const complex &rhs) const {
    return complex(a * rhs.a - b * rhs.b, a * rhs.b + b * rhs.a);
  }
  complex operator/(const complex &rhs) const {
    if (std::abs(rhs.a) < 1e-6 && std::abs(rhs.b) < 1e-6) {
      throw divided_by_zero();
    }
    double denominator = rhs.a * rhs.a + rhs.b * rhs.b;
    return complex((a * rhs.a + b * rhs.b) / denominator, (b * rhs.a - a * rhs.b) / denominator);
  }

  complex &operator+=(const complex &rhs) {
    a += rhs.a;
    b += rhs.b;
    return *this;
  }
  complex &operator-=(const complex &rhs) {
    a -= rhs.a;
    b -= rhs.b;
    return *this;
  }
  complex &operator*=(const complex &rhs) {
    double new_a = a * rhs.a - b * rhs.b;
    double new_b = a * rhs.b + b * rhs.a;
    a = new_a;
    b = new_b;
    return *this;
  }
  complex &operator/=(const complex &rhs) {
    if (std::abs(rhs.a) < 1e-6 && std::abs(rhs.b) < 1e-6) {
      throw divided_by_zero();
    }
    double denominator = rhs.a * rhs.a + rhs.b * rhs.b;
    double new_a = (a * rhs.a + b * rhs.b) / denominator;
    double new_b = (b * rhs.a - a * rhs.b) / denominator;
    a = new_a;
    b = new_b;
    return *this;
  }

  bool operator==(const complex &rhs) const {
    return std::abs(a - rhs.a) < 1e-6 && std::abs(b - rhs.b) < 1e-6;
  }

  explicit operator bool() const {
    return !(std::abs(a) < 1e-6 && std::abs(b) < 1e-6);
  }

  friend std::ostream &operator<<(std::ostream &os, const complex &x) {
    double real_part = x.a;
    double imag_part = x.b;

    os << std::fixed << std::setprecision(6);
    
    if (sign(real_part) == -1) {
      os << real_part;
    } else {
      os << std::abs(real_part); // to avoid -0.000000
    }
    
    if (sign(imag_part) == -1) {
      os << imag_part << "i";
    } else {
      os << "+" << std::abs(imag_part) << "i";
    }
    
    return os;
  }
};

} // namespace sjtu

#endif
