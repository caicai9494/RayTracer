#include "Triangle.h"

Triangle::Triangle()
{
    Vtx[0] = 0;
    Vtx[1] = 0;
    Vtx[2] = 0;

    Mtl = 0;
}

bool Triangle::Intersect(const Ray &ray, Intersection &hit) const
{

    float t, alpha, beta, D;
    Vertex *a, *b, *c;
    Vector3 p, d; 
    Vector3 b_axc_a, p_axc_a, b_axp_a;
    Vector3 b_a, c_a, p_a;

    a = Vtx[0];
    b = Vtx[1];
    c = Vtx[2];

    d = ray.Direction;
    b_a = b->Position - a->Position;
    c_a = c->Position - a->Position;
    p_a = p - a->Position;

    b_axc_a.Cross(b_a, c_a);

    D = -d.Dot(b_axc_a);

    if(abs(D) > 0)
    {
	p = ray.Origin;
	t = (p - a->Position).Dot(b_axc_a) / D;

	p_axc_a.Cross(p_a , c_a);
	alpha = -d.Dot(p_axc_a) / D;

	b_axp_a.Cross(b_a, p_a);
	beta = -d.Dot(b_axp_a) / D;

	if(alpha > 0 && beta > 0 && alpha + beta < 1 && t > 0)
	{
	    hit.Position = a->Position + alpha * b_a + beta * c_a;
	    hit.HitDistance = ray.Origin.Distance(hit.Position);
	    hit.Normal = b_axc_a;
	    hit.Normal.Normalize();

	    return true;
	}
	else 
	    return false;
    }

    return false;
}
