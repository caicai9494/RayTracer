#include <Material/LambertMaterial.h>
#include "p.h"

LambertMaterial::LambertMaterial(){}
LambertMaterial::~LambertMaterial(){}

void LambertMaterial::GenerateSample(Color &col, Vector3 &in, const Vector3 &out, const Intersection &hit)
{
    float s, t, u, v;
    s = Rand1();
    t = Rand1();
    u = 2*PI*s;
    v = sqrt(1 - t);

    Vector3 trans;
    trans.x = v * cosf(u);
    trans.y = sqrt(t);
    trans.z = v * sinf(u);

    Matrix34 coordinate;
    coordinate.a = hit.TangentU;
    coordinate.b = hit.Normal;
    coordinate.c = hit.TangentV;
    coordinate.d = Vector3::ORIGIN;

    coordinate.Transform3x3(trans, in);
}

void LambertMaterial::ComputeReflectance(Color &col, const Vector3 &in, const Vector3 &out, const Intersection &hit) 
{
    col.Multiply(Color(DiffuseColor.GetIntVector() * 1.0f / PI));
}

void LambertMaterial::SetDiffuseColor(Color color)
{
    DiffuseColor = color;
}
