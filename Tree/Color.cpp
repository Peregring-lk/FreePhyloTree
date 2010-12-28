#include "Color.hpp"

using namespace FreePhyloTree;

Color::Color()
{
  _color[R] = _color[G] = _color[B] = 1;
}

Color::Color(GLfloat r, GLfloat g, GLfloat b)
{
  _color[R] = r;
  _color[G] = g;
  _color[B] = b;
}

Color::Color(const Color& color)
{
  _color[R] = color.r();
  _color[G] = color.g();
  _color[B] = color.b();
}

GLfloat Color::r() const
{
  return _color[R];
}

GLfloat Color::g() const
{
  return _color[G];
}

GLfloat Color::b() const
{
  return _color[B];
}

GLfloat Color::color(TypeColor t) const
{
  return _color[t];
}

void Color::setColor(GLfloat r, GLfloat g, GLfloat b)
{
  _color[R] = r;
  _color[G] = g;
  _color[B] = b;
}

void Color::setColor(TypeColor t, GLfloat value)
{
  _color[t] = value;
}
