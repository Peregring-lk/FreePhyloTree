#ifndef _GL_ENGINE_
#define _GL_ENGINE_

#include <QGLWidget>
#include "PhyloTree.hpp"

namespace FreePhyloTree
{
  class GLEngine : public QGLWidget
  {
  public:
    GLEngine(PhyloTree *tree);
    ~GLEngine();

  private:
    PhyloTree *_tree;

    void initializeGL();
    void paintGL();
  };
}

#endif
