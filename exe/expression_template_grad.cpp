#include <array>
#include <cmath>
#include <iostream>
#include <type_traits>

#define VARIABLE Variable<float, __COUNTER__>

template <typename T, int ID> class Variable;

template <typename Operator, typename Operand> class UnaryExpression;

template <class Left, class Operator, class Right> class BinaryExpression;

namespace operators {

/*
struct plus {
  static float apply(float left, float right) { return left + right; }

  template <typename Left, typename Right, int ID>
  static float grad(const Variable<float, ID> &target, const Left &left,
                    const Right &right) {
    return left.get_grad(target) + right.get_grad(target);
  }
};
*/

/*
struct multiply {
  static float apply(float left, float right) { return left * right; }

  template <typename Left, typename Right, int ID>
  static float grad(const Variable<float, ID> &target, const Left &left,
                    const Right &right) {
    return left.get_grad(target) * right.get_value() +
           left.get_value() * right.get_grad(target);
  }
};
*/

template <typename Derived> struct ApplyUnaryFunctionBase {
  Derived &derived() { return static_cast<Derived &>(*this); }

  const Derived &derived() const { return static_cast<Derived &>(*this); }

  static float apply(float operand) {
#if DEBUG
    std::cerr << "operand:" << operand
              << " apply:" << Derived::apply_detail(operand) << std::endl;
#endif
    return Derived::apply_detail(operand);
  }

  template <typename Operand, int ID>
  static float grad(const Variable<float, ID> &target, const Operand &operand) {
#if DEBUG
    std::cerr << "grad:"
              << Derived::grad_detail(operand.get_value()) *
                     operand.get_grad(target)
              << std::endl;
#endif
    return Derived::grad_detail(operand.get_value()) * operand.get_grad(target);
  }

  static float grad_detail(float x);
  static float apply_detail(float x);
};

struct sin : public ApplyUnaryFunctionBase<sin> {
  static float apply_detail(float x) { return std::sin(x); }
  static float grad_detail(float x) { return std::cos(x); }
};

struct cos : public ApplyUnaryFunctionBase<cos> {
  static float apply_detail(float x) { return std::cos(x); }
  static float grad_detail(float x) { return -std::sin(x); }
};

struct exp : public ApplyUnaryFunctionBase<exp> {
  static float apply_detail(float x) { return std::exp(x); }
  static float grad_detail(float x) { return std::exp(x); }
};

template <typename Derived> struct ApplyBinaryFunctionBase {
  Derived &derived() { return static_cast<Derived &>(*this); }

  const Derived &derived() const { return static_cast<Derived &>(*this); }

  static float apply(float left, float right) {
    return Derived::apply_detail(left, right);
  }

  template <typename Left, typename Right, int ID>
  static float grad(const Variable<float, ID> &target, const Left &left,
                    const Right &right) {
    return (Derived::grad_detail_left(left.get_value(), right.get_value()) *
                left.get_grad(target) +
            Derived::grad_detail_right(left.get_value(), right.get_value()) *
                right.get_grad(target));
  }

  static float apply_detail(float x, float y);
  static float grad_detail(float x, float y) ;
  static float grad_detail_left(float x, float y) { return Derived::grad_detail(x, y); }
  static float grad_detail_right(float x, float y) { return Derived::grad_detail(x, y); }
};

struct max : public ApplyBinaryFunctionBase<max> {
  static float apply_detail(float x, float y) { return x > y ? x : y; }
  static float grad_detail_left(float x, float y) { return x > y ? 1 : 0; }
  static float grad_detail_right(float x, float y) { return x < y ? 1 : 0; }
};

struct min : public ApplyBinaryFunctionBase<min> {
  static float apply_detail(float x, float y) { return x < y ? x : y; }
  static float grad_detail_left(float x, float y) { return x < y ? 1 : 0; }
  static float grad_detail_right(float x, float y) { return x > y ? 1 : 0; }
};

struct plus : public ApplyBinaryFunctionBase<plus> 
{
  static float apply_detail(float x, float y) { return x + y; }
  static float grad_detail(float x, float y) { return 1; }
};

struct multiply : public ApplyBinaryFunctionBase<multiply> 
{
  static float apply_detail(float x, float y) { return x * y; }
  static float grad_detail_left(float x, float y) { return x; }
  static float grad_detail_right(float x, float y) { return y; }
};

}

