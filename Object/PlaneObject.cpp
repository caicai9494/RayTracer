#include <Object/PlaneObject.h>


PlaneObject::PlaneObject(): Normal(Vector3::YAXIS), Point(Vector3::ORIGIN){}
PlaneObject::~PlaneObject(){}

bool PlaneObject::Intersect(const Ray &ray,Intersection &hit)const
{
    float denominator = Normal.Dot(ray.Direction);
    if(denominator == 0) return false;

    float t;
    t = (Normal.Dot(Point) - Normal.Dot(ray.Origin)) / denominator;
    if(t < RAYOFFSET || t >= hit.HitDistance) return false;

    hit.Normal = Normal;
    hit.HitDistance = t;
    hit.Position = ray.Origin + t * ray.Direction;
    return true;
}
