#include "Assignment1.h"
#include "GL\glew.h"
#include "Mtx44.h"
#include "Application.h"
#include "shader.hpp"

Assignment1::Assignment1()
{

}

Assignment1::~Assignment1()
{

}

void Assignment1::Init()
{
	// Set background color to black
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// Init VBO here

	glEnable(GL_DEPTH_TEST);

	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	// Generate buffers
	glGenBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glGenBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);

	Death_Star();
	Star_Destroyer();
	Oval();
	Tie();

	ATie();
	Star();
	XWing();
	Laser();
	Explosion();

	//Load vertex and fragment shaders
	m_programID = LoadShaders(
		"Shader//TransformVertexShader.vertexshader",
		"Shader//SimpleFragmentShader.fragmentshader");

	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");

	//Use our shader
	glUseProgram(m_programID);
}

void Assignment1::Death_Star() //Works as a grey circle
{
	static const GLfloat DeathStar_data[] = {
		-0.2f, -0.2f, 0.0f,
		-0.16f, -0.25f, 0.0f,
		-0.1f, -0.28f, 0.0f,
		0.0f, -0.3f, 0.0f,//First
		0.1f, -0.27f, 0.0f,
		0.2f, -0.2f, 0.0f,//Second
		0.25f, -0.14f, 0.0f,
		0.3f, 0.0f, 0.0f,//Last
		0.29f, 0.1f, 0.0f,
		0.26f, 0.17f, 0.0f,
		0.23f, 0.21f, 0.0f,
		0.18f, 0.25f, 0.0f,
	}; // 8 Vertices

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[DEATH_STAR]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(DeathStar_data), DeathStar_data, GL_STATIC_DRAW);

	static const GLfloat DeathStar_color_data[] = {
		0.4f, 0.4f, 0.4f,
		0.4f, 0.4f, 0.4f,
		0.4f, 0.4f, 0.4f,
		0.502f, 0.502f, 0.502f,
		0.502f, 0.502f, 0.502f,
		0.502f, 0.502f, 0.502f,
		0.502f, 0.502f, 0.502f,
		0.502f, 0.502f, 0.502f,
		0.502f, 0.502f, 0.502f,
		0.502f, 0.502f, 0.502f,
		0.502f, 0.502f, 0.502f,
		0.4f, 0.4f, 0.4f,
		0.4f, 0.4f, 0.4f,
		0.4f, 0.4f, 0.4f,
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[DEATH_STAR]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(DeathStar_color_data), DeathStar_color_data, GL_STATIC_DRAW);

	//can be used to draw circle
}

void Assignment1::Star_Destroyer()
{
	static const GLfloat StarDestroyer_data[] = {
		-1.2f, 0.3f, 0.0f, //Top Booster
		-1.2f, -0.05f, 0.0f, // Bottom Booster
		1.0f, 0.0f, 0.0f, //Bottom Right
		1.0f, 0.1f, 0.0f, //Above Bottom Right
		-0.55f, 0.3f, 0.0f, 
		-0.55f, 0.35f, 0.0f, //First layer top right
		-0.6f, 0.35f, 0.0f, //Move left a bit
		-0.6f, 0.4f, 0.0f, //Move up (second layer top right)
		-0.85f, 0.4f, 0.0f, //Move Left a bit
		-0.85f, 0.6f, 0.0f, //Move up
		-0.7f, 0.6f, 0.0f,
		-0.7f, 0.65f, 0.0f,
		-1.1f, 0.65f, 0.0f,
		-1.0f, 0.35f, 0.0f,
		-1.0f, 0.2f, 0.0f,
	}; //15 Vertices

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[STAR_DESTROYER]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(StarDestroyer_data), StarDestroyer_data, GL_STATIC_DRAW);

	static const GLfloat StarDestroyer_color_data[] = {
		0.4f, 0.4f, 0.4f,
		0.4f, 0.4f, 0.4f,
		0.4f, 0.4f, 0.4f,
		0.4f, 0.4f, 0.4f,
		0.4f, 0.4f, 0.4f,
		0.4f, 0.4f, 0.4f,
		0.4f, 0.4f, 0.4f,
		0.4f, 0.4f, 0.4f,
		0.4f, 0.4f, 0.4f,
		0.4f, 0.4f, 0.4f,
		0.4f, 0.4f, 0.4f,
		0.4f, 0.4f, 0.4f,
		0.4f, 0.4f, 0.4f,
		0.4f, 0.4f, 0.4f,
		0.4f, 0.4f, 0.4f,
		0.4f, 0.4f, 0.4f,
		0.4f, 0.4f, 0.4f,
		0.4f, 0.4f, 0.4f,
		0.4f, 0.4f, 0.4f,
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[STAR_DESTROYER]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(StarDestroyer_color_data), StarDestroyer_color_data, GL_STATIC_DRAW);
}

