#include <iostream>
#include <cmath>
#include "Alloc.hpp"

using namespace std;
using namespace FreePhyloTree;

SpringAlloc::SpringAlloc(float c1, float c2, float c3, float c4)
  : _c1(c1), _c2(c2), _c3(c3), _c4(c4)
{}

void SpringAlloc::reAlloc(Tree *tree)
{
  _moves.clear();
  _moves.resize(tree->order());

  const Edges& edges = tree->edges();
  const Edges& noAdjs = tree->noAdjs();

  for (int i = 0; i < edges.size(); ++i) {
    Edge edge = edges[i];

    _fa(edge.source(), edge.target(), edge.weight());
    _fa(edge.target(), edge.source(), edge.weight());
  }

  for (int i = 0; i < noAdjs.size(); ++i) {
    Edge edge = noAdjs[i];

    _fr(edge.source(), edge.target());
    _fr(edge.target(), edge.source());
  }

  for (int i = 0; i < _moves.size(); ++i)
    tree->node(i)->move(_moves[i]);
}

void SpringAlloc::_fa(Node *source, Node *target, int weight)
{
  Vec2f vu = source->alloc() - target->alloc();
  Vec2f fa = vu.unit() * _c1 * log(vu.norm() / weight);

  _moves[target->label()] += fa * _c4;
}

void SpringAlloc::_fr(Node *source, Node *target)
{
  Vec2f uv = target->alloc() - source->alloc();
  Vec2f fr = uv.unit() * (_c3 / pow(uv.norm(), 2));

  _moves[target->label()] += fr * _c4;
}
