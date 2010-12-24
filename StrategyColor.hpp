#ifndef _STRATEGY_COLOR_
#define _STRATEGY_COLOR_

#include <GL/gl.h>

namespace FreePhyloTree
{
  enum TypeColor { R, G, B };

  struct Color
  {
    Color();
    Color(GLfloat r, GLfloat g, GLfloat b);
    Color(const Color& color);

    GLfloat _color[3];
  };

  struct Interval
  {
    Interval(TypeColor type, GLfloat value);

    Color center() const;

    void step(TypeColor type, int windows, float dir);
    void cutUp(TypeColor type, int pieces, int n);

    Color _i;
    Color _s;
  };

  class StrategyColor
  {
  public:
    StrategyColor(TypeColor f, bool pos, TypeColor s, TypeColor t);

    Interval getInterval(int depth, int brothers, int n,
			 const Interval *father = NULL);

    Color getColor(const Interval& interval);

  private:
    TypeColor _f, _s, _t;  // First, second, third.

    float _dir;
  };
}

#endif
