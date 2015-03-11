#include <Object/SphereObject.h>

SphereObject::SphereObject(){}
SphereObject::~SphereObject(){}

void SphereObject::SetRadius(float r)
{
    Radius = r;
}
void SphereObject::SetCenter(const Vector3 &c)
{
    Center = c;
}

bool SphereObject::Intersect(const Ray &ray,Intersection &hit)const
{
    float t;
    Vector3 P,D;
    P = ray.Origin;
    D = ray.Direction;
    t = Center.Dot(D) - P.Dot(D);

    if(t < 0 || t >= hit.HitDistance)
	return false;

    Vector3 Q;
    Q = P + D * t;

    if(Q.Distance(Center) > Radius)
	return false;

    hit.HitDistance = t;
    hit.Position = P + t * D;
    hit.Normal = hit.Position - Center;
    hit.Normal.Normalize();

    return true;
}

