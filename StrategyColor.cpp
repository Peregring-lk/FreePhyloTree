#include "StrategyColor.hpp"

using namespace FreePhyloTree;

Color::Color()
{
  _color[0] = _color[1] = _color[2] = 0;
}

Color::Color(GLfloat r, GLfloat g, GLfloat b)
{
  _color[0] = r;
  _color[1] = g;
  _color[2] = b;
}

Color::Color(const Color& color)
{
  _color[0] = color._color[0];
  _color[1] = color._color[1];
  _color[2] = color._color[2];
}

Interval::Interval(TypeColor type, GLfloat value)
{
  TypeColor first = type;
  TypeColor second = (TypeColor)((type + 1) % 3);
  TypeColor third = (TypeColor)((type + 2) % 3);

  if (value < 0)
    value = 0;
  else if (value > 1)
    value = 1;

  _i._color[first] = _s._color[first] = value;
  _i._color[second] = _i._color[third] = 0;
  _s._color[second] = _s._color[third] = 1;
}

Color Interval::center() const
{
  return Color((_i._color[0] + _s._color[0]) / 2,
	       (_i._color[1] + _s._color[1]) / 2,
	       (_i._color[2] + _s._color[2]) / 2);
}

void Interval::step(TypeColor type, int windows, float dir)
{
  float move = dir / windows;

  _i._color[type] += move;
  _s._color[type] += move;
}

void Interval::cutUp(TypeColor type, int pieces, int n)
{
  float step = (_s._color[type] - _i._color[type]) / pieces;

  _i._color[type] += n * step;
  _s._color[type] = _i._color[type] + step;
}

StrategyColor::StrategyColor(TypeColor f, bool pos, TypeColor s,
			     TypeColor t)
  :_f(f), _s(s), _t(t)
{
  if (pos)
    _dir = 1;
  else
    _dir = -1;
}

Interval StrategyColor::getInterval(int windows, int depth,
				    int brothers, int n,
				    const Interval *father) 
{
  if (father == NULL)
    return Interval(_f, _dir < 0);
  else {
    Interval interval = *father;

    interval.step(_f, windows, _dir);

    // Si es impar
    if (depth % 2)
      interval.cutUp(_s, brothers, n);
    else
      interval.cutUp(_t, brothers, n);

    return interval;
  } 
}

Color StrategyColor::getColor(const Interval& interval)
{
  return interval.center();
}
