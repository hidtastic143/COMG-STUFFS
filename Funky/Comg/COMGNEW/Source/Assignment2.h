#ifndef ASSIGNMENT2_H
#define ASSIGNMENT2_H

#include "Scene.h"
#include "Camera.h"
#include "Camera2.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"

class Assignment2 : public Scene
{
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_QUAD,
		GEO_CUBE,
		GEO_CIRCLE,
		GEO_RING,
		GEO_SPHERE,
		GEO_HEMISPHERE,
		GEO_LIGHTBALL,

		GEO_BODY,
		GEO_SHOULDER,
		GEO_UPARMS,
		GEO_LOWARMS,
		GEO_ELBOW,
		GEO_LEG,
		GEO_KNEE,
		GEO_DUMMY_HEAD,
		GEO_DUMMY_BODY,
		GEO_DUMMY_POLE,

		NUM_GEOMETRY,
	};
	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,
		U_LIGHT0_POSITION,
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,
		U_LIGHTENABLED,
		U_TOTAL,
	};
public:
	Assignment2();
	~Assignment2();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	MS modelStack, viewStack, projectionStack;

private:
	void RenderMesh(Mesh *mesh, bool enableLight);
	unsigned m_vertexArrayID;
	Mesh *meshList[NUM_GEOMETRY];

	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	bool fightStance = false;
	bool ready = false;
	bool punch = false;
	bool enablelight = true;
	bool fall = false;
	

	float DUMMYROTATE = 0;
	float bodyRotate;
	float bodyx;
	float bodyz;
	float LshoulderRotate = -13.f;
	float RshoulderRotate = 13.f;


	float Rarmy = 0.f;

	float Lx = 0.f;
	float Rx = 0.f;
	float Ly = 0.f;
	float Ry = 0.f;
	float Lz = 1.f;
	float Rz = 1.f;

	float rotateAngle;
	float LSPEED = 10.f;

	Camera2 camera;
	Light light[1];
};

#endif