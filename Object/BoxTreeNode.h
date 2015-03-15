////////////////////////////////////////
// BoxTreeNode.h
////////////////////////////////////////

#ifndef CSE168_BOXTREENODE_H
#define CSE168_BOXTREENODE_H

#include <Core/Vector3.h>
#include <Camera/Intersection.h>
#include <Object/Triangle.h>
#include <Object/Vertex.h>

////////////////////////////////////////////////////////////////////////////////


class BoxTreeNode
{
    friend class BoxTreeObject;
public:
        BoxTreeNode();
	~BoxTreeNode();


	bool Intersect(const Ray &ray, Intersection &hit);
	bool IntersectVolume(const Ray &ray, float &t);
	void Construct(int count, Triangle** tri);

	int GetNumTriangles();
	bool IsLeaf() const;
private:
	Vector3 BoxMax, BoxMin;
	BoxTreeNode *Child1, *Child2;
	Triangle *Tri[MaxTrianglesPerBox];
	void FindBoxLimit(int count, Triangle** tri);
	int NumTriangles;
};

////////////////////////////////////////////////////////////////////////////////

#endif
