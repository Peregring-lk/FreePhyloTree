#include "Interval.hpp"

using namespace FreePhyloTree;

Interval::Interval() : _inf(0, 0, 0), _sup(1, 1, 1)
{}

Interval::Interval(const Color& inf, const Color& sup)
  : _inf(inf), _sup(sup)
{}

Color Interval::inf() const
{
  return _inf;
}

Color Interval::sup() const
{
  return _sup;
}

Color Interval::center() const
{
  return Color((_inf.r() + _sup.r()) / 2,
	       (_inf.g() + _sup.g()) / 2,
	       (_inf.b() + _sup.b()) / 2);
}

void Interval::cut(TypeColor t, unsigned pieces, unsigned n)
{
  GLfloat infT = _inf.color(t);
  GLfloat supT = _sup.color(t);

  GLfloat intervalT = supT - infT;
  GLfloat step = intervalT / pieces;

  infT += n * step;
  supT = infT + step;

  _inf.setColor(t, infT);
  _sup.setColor(t, supT);
}
