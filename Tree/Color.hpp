#ifndef _COLOR_
#define _COLOR_

#include <GL/gl.h>

namespace FreePhyloTree
{
  enum TypeColor { R, G, B };

  class Color
  {
  public:
    Color();
    Color(GLfloat r, GLfloat g, GLfloat b);
    Color(const Color& color);

    GLfloat r() const;
    GLfloat g() const;
    GLfloat b() const;

    GLfloat color(TypeColor t) const;

    void setColor(GLfloat r, GLfloat g, GLfloat b);
    void setColor(TypeColor t, GLfloat value);

  private:
    GLfloat _color[3];
  };
}

#endif
