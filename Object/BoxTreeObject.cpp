#include <Object/BoxTreeObject.h>
#include <iostream>
using namespace std;

void BoxTreeObject::Construct(MeshObject &obj)
{
    /*
    for(int i = 0; i < obj.NumTriangles; i++)
    {
	cout << obj.Triangles[i].Vtx[0]->Position.x << " " << endl;
	cout << obj.Triangles[i].Vtx[0]->Position.y << " " << endl;
	cout << obj.Triangles[i].Vtx[0]->Position.z << " " << endl;
    }
    */

    RootNode->Construct(obj.NumTriangles, &(obj.Triangles));
}
