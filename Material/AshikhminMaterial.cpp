#include <Material/AshikhminMaterial.h>

AshikhminMaterial::AshikhminMaterial(){}
AshikhminMaterial::~AshikhminMaterial(){}
void AshikhminMaterial::GenerateSample(Color &col, Vector3 &in, const Vector3 &out, const Intersection &hit){}

void AshikhminMaterial::ComputeReflectance(Color &col, const Vector3 &in, const Vector3 &out, const Intersection &hit)
{
    Color total = Color::BLACK, SpecularComponent, DiffuseComponent;

    ComputeDiffuse(DiffuseComponent, in, out, hit);
    ComputeDiffuse(SpecularComponent, in, out, hit);
    total.Add(DiffuseComponent);
    total.Add(SpecularComponent);

    col.Multiply(total);
}
void AshikhminMaterial::SetSpecularLevel(float sl)
{
    SpecularLevel = sl;
}

void AshikhminMaterial::SetSpecularColor(Color c)
{
    SpecularColor = c;
}

void AshikhminMaterial::SetDiffuseLevel(float dl)
{
    DiffuseLevel = dl;
}
void AshikhminMaterial::SetDiffuseColor(Color c)
{
    DiffuseColor = c;
}

void AshikhminMaterial::SetRoughness(float u, float v)
{
    RoughnessU = u;
    RoughnessV = v;
}

void AshikhminMaterial::ComputeSpecular(Color &col, const Vector3 &in, const Vector3 &out, const Intersection &hit)
{
    Vector3 H = in + out;
    H.Normalize();

    float nDotk1 = hit.Normal.Dot(in);
    float nDotk2 = hit.Normal.Dot(out);

    float hDotn = H.Dot(hit.Normal);
    float hDotk = H.Dot(in);
    float hDotu = H.Dot(hit.TangentU);
    float hDotv = H.Dot(hit.TangentV);

    float exponent = (RoughnessU * pow(hDotu,2) + RoughnessV * pow(hDotv,2)) / (1 - pow(hDotn,2));

    float numinator = sqrt((RoughnessV + 1) * (RoughnessV + 1)) * pow(hDotn, exponent);
    float denominator = 8 * PI * hDotk * Max(nDotk2, nDotk1);

    float coeff = SpecularLevel + (1 - SpecularLevel) * (1 - pow(hDotk, 5));

    col = SpecularColor;
    col.Scale(coeff * numinator / denominator);
}
void AshikhminMaterial::ComputeDiffuse(Color &col, const Vector3 &in, const Vector3 &out, const Intersection &hit)
{
    float nDotk1 = hit.Normal.Dot(in);
    float nDotk2 = hit.Normal.Dot(out);

    float right = (1 - pow(1 - nDotk1 / 2, 5)) * (1 - pow(1 - nDotk2 / 2, 5)) * (1 - SpecularLevel); 
    float coeff = right * DiffuseLevel * 28 / 23 / PI;

    col = DiffuseColor;
    col.Scale(coeff);
}
