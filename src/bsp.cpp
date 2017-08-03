#include "bsp.hpp"

#include <string>

BSP::BSP(){
}

void BSP::addWall(Vector2f a,Vector2f b){
  Wall temp;
  temp.p1=a;
  temp.p2=b;
  temp.normal=getNormal(a,b);
  walls.push_back(temp);
}

unsigned int BSP::getNumberOfWalls(){
  return walls.size();
}

Wall BSP::getWall(unsigned int i){
  return walls.at(i);
}

void BSP::build(){
  if(getNumberOfWalls()==0){
    throw std::string("imppossible de construire le BSP: pas de mure");
  }
	
  MainNode = new Node;
  MainNode->mWall=&walls.at(0);
  MainNode->back=NULL;
  MainNode->front=NULL;
  
  for(unsigned int i(1);i<walls.size();i++){
    buildWall(i,MainNode);
  }
}

void BSP::buildWall(unsigned int wallid, Node* node){
  Vector2f AB;
  AB=node->mWall->p2-node->mWall->p1;
  float d1=Determinant(AB,walls.at(wallid).p1-node->mWall->p2);
  float d2=Determinant(AB,walls.at(wallid).p2-node->mWall->p2);
	
  if(d1>0 || d2>0){
    if(node->front==NULL){
      node->front = new Node;
      node->front->mWall=&walls.at(wallid);
      node->front->back=NULL;
      node->front->front=NULL;
    }else{
      buildWall(wallid,node->front);
    }
  }
  
  if(d1<0 || d2<0){
    if(node->back==NULL){
      node->back = new Node;
      node->back->mWall=&walls.at(wallid);
      node->back->back=NULL;
      node->back->front=NULL;
    }else{
      buildWall(wallid,node->back);
    }
  }
}

bool BSP::testPoint(Vector2f v){
  return testPointWall(v,MainNode);
}

bool BSP::testPointWall(Vector2f v,Node* node){
  Vector2f AB;
  AB=node->mWall->p2-node->mWall->p1;
  float d=Determinant(AB,v-node->mWall->p2);
	
  if(d>=0){
    if(node->front==NULL){
      return false;
    }else{
      return testPointWall(v,node->front);
    }
  }else{
    if(node->back==NULL){
      return true;
    }else{
      return testPointWall(v,node->back);
    }
  }
}
