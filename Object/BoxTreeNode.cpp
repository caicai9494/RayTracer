#include <Object/BoxTreeNode.h>
#include <iostream>
using namespace std;

BoxTreeNode::BoxTreeNode(): Child1(0), Child2(0)
{
}
Vector3 BoxTreeNode::FindBoxLimit(int count, Triangle** tri)
{
    float xmin, ymin, zmin;
    float xmax, ymax, zmax;
    xmin = xmax = tri[0]->Vtx[0]->Position.x;
    ymin = ymax = tri[0]->Vtx[0]->Position.y;
    zmin = zmax = tri[0]->Vtx[0]->Position.z;

    for(int i = 1; i < count; i++)
    {
	Triangle *triangle = tri[i];
	for(int j = 0; j < 3; j++)
	{
	    Vertex *vertex = triangle->Vtx[j];
	    if(vertex->Position.x > xmax)
		xmax = vertex->Position.x;
	    if(vertex->Position.y > ymax)
		ymax = vertex->Position.y;
	    if(vertex->Position.z > zmax)
		zmax = vertex->Position.z;

	    if(vertex->Position.x < xmin)
		xmin = vertex->Position.x;
	    if(vertex->Position.y < ymin)
		ymin = vertex->Position.y;
	    if(vertex->Position.z < zmin)
		zmin = vertex->Position.z;
	}
    }

    BoxMax = Vector3(xmax, ymax, zmax);
    BoxMin = Vector3(xmin, ymin, zmin);

    return Vector3(xmax - xmin, ymax - ymin, zmax - zmin);
}

void BoxTreeNode::Construct(int count, Triangle** tri)
{
    // copy tri array
    if(count < MaxTrianglesPerBox)
    {
	for(int i = 0; i < count; i++)
	    Tri[i] = tri[i];
	return;
    }

    Vector3 BoxSize;
    BoxSize = FindBoxLimit(count, tri);


    Vector3 BoxCenter;
    Vector3 SplitPlaneNormal;
    BoxCenter = (BoxMin + BoxMax) / 2;
    if(BoxSize.x > BoxSize.y && BoxSize.x > BoxSize.z)
	SplitPlaneNormal = Vector3::XAXIS;
    else if(BoxSize.y > BoxSize.z && BoxSize.y > BoxSize.x)
	SplitPlaneNormal = Vector3::YAXIS;
    else
	SplitPlaneNormal = Vector3::ZAXIS;


    // initial temp tri array
    // store in tri1 if above plane
    Triangle **tri1 = new Triangle*[count];
    // store in tri2 if below plane
    Triangle **tri2 = new Triangle*[count];
    int count1 = 0, count2 = 0;
    for(int i = 0; i < count; i++)
    {
	Triangle *triangle = tri[i];
	Vector3 Center = (
			 triangle->Vtx[0]->Position + 
	    		 triangle->Vtx[1]->Position +
	    		 triangle->Vtx[2]->Position
			 ) / 3;

	if((Center - BoxCenter).Dot(SplitPlaneNormal) > 0)
	    tri1[count1++] = triangle;
	else
	    tri2[count2++] = triangle;
    }

    /*
    cout << " debug\n";
    cout << count1 << " count1\n";
    cout << count2 << " count2\n";
    cout << " debug\n";
    */

    if(count1 == 0)
	tri1[count1++] = tri2[count2-1], count2--;
    else if(count2 == 0)
	tri2[count2++] = tri1[count1-1], count1--;


    Child1 = new BoxTreeNode;
    //cout << " debug\n";
    //cout << count1 << " count1\n";
    Child1->Construct(count1, tri1);
    delete []tri1;

    Child2 = new BoxTreeNode;
    //cout << " debug\n";
    //cout << count2 << " count2\n";
    Child2->Construct(count2, tri2);
    delete []tri2;
}
