////////////////////////////////////////
// BoxTreeNode.h
////////////////////////////////////////

#ifndef CSE168_BOXTREENODE_H
#define CSE168_BOXTREENODE_H

#include <Core/Vector3.h>
#include <Intersection.h>
#include <Object/Triangle.h>
#include <Object/Vertex.h>

////////////////////////////////////////////////////////////////////////////////


class BoxTreeNode
{
public:
        BoxTreeNode();
	~BoxTreeNode(){}
	bool Intersect(const Ray &ray, Intersection &hit)const ;
	void Construct(int count, Triangle** tri);
private:
	Vector3 BoxMax, BoxMin;
	BoxTreeNode *Child1, *Child2;
	Triangle *Tri[MaxTrianglesPerBox];

	Vector3 FindBoxLimit(int count, Triangle** tri);
};

////////////////////////////////////////////////////////////////////////////////

#endif
