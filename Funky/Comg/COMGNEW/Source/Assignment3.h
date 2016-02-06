#ifndef ASSIGNMENT3_H
#define ASSIGNMENT3_H

#include "Scene.h"
#include "Camera.h"
#include "Camera3.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"

class Assignment3 : public Scene
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
		GEO_LEFT,
		GEO_RIGHT,
		GEO_TOP,
		GEO_BOTTOM,
		GEO_FRONT,
		GEO_BACK,
		GEO_TEXT,
		GEO_TENT,
		GEO_SHELF,
		GEO_BEER,
		GEO_BEEER,
		GEO_DRINK,
		GEO_ICECREAM,
		GEO_ICECREAM1,
		GEO_ICECREAM2,
		GEO_KEG,
		GEO_FERRISWHEEL,
		GEO_CARRIAGE,
		GEO_INSTRUCTIONS,

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
		U_LIGHT0_TYPE,
		U_LIGHT0_SPOTDIRECTION,
		U_LIGHT0_COSCUTOFF,
		U_LIGHT0_COSINNER,
		U_LIGHT0_EXPONENT,

		U_LIGHT1_POSITION,
		U_LIGHT1_TYPE,
		U_LIGHT1_COLOR,
		U_LIGHT1_POWER,
		U_LIGHT1_KC,
		U_LIGHT1_KL,
		U_LIGHT1_KQ,
		U_LIGHT1_COSCUTOFF,
		U_LIGHT1_COSINNER,
		U_LIGHT1_EXPONENT,
		U_LIGHT1_SPOTDIRECTION,

		U_LIGHT2_POSITION,
		U_LIGHT2_TYPE,
		U_LIGHT2_COLOR,
		U_LIGHT2_POWER,
		U_LIGHT2_KC,
		U_LIGHT2_KL,
		U_LIGHT2_KQ,
		U_LIGHT2_COSCUTOFF,
		U_LIGHT2_COSINNER,
		U_LIGHT2_EXPONENT,
		U_LIGHT2_SPOTDIRECTION,

		U_LIGHT3_POSITION,
		U_LIGHT3_TYPE,
		U_LIGHT3_COLOR,
		U_LIGHT3_POWER,
		U_LIGHT3_KC,
		U_LIGHT3_KL,
		U_LIGHT3_KQ,
		U_LIGHT3_COSCUTOFF,
		U_LIGHT3_COSINNER,
		U_LIGHT3_EXPONENT,
		U_LIGHT3_SPOTDIRECTION,

		U_LIGHT4_POSITION,
		U_LIGHT4_TYPE,
		U_LIGHT4_COLOR,
		U_LIGHT4_POWER,
		U_LIGHT4_KC,
		U_LIGHT4_KL,
		U_LIGHT4_KQ,
		U_LIGHT4_COSCUTOFF,
		U_LIGHT4_COSINNER,
		U_LIGHT4_EXPONENT,
		U_LIGHT4_SPOTDIRECTION,
		U_NUMLIGHTS,

		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,
		U_TEXT_ENABLED,
		U_TEXT_COLOR,

		U_TOTAL,
	};
public:
	Assignment3();
	~Assignment3();

	bool takenDrink = false;
	bool takenBeer = false;
	bool holdBeer = false;
	bool drinkBeer = false;
	bool drunk = false;
	bool textDrunk = false;
	bool textDrank = false;
	bool textTaken = false;
	bool textRefill = false;
	bool textInstructions = true;
	bool dropItem = false;

	void initLight();
	void initFerrisWheel();
	void initBox();
	void initTent();
	void initShelf();
	void initBeer();
	void initDrink();
	void initIceCream();
	void initKeg();

	void RenderLight();
	void RenderFerrisWheel();
	void RenderBox();
	void RenderTent();
	void RenderShelf();
	void RenderBeer();
	void RenderDrink();
	void RenderIceCream();
	void RenderKeg();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	MS modelStack, viewStack, projectionStack;

private:
	void RenderMesh(Mesh *mesh, bool enableLight);
	void RenderSkybox();
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	unsigned m_vertexArrayID;
	Mesh *meshList[NUM_GEOMETRY];

	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	float lightPower = 0.f;
	float rotateAngle;
	float LSPEED = 10.f;
	float drank;
	double FPS = 0;

	Camera3 camera;
	Light light[5];
};

#endif