void Assignment1::Oval()
{
	static const GLfloat Oval_data[] = {
		0.0f, 0.3f, 0.0f, // the top of oval
		-0.05f, 0.29f, 0.0f,
		-0.1f, 0.27f, 0.0f,
		-0.15f, 0.25f, 0.0f,
		-0.17f, 0.23f, 0.0f,
		-0.2f, 0.2f, 0.0f,
		-0.25f, 0.15f, 0.0f,
		-0.28f, 0.09f, 0.0f,

		-0.3f, 0.0f, 0.0f, // left of oval

		-0.28f, -0.09f, 0.0f,
		-0.25f, -0.15f, 0.0f,
		-0.2f, -0.2f, 0.0f,
		-0.17f, -0.23f, 0.0f,
		-0.15f, -0.25f, 0.0f,
		-0.1f, -0.27f, 0.0f,
		-0.05f, -0.29f, 0.0f,
		0.0f, -0.3f, 0.0f,// bottom of oval
	}; //17 Vertices

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[OVAL]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Oval_data), Oval_data, GL_STATIC_DRAW);

	static const GLfloat Oval_color_data[] = {
		0.4f, 0.4f, 0.4f,
		0.4f, 0.4f, 0.4f,
		0.4f, 0.4f, 0.4f,

		0.4f, 0.4f, 0.4f,
		0.4f, 0.4f, 0.4f,
		0.4f, 0.4f, 0.4f,

		0.4f, 0.4f, 0.4f,
		0.4f, 0.4f, 0.4f,
		0.4f, 0.4f, 0.4f,

		0.4f, 0.4f, 0.4f,
		0.4f, 0.4f, 0.4f,
		0.4f, 0.4f, 0.4f,

		0.4f, 0.4f, 0.4f,
		0.4f, 0.4f, 0.4f,
		0.4f, 0.4f, 0.4f,

		0.4f, 0.4f, 0.4f,
		0.4f, 0.4f, 0.4f,
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[OVAL]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Oval_color_data), Oval_color_data, GL_STATIC_DRAW);

}

void Assignment1::Tie()
{
	static const GLfloat Tie_data[] = {
		-0.05f, 0.24f, 0.0f,
		-0.1f, 0.12f, 0.0f,
		-0.05f, 0.0f, 0.0f,

		0.05f, 0.0f, 0.0f,
		0.1f, 0.12f, 0.0f,
		0.05f, 0.24f, 0.0f,
	}; //6 Vertices

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[TIE]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Tie_data), Tie_data, GL_STATIC_DRAW);

	static const GLfloat Tie_color_data[] = {
		0.753f, 0.753f, 0.753f,
		0.753f, 0.753f, 0.753f,
		0.753f, 0.753f, 0.753f,

		0.753f, 0.753f, 0.753f,
		0.753f, 0.753f, 0.753f,
		0.753f, 0.753f, 0.753f,
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[TIE]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Tie_color_data), Tie_color_data, GL_STATIC_DRAW);
}

void Assignment1::ATie() // Works as a square or rectangle
{
	static const GLfloat ATie_data[] = {
		0.5f, 0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
	}; //4 Vertices

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[ATIE]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(ATie_data), ATie_data, GL_STATIC_DRAW);

	static const GLfloat ATie_color_data[] = {
		0.753f, 0.753f, 0.753f,
		0.753f, 0.753f, 0.753f,
		0.753f, 0.753f, 0.753f,
		0.753f, 0.753f, 0.753f,
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[ATIE]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(ATie_color_data), ATie_color_data, GL_STATIC_DRAW);
}

void Assignment1::Star() //Can be used for x-wing gun thingy
{
	static const GLfloat Star_data[] = {
		0.0f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[STAR]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Star_data), Star_data, GL_STATIC_DRAW);

	static const GLfloat Star_color_data[] = {
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[STAR]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Star_color_data), Star_color_data, GL_STATIC_DRAW);
}

