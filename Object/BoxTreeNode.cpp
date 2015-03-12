#include <Object/BoxTreeNode.h>
#include <iostream>
using namespace std;

BoxTreeNode::~BoxTreeNode(){}
BoxTreeNode::BoxTreeNode(): Child1(0), Child2(0), NumTriangles(0)
{
}

bool BoxTreeNode::IntersectVolume(const Ray &ray, float &t)const 
{
    Vector3 t1, t2;
    t1 = BoxMin - ray.Origin;
    t2 = BoxMax - ray.Origin;

    t1.x /= ray.Direction.x;
    t1.y /= ray.Direction.y;
    t1.z /= ray.Direction.z;

    t2.x /= ray.Direction.x;
    t2.y /= ray.Direction.y;
    t2.z /= ray.Direction.z;

    float tmin = Max((Min(t1.x, t2.x), Min(t1.y, t2.y)), Min(t1.z, t2.z));
    float tmax = Min((Max(t1.x, t2.x), Max(t1.y, t2.y)), Max(t1.z, t2.z));

    if(tmin < RAYOFFSET) 
	return false;
    if(tmin <= tmax)
    {
	t = tmin;
	//cout << t << endl;
	return true;
    }

    return false;
}

bool BoxTreeNode::Intersect(const Ray &ray, Intersection &hit)const 
{
	//cout << NumTriangles<<" debug\n";
    if(IsLeaf() && NumTriangles < MaxTrianglesPerBox && NumTriangles > 0)
    {
	bool success = false;
	for(int i = 0; i < NumTriangles; i++)
	    success = Tri[i]->Intersect(ray, hit);
	return success;
    }

    if(Child1 == 0 && Child2 == 0)
	return false;

    float volhit[2];
    bool isHit1 = false, isHit2 = false;
    if(Child1 != 0)
        isHit1 = Child1->IntersectVolume(ray, volhit[0]);
    
    if(Child2 != 0)
        isHit2 = Child2->IntersectVolume(ray, volhit[1]);

    /*
    bool success = false;
    if(isHit2 && isHit1)
    {
	if(volhit[0].HitDistance < volhit[1].HitDistance)
	    return Child1->Intersect(ray,hit) || Child2->Intersect(ray,hit);
	else 
	    return Child2->Intersect(ray,hit) || Child1->Intersect(ray,hit);
    }
    else if(isHit1)
	success = Child1->Intersect(ray, hit);
    else if(isHit2)
	success = Child2->Intersect(ray, hit);

    return success;
    */


    if(!isHit1 && !isHit2)
	return false;

    else if(isHit1 && !isHit2)
	return Child1->Intersect(ray, hit);

    else if(isHit2 && !isHit1)
	return Child2->Intersect(ray, hit);
    else
    {
	if(volhit[0] < volhit[1])
	{
	    if(Child1->Intersect(ray, hit))
	    {
		if(hit.HitDistance > volhit[1])
		    Child2->Intersect(ray, hit);
		return true;
	    }
	    else return Child2->Intersect(ray, hit);
	}
	else //if(volhit[1].HitDistance < volhit[0].HitDistance)
	{
	    if(Child2->Intersect(ray, hit))
	    {
		if(hit.HitDistance > volhit[0])
		    Child1->Intersect(ray, hit);
		return true;
	    }
	    else return Child1->Intersect(ray, hit);
	}
    }

    //bool success = false;
}
int BoxTreeNode::GetNumTriangles()
{
    return NumTriangles;
}
bool BoxTreeNode::IsLeaf() const
{
    return NumTriangles > 0;
}
void BoxTreeNode::FindBoxLimit(int count, Triangle** tri)
{
    BoxMax.x = BoxMin.x = tri[0]->Vtx[0]->Position.x;
    BoxMax.y = BoxMin.y = tri[0]->Vtx[0]->Position.y;
    BoxMax.z = BoxMin.z = tri[0]->Vtx[0]->Position.z;

    for(int i = 1; i < count; i++)
    {
	Triangle *triangle = tri[i];
	for(int j = 0; j < 3; j++)
	{
	    for(int k = 0; k < 3; k++)
	    {
		BoxMax[k] = Max(BoxMax[k], triangle->Vtx[j]->Position[k]);
		BoxMin[k] = Min(BoxMin[k], triangle->Vtx[j]->Position[k]);
	    }
	}
    }

   // return Vector3(xmax - xmin, ymax - ymin, zmax - zmin);
}

void BoxTreeNode::Construct(int count, Triangle** tri)
{
    FindBoxLimit(count, tri);
    //Vector3 BoxSize;
    //BoxSize = FindBoxLimit(count, tri);

    // copy tri array
    if(count < MaxTrianglesPerBox)
    {
	NumTriangles = count;
	for(int i = 0; i < count; i++)
	    Tri[i] = tri[i];
	return;
    }

    Vector3 BoxCenter, SplitPlaneNormal, BoxSize;
    BoxCenter = (BoxMin + BoxMax) / 2;
    BoxSize = BoxMax - BoxMin;
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
	Vector3 Center = triangle->ComputeCenter();

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
    /*
    if(count1 == 0)
	for(int i = 0; i < MaxTrianglesPerBox/2; i++)
	    tri1[count1++] = tri2[count2-1-i], count2--;
    else if(count2 == 0)
	for(int i = 0; i < MaxTrianglesPerBox/2; i++)
	    tri2[count2++] = tri1[count1-1-i], count1--;
	    */


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
