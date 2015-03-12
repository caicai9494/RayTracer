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
    Vector3 P,D;
    P = ray.Origin;
    D = ray.Direction;

    Vector3 ray_to_center;
    ray_to_center = Center - P;

    float q_dist;
    q_dist = ray_to_center.Dot(D);

    Vector3 Q;
    Q = P + q_dist * D;

    float q_to_center;
    q_to_center = Q.Distance(Center);
    if(q_to_center > Radius)
	return false;

    float hit_to_q;
    hit_to_q = sqrt(Radius * Radius - q_to_center * q_to_center);

    if(q_dist - hit_to_q >= 0)
    {
	    //Vector3 Q1;
	hit.HitDistance = q_dist - hit_to_q;
	hit.Position = P + hit.HitDistance * D;
	hit.Normal = (hit.Position - Center) / Radius;

	return true;
    }

    return false;
}

