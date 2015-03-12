#include <Object/Triangle.h>

Triangle::Triangle()
{
    Vtx[0] = 0;
    Vtx[1] = 0;
    Vtx[2] = 0;

    Mtl = 0;
}

bool Triangle::Intersect(const Ray &ray, Intersection &hit) 
{
    Vector3 pa, pb, pc;
    pa = Vtx[0]->Position;
    pb = Vtx[1]->Position;
    pc = Vtx[2]->Position;

    Vector3 p, d;
    p = ray.Origin;
    d = ray.Direction;

    Vector3 b_a, c_a, p_a;
    b_a = pb - pa;
    c_a = pc - pa;
    p_a = p - pa;

    Vector3 b_axc_a;
    b_axc_a.Cross(b_a, c_a);

    float D;
    D = -d.Dot(b_axc_a);
    
    if(D == 0.0) return false;

    Vector3 p_axc_a;
    p_axc_a.Cross(p_a , c_a);
    float alpha;
    alpha = -d.Dot(p_axc_a) / D;
    if(alpha < 0 || alpha > 1) 
	return false;

    Vector3 b_axp_a;
    b_axp_a.Cross(b_a, p_a);
    float beta;
    beta = -d.Dot(b_axp_a) / D;
    if(beta < 0 || beta > 1 || alpha + beta > 1) 
	return false;

    float t;
    p = ray.Origin;
    t = (p - pa).Dot(b_axc_a) / D;
    if(t < RAYOFFSET || t >= hit.HitDistance)
	return false;

    hit.Position = p + t * ray.Direction;
    hit.HitDistance = t;
    hit.Mtl = Mtl;

    Vector3 na, nb, nc; 
    na = Vtx[0]->Normal;
    nb = Vtx[1]->Normal;
    nc = Vtx[2]->Normal;
    
    hit.Normal = (1 - beta - alpha) * na + 
		 alpha * nb + 
		 beta * nc;
    hit.Normal.Normalize();
    return true;

}

Vector3 Triangle::ComputeCenter()
{
    Vector3 a, b, c, b_a, c_a;
    float alpha = 0.5, beta = 0.5;

    a = Vtx[0]->Position;
    b = Vtx[1]->Position;
    c = Vtx[2]->Position;

    b_a = b - a;
    c_a = c - a;

    return a + alpha * b_a + beta * c_a;
}
