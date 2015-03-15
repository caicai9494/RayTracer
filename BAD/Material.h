////////////////////////////////////////
// Material.h
////////////////////////////////////////

#ifndef CSE168_MATERIAL_H
#define CSE168_MATERIAL_H

#include <Camera/Intersection.h>

////////////////////////////////////////////////////////////////////////////////

class Intersection;

class Material {
public:
	virtual void ComputeReflectance(Color &col, const Vector3 &in, const Vector3 &out, const Intersection &hit)=0;
	virtual void GenerateSample(Color &col, Vector3 &in, const Vector3 &out, const Intersection &hit)=0;
};

////////////////////////////////////////////////////////////////////////////////

#endif
