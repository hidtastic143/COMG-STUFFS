#ifndef ASSIGNMENT_1_H
#define ASSIGNMENT_1_H

#include "Scene.h"

class Assignment1 : public Scene
{
	enum GEOMETRY_TYPE
	{
		DEATH_STAR = 0, //Works as circle
		STAR_DESTROYER,
		OVAL,
		TIE,
		ATIE, //Works as square or rectangle
		STAR,
		XWING,
		LASER,
		EXPLOSION,

		NUM_GEOMETRY,
	};

	enum UNIFORM_TYPE
	{
		U_MVP = 0,

		U_TOTAL,
	};

private:
	unsigned m_vertexArrayID;
	unsigned m_vertexBuffer[NUM_GEOMETRY];
	unsigned m_colorBuffer[NUM_GEOMETRY];
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

public:
	Assignment1();
	~Assignment1();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
	void Death_Star();
	void Star_Destroyer();
	void Oval();
	void Tie();
	void ATie();
	void Star();
	void XWing();
	void Laser();
	void Explosion();


	bool Spacebarr = false;
	bool DistanceStuffs = false;
	bool Spacebarr2 = false;
	bool Spacebarr3 = false;
	bool Boom = false;
	bool Boom2 = false;

	float DSangle = 30.f;
	float XwingX1 = 40.f;
	float XwingX2 = 45.f;
	float TieX = -43.f;
	float ATieX = -38.f;
	float StarDX = -38.f;
	float StarDRX = -44.f;
	float StarDCX = -51.f;
	float OvalX = 38.f;
	float BlasterX = 22.f;
	float BlasterNX = -22.5f;

	float LaserSD1 = -50.f;
	float LaserSD2 = -24.f;

	float LaserOval1 = 42.f;
	float LaserOval2 = 23.6f;

	float LaserAT = ATieX;
	float LaserT = TieX;
	float LaserX1 = XwingX1 + 0.5f;
	float LaserX2 = XwingX2 + 0.5f;

	float SExplosion = 0.05f;
	float SExplosion1 = 0.05f;

	float distanceS = XwingX1;
	float distanceD = 0.f;
	float distanceT = 0.f;
};

#endif