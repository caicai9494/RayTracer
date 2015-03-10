////////////////////////////////////////
// DirectLight.h
////////////////////////////////////////

#ifndef CSE168_DIRECTLIGHT_H
#define CSE168_DIRECTLIGHT_H

#include <Light/Light.h>

class DirectLight : public Light
{
    public:
	DirectLight(){}

	void SetDirection(const Vector3 &v)
	{
	    Direction = v;
	    Direction.Normalize();
	}

	float Illuminate(const Vector3 &pos, Color &col, Vector3 &toLight, Vector3 &ltPos)
	{
	    toLight = -Direction;
	    col = BaseColor;
	    ltPos = pos - 1000000.0 * Direction;
	    return Intensity;
	}

    private:
	Vector3 Direction;
};

#endif
