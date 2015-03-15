#include <Material/LambertMaterial.h>

LambertMaterial::LambertMaterial(){}
LambertMaterial::~LambertMaterial(){}

void LambertMaterial::GenerateSample(Color &col, Vector3 &in, const Vector3 &out, const Intersection &hit)
{
}

void LambertMaterial::ComputeReflectance(Color &col, const Vector3 &in, const Vector3 &out, const Intersection &hit) 
{
    //col = DiffuseColor;
    //col.Multiply(DiffuseColor);
    //col.Scale(1.0f/PI);
    col = DiffuseColor;
    col.Scale(1.0f/PI);
}

void LambertMaterial::SetColor(const Color& color)
{
    DiffuseColor = color;
}
