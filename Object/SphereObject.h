////////////////////////////////////////
// SphereObject.h
////////////////////////////////////////

#ifndef CSE168_SPHEREOBJECT_H
#define CSE168_SPHEREOBJECT_H

#include <Object/Object.h>
#include <Material/LambertMaterial.h>
#include <Core/Matrix34.h>

////////////////////////////////////////////////////////////////////////////////
//
class SphereObject:public Object {
public:
	SphereObject();
	~SphereObject();

	bool Intersect(const Ray &ray,Intersection &hit)const;

	void SetRadius(float r);
	void SetCenter(const Vector3 &c);

private:
	Vector3 Center;
	float Radius;
};

////////////////////////////////////////////////////////////////////////////////

#endif
