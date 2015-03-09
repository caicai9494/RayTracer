////////////////////////////////////////
// DirectLight.h
////////////////////////////////////////

#ifndef CSE168_DIRECTLIGHT_H
#define CSE168_DIRECTLIGHT_H

#include "Light.h"

class DirectLight : public Light
{
    public:
	DirectLight(){}

	void SetDirection(const Vector3 &v)
	{
	    DirectLight = v;
	}

	float Illuminate(const Vector3 &pos, Color &col, Vector3 &toLight, Vector3 &ltPos)
	{
	    toLight = -Direction;
	    col = BaseColor;
	    ltpos = pos - 1000000.0 * Direction;
	    return Intensity;
	}

    private:
	Vector3 Direction;
};