template <typename T, int ID = 0> class Variable {
public:
  static const int id = ID;

  Variable(const T &_value) : value(_value) {}
  T get_value() const { return value; }
  template <int OTHER_ID>
  T get_grad(const Variable<T, OTHER_ID> &target) const {
    return (target.id == ID ? 1 : 0);
  }

private:
  T value;
};

template <typename T> class ConstVariable {
public:
  ConstVariable(const T &_value) : value(_value) {}
  T get_value() const { return value; }

  template <int OTHER_ID>
  T get_grad(const Variable<T, OTHER_ID> &target) const {
    return 0;
  }

private:
  T value;
};

template <typename Operator, typename Operand> class UnaryExpression {
public:
  UnaryExpression(const Operand &o) : operand(o) {}

  float get_value() const { return Operator::apply(operand.get_value()); }

  template <int ID> float get_grad(const Variable<float, ID> &target) const {
    return Operator::grad(target, operand);
  }

private:
  Operand operand;
};

template <class Left, class Operator, class Right> 
class BinaryExpression {
  Left left;
  Right right;

public:
  BinaryExpression(const Left &l, const Right &r) : left(l), right(r) {}

  float get_value() const {
    return Operator::apply(left.get_value(), right.get_value());
  }

  template <int ID> float get_grad(const Variable<float, ID> &target) const {
    return Operator::grad(target, left, right);
  }
};

template <class Left, class Right>
BinaryExpression<Left, operators::plus, Right> operator+(const Left &left,
                                                         const Right &right) {
  return BinaryExpression<Left, operators::plus, Right>(left, right);
}

template <class Left>
BinaryExpression<Left, operators::plus, ConstVariable<float>>
operator+(const Left &left, const float &right) {
  return BinaryExpression<Left, operators::plus, ConstVariable<float>>(left, ConstVariable<float>(right));
}

template <class Left, class Right>
BinaryExpression<Left, operators::multiply, Right>
operator*(const Left &left, const Right &right) {
  return BinaryExpression<Left, operators::multiply, Right>(left, right);
}

template <class Left>
BinaryExpression<Left, operators::multiply, ConstVariable<float>>
operator*(const Left &left, const float &right) {
  return BinaryExpression<Left, operators::multiply, ConstVariable<float>>(
      left, ConstVariable<float>(right));
}

template <typename Operand>
UnaryExpression<operators::sin, Operand> sin(const Operand &operand) {
  return UnaryExpression<operators::sin, Operand>(operand);
}

template <typename Operand>
UnaryExpression<operators::exp, Operand> exp(const Operand &operand) {
  return UnaryExpression<operators::exp, Operand>(operand);
}

int main(void) {
  auto a = VARIABLE(1);
  auto b = VARIABLE(2);

  std::cout << "a=" << a.get_value() << std::endl;
  std::cout << "a'=" << a.get_grad(a) << std::endl;
  std::cout << "a*a'=" << (a * a).get_grad(a) << std::endl;
  std::cout << "b=" << b.get_value() << std::endl;
  std::cout << "b'=" << b.get_grad(b) << std::endl;

  auto c = a + b;
  std::cout << "c=" << c.get_value() << std::endl;
  std::cout << "c'a=" << c.get_grad(a) << std::endl;
  std::cout << "c'b=" << c.get_grad(b) << std::endl;

  auto d = sin(c);
  std::cout << "d=" << d.get_value() << std::endl;

  auto temp = VARIABLE(M_PI / 2);
  auto e = sin(temp);
  std::cout << "e=" << e.get_value() << std::endl;
  std::cout << "e'=" << e.get_grad(temp) << std::endl;

  auto temp2 = VARIABLE(5.0);
  auto f = exp(temp2);
  std::cout << "f=" << f.get_value() << std::endl;
  std::cout << "f'=" << f.get_grad(temp2) << std::endl;

  auto g = sin(b * b) + 1.0f;
  std::cout << "g=" << g.get_value() << std::endl;
  std::cout << "g'=" << g.get_grad(b) << std::endl;
  std::cout << "sin^2(2)=" << (sin(b) * sin(b)).get_value() << std::endl;
  std::cout << "sin^2'(2)=" << (sin(b) * sin(b)).get_grad(b) << std::endl;
}
