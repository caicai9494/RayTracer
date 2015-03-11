////////////////////////////////////////
// Main.cpp
////////////////////////////////////////

#include <Object/MeshObject.h>
#include <Object/PlaneObject.h>
#include <Object/SphereObject.h>
#include <Object/InstanceObject.h>
#include <Camera.h>
#include <Light/PointLight.h>
#include <Light/DirectLight.h>
#include <Scene.h>
#include <stdio.h>
#include <time.h>

void project1();
void Sphere();

////////////////////////////////////////////////////////////////////////////////

int main(int argc,char **argv) {

        srand(time(NULL));
	Sphere();
	return 0;
}

////////////////////////////////////////////////////////////////////////////////

void project1() {
	// Create scene
	Scene scn;
	scn.SetSkyColor(Color(0.8f, 0.9f, 1.0f));

	// Create boxes
	MeshObject box1;
	box1.MakeBox(5.0f,0.1f,5.0f);
	scn.AddObject(box1);

	MeshObject box2;
	box2.MakeBox(1.0f,1.0f,1.0f);

	InstanceObject inst1(box2);
	Matrix34 mtx;
	mtx.MakeRotateX(0.5f);
	mtx.d.y=1.0f;
	inst1.SetMatrix(mtx);
	scn.AddObject(inst1);

	InstanceObject inst2(box2);
	mtx.MakeRotateY(1.0f);
	mtx.d.Set(-1.0f,0.0f,1.0f);
	inst2.SetMatrix(mtx);
	scn.AddObject(inst2);

	// Create lights
	DirectLight sunlgt;
	sunlgt.SetBaseColor(Color(1.0f, 1.0f, 0.9f));
	sunlgt.SetIntensity(0.5f);
	sunlgt.SetDirection(Vector3(-0.5f, -1.0f, -0.5f));
	scn.AddLight(sunlgt);

	PointLight redlgt;
	redlgt.SetBaseColor(Color(1.0f, 0.2f, 0.2f));
	redlgt.SetIntensity(2.0f);
	redlgt.SetPosition(Vector3(2.0f, 2.0f, 0.0f));
	scn.AddLight(redlgt);

	// Create camera
	Camera cam;
	cam.LookAt(Vector3(2.0f,2.0f,5.0f),Vector3(0.0f,0.0f,0.0f));
	cam.SetResolution(800,600);
	cam.SetFOV(40.0f);
	cam.SetAspect(1.33f);

	// Render image
	cam.Render(scn);
	cam.SaveBitmap("project1.bmp");
}

////////////////////////////////////////////////////////////////////////////////

void Sphere()
{ 
    Scene scn;
    scn.SetSkyColor(Color(0.8f, 0.8f, 1.0f));
    // Create ground plane
    PlaneObject ground;
    scn.AddObject(ground);

    // Create spheres
    for(int i=0;i<10;i++) {
    SphereObject *sphere=new SphereObject;
    float rad=RangeRand(0.25f,0.5f);
    Vector3 pos(RangeRand(-0.0f,5.0f),rad,RangeRand(-0.0f,5.0f));
    sphere->SetRadius(rad);
    sphere->SetCenter(pos);
    scn.AddObject(*sphere);
    }

    // Create lights
    DirectLight sunlgt;
    sunlgt.SetBaseColor(Color(1.0f, 1.0f, 0.9f));
    
    sunlgt.SetIntensity(1.0f);
    sunlgt.SetDirection(Vector3(2.0f, -3.0f, -2.0f));
    scn.AddLight(sunlgt);

    // Create camera
    Camera cam;
    cam.LookAt(Vector3(-0.75f,0.25f,5.0f),Vector3(0.0f,0.5f,0.0f));
    cam.SetFOV(40.0f);
    cam.SetAspect(1.33f);
    cam.SetResolution(800,600);
    // Render image
    cam.Render(scn);
    cam.SaveBitmap("spheres.bmp");

}
