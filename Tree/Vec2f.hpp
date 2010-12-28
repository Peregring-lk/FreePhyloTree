#ifndef _VEC_
#define _VEC_

#include <GL/gl.h>

namespace FreePhyloTree
{
  class Vec2f
  {
  public:
    Vec2f();
    Vec2f(GLfloat x, GLfloat y);

    GLfloat x() const;
    GLfloat y() const;

    GLfloat norm() const;
    Vec2f unit() const;

    Vec2f operator+ (const Vec2f& vec) const;
    Vec2f operator- (const Vec2f& vec) const;
    Vec2f operator* (GLfloat k) const;
    Vec2f operator/ (GLfloat k) const;

    bool inRadius(Vec2f vec, GLfloat radius) const;

    void setAlloc(GLfloat x, GLfloat y);
    void setX(GLfloat x);
    void setY(GLfloat y);

    Vec2f operator+= (const Vec2f& vec);
    Vec2f operator-= (const Vec2f& vec);
    Vec2f operator*= (GLfloat k);
    Vec2f operator/= (GLfloat k);

  private:
    GLfloat _x;
    GLfloat _y;

    GLfloat _norm;

    void _calcNorm();
  };
}

#endif
