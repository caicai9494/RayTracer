////////////////////////////////////////
// LambertMaterial.h
////////////////////////////////////////

#ifndef CSE168_LAMBERTMATERIAL_H
#define CSE168_LAMBERTMATERIAL_H

#include <Material/Material.h>
#include <Core/Matrix34.h>

////////////////////////////////////////////////////////////////////////////////

class LambertMaterial:public Material {
public:

    LambertMaterial();
    ~LambertMaterial();
    void ComputeReflectance(Color &col, const Vector3 &in, const Vector3 &out, const Intersection &hit);
    void GenerateSample(Color &col, Vector3 &in, const Vector3 &out, const Intersection &hit);
    void SetDiffuseColor(Color color);

private:
	Color DiffuseColor;
};

////////////////////////////////////////////////////////////////////////////////

#endif
