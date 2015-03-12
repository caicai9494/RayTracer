#include <Object/BoxTreeObject.h>

BoxTreeObject::BoxTreeObject():Object()
{
    RootNode = NULL;
}
BoxTreeObject::~BoxTreeObject()
{
    //DeleteNode(RootNode);
}

void BoxTreeObject::DeleteNode(BoxTreeNode *node)
{
    if(node->Child1 == NULL)
    {
	delete node;
	return;
    }
    DeleteNode(node->Child1);
    DeleteNode(node->Child2);
}
void BoxTreeObject::Construct(MeshObject &obj)
{
    //cout << obj.NumTriangles << endl;
    Triangle **triangles;
    triangles = new Triangle*[obj.NumTriangles];
    for(int i = 0; i < obj.NumTriangles; i++)
	triangles[i] = obj.Triangles + i;

    RootNode = new BoxTreeNode;
    RootNode->Construct(obj.NumTriangles, triangles);
}
bool BoxTreeObject::Intersect(const Ray &ray, Intersection &hit)
{
    bool success = false;
    float t;
    if(RootNode->IntersectVolume(ray, t))
        success = RootNode->Intersect(ray, hit);

    return success;
}
