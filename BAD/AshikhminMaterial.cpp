#include <Material/AshikhminMaterial.h>
#include "p.h"

AshikhminMaterial::AshikhminMaterial(){}
AshikhminMaterial::~AshikhminMaterial(){}
void AshikhminMaterial::GenerateSample(Color &col, Vector3 &in, const Vector3 &out, const Intersection &hit)
{
    float costheta, phi, sintheta, epsilon1, epsilon2, epsilon3, exponent, r;

    Matrix34 coordinateSpace;
    coordinateSpace.a = hit.TangentU;
    coordinateSpace.b = hit.Normal;
    coordinateSpace.c = hit.TangentV;
    coordinateSpace.d = Vector3(0.0f, 0.0f, 0.0f);

    
    r = Rand1();
    if (r < SpecularLevel) {
	    
	    Color newColor = SpecularColor;
	    col = newColor;

	    // Anisotropic problem where dark in places it shouldn't be
	    epsilon1 = Rand1();
	    phi = atan(sqrt((RoughnessU + 1) / (RoughnessV + 1)) * tan(PI * epsilon1 / 2.0));

	    epsilon2 = Rand1();
	    exponent = 1.0 / ((RoughnessU * cos(phi) * cos(phi)) + (RoughnessV * sin(phi) * sin(phi)) + 1.0);
	    costheta = pow((1 - epsilon2), exponent);
	    sintheta = sqrt(1 - costheta*costheta);

	    epsilon3 = Rand1();
	    Vector3 h, inH = Vector3(sintheta * cos(phi), costheta, sintheta * sin(phi));
	    inH.Normalize(); //just in case...
	    if (epsilon3 < 0.5) h.x = h.x * -1.0;
	    if ((0.0 <= epsilon3 && epsilon3 <= 0.25) || (0.5 <= epsilon3 && epsilon3 <= 0.75)) h.z = h.z * -1.0;

	    //orient the h vector into the surface coordinate space:
	    coordinateSpace.Transform3x3(inH, h); // transform the vector

	    //create reflection vector
	    in = -in + (2 * (in).Dot(h) * h);
	    if (in.Dot(hit.Normal) < 0.0f) col = Color::BLACK; //check if valid in
	    
    }
    else {
	    col = DiffuseColor; //.AddScaled(DiffuseColor, cos(asin(inCrossN.Magnitude() / (in.Magnitude() * hit.Normal.Magnitude()))));

	    //perform hemisphere in
	    float s, t, u, v;
	    Vector3 preTrans;
	    s = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	    u = 2.0f * PI * s;
	    t = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	    v = sqrt(1.0 - t);

	    preTrans.x = v * cos(u);
	    preTrans.y = sqrt(t);
	    preTrans.z = v * sin(u);

	    //orient the h vector into the surface coordinate space:
	    coordinateSpace.Transform3x3(preTrans, in);
    }
	
}

void AshikhminMaterial::ComputeReflectance(Color &col, const Vector3 &in, const Vector3 &out, const Intersection &hit)
{
    Color total = Color::BLACK, SpecularComponent, DiffuseComponent;

    ComputeDiffuse(DiffuseComponent, in, out, hit);
    ComputeSpecular(SpecularComponent, in, out, hit);
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

    float right = (1 - pow(1 - nDotk1 / 2.0f, 5.0f)) * (1 - pow(1 - nDotk2 / 2.0f, 5.0f)) * (1 - SpecularLevel); 
    float coeff = right * DiffuseLevel * 28.0f / 23 / PI;

    col = DiffuseColor;
    col.Scale(coeff);
}
