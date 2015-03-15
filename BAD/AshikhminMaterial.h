////////////////////////////////////////
// AshikhminMaterial.h
////////////////////////////////////////

#ifndef CSE168_ASHIKHMINMATERIAL_H
#define CSE168_ASHIKHMINMATERIAL_H

#include <Material/Material.h>
#include <Core/Matrix34.h>

////////////////////////////////////////////////////////////////////////////////

class AshikhminMaterial:public Material {
public:

    AshikhminMaterial();
    ~AshikhminMaterial();
    void GenerateSample(Color &col, Vector3 &in, const Vector3 &out, const Intersection &hit);
    void ComputeReflectance(Color &col, const Vector3 &in, const Vector3 &out, const Intersection &hit);

    void SetSpecularLevel(float sl);
    void SetSpecularColor(Color c);

    void SetDiffuseLevel(float dl);
    void SetDiffuseColor(Color c);

    void SetRoughness(float u, float v);

private:
    Color DiffuseColor, SpecularColor;
    float DiffuseLevel, SpecularLevel;
    float RoughnessU, RoughnessV;


    void ComputeDiffuse(Color &col, const Vector3 &in, const Vector3 &out, const Intersection &hit);
    void ComputeSpecular(Color &col, const Vector3 &in, const Vector3 &out, const Intersection &hit);
};

////////////////////////////////////////////////////////////////////////////////

#endif
