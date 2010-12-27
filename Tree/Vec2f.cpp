#include <cmath>
#include "Vec2f.hpp"

using namespace FreePhyloTree;

Vec2f::Vec2f()
{
  _x = _y = 0;
  _norm = 0;
}

Vec2f::Vec2f(GLfloat x, GLfloat y) : _x(x), _y(y)
{
  _calcNorm();
}

GLfloat Vec2f::x() const
{
  return _x;
}

GLfloat Vec2f::y() const
{
  return _y;
}

GLfloat Vec2f::norm() const
{
  return _norm;
}

Vec2f Vec2f::unit() const
{
  return Vec2f(_x / _norm, _y / _norm);
}

Vec2f Vec2f::operator+ (const Vec2f& vec) const
{
  return Vec2f(*this) += vec;
}

Vec2f Vec2f::operator- (const Vec2f& vec) const
{
  return Vec2f(*this) -= vec;
}

Vec2f Vec2f::operator* (GLfloat k) const
{
  return Vec2f(*this) *= k;
}

Vec2f Vec2f::operator/ (GLfloat k) const
{
  return Vec2f(*this) /= k;
}

void Vec2f::setAlloc(GLfloat x, GLfloat y)
{
  _x = x;
  _y = y;

  _calcNorm();
}

Vec2f Vec2f::operator+= (const Vec2f& vec)
{
  _x += vec.x();
  _y += vec.y();

  _calcNorm();

  return *this;
}

Vec2f Vec2f::operator-= (const Vec2f& vec)
{
  _x -= vec.x();
  _y -= vec.y();

  _calcNorm();

  return *this;
}

Vec2f Vec2f::operator*= (GLfloat k)
{
  _x *= k;
  _y *= k;

  if (k != 0)
    _norm *= k;
  else
    _norm = 0;

  return *this;
}

Vec2f Vec2f::operator/= (GLfloat k)
{
  _x /= k;
  _y /= k;

  _norm /= k;

  return *this;
}

void Vec2f::_calcNorm()
{
  _norm = sqrt(pow(_x, 2) + pow(_y, 2));
}
