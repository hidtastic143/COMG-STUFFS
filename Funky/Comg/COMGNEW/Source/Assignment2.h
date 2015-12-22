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
		GEO_LIGHTBALL,

		GEO_HEAD,
		GEO_NOSE,
		GEO_MOUSTACHE1,
		GEO_MOUSTACHE2,
		GEO_MOUSTACHE3,
		GEO_MOUSTACHE4,
		GEO_EYES,
		GEO_EYELINER,
		GEO_BODY,
		GEO_SHIRT,
		GEO_HAT1,
		GEO_HAT_W,
		GEO_SHOULDER,
		GEO_UPARMS,
		GEO_LOWARMS,
		GEO_HAND,
		GEO_LEG,
		GEO_KNEE,
		GEO_DUMMY_HEAD,
		GEO_DUMMY_BODY,
		GEO_DUMMY_POLE,
		GEO_HAMMER_HANDLE,
		GEO_HAMMER_HEAD,

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
	bool fall = false;
	bool hammerTime = false;
	bool resetTime = false;
	bool posReady = false;
	bool spin = false;
	bool posReady1 = false;
	bool walk = false;
	bool jump = false;
	bool reset = false;
	bool stop = false;
	bool walkie = false;
	bool enablelight = true;

	float transBodyX = 0.f;
	float transBodyY = 7.f;
	float transBodyZ = 0.f;

	float DUMMYROTATE = 0.f;
	float bodyRotate = 0.f;
	float RshoulderRotateX = 0.f;
	float RshoulderRotateY = 0.f;
	float RshoulderRotateZ = 0.f;
	float LshoulderRotateX = 0.f;
	float LshoulderRotateY = 0.f;
	float LshoulderRotateZ = 0.f;
	float LlegRotateX = 0.f;
	float RlegRotateX = 0.f;
	float rotateHandX = 0.f;
	float rotateHandY = 0.f;
	float rotateHandZ = 0.f;

	float scaleXZ = 0.1f;
	float scaleY = 0.1f;
	float hammerSXZ = 0.1f;
	float hammerSY = 0.1f;
	float hammerHeadY = 0.f;
	float hammerHeadZ = 0.f;

	float timer = 0.f;
	float LSPEED = 10.f;

	Camera2 camera;
	Light light[1];
};

#endif