#include "Assignment2.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"

#include "Application.h"
#include "MeshBuilder.h"
#include "Utility.h"

Assignment2::Assignment2()
{
}

Assignment2::~Assignment2()
{
}

void Assignment2::Init()
{
	// Init VBO here

	// Set background color to dark blue
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	//Enable depth buffer and depth testing
	glEnable(GL_DEPTH_TEST);

	//Enable back face culling
	glEnable(GL_CULL_FACE);

	//Default to fill mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	m_programID = LoadShaders("Shader//Shading.vertexshader", "Shader//Shading.fragmentshader");
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");
	m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
	m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
	m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");
	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	glUseProgram(m_programID);

	light[0].position.Set(0, 30, 0);
	light[0].color.Set(1, 1, 1);
	light[0].power = 2;
	light[0].kC = 1.f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;

	// Make sure you pass uniform parameters after glUseProgram()
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);


	Mtx44 projection;
	projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 1000.f);
	projectionStack.LoadMatrix(projection);

	//variable to rotate geometry

	//Initialize camera settings
	camera.Init(Vector3(0, 15, -40), Vector3(0, 10, 0), Vector3(0, 1, 0));

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000.f, 1000.f, 1000.f);

	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightlight", Color(1, 1, 1), 18.f, 36);

	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("floor", Color(0.000, 1.000, 0.000));
	meshList[GEO_QUAD]->material.kAmbient.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_QUAD]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_QUAD]->material.kSpecular.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_QUAD]->material.kShininess = 5.f;

	meshList[GEO_HEAD] = MeshBuilder::GenerateSphere("Wario Head", Color(0.957f, 0.643f, 0.376f), 18.f, 36);
	meshList[GEO_HEAD]->material.kAmbient.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_HEAD]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_HEAD]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_HEAD]->material.kShininess = 0.5f;

	meshList[GEO_HAT1] = MeshBuilder::GenerateSphere("Wario Hat", Color(1, 1, 0), 18.f, 36);
	meshList[GEO_HAT1]->material.kAmbient.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_HAT1]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_HAT1]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_HAT1]->material.kShininess = 0.5f;

	meshList[GEO_HAT_W] = MeshBuilder::GenerateCube("Wario W", Color(0.f, 0.f, 0.804f));
	meshList[GEO_HAT_W]->material.kAmbient.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_HAT_W]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_HAT_W]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_HAT_W]->material.kShininess = 0.5f;

	meshList[GEO_NOSE] = MeshBuilder::GenerateSphere("Wario Nose", Color(1.f, 0.412f, 0.706f), 18.f, 36);
	meshList[GEO_NOSE]->material.kAmbient.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_NOSE]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_NOSE]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_NOSE]->material.kShininess = 0.5f;

	meshList[GEO_MOUSTACHE1] = MeshBuilder::GenerateMoustache("Wario Moustache", Color(0, 0, 0));
	meshList[GEO_MOUSTACHE1]->material.kAmbient.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_MOUSTACHE1]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_MOUSTACHE1]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_MOUSTACHE1]->material.kShininess = 0.5f;

	meshList[GEO_MOUSTACHE2] = MeshBuilder::GenerateMoustache2("Wario Moustache", Color(0, 0, 0));
	meshList[GEO_MOUSTACHE2]->material.kAmbient.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_MOUSTACHE2]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_MOUSTACHE2]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_MOUSTACHE2]->material.kShininess = 0.5f;

	meshList[GEO_MOUSTACHE3] = MeshBuilder::GenerateMoustache3("Wario Moustache", Color(0, 0, 0));
	meshList[GEO_MOUSTACHE3]->material.kAmbient.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_MOUSTACHE3]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_MOUSTACHE3]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_MOUSTACHE3]->material.kShininess = 0.5f;

	meshList[GEO_MOUSTACHE4] = MeshBuilder::GenerateMoustache4("Wario Moustache", Color(0, 0, 0));
	meshList[GEO_MOUSTACHE4]->material.kAmbient.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_MOUSTACHE4]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_MOUSTACHE4]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_MOUSTACHE4]->material.kShininess = 0.5f;

	meshList[GEO_EYES] = MeshBuilder::GenerateSphere("Wario Body", Color(1, 1, 1), 18.f, 36);
	meshList[GEO_EYES]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_EYES]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_EYES]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_EYES]->material.kShininess = 0.5f;

	meshList[GEO_EYELINER] = MeshBuilder::GenerateCircle("Wario Body", Color(0.f, 0.749, 1.f), 36);
	meshList[GEO_EYELINER]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_EYELINER]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_EYELINER]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_EYELINER]->material.kShininess = 0.5f;

	meshList[GEO_BODY] = MeshBuilder::GenerateSphere("Wario Body", Color(1, 1, 0), 18.f, 36);
	meshList[GEO_BODY]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_BODY]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_BODY]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_BODY]->material.kShininess = 0.5f;

	meshList[GEO_SHIRT] = MeshBuilder::GenerateHemiSphere("Wario Body", Color(0.502f, 0.f, 0.502f), 18.f, 36);
	meshList[GEO_SHIRT]->material.kAmbient.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_SHIRT]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_SHIRT]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_SHIRT]->material.kShininess = 0.5f;

	meshList[GEO_SHOULDER] = MeshBuilder::GenerateSphere("Wario Shoulder", Color(1, 1, 0), 18.f, 36);
	meshList[GEO_SHOULDER]->material.kAmbient.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_SHOULDER]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_SHOULDER]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_SHOULDER]->material.kShininess = 0.5f;

	meshList[GEO_UPARMS] = MeshBuilder::GenerateSphere("Wario Upper Arm", Color(1, 1, 0), 18.f, 36);
	meshList[GEO_UPARMS]->material.kAmbient.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_UPARMS]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_UPARMS]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_UPARMS]->material.kShininess = 0.5f;

	meshList[GEO_LOWARMS] = MeshBuilder::GenerateSphere("Wario Lower Arm", Color(1, 1, 0), 18.f, 36);
	meshList[GEO_LOWARMS]->material.kAmbient.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_LOWARMS]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_LOWARMS]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_LOWARMS]->material.kShininess = 0.5f;

	meshList[GEO_HAND] = MeshBuilder::GenerateSphere("Wario Circular Hands", Color(1, 1, 1), 18.f, 36);
	meshList[GEO_HAND]->material.kAmbient.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_HAND]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_HAND]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_HAND]->material.kShininess = 0.5f;

	meshList[GEO_LEG] = MeshBuilder::GenerateCylinder("WARIO LEG", Color(0.502f, 0.f, 0.502f), 36);
	meshList[GEO_LEG]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_LEG]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_LEG]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_LEG]->material.kShininess = 0.5f;

	meshList[GEO_KNEE] = MeshBuilder::GenerateSphere("Knee", Color(0.502f, 0.f, 0.502f), 18.f, 36);
	meshList[GEO_KNEE]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_KNEE]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_KNEE]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_KNEE]->material.kShininess = 0.5f;

	meshList[GEO_DUMMY_HEAD] = MeshBuilder::GenerateCube("head of justice", Color(0.722f, 0.525f, 0.043f));
	meshList[GEO_DUMMY_HEAD]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_DUMMY_HEAD]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_DUMMY_HEAD]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_DUMMY_HEAD]->material.kShininess = 1.f;

	meshList[GEO_DUMMY_BODY] = MeshBuilder::GenerateCube("body of justice", Color(0.722f, 0.525f, 0.043f));
	meshList[GEO_DUMMY_BODY]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_DUMMY_BODY]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_DUMMY_BODY]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_DUMMY_BODY]->material.kShininess = 1.f;

	meshList[GEO_DUMMY_POLE] = MeshBuilder::GenerateCube("pole of justice", Color(0.502f, 0.f, 0.f));
	meshList[GEO_DUMMY_POLE]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_DUMMY_POLE]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_DUMMY_POLE]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_DUMMY_POLE]->material.kShininess = 0.5f;

	meshList[GEO_HAMMER_HANDLE] = MeshBuilder::GenerateCylinder("Hammer handle", Color(0.545f, 0.271f, 0.075f), 36);
	meshList[GEO_HAMMER_HANDLE]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_HAMMER_HANDLE]->material.kDiffuse.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_HAMMER_HANDLE]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_HAMMER_HANDLE]->material.kShininess = 0.5f;

	meshList[GEO_HAMMER_HEAD] = MeshBuilder::GenerateCylinder("Hammer head", Color(0.f,0.f,0.f), 36);
	meshList[GEO_HAMMER_HEAD]->material.kAmbient.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_HAMMER_HEAD]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_HAMMER_HEAD]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_HAMMER_HEAD]->material.kShininess = 10.f;
}

