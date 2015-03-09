#include <Object/InstanceObject.h>


InstanceObject::InstanceObject(Object &obj)
{
    child = &obj;
}

void InstanceObject::SetChild(Object &obj)
{
    child = &obj;
}
void InstanceObject::SetMatrix(const Matrix34 &mtx)
{
    Matrix = mtx;

    InverseMatrix = mtx;
    InverseMatrix.Inverse();
}

bool InstanceObject::Intersect(const Ray &ray, Intersection &hit) const
{
    Ray ray2;
    InverseMatrix.Transform(ray.Origin, ray2.Origin);
    InverseMatrix.Transform3x3(ray.Direction, ray2.Direction);

    if(!child->Intersect(ray2, hit))
	return false;

    Matrix.Transform(hit.Position, hit.Position);
    Matrix.Transform3x3(hit.Normal, hit.Normal);
    hit.HitDistance = ray.Origin.Distance(hit.Position);

    return true;
}