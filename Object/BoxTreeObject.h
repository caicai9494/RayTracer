////////////////////////////////////////
// BoxTreeObject.h
////////////////////////////////////////

#ifndef CSE168_BOXTREEOBJECT_H
#define CSE168_BOXTREEOBJECT_H

#include <Core/Vector3.h>
#include <Intersection.h>
#include <Object/BoxTreeNode.h>
#include <Object/MeshObject.h>
#include <Object/Triangle.h>

////////////////////////////////////////////////////////////////////////////////


class BoxTreeObject: public Object
{
public:
        BoxTreeObject();
	~BoxTreeObject();
	bool Intersect(const Ray &ray, Intersection &hit);
	void Construct(MeshObject &obj);
private:
	BoxTreeNode *RootNode;
	void DeleteNode(BoxTreeNode *node);
};

////////////////////////////////////////////////////////////////////////////////

#endif
