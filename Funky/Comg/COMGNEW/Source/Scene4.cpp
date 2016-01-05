#include "Scene4.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"

#include "Application.h"
#include "MeshBuilder.h"

Scene4::Scene4()
{
}

Scene4::~Scene4()
{
}

void Scene4::Init()
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

	//Load vertex and fragment shaders
	m_programID = LoadShaders("Shader//TransformVertexShader.vertexshader", "Shader//SimpleFragmentShader.fragmentshader");
	// Use our shader
	glUseProgram(m_programID);
	// Get a handle for our "MVP" uniform
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");

	Mtx44 projection;
	projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 1000.f);
	projectionStack.LoadMatrix(projection);

	//variable to rotate geometry
	rotateAngle = 0;

	//Initialize camera settings
	camera.Init(Vector3(4, 3, 3), Vector3(0, 0, 0), Vector3(0, 1, 0));

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);
	meshList[GEO_RING] = MeshBuilder::GenerateRing("ring", Color(1, 1, 0), 0.5, 36);


	//meshList[GEO_SUN] = MeshBuilder::GenerateSphere("sun", Color(1, 0.647, 0), 18, 36);
	//meshList[GEO_MERCURY] = MeshBuilder::GenerateSphere("mercury", Color(0.4, 0.4, 0.4), 18, 36);
	//meshList[GEO_VENUS] = MeshBuilder::GenerateSphere("venus", Color(0.941, 0.902, 0.549), 18, 36);
	//meshList[GEO_EARTH] = MeshBuilder::GenerateSphere("earth", Color(0, 1, 0), 18, 36);
	//meshList[GEO_EARTHM] = MeshBuilder::GenerateSphere("earthmoon", Color(0.663, 0.663, 0.663), 18, 36);
	//meshList[GEO_MARS] = MeshBuilder::GenerateSphere("mars", Color(0.957, 0.643, 0.376), 18, 36);
	//meshList[GEO_MARSM] = MeshBuilder::GenerateSphere("marsmoon", Color(0.663, 0.663, 0.663), 18, 36);
	//meshList[GEO_JUPITER] = MeshBuilder::GenerateSphere("jupiter", Color(0.902, 0.902, 0.980), 18, 36);
	//meshList[GEO_SATURN] = MeshBuilder::GenerateSphere("saturn", Color(1, 0.855, 0.725), 18, 36);
	//meshList[GEO_SATURNR] = MeshBuilder::GenerateRing("saturnring", Color(1, 1, 0), 0.7, 36);

	meshList[GEO_CIRCLE] = MeshBuilder::GenerateCircle("CIRCLE", Color(1, 0, 0), 36);
}

static float ROT_LIMIT = 45.f;
static float SCALE_LIMIT = 5.f;

void Scene4::Update(double dt)
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

	rotateAngle += (float)(10 * dt);
}

