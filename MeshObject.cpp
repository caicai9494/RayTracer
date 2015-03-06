////////////////////////////////////////
// MeshObject.cpp
////////////////////////////////////////

#include "MeshObject.h"
#include "LambertMaterial.h"
#include "Matrix34.h"

////////////////////////////////////////////////////////////////////////////////

MeshObject::MeshObject() {
	NumVertexes=0;
	NumTriangles=0;

	Vertexes=0;
	Triangles=0;
}

////////////////////////////////////////////////////////////////////////////////

MeshObject::~MeshObject() {
	delete []Vertexes;
	delete []Triangles;
}

////////////////////////////////////////////////////////////////////////////////

bool MeshObject::Intersect(const Ray &ray, Intersection &hit) {
	bool success=false;
	for(int i=0;i<NumTriangles;i++)
		if(Triangles[i].Intersect(ray,hit)) success=true;
	if(true) hit.Obj=this;
	return success;
}

////////////////////////////////////////////////////////////////////////////////

void MeshObject::MakeBox(float x,float y,float z,Material *mtl) {
	// Allocate arrays
	NumVertexes=24;
	NumTriangles=12;
	Vertexes=new Vertex[NumVertexes];
	Triangles=new Triangle[NumTriangles];
	if(mtl==0) mtl=new LambertMaterial;

	x*=0.5f;
	y*=0.5f;
	z*=0.5f;

	// Corners
	Vector3 p000(-x,-y,-z);
	Vector3 p001(-x,-y,z);
	Vector3 p010(-x,y,-z);
	Vector3 p011(-x,y,z);
	Vector3 p100(x,-y,-z);
	Vector3 p101(x,-y,z);
	Vector3 p110(x,y,-z);
	Vector3 p111(x,y,z);

	// Tex coords
	Vector3 t00(0.0f,0.0f,0.0f);
	Vector3 t01(0.0f,1.0f,0.0f);
	Vector3 t10(1.0f,0.0f,0.0f);
	Vector3 t11(1.0f,1.0f,0.0f);

	// Right
	Vertexes[0].Set(p101,Vector3::XAXIS,t00);
	Vertexes[1].Set(p100,Vector3::XAXIS,t10);
	Vertexes[2].Set(p110,Vector3::XAXIS,t11);
	Vertexes[3].Set(p111,Vector3::XAXIS,t01);
	Triangles[0].Init(&Vertexes[0],&Vertexes[1],&Vertexes[2],mtl);
	Triangles[1].Init(&Vertexes[0],&Vertexes[2],&Vertexes[3],mtl);

	// Left
	Vertexes[4].Set(p000,-Vector3::XAXIS,t00);
	Vertexes[5].Set(p001,-Vector3::XAXIS,t10);
	Vertexes[6].Set(p011,-Vector3::XAXIS,t11);
	Vertexes[7].Set(p010,-Vector3::XAXIS,t01);
	Triangles[2].Init(&Vertexes[4],&Vertexes[5],&Vertexes[6],mtl);
	Triangles[3].Init(&Vertexes[4],&Vertexes[6],&Vertexes[7],mtl);

	// Top
	Vertexes[8].Set(p011,Vector3::YAXIS,t00);
	Vertexes[9].Set(p111,Vector3::YAXIS,t10);
	Vertexes[10].Set(p110,Vector3::YAXIS,t11);
	Vertexes[11].Set(p010,Vector3::YAXIS,t01);
	Triangles[4].Init(&Vertexes[8],&Vertexes[9],&Vertexes[10],mtl);
	Triangles[5].Init(&Vertexes[8],&Vertexes[10],&Vertexes[11],mtl);

	// Bottom
	Vertexes[12].Set(p000,-Vector3::YAXIS,t00);
	Vertexes[13].Set(p100,-Vector3::YAXIS,t10);
	Vertexes[14].Set(p101,-Vector3::YAXIS,t11);
	Vertexes[15].Set(p001,-Vector3::YAXIS,t01);
	Triangles[6].Init(&Vertexes[12],&Vertexes[13],&Vertexes[14],mtl);
	Triangles[7].Init(&Vertexes[12],&Vertexes[14],&Vertexes[15],mtl);

	// Front
	Vertexes[16].Set(p001,Vector3::ZAXIS,t00);
	Vertexes[17].Set(p101,Vector3::ZAXIS,t10);
	Vertexes[18].Set(p111,Vector3::ZAXIS,t11);
	Vertexes[19].Set(p011,Vector3::ZAXIS,t01);
	Triangles[8].Init(&Vertexes[16],&Vertexes[17],&Vertexes[18],mtl);
	Triangles[9].Init(&Vertexes[16],&Vertexes[18],&Vertexes[19],mtl);

	// Back
	Vertexes[20].Set(p100,-Vector3::ZAXIS,t00);
	Vertexes[21].Set(p000,-Vector3::ZAXIS,t10);
	Vertexes[22].Set(p010,-Vector3::ZAXIS,t11);
	Vertexes[23].Set(p110,-Vector3::ZAXIS,t01);
	Triangles[10].Init(&Vertexes[20],&Vertexes[21],&Vertexes[22],mtl);
	Triangles[11].Init(&Vertexes[20],&Vertexes[22],&Vertexes[23],mtl);
}

////////////////////////////////////////////////////////////////////////////////
