#include <Material/LambertMaterial.h>

LambertMaterial::LambertMaterial(){}
LambertMaterial::~LambertMaterial(){}

void LambertMaterial::ComputeReflectance(Color &col, const Vector3 &in, const Vector3 &out, const Intersection &hit) 
{
    col.Scale(DiffuseColor,1.0f/PI);
}

void LambertMaterial::SetColor(const Color& color)
{
    DiffuseColor = color;
}
