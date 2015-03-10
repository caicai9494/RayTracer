#include "Triangle.h"

static const double IGNORE = 1E-5;

Triangle::Triangle()
{
    Vtx[0] = 0;
    Vtx[1] = 0;
    Vtx[2] = 0;

    Mtl = 0;
}

bool Triangle::Intersect(const Ray &ray, Intersection &hit) 
{
    float t, alpha, beta, D;
    Vertex *a, *b, *c;
    Vector3 p, d; 
    Vector3 b_axc_a, p_axc_a, b_axp_a;
    Vector3 b_a, c_a, p_a;

    a = Vtx[0];
    b = Vtx[1];
    c = Vtx[2];

    p = ray.Origin;
    d = ray.Direction;

    b_a = b->Position - a->Position;
    c_a = c->Position - a->Position;
    p_a = p - a->Position;

    b_axc_a.Cross(b_a, c_a);

    D = -d.Dot(b_axc_a);
    
    if(D == 0.0) return false;

    p = ray.Origin;
    t = (p - a->Position).Dot(b_axc_a) / D;
    if(t < 0 || t > hit.HitDistance)
	return false;

    p_axc_a.Cross(p_a , c_a);
    alpha = -d.Dot(p_axc_a) / D;
    if(alpha < 0 || alpha > 1) 
	return false;

    b_axp_a.Cross(b_a, p_a);
    beta = -d.Dot(b_axp_a) / D;
    if(beta < 0 || beta > 1 || alpha + beta > 1) 
	return false;

    hit.Position = a->Position + t * ray.Direction;
    hit.HitDistance = t;
    hit.Mtl = Mtl;
    
    hit.Normal = (1 - beta - alpha) * a->Normal + 
		 alpha * b->Normal + 
		 beta * c->Normal;
    hit.Normal.Normalize();
    return true;

}