void Assignment2::RenderMesh(Mesh *mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
	if (enableLight && this->enablelight)
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView_inverse_transpose.a[0]);
		//load material
		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
		glUniform1f(m_parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);
	}
	else
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}
	mesh->Render();
}

static float ROT_LIMIT = 45.f;
static float SCALE_LIMIT = 5.f;

void Assignment2::Update(double dt)
{
	camera.Update(dt);
	if (Application::IsKeyPressed('1')) //enable back face culling
		glEnable(GL_CULL_FACE);
	if (Application::IsKeyPressed('2')) //disable back face culling
		glDisable(GL_CULL_FACE);
	if (Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
	if (Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode

	if (Application::IsKeyPressed('I'))
		light[0].position.y += (float)(LSPEED * dt);
	if (Application::IsKeyPressed('K'))
		light[0].position.y -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('J'))
		light[0].position.x -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('L'))
		light[0].position.x += (float)(LSPEED * dt);
	if (Application::IsKeyPressed('O'))
		light[0].position.z -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('P'))
		light[0].position.z += (float)(LSPEED * dt);

	if (Application::IsKeyPressed('Z'))
		enablelight = true;
	if (Application::IsKeyPressed('X'))
		enablelight = false;

	if (Application::IsKeyPressed('F'))
	{
		if (hammerTime == false)
		{
			fightStance = true;
			walk = false;
			reset = false;
		}
		if (hammerTime == true)
		fightStance = false;
	}

	if (Application::IsKeyPressed('G'))
	{
		if (fightStance == false && spin == false)
		{
			hammerTime = true;
			walk = false;
			reset = false;
		}
	}

	if (Application::IsKeyPressed('H') && spin == true)
	{
		reset = true;
	}
	if (Application::IsKeyPressed(VK_SPACE))
	{
		jump = true;
		walk = false;
		reset = false;
	}

	if (fightStance == true && ready == false)
	{
		if (bodyRotate >= -25)
		{
			bodyRotate -= (float)(10 * dt);
			LshoulderRotateX -= (float)(45 * dt);
			LshoulderRotateZ -= (float)(20 * dt);
			RshoulderRotateX -= (float)(40 * dt);
		}
		else
		{
			ready = false;
			fightStance = false;
			punch = true;
		}
	}

	if (fightStance == false && ready == false && punch == true)
	{
		if (bodyRotate <= 45)
		{
			bodyRotate += (float)(50 * dt);

			if (LshoulderRotateZ <= 0)
			LshoulderRotateZ += (float)(50 * dt);

			if (LshoulderRotateX <= 0)
			LshoulderRotateX += (float)(100 * dt);
		}
		else
		{
			punch = false;
			fall = true;
		}
	}

	if (punch == false && fall == true)
	{
		if (DUMMYROTATE <= 90)
			DUMMYROTATE += (float)(20 * dt);
		else
		{
			if (bodyRotate >= 0)
			{
				bodyRotate -= (float)(35 * dt);
				if (RshoulderRotateX <= 0)
				{
					RshoulderRotateX += (float)(80 * dt);
				}
				else
				{
					fall = false;
					walk = true;
				}	
			}
		}
	}

	if (hammerTime == true)
	{
		if (RshoulderRotateX >= -180)
		{
			RshoulderRotateX -= (float)(50 * dt);
		}
		else
		{
			if (scaleXZ <= 0.5)
				scaleXZ += (float)(10 * dt);
			if (scaleY <= 10)
				scaleY += (float)(5 * dt);
			else
			{
				hammerHeadY = 7.f;
				hammerHeadZ = 2.5;
				if (hammerSY <= 5)
				{
					hammerSXZ += (float)(5 * dt);
					hammerSY += (float)(10 * dt);
				}
				else
				{
					hammerTime = false;
					posReady = true;
				}
			}
		}
	}
	else if (hammerTime == false && posReady == true && fightStance == false)
	{

		if (RshoulderRotateX <= -90)
		{
			RshoulderRotateX += (float)(30 * dt);
			LshoulderRotateX -= (float)(30 * dt);
			if (rotateHandX <= 90)
				rotateHandX += (float)(40 * dt);
		}
		else
		{
			if (RshoulderRotateZ <= 72)
			{
				RshoulderRotateZ += (float)(50 * dt);
				LshoulderRotateZ -= (float)(50 * dt);
				rotateHandY -= (float)(50 * dt);
			}
			else if (RshoulderRotateZ >= 72)
			{
				spin = true;
				posReady = false;
			}
		}
	}

	if (spin == true)
	{
		bodyRotate += (float)(200 * dt);
		if (Application::IsKeyPressed(VK_RIGHT))
			transBodyX -= (float)(15 * dt);
		if (Application::IsKeyPressed(VK_LEFT))
			transBodyX += (float)(15 * dt);
		if (Application::IsKeyPressed(VK_UP))
			transBodyZ += (float)(15 * dt);
		if (Application::IsKeyPressed(VK_DOWN))
			transBodyZ -= (float)(15 * dt);
		if (bodyRotate >= 360)
			bodyRotate = 0;
	}

	if (walk == true)
	{
		reset = false;
		if (Application::IsKeyPressed(VK_UP))
		{
			transBodyX += (float)(sin(Math::DegreeToRadian(bodyRotate)))*(15 * dt);
			transBodyZ += (float)(cos(Math::DegreeToRadian(bodyRotate)))*(15 * dt);
			if (LshoulderRotateX >= -35 && walkie == false)
			{
				RshoulderRotateX += (float)(75 * dt);
				LshoulderRotateX -= (float)(75 * dt);
				RlegRotateX -= (float)(75 * dt);
				LlegRotateX += (float)(75 * dt);
				if (LshoulderRotateX <= -35)
					walkie = true;
			}
			else if (LshoulderRotateX <= 35 && walkie == true)
			{
				RshoulderRotateX -= (float)(75 * dt);
				LshoulderRotateX += (float)(75 * dt);
				RlegRotateX += (float)(75 * dt);
				LlegRotateX -= (float)(75 * dt);
				if (LshoulderRotateX >= 35)
					walkie = false;
			}
		}
		else
		{
			RshoulderRotateX = 0;
			LshoulderRotateX = 0;
			RlegRotateX = 0;
			LlegRotateX = 0;
		}
		if (Application::IsKeyPressed(VK_RIGHT))
			bodyRotate -= (float)(75 * dt);
		if (Application::IsKeyPressed(VK_LEFT))
			bodyRotate += (float)(75 * dt);
	}

	if (reset == true)
	{
		bodyRotate = 0;
		RshoulderRotateX = 0;
		RshoulderRotateY = 0;
		RshoulderRotateZ = 0;
		LshoulderRotateX = 0;
		LshoulderRotateY = 0;
		LshoulderRotateZ = 0;
		rotateHandX = 0;
		rotateHandY = 0;
		rotateHandZ = 0;
		scaleXZ = 0.1f;
		scaleY = 0.1f;
		hammerHeadY = 0;
		hammerHeadZ = 0;
		hammerSXZ = 0.1f;
		hammerSY = 0.1f;

		fightStance = false;
		ready = false;
		punch = false;
		fall = false;
		hammerTime = false;
		resetTime = false;
		posReady = false;
		spin = false;
		posReady1 = false;
		walk = true;
		jump = false;
		reset = false;
		stop = false;
		walkie = false;
	}
}

void Assignment2::Render()
{
	// Render VBO here
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	viewStack.LoadIdentity();
	viewStack.LookAt(camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z);
	modelStack.LoadIdentity();

	Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
	glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);

	RenderMesh(meshList[GEO_AXES], false);

	modelStack.PushMatrix();
	modelStack.Translate(light[0].position.x, light[0].position.y, light[0].position.z);
	RenderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0.f, -5.f, 0.f);
	modelStack.Scale(500.f, 500.f, 500.f);
	RenderMesh(meshList[GEO_QUAD], true);
	modelStack.PopMatrix();
	
	//This is Wario's body
	modelStack.PushMatrix();
	modelStack.Translate(transBodyX, transBodyY, transBodyZ);
	modelStack.Rotate(bodyRotate, 0.f, 1.f, 0.f);

	modelStack.PushMatrix();
	modelStack.Scale(7.f, 7.f, 7.f);
	RenderMesh(meshList[GEO_BODY], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Scale(7.1f, 7.1f, 7.1f);
	modelStack.Rotate(90, 1, 0, 0);
	RenderMesh(meshList[GEO_SHIRT], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0.f, 9.f, 0.f);

	modelStack.PushMatrix();
	modelStack.Scale(3.7f, 3.7f, 3.7f);
	RenderMesh(meshList[GEO_HEAD], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0.f, 3.f, 0.5f);

	modelStack.PushMatrix();
	modelStack.Rotate(-30, 1, 0, 0);
	modelStack.Scale(3.f, 1.5f, 3.f);
	RenderMesh(meshList[GEO_HAT1], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-0.75f, 1.f, 2.5f);
	modelStack.Rotate(35, 0, 0, 1);
	modelStack.Scale(0.5f, 1.2f, 0.5f);
	RenderMesh(meshList[GEO_HAT_W], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-0.25f, 1.f, 2.5f);
	modelStack.Rotate(-35, 0, 0, 1);
	modelStack.Scale(0.5f, 1.2f, 0.5f);
	RenderMesh(meshList[GEO_HAT_W], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0.25f, 1.f, 2.5f);
	modelStack.Rotate(35, 0, 0, 1);
	modelStack.Scale(0.5f, 1.2f, 0.5f);
	RenderMesh(meshList[GEO_HAT_W], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0.75f, 1.f, 2.5f);
	modelStack.Rotate(-35, 0, 0, 1);
	modelStack.Scale(0.5f, 1.2f, 0.5f);
	RenderMesh(meshList[GEO_HAT_W], true);
	modelStack.PopMatrix();

	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0.f, 2.8f, 0.f);
	modelStack.Scale(3.05f, 1.f, 3.5f);
	RenderMesh(meshList[GEO_HAT1], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0.6f, 0.9f, 2.6f);
	RenderMesh(meshList[GEO_EYES], true);
	modelStack.PushMatrix();
	modelStack.Translate(-1.4f, 0.f, 0.6f);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(0.7f, 0.7f, 1.f);
	RenderMesh(meshList[GEO_EYELINER], true);
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-0.6f, 0.9f, 2.6f);
	RenderMesh(meshList[GEO_EYES], true);
	modelStack.PushMatrix(); 
	modelStack.Translate(1.4f, 0.f, 0.6f);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(0.7f, 0.7f, 1.f);
	RenderMesh(meshList[GEO_EYELINER], true);
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0.f, 0.5f, 3.6f);

	modelStack.PushMatrix();
	modelStack.Scale(0.5f, 0.7f, 0.4f);
	RenderMesh(meshList[GEO_NOSE], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-0.5f, -0.2f, -0.1f);

	modelStack.PushMatrix();
	modelStack.Scale(0.4f, 0.4f, 0.4f);
	RenderMesh(meshList[GEO_NOSE], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-3.5f, -0.7f, -0.2f);

	modelStack.PushMatrix();
	modelStack.Scale(1.f, 0.7f, 0.7f);
	RenderMesh(meshList[GEO_MOUSTACHE1], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Scale(1.f, 0.7f, 0.7f);
	RenderMesh(meshList[GEO_MOUSTACHE2], true);
	modelStack.PopMatrix();

	modelStack.PopMatrix();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0.5f, -0.2f, -0.1f);

	modelStack.PushMatrix();
	modelStack.Scale(0.4f, 0.4f, 0.4f);
	RenderMesh(meshList[GEO_NOSE], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(3.5f, -0.7f, -0.2f);

	modelStack.PushMatrix();
	modelStack.Scale(1.f, 0.7f, 0.7f);
	RenderMesh(meshList[GEO_MOUSTACHE3], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Scale(1.f, 0.7f, 0.7f);
	RenderMesh(meshList[GEO_MOUSTACHE4], true);
	modelStack.PopMatrix();

	modelStack.PopMatrix();
	modelStack.PopMatrix();
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////LEFT ARM//////////////////////////////////////////////////////////////////////

	//this is left shoulder
	modelStack.PushMatrix();
	modelStack.Translate(5.5f, 5.f, 0.f);
	modelStack.Rotate(LshoulderRotateX, 1, 0, 0);
	modelStack.Rotate(LshoulderRotateY, 0, 1, 0);
	modelStack.Rotate(LshoulderRotateZ, 0, 0, 1);

	modelStack.PushMatrix();
	modelStack.Scale(2.f, 2.f, 2.f);
	RenderMesh(meshList[GEO_SHOULDER], true);
	modelStack.PopMatrix();

	//this is left upper arm
	modelStack.PushMatrix();
	modelStack.Translate(2.f, -1.f, 0.f);
	modelStack.Rotate(50, 0.f, 0.f, 1.f);

	modelStack.PushMatrix();
	modelStack.Scale(1.3f, 3.5f, 1.3f);
	RenderMesh(meshList[GEO_UPARMS], true);
	modelStack.PopMatrix();
	

	// this is the left lower arm
	modelStack.PushMatrix();
	modelStack.Translate(-1.2f, -4.f, 0.f);
	modelStack.Rotate(-35, 0.f, 0.f, 1.f);

	modelStack.PushMatrix();
	modelStack.Scale(1.2f, 3.5f, 1.2f);
	RenderMesh(meshList[GEO_LOWARMS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0.f, -3.f, 0.f);
	modelStack.Scale(1.5f, 1.5f, 1.5f);
	RenderMesh(meshList[GEO_HAND], true);
	modelStack.PopMatrix();

	modelStack.PopMatrix();
	modelStack.PopMatrix();//left upper arm pop
	modelStack.PopMatrix();//left shoulder pop

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////RIGHT ARM//////////////////////////////////////////////////////////////////////

	//this is right shoulder
	modelStack.PushMatrix();
	modelStack.Translate(-5.5f, 5.f, 0.f);
	modelStack.Rotate(RshoulderRotateX, 1, 0, 0);
	modelStack.Rotate(RshoulderRotateY, 0, 1, 0);
	modelStack.Rotate(RshoulderRotateZ, 0, 0, 1);

	modelStack.PushMatrix();
	modelStack.Scale(2.f, 2.f, 2.f);
	RenderMesh(meshList[GEO_SHOULDER], true);
	modelStack.PopMatrix();

	//this is right upper arm
	modelStack.PushMatrix();
	modelStack.Translate(-2.f, -1.f, 0.f);
	modelStack.Rotate(-50, 0.f, 0.f, 1.f);

	modelStack.PushMatrix();
	modelStack.Scale(1.3f, 3.5f, 1.3f);
	RenderMesh(meshList[GEO_UPARMS], true);
	modelStack.PopMatrix();


	// this is the right lower arm
	modelStack.PushMatrix();
	modelStack.Translate(1.2f, -4.f, 0.f);
	modelStack.Rotate(35, 0.f, 0.f, 1.f);

	modelStack.PushMatrix();
	modelStack.Scale(1.2f, 3.5f, 1.2f);
	RenderMesh(meshList[GEO_LOWARMS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0.f, -3.f, 0.f);
	modelStack.Rotate(15, 0, 0, 1);
	modelStack.Rotate(rotateHandX, 1, 0, 0);
	modelStack.Rotate(rotateHandY, 0, 1, 0);
	modelStack.Rotate(rotateHandZ, 0, 0, 1);

	modelStack.PushMatrix();
	modelStack.Scale(1.5f, 1.5f, 1.5f);
	RenderMesh(meshList[GEO_HAND], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.PushMatrix();
	modelStack.Scale(scaleXZ, scaleY, scaleXZ);
	RenderMesh(meshList[GEO_HAMMER_HANDLE], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0.f, hammerHeadY, hammerHeadZ);
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.PushMatrix();
	modelStack.Scale(hammerSXZ, hammerSY, hammerSXZ);
	RenderMesh(meshList[GEO_HAMMER_HEAD], true);
	modelStack.PopMatrix();
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	modelStack.PopMatrix();

	modelStack.PopMatrix();
	modelStack.PopMatrix();//right upper arm pop
	modelStack.PopMatrix();//right shoulder pop

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////RIGHT LEG//////////////////////////////////////////////////////////////////////

	//Right Leg
	modelStack.PushMatrix();
	modelStack.Translate(-3.f, -7.f, 0.f);
	modelStack.Rotate(RlegRotateX, 1, 0, 0);

	modelStack.PushMatrix();
	modelStack.Scale(1.5f, 4.f, 1.5f);
	RenderMesh(meshList[GEO_LEG], true);
	modelStack.PopMatrix();

	//RIGHT KNEE
	modelStack.PushMatrix();
	modelStack.Translate(0.f, -0.3f, 0.f);

	modelStack.PushMatrix();
	modelStack.Scale(1.5f, 1.5f, 1.5f);
	RenderMesh(meshList[GEO_KNEE], true);
	modelStack.PopMatrix();
	
	//RIGHT LOW LEG
	modelStack.PushMatrix();
	modelStack.Translate(0.f, -3.7f, 0.f);

	modelStack.PushMatrix();
	modelStack.Scale(1.5f, 4.f, 1.5f);
	RenderMesh(meshList[GEO_LEG], true);
	modelStack.PopMatrix();
	
	modelStack.PopMatrix();
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////LEFT LEG//////////////////////////////////////////////////////////////////////
	//Left Leg
	modelStack.PushMatrix();
	modelStack.Translate(3.f, -7.f, 0.f);
	modelStack.Rotate(LlegRotateX, 1, 0, 0);

	modelStack.PushMatrix();
	modelStack.Scale(1.5f, 4.f, 1.5f);
	RenderMesh(meshList[GEO_LEG], true);
	modelStack.PopMatrix();

	//LEFT KNEE
	modelStack.PushMatrix();
	modelStack.Translate(0.f, -0.3f, 0.f);

	modelStack.PushMatrix();
	modelStack.Scale(1.5f, 1.5f, 1.5f);
	RenderMesh(meshList[GEO_KNEE], true);
	modelStack.PopMatrix();

	//LEFT LOW LEG
	modelStack.PushMatrix();
	modelStack.Translate(0.f, -3.7f, 0.f);

	modelStack.PushMatrix();
	modelStack.Scale(1.5f, 4.f, 1.5f);
	RenderMesh(meshList[GEO_LEG], true);
	modelStack.PopMatrix();

	modelStack.PopMatrix();
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	modelStack.PopMatrix();

	//DUMMY
	modelStack.PushMatrix();
	modelStack.Rotate(DUMMYROTATE, 1.f, 0.f, 1.f);
	modelStack.Translate(-5.f, 3.f, 15.f);

	modelStack.PushMatrix();
	modelStack.Scale(2.f, 20.f, 2.f);
	RenderMesh(meshList[GEO_DUMMY_POLE], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0.f, 10.f, 0.f);

	modelStack.PushMatrix();
	modelStack.Scale(3.5f, 3.5f, 3.5f);
	RenderMesh(meshList[GEO_DUMMY_HEAD], true);
	modelStack.PopMatrix();
	
	modelStack.PushMatrix();
	modelStack.Translate(0.f, -10.f, 0.f);

	modelStack.PushMatrix();
	modelStack.Scale(5.f, 13.f, 5.f);
	RenderMesh(meshList[GEO_DUMMY_BODY], true);
	modelStack.PopMatrix();

	modelStack.PopMatrix();
	modelStack.PopMatrix();
	modelStack.PopMatrix();
}

void Assignment2::Exit()
{
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}