void Scene4::Render()
{
	// Render VBO here
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	viewStack.LoadIdentity();
	viewStack.LookAt(camera.position.x, camera.position.y, camera.position.z,
					 camera.target.x, camera.target.y, camera.target.z,
					 camera.up.x, camera.up.y, camera.up.z);
					 modelStack.LoadIdentity();

	modelStack.LoadIdentity();
	//Temp variables
	Mtx44 MVP;

	modelStack.PushMatrix();
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_AXES]->Render();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_CIRCLE]->Render();
	modelStack.PopMatrix();


	//modelStack.PushMatrix();

	//modelStack.Scale(10, 10, 10);
	//modelStack.Rotate(0.1 * rotateAngle, 0, 1, 0);
	//MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	//glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	//meshList[GEO_SUN]->Render();

	////MERCURY
	//modelStack.PushMatrix();
	//modelStack.Rotate(2 * rotateAngle, 0, 1, 0);
	//modelStack.Translate(2.5, 0, 0);
	//modelStack.Scale(0.1, 0.1, 0.1);
	//modelStack.Rotate(3 * rotateAngle, 0, 1, 0);
	//MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	//glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	//meshList[GEO_MERCURY]->Render();
	//modelStack.PopMatrix();

	////VENUS
	//modelStack.PushMatrix();
	//modelStack.Rotate(1.5* rotateAngle, 0, 1, 0);
	//modelStack.Translate(4, 0, 0);
	//modelStack.Scale(0.3, 0.3, 0.3);
	//modelStack.Rotate(1.5 * rotateAngle, 0, 1, 0);
	//MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	//glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	//meshList[GEO_VENUS]->Render();
	//modelStack.PopMatrix();

	////EARTH
	//modelStack.PushMatrix();
	//modelStack.Rotate(0.8 * rotateAngle, 0, 1, 0);
	//modelStack.Translate(6.5, 0, 0);
	//modelStack.Scale(0.5, 0.5, 0.5);
	//modelStack.Rotate(-2 * rotateAngle, 0, 1, 0);
	//MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	//glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	//meshList[GEO_EARTH]->Render();

	////EARTH'S MOON
	//modelStack.PushMatrix();
	//modelStack.Rotate(5.5 * rotateAngle, 0, 1, 0);
	//modelStack.Translate(1.7, 0, 0);
	//modelStack.Scale(0.1, 0.1, 0.1);
	//modelStack.Rotate(2 * rotateAngle, 0, 1, 0);
	//MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	//glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	//meshList[GEO_EARTHM]->Render();
	//modelStack.PopMatrix();//MOON POP

	//modelStack.PopMatrix();// EARTH POP

	////MARS
	//modelStack.PushMatrix();
	//modelStack.Rotate(0.5 * rotateAngle, 0, 1, 0);
	//modelStack.Translate(11, 0, 0);
	//modelStack.Scale(0.55, 0.55, 0.55);
	//modelStack.Rotate(2 * rotateAngle, 0, 1, 0);
	//MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	//glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	//meshList[GEO_MARS]->Render();
	////modelStack.PopMatrix();

	////MARS MOON1
	//modelStack.PushMatrix();
	//modelStack.Rotate(rotateAngle, 0, 1, 0);
	//modelStack.Translate(1.8, 0, 0);
	//modelStack.Scale(0.1, 0.1, 0.1);
	//modelStack.Rotate(2 * rotateAngle, 0, 1, 0);
	//MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	//glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	//meshList[GEO_MARSM]->Render();
	//modelStack.PopMatrix();

	////MARS MOON2
	//modelStack.PushMatrix();
	//modelStack.Rotate(2 * rotateAngle, 0, 1, 0);
	//modelStack.Translate(-2.5, 0, 0);
	//modelStack.Scale(0.1, 0.1, 0.1);
	//modelStack.Rotate(2 * rotateAngle, 0, 1, 0);
	//MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	//glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	//meshList[GEO_MARSM]->Render();
	//modelStack.PopMatrix();

	//modelStack.PopMatrix(); //MARS POP

	////JUPITER
	//modelStack.PushMatrix();
	//modelStack.Rotate(0.3 * rotateAngle, 0, 1, 0);
	//modelStack.Translate(14, 0, 0);
	//modelStack.Scale(0.7, 0.7, 0.7);
	//modelStack.Rotate(1.5 * rotateAngle, 0, 1, 0);
	//MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	//glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	//meshList[GEO_JUPITER]->Render();
	//modelStack.PopMatrix();

	////SATURN
	//modelStack.PushMatrix();
	//modelStack.Rotate(0.2 * rotateAngle, 0, 1, 0);
	//modelStack.Translate(18, 0, 0);
	//modelStack.Scale(0.6, 0.6, 0.6);
	//modelStack.Rotate(1.5 * rotateAngle, 0, 1, 0);
	//MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	//glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	//meshList[GEO_SATURN]->Render();

	//modelStack.PushMatrix();
	//modelStack.Rotate(rotateAngle, 0, 1, 0);
	//modelStack.Scale(2.5, 0.2, 2.5);
	//MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	//glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	//meshList[GEO_SATURNR]->Render();
	//modelStack.PopMatrix();

	//modelStack.PopMatrix();//SATURN POP

	//modelStack.PopMatrix();
}

void Scene4::Exit()
{
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}