void Assignment1::XWing()
{
	static const GLfloat XWing_data[] = {
		0.5f, 0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[XWING]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(XWing_data), XWing_data, GL_STATIC_DRAW);

	static const GLfloat XWing_color_data[] = {
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		0.941f, 0.502f, 0.502f, //the red in bottom left
		1.0f, 1.0f, 1.0f,
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[XWING]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(XWing_color_data), XWing_color_data, GL_STATIC_DRAW);
}

void Assignment1::Laser()
{
	static const GLfloat Laser_data[] = {
		0.5f, 0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[LASER]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Laser_data), Laser_data, GL_STATIC_DRAW);

	static const GLfloat Laser_color_data[] = {
		0.486f, 0.988f, 0.0f,
		0.486f, 0.988f, 0.0f,
		0.486f, 0.988f, 0.0f,
		0.486f, 0.988f, 0.0f,
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[LASER]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Laser_color_data), Laser_color_data, GL_STATIC_DRAW);

}

void Assignment1::Explosion()
{
	static const GLfloat Explosion_color_data[] = {
		1.0f, 0.843f, 0.0f,
		1.0f, 0.271f, 0.0f,
		1.0f, 0.271f, 0.0f,
	};


	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[EXPLOSION]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Explosion_color_data), Explosion_color_data, GL_STATIC_DRAW);
}

void Assignment1::Update(double dt)
{
	XwingX1 -= (float)(10 * dt);
	XwingX2 -= (float)(10 * dt);
	TieX += (float)(10 * dt);
	ATieX += (float)(10 * dt);

	if (Application::IsKeyPressed(VK_SPACE))
	{
		Spacebarr = true;
		Spacebarr2 = true;
		Spacebarr3 = true;
		DistanceStuffs = true;
	}

	// Moving Big Ships codes here
	if (StarDX <= -27.f)
	{
		StarDX += (float)(3 * dt);
		StarDCX += (float)(3 * dt);
		StarDRX += (float)(3 * dt);
		BlasterNX += (float)(3 * dt);
		LaserSD1 += (float)(3 * dt);
		LaserSD2 += (float)(3 * dt);
	}
	if (OvalX >= 27.f)
	{
		OvalX -= (float)(3 * dt);
		BlasterX -= (float)(3 * dt);
		LaserOval1 -= (float)(3 * dt);
		LaserOval2 -= (float)(3 * dt);
	}
	
	// This is for the laser from Ties and Xwings to travel a certain distance instead of going on forever
	if (Spacebarr == true)
	{
		LaserX1 -= (float)(20 * dt);
		LaserX2 -= (float)(20 * dt);
		LaserAT += (float)(20 * dt);
		LaserT += (float)(20 * dt);
		distanceS = XwingX1;
		if (Spacebarr == true && DistanceStuffs == true)
		{
			distanceD = (distanceS - 16.f);
			DistanceStuffs = false;
		}
	}
	else
	{
		LaserX1 -= (float)(10 * dt);
		LaserX2 -= (float)(10 * dt);
		LaserAT += (float)(10 * dt);
		LaserT += (float)(10 * dt);
	}
	 
	// Lasers on big ships
	if (Spacebarr2 == true && StarDX <= 27.f)
	{
		LaserSD1 += (float)(10 * dt);
		LaserOval1 -= (float)(10 * dt);
	}

	if (Spacebarr3 == true && StarDX <= 27.f)
	{
		LaserSD2 += (float)(10 * dt);
		LaserOval2 -= (float)(10 * dt);
	}

	if ((distanceS <= distanceD || LaserX1 <= -50.f) && Spacebarr == true)
	{
		LaserX1 = XwingX1 + 0.5f;
		LaserX2 = XwingX2 + 0.5f;
		LaserAT = ATieX;
		LaserT = TieX;
		Spacebarr = false;
	}

	if (LaserSD1 >= 12.f)
	{
		LaserSD1 = -43.f;
		LaserOval1 = 33.f;
		SExplosion1 = 1.f;
		Spacebarr2 = false;
		Boom2 = true;
	}
	if (Boom2 == true)
	{
		SExplosion1 += (float)(2 * dt);
	}
	if (SExplosion1 >= 4.f)
	{
		Boom2 = false;
		SExplosion1 = 0.f;
	}

	if (LaserSD2 >= 0.f)
	{
		LaserSD2 = -16.f;
		LaserOval2 = 16.f;
		SExplosion = 1.f;
		Spacebarr3 = false;
		Boom = true;
	}
	if (Boom == true)
	{
		SExplosion += (float)(2 * dt);
	}

	if (SExplosion >= 4)
	{
		Boom = false;
		SExplosion = 0.f;
	}
	
	// Small ships reset to the border (or loop their travel)
	if (XwingX1 <= -50.f)
	{
		XwingX1 = 50.f;
	}
	if (XwingX2 <= -50.f)
	{
		XwingX2 = 50.f;
	}
	if (ATieX >= 50.f)
	{
		ATieX = -50.f;
	}
	if (TieX >= 50.f)
	{
		TieX = -50.f;
	}
}

