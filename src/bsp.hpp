#ifndef BSP_H
#define BSP_H

#include <vector>
#include "base.hpp"

struct Wall
{
  Vector2f p1;
  Vector2f p2;
  Vector2f normal;
};

struct Node
{
  Wall* mWall;
  Node* front;
  Node* back;
};

class BSP
{
 public:
  BSP();
  
  void addWall(Vector2f a,Vector2f b);
  unsigned int getNumberOfWalls();
  Wall getWall(unsigned int i);
  
  void build();
  
  bool testPoint(Vector2f v);
  
 private:
  std::vector<Wall> walls;
  Node* MainNode;
  void buildWall(unsigned int wallid, Node* node);
  bool testPointWall(Vector2f v,Node* node);
};

#endif /* BSP_H */ 
