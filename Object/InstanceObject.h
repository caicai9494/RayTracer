////////////////////////////////////////
// InstanceObject.h
////////////////////////////////////////

#ifndef CSE168_INSTANCEOBJECT_H
#define CSE168_INSTANCEOBJECT_H

#include <Camera/Ray.h>
#include <Camera/Intersection.h>
#include <Object/Object.h>
#include <Core/Matrix34.h>

class InstanceObject: public Object
{
    public:
	InstanceObject(Object &obj);

	bool Intersect(const Ray &ray, Intersection &hit);
	void SetChild(Object &obj);
	void SetMatrix(const Matrix34 &mtx);
	void SetMaterial(Material *mtl);

    private:
	Object *child;
	Matrix34 Matrix;
	Matrix34 InverseMatrix;
	Material *Mtl;
};


#endif