void Assignment1::Render()
{
	Mtx44 translate, rotate, scale;
	Mtx44 model;
	Mtx44 view;
	Mtx44 projection;
	Mtx44 MVP;

	translate.SetToIdentity();
	rotate.SetToIdentity();
	scale.SetToIdentity();
	model.SetToIdentity();
	view.SetToIdentity();
	projection.SetToOrtho(-50, 50, -40, 40, -20, 20);

	// Clear color buffer every frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Render VBO here
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);


	//This is DEATH STAR
	scale.SetToScale(100.f, 100.f, 100.f);
	rotate.SetToRotation(0.f, 0.f, 0.f, 1.f);
	translate.SetToTranslation(-50.f, 40.f, 0.f);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[DEATH_STAR]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[DEATH_STAR]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 21); // Draw DEATHSTAR PLOX

	scale.SetToScale(30.f, 3.f, 2.f);
	rotate.SetToRotation(0.f, 0.f, 0.f, 1.f);
	translate.SetToTranslation(-36.f, 40.f, 1.f);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[ATIE]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[ATIE]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4); // Draw Rectangle OF GOODNESS PLOX



	//This is STAR DESTROYER
	scale.SetToScale(16.f, 16.f, 16.f);
	rotate.SetToRotation(0.f, 0.f, 0.f, 1.f);
	translate.SetToTranslation(StarDX, -9.8f, 0.f);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[STAR_DESTROYER]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[STAR_DESTROYER]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 19); // Draw STAR DESTROYER PLOX

	//Star Destroyer circle top
	scale.SetToScale(3.f, 3.f, 3.f);
	rotate.SetToRotation(0.f, 0.f, 0.f, 1.f);
	translate.SetToTranslation(StarDCX, 1.f, 0.f);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[OVAL]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[OVAL]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 17); // Draw CIRCLE PLOX

	scale.SetToScale(-3.f, -3.f, -3.f);
	rotate.SetToRotation(0.f, 0.f, 0.f, 1.f);
	translate.SetToTranslation(StarDCX, 1.f, 0.f);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[OVAL]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[OVAL]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 17); // Draw CIRCLE PLOX

	scale.SetToScale(2.f, 1.f, 1.f);
	rotate.SetToRotation(0.f, 0.f, 0.f, 1.f);
	translate.SetToTranslation(BlasterNX, -8.8f, -2.f);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[XWING]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[XWING]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4); // Draw Blaster PLOX

	scale.SetToScale(25.f, 2.f, 2.f);
	rotate.SetToRotation(1.f, 0.f, 0.f, 1.f);
	translate.SetToTranslation(StarDRX, -8.8f, 1.f);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[ATIE]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[ATIE]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4); // Draw Rectangle OF GOODNESS PLOX



	//OVAL
	scale.SetToScale(60, 18, 15);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(OvalX, -7, 0);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[OVAL]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[OVAL]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 17); // Draw HALF OVAL PLOX


	scale.SetToScale(-60, -18, 15);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(OvalX, -7, 0);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[OVAL]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[OVAL]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 17); // Draw OTHER HALF OVAL PLOX

	scale.SetToScale(20, 3, 0);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(OvalX, -2, 0);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[OVAL]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[OVAL]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 17); // Draw HALF OVAL PLOX


	scale.SetToScale(-20, -3, 0);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(OvalX, -2, 0);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[OVAL]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[OVAL]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 17); // Draw OTHER HALF OVAL PLOX

	scale.SetToScale(6, 1, 2);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(OvalX, -2, 1);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[ATIE]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[ATIE]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4); // Draw Rectangle OF GOODNESS PLOX

	scale.SetToScale(2, 1, 1);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(BlasterX, -8.8, -2);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[XWING]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[XWING]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4); // Draw Blaster PLOX


	//Tie Fighter here
	scale.SetToScale(10, 10, 10);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(TieX, -17, 0);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[TIE]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[TIE]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 6); // Draw OVAL PLOX

	//Tie Fighter 2
	scale.SetToScale(10, 10, 10);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(TieX, -26.5, 0);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[TIE]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[TIE]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 6); // Draw OVAL PLOX



	//Advanced Tie Fighther
	scale.SetToScale(3, 2, 2);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(ATieX, -20.5, 0);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[ATIE]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[ATIE]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4); // Draw DARTH VADER SHIP OF GOODNESS PLOX


	//Star codes go here

	//Star
	scale.SetToScale(1, 1, 1);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(20, 30.5, 1);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[STAR]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[STAR]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 3); // Draw STARRRRR PLOX


	scale.SetToScale(1, 1, 1);
	rotate.SetToRotation(90, 0, 0, 1);
	translate.SetToTranslation(19.5, 30, 1);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[STAR]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[STAR]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 3); // Draw STARRRRR PLOX


	scale.SetToScale(1, 1, 1);
	rotate.SetToRotation(180, 0, 0, 1);
	translate.SetToTranslation(20, 29.5, 1);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[STAR]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[STAR]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 3); // Draw STARRRRR PLOX


	scale.SetToScale(1, 1, 1);
	rotate.SetToRotation(270, 0, 0, 1);
	translate.SetToTranslation(20.5, 30, 1);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[STAR]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[STAR]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 3); // Draw STARRRRR PLOX



	//Star 2
	scale.SetToScale(1, 1, 1);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(0, 15.5, 1);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[STAR]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[STAR]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 3); // Draw STARRRRR PLOX


	scale.SetToScale(1, 1, 1);
	rotate.SetToRotation(90, 0, 0, 1);
	translate.SetToTranslation(-0.5, 15, 1);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[STAR]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[STAR]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 3); // Draw STARRRRR PLOX


	scale.SetToScale(1, 1, 1);
	rotate.SetToRotation(180, 0, 0, 1);
	translate.SetToTranslation(0, 14.5, 1);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[STAR]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[STAR]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 3); // Draw STARRRRR PLOX


	scale.SetToScale(1, 1, 1);
	rotate.SetToRotation(270, 0, 0, 1);
	translate.SetToTranslation(0.5, 15, 1);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[STAR]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[STAR]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 3); // Draw STARRRRR PLOX
	


	//Star 3
	scale.SetToScale(1, 1, 1);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(-20, 10.5, 1);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[STAR]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[STAR]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 3); // Draw STARRRRR PLOX


	scale.SetToScale(1, 1, 1);
	rotate.SetToRotation(90, 0, 0, 1);
	translate.SetToTranslation(-20.5, 10, 1);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[STAR]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[STAR]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 3); // Draw STARRRRR PLOX


	scale.SetToScale(1, 1, 1);
	rotate.SetToRotation(180, 0, 0, 1);
	translate.SetToTranslation(-20, 9.5, 1);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[STAR]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[STAR]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 3); // Draw STARRRRR PLOX


	scale.SetToScale(1, 1, 1);
	rotate.SetToRotation(270, 0, 0, 1);
	translate.SetToTranslation(-19.5, 10, 1);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[STAR]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[STAR]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 3); // Draw STARRRRR PLOX


	//Star 4
	scale.SetToScale(1, 1, 1);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(40, 8.5, 1);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[STAR]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[STAR]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 3); // Draw STARRRRR PLOX


	scale.SetToScale(1, 1, 1);
	rotate.SetToRotation(90, 0, 0, 1);
	translate.SetToTranslation(39.5, 8, 1);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[STAR]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[STAR]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 3); // Draw STARRRRR PLOX


	scale.SetToScale(1, 1, 1);
	rotate.SetToRotation(180, 0, 0, 1);
	translate.SetToTranslation(40, 7.5, 1);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[STAR]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[STAR]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 3); // Draw STARRRRR PLOX


	scale.SetToScale(1, 1, 1);
	rotate.SetToRotation(270, 0, 0, 1);
	translate.SetToTranslation(40.5, 8, 1);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[STAR]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[STAR]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 3); // Draw STARRRRR PLOX



	//X-wing
	scale.SetToScale(3, 1, 1);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(XwingX1, -20.5, 1);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[XWING]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[XWING]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4); // Draw X-WING PLOX


	scale.SetToScale(0.5, 2.3, 1);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(XwingX1 + 1, -20.5, 1);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[XWING]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[XWING]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4); // Draw X-WING PLOX


	scale.SetToScale(1.f, 0.3f, 1.f);
	rotate.SetToRotation(0.f, 0.f, 0.f, 1.f);
	translate.SetToTranslation(XwingX1 + 0.5f, -19.5f, 1.f);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[XWING]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[XWING]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4); // Draw X-WING WINGG PLOX


	scale.SetToScale(1, 0.3, 1);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(XwingX1 + 0.5, -21.5, 1);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[XWING]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[XWING]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4); // Draw X-WING WINGG PLOX



	//X-WING TWO
	scale.SetToScale(3, 1, 1);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(XwingX2, -15, -1);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[XWING]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[XWING]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4); // Draw X-WING PLOX


	scale.SetToScale(2.3, 0.5, 1);
	rotate.SetToRotation(270, 0, 0, 1);
	translate.SetToTranslation(XwingX2 + 1, -15, -1);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[XWING]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[XWING]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4); // Draw X-WING PLOX


	scale.SetToScale(1, 0.3, 1);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(XwingX2 + 0.5, -14, -1);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[XWING]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[XWING]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4); // Draw X-WING WINGG PLOX


	scale.SetToScale(1, 0.3, 1);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(XwingX2 + 0.5, -16, -1);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[XWING]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[XWING]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4); // Draw X-WING WINGG PLOX



	//X-WING THREE
	scale.SetToScale(3, 1, 1);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(XwingX2, -25, -1);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[XWING]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[XWING]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4); // Draw X-WING PLOX


	scale.SetToScale(2.3, 0.5, 1);
	rotate.SetToRotation(270, 0, 0, 1);
	translate.SetToTranslation(XwingX2 + 1, -25, -1);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[XWING]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[XWING]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4); // Draw X-WING PLOX


	scale.SetToScale(1, 0.3, 1);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(XwingX2 + 0.5, -26, -1);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[XWING]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[XWING]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4); // Draw X-WING WINGG PLOX


	scale.SetToScale(1, 0.3, 1);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(XwingX2 + 0.5, -24, -1);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[XWING]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[XWING]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4); // Draw X-WING WINGG PLOX


	//Laser codes go here

	//Laser Xwing1
	scale.SetToScale(1.5, 0.3, 1);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(LaserX1, -19.5, 1);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[LASER]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[LASER]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4); // Draw LASER PLOX
	
	//Laser Wing2
	scale.SetToScale(1.5, 0.3, 1);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(LaserX2, -24, -1);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[LASER]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[LASER]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4); // Draw LASER PLOX

	//Laser Wing3
	scale.SetToScale(1.5, 0.3, 1);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(LaserX2, -14, -1);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[LASER]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[LASER]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4); // Draw LASER PLOX

	//Laser ATie
	scale.SetToScale(1.5, 0.3, 1);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(LaserAT, -20.5, 0);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[LASER]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[LASER]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4); // Draw LASER PLOX

	//Laser Tie1
	scale.SetToScale(1.5, 0.3, 1);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(LaserT, -25.5, 0);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[LASER]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[LASER]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4); // Draw LASER PLOX

	//Laser Tie2
	scale.SetToScale(1.5, 0.3, 1);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(LaserT, -16, 0);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[LASER]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[LASER]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4); // Draw LASER PLOX

	// Laser For SD
	scale.SetToScale(3.f, 0.9f, 1.f);
	rotate.SetToRotation(0.f, 0.f, 0.f, 1.f);
	translate.SetToTranslation(LaserSD1, -4.3f, -1.f);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[LASER]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[LASER]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4); // Draw LASER PLOX

	// Laser for SD2
	scale.SetToScale(3.f, 0.9f, 1.f);
	rotate.SetToRotation(0.f, 0.f, 0.f, 1.f);
	translate.SetToTranslation(LaserSD2, -8.8f, -1.f);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[LASER]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[LASER]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4); // Draw LASER PLOX

	//Laser for Oval1
	scale.SetToScale(3, 0.9, 1);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(LaserOval1, -6.8, -1);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[LASER]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[LASER]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4); // Draw LASER PLOX

	//Laser for Oval2 
	scale.SetToScale(3, 0.9, 1);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(LaserOval2, -8.8, -1);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[LASER]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[LASER]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4); // Draw LASER PLOX


	// Explosion Stuffs go here

	//Explosion 1
	scale.SetToScale(SExplosion, SExplosion, SExplosion);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(0.0, -8.8, -1);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[STAR]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[EXPLOSION]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4); // Draw Explosion PLOX

	//Explosion 2
	scale.SetToScale(SExplosion, SExplosion, SExplosion);
	rotate.SetToRotation(25, 0, 0, 1);
	translate.SetToTranslation(0.0, -8.8, -1);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[STAR]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[EXPLOSION]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4); // Draw Explosion PLOX

	//Explosion 3
	scale.SetToScale(SExplosion, SExplosion, SExplosion);
	rotate.SetToRotation(335, 0, 0, 1);
	translate.SetToTranslation(0.0, -8.8, -1);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[STAR]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[EXPLOSION]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4); // Draw Explosion PLOX

	//Explosion 4
	scale.SetToScale(SExplosion, SExplosion, SExplosion);
	rotate.SetToRotation(310, 0, 0, 1);
	translate.SetToTranslation(0.0, -8.8, -1);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[STAR]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[EXPLOSION]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4); // Draw Explosion PLOX

	//Explosion 5
	scale.SetToScale(SExplosion, SExplosion, SExplosion);
	rotate.SetToRotation(50, 0, 0, 1);
	translate.SetToTranslation(0.0, -8.8, -1);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[STAR]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[EXPLOSION]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4); // Draw Explosion PLOX


	//Second Explosion
	//Explosion 1
	scale.SetToScale(SExplosion1, SExplosion1, SExplosion1);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(12, -4.3, -1);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[STAR]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[EXPLOSION]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4); // Draw Explosion PLOX

	//Explosion 2
	scale.SetToScale(SExplosion1, SExplosion1, SExplosion1);
	rotate.SetToRotation(25, 0, 0, 1);
	translate.SetToTranslation(12, -4.3, -1);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[STAR]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[EXPLOSION]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4); // Draw Explosion PLOX

	//Explosion 3
	scale.SetToScale(SExplosion1, SExplosion1, SExplosion1);
	rotate.SetToRotation(335, 0, 0, 1);
	translate.SetToTranslation(12, -4.3, -1);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[STAR]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[EXPLOSION]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4); // Draw Explosion PLOX

	//Explosion 4
	scale.SetToScale(SExplosion1, SExplosion1, SExplosion1);
	rotate.SetToRotation(310, 0, 0, 1);
	translate.SetToTranslation(12, -4.3, -1);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[STAR]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[EXPLOSION]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4); // Draw Explosion PLOX

	//Explosion 5
	scale.SetToScale(SExplosion1, SExplosion1, SExplosion1);
	rotate.SetToRotation(50, 0, 0, 1);
	translate.SetToTranslation(12, -4.3, -1);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[STAR]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[EXPLOSION]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4); // Draw Explosion PLOX

	//Third Explosion
	//Explosion 1
	scale.SetToScale(SExplosion1, SExplosion1, SExplosion1);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(-20, -7.3, -1);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[STAR]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[EXPLOSION]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4); // Draw Explosion PLOX

	//Explosion 2
	scale.SetToScale(SExplosion1, SExplosion1, SExplosion1);
	rotate.SetToRotation(25, 0, 0, 1);
	translate.SetToTranslation(-20, -7.3, -1);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[STAR]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[EXPLOSION]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4); // Draw Explosion PLOX

	//Explosion 3
	scale.SetToScale(SExplosion1, SExplosion1, SExplosion1);
	rotate.SetToRotation(335, 0, 0, 1);
	translate.SetToTranslation(-20, -7.3, -1);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[STAR]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[EXPLOSION]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4); // Draw Explosion PLOX

	//Explosion 4
	scale.SetToScale(SExplosion1, SExplosion1, SExplosion1);
	rotate.SetToRotation(310, 0, 0, 1);
	translate.SetToTranslation(-20, -7.3, -1);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[STAR]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[EXPLOSION]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4); // Draw Explosion PLOX

	//Explosion 5
	scale.SetToScale(SExplosion1, SExplosion1, SExplosion1);
	rotate.SetToRotation(50, 0, 0, 1);
	translate.SetToTranslation(-20, -7.3, -1);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[STAR]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[EXPLOSION]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4); // Draw Explosion PLOX

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void Assignment1::Exit()
{
	// Cleanup VBO here
	glDeleteBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glDeleteBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}