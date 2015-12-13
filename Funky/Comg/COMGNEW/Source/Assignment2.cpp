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
	rotateAngle = 0;

	//Initialize camera settings
	camera.Init(Vector3(0, 5, 40), Vector3(0, 10, 0), Vector3(0, 1, 0));

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000.f, 1000.f, 1000.f);

	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightlight", Color(1, 1, 1), 18.f, 36);

	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("floor", Color(0.000, 1.000, 0.000));
	meshList[GEO_QUAD]->material.kAmbient.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_QUAD]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_QUAD]->material.kSpecular.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_QUAD]->material.kShininess = 5.f;

	meshList[GEO_BODY] = MeshBuilder::GenerateSphere("Wario Body", Color(1, 1, 0), 18.f, 36);
	meshList[GEO_BODY]->material.kAmbient.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_BODY]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_BODY]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_BODY]->material.kShininess = 0.5f;

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

	meshList[GEO_LEG] = MeshBuilder::GenerateCylinder("WARIO LEG", Color(0.502f, 0.000f, 0.502f), 36);
	meshList[GEO_LEG]->material.kAmbient.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_LEG]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_LEG]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_LEG]->material.kShininess = 0.5f;

	meshList[GEO_KNEE] = MeshBuilder::GenerateSphere("Knee", Color(0.502f, 0.000f, 0.502f), 18.f, 36);
	meshList[GEO_KNEE]->material.kAmbient.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_KNEE]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_KNEE]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_KNEE]->material.kShininess = 0.5f;

	meshList[GEO_DUMMY_HEAD] = MeshBuilder::GenerateCube("head of justice", Color(0.722, 0.525, 0.043));
	meshList[GEO_DUMMY_HEAD]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_DUMMY_HEAD]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_DUMMY_HEAD]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_DUMMY_HEAD]->material.kShininess = 1.f;

	meshList[GEO_DUMMY_BODY] = MeshBuilder::GenerateCube("body of justice", Color(0.722, 0.525, 0.043));
	meshList[GEO_DUMMY_BODY]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_DUMMY_BODY]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_DUMMY_BODY]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_DUMMY_BODY]->material.kShininess = 1.f;

	meshList[GEO_DUMMY_POLE] = MeshBuilder::GenerateCube("pole of justice", Color(0.502, 0.000, 0.000));
	meshList[GEO_DUMMY_POLE]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_DUMMY_POLE]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_DUMMY_POLE]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_DUMMY_POLE]->material.kShininess = 0.5f;
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
		fightStance = true;

	if (fightStance == true && ready == false)
	{
		if (bodyRotate >= -25)
		{
			Rz = 0;
			Lz = 0;
			Ry = 1;
			Ly = 1;
			Rx = 1;
			Lx = 1;
			bodyRotate -= (float)(10 * dt);
			LshoulderRotate -= (float)(30 * dt);
			RshoulderRotate -= (float)(30 * dt);
		}
		else
			ready = true;
	}


	if (Application::IsKeyPressed(VK_RETURN))
	{
		ready = false;
		fightStance = false;
		punch = true;
		Rarmy = -45.f;
	}

	if (fightStance == false && ready == false && punch == true)
	{
		if (bodyRotate <= 45)
		{
			//Rarmy = 1.f;
			Rz = 0;
			Ry = 1;
			Rx = 0;
			bodyRotate += (float)(50 * dt);
			LshoulderRotate += (float)(15 * dt);
			RshoulderRotate += (float)(15 * dt);
			Rarmy -= (float)(13 * dt);
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
	}

	rotateAngle += (float)(10 * dt);
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
	modelStack.Scale(100.f, 100.f, 100.f);
	RenderMesh(meshList[GEO_QUAD], true);
	modelStack.PopMatrix();
	
	//This is Wario's body
	modelStack.PushMatrix();
	modelStack.Translate(0.f, 7.f, 0.f);
	modelStack.Rotate(bodyRotate, 0.f, 1.f, 0.f);

	modelStack.PushMatrix();
	modelStack.Scale(7.f, 7.f, 7.f);
	RenderMesh(meshList[GEO_BODY], true);
	modelStack.PopMatrix();

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////LEFT ARM//////////////////////////////////////////////////////////////////////

	//this is left shoulder
	modelStack.PushMatrix();
	modelStack.Translate(5.5f, 5.f, 0.f);
	modelStack.Rotate(LshoulderRotate, Lx, Ly, Lz);

	modelStack.PushMatrix();
	modelStack.Scale(2.f, 2.f, 2.f);
	RenderMesh(meshList[GEO_SHOULDER], true);
	modelStack.PopMatrix();

	//this is left upper arm
	modelStack.PushMatrix();
	modelStack.Translate(2.f, -1.f, 0.f);
	modelStack.Rotate(45, 0.f, 0.f, 1.f);

	modelStack.PushMatrix();
	modelStack.Scale(1.2f, 3.5f, 1.2f);
	RenderMesh(meshList[GEO_UPARMS], true);
	modelStack.PopMatrix();
	

	// this is the left lower arm
	modelStack.PushMatrix();
	modelStack.Translate(-1.f, -4.f, 0.f);
	modelStack.Rotate(-30, 0.f, 0.f, 1.f);

	modelStack.PushMatrix();
	modelStack.Scale(1.2f, 3.5f, 1.2f);
	RenderMesh(meshList[GEO_LOWARMS], true);
	modelStack.PopMatrix();

	modelStack.PopMatrix();
	modelStack.PopMatrix();//left upper arm pop
	modelStack.PopMatrix();//left shoulder pop

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////RIGHT ARM//////////////////////////////////////////////////////////////////////

	//this is right shoulder
	modelStack.PushMatrix();
	modelStack.Translate(-5.5f, 5.f, 0.f);
	modelStack.Rotate(RshoulderRotate, Lx, Ly, Lz);

	modelStack.PushMatrix();
	modelStack.Scale(2.f, 2.f, 2.f);
	RenderMesh(meshList[GEO_SHOULDER], true);
	modelStack.PopMatrix();

	//this is right upper arm
	modelStack.PushMatrix();
	modelStack.Rotate(Rarmy, 1.f, 0.f, 0.f);
	modelStack.Translate(-2.f, -1.f, 0.f);
	modelStack.Rotate(-45, 0.f, 0.f, 1.f);

	modelStack.PushMatrix();
	modelStack.Scale(1.2f, 3.5f, 1.2f);
	RenderMesh(meshList[GEO_UPARMS], true);
	modelStack.PopMatrix();


	// this is the right lower arm
	modelStack.PushMatrix();
	modelStack.Translate(1.f, -4.f, 0.f);
	modelStack.Rotate(30, 0.f, 0.f, 1.f);

	modelStack.PushMatrix();
	modelStack.Scale(1.2f, 3.5f, 1.2f);
	RenderMesh(meshList[GEO_LOWARMS], true);
	modelStack.PopMatrix();

	modelStack.PopMatrix();
	modelStack.PopMatrix();//left upper arm pop
	modelStack.PopMatrix();//left shoulder pop

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////RIGHT LEG//////////////////////////////////////////////////////////////////////

	//Right Leg
	modelStack.PushMatrix();
	modelStack.Translate(-3.f, -9.f, 0.f);

	modelStack.PushMatrix();
	modelStack.Scale(1.5f, 5.f, 1.5f);
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
	modelStack.Translate(0.f, -4.7f, 0.f);

	modelStack.PushMatrix();
	modelStack.Scale(1.5f, 5.f, 1.5f);
	RenderMesh(meshList[GEO_LEG], true);
	modelStack.PopMatrix();
	
	modelStack.PopMatrix();
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////LEFT LEG//////////////////////////////////////////////////////////////////////
	//Left Leg
	modelStack.PushMatrix();
	modelStack.Translate(3.f, -9.f, 0.f);

	modelStack.PushMatrix();
	modelStack.Scale(1.5f, 5.f, 1.5f);
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
	modelStack.Translate(0.f, -4.7f, 0.f);

	modelStack.PushMatrix();
	modelStack.Scale(1.5f, 5.f, 1.5f);
	RenderMesh(meshList[GEO_LEG], true);
	modelStack.PopMatrix();

	modelStack.PopMatrix();
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	modelStack.PopMatrix();

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

}

void Assignment2::Exit()
{
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}