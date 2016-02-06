#include "Assignment3.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"
#include "LoadTGA.h"

#include "Application.h"
#include "MeshBuilder.h"
#include "Utility.h"
#include <sstream>

Assignment3::Assignment3()
{
}

Assignment3::~Assignment3()
{
}

void Assignment3::Init()
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

	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	m_programID = LoadShaders("Shader//Texture.vertexshader", "Shader//Text.fragmentshader");

	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");
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

	m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
	m_parameters[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[0].spotDirection");
	m_parameters[U_LIGHT0_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[0].cosCutoff");
	m_parameters[U_LIGHT0_COSINNER] = glGetUniformLocation(m_programID, "lights[0].cosInner");
	m_parameters[U_LIGHT0_EXPONENT] = glGetUniformLocation(m_programID, "lights[0].exponent");

	m_parameters[U_LIGHT1_POSITION] = glGetUniformLocation(m_programID, "lights[1].position_cameraspace");
	m_parameters[U_LIGHT1_COLOR] = glGetUniformLocation(m_programID, "lights[1].color");
	m_parameters[U_LIGHT1_POWER] = glGetUniformLocation(m_programID, "lights[1].power");
	m_parameters[U_LIGHT1_KC] = glGetUniformLocation(m_programID, "lights[1].kC");
	m_parameters[U_LIGHT1_KL] = glGetUniformLocation(m_programID, "lights[1].kL");
	m_parameters[U_LIGHT1_KQ] = glGetUniformLocation(m_programID, "lights[1].kQ");
	m_parameters[U_LIGHT1_TYPE] = glGetUniformLocation(m_programID, "lights[1].type");
	m_parameters[U_LIGHT1_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[1].spotDirection");
	m_parameters[U_LIGHT1_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[1].cosCutoff");
	m_parameters[U_LIGHT1_COSINNER] = glGetUniformLocation(m_programID, "lights[1].cosInner");
	m_parameters[U_LIGHT1_EXPONENT] = glGetUniformLocation(m_programID, "lights[1].exponent");

	m_parameters[U_LIGHT2_POSITION] = glGetUniformLocation(m_programID, "lights[2].position_cameraspace");
	m_parameters[U_LIGHT2_COLOR] = glGetUniformLocation(m_programID, "lights[2].color");
	m_parameters[U_LIGHT2_POWER] = glGetUniformLocation(m_programID, "lights[2].power");
	m_parameters[U_LIGHT2_KC] = glGetUniformLocation(m_programID, "lights[2].kC");
	m_parameters[U_LIGHT2_KL] = glGetUniformLocation(m_programID, "lights[2].kL");
	m_parameters[U_LIGHT2_KQ] = glGetUniformLocation(m_programID, "lights[2].kQ");
	m_parameters[U_LIGHT2_TYPE] = glGetUniformLocation(m_programID, "lights[2].type");
	m_parameters[U_LIGHT2_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[2].spotDirection");
	m_parameters[U_LIGHT2_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[2].cosCutoff");
	m_parameters[U_LIGHT2_COSINNER] = glGetUniformLocation(m_programID, "lights[2].cosInner");
	m_parameters[U_LIGHT2_EXPONENT] = glGetUniformLocation(m_programID, "lights[2].exponent");

	m_parameters[U_LIGHT3_POSITION] = glGetUniformLocation(m_programID, "lights[3].position_cameraspace");
	m_parameters[U_LIGHT3_COLOR] = glGetUniformLocation(m_programID, "lights[3].color");
	m_parameters[U_LIGHT3_POWER] = glGetUniformLocation(m_programID, "lights[3].power");
	m_parameters[U_LIGHT3_KC] = glGetUniformLocation(m_programID, "lights[3].kC");
	m_parameters[U_LIGHT3_KL] = glGetUniformLocation(m_programID, "lights[3].kL");
	m_parameters[U_LIGHT3_KQ] = glGetUniformLocation(m_programID, "lights[3].kQ");
	m_parameters[U_LIGHT3_TYPE] = glGetUniformLocation(m_programID, "lights[3].type");
	m_parameters[U_LIGHT3_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[3].spotDirection");
	m_parameters[U_LIGHT3_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[3].cosCutoff");
	m_parameters[U_LIGHT3_COSINNER] = glGetUniformLocation(m_programID, "lights[3].cosInner");
	m_parameters[U_LIGHT3_EXPONENT] = glGetUniformLocation(m_programID, "lights[3].exponent");

	m_parameters[U_LIGHT4_POSITION] = glGetUniformLocation(m_programID, "lights[4].position_cameraspace");
	m_parameters[U_LIGHT4_COLOR] = glGetUniformLocation(m_programID, "lights[4].color");
	m_parameters[U_LIGHT4_POWER] = glGetUniformLocation(m_programID, "lights[4].power");
	m_parameters[U_LIGHT4_KC] = glGetUniformLocation(m_programID, "lights[4].kC");
	m_parameters[U_LIGHT4_KL] = glGetUniformLocation(m_programID, "lights[4].kL");
	m_parameters[U_LIGHT4_KQ] = glGetUniformLocation(m_programID, "lights[4].kQ");
	m_parameters[U_LIGHT4_TYPE] = glGetUniformLocation(m_programID, "lights[4].type");
	m_parameters[U_LIGHT4_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[4].spotDirection");
	m_parameters[U_LIGHT4_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[4].cosCutoff");
	m_parameters[U_LIGHT4_COSINNER] = glGetUniformLocation(m_programID, "lights[4].cosInner");
	m_parameters[U_LIGHT4_EXPONENT] = glGetUniformLocation(m_programID, "lights[4].exponent");

	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");
	// Get a handle for our "textColor" uniform
	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");

	glUseProgram(m_programID);
	glUniform1i(m_parameters[U_NUMLIGHTS], 5);

	Mtx44 projection;
	projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 2000.f);
	projectionStack.LoadMatrix(projection);

	//variable to rotate geometry
	rotateAngle = 0;
	drank = 0.f;
	textInstructions = true;

	//Initialize camera settings
	camera.Init(Vector3(0, 5, 15), Vector3(0, 7, 0), Vector3(0, 1, 0));
	
	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("GroundMesh", Color(1, 1, 1));
	meshList[GEO_QUAD]->textureID = LoadTGA("Image//GMesh_Texture.tga");
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000.f, 1000.f, 1000.f);

	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightlight", Color(1, 1, 1), 18.f, 36);

	meshList[GEO_INSTRUCTIONS] = MeshBuilder::GenerateQuad("Instructions", Color(1, 1, 1));
	meshList[GEO_INSTRUCTIONS]->textureID = LoadTGA("Image//Instructions.tga");

	initLight();
	initFerrisWheel();
	initBox();
	initTent();
	initShelf();
	initBeer();
	initDrink();
	initKeg();
	initIceCream();

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//Gothic.tga");
}

void Assignment3::initLight()
{
	light[0].type = Light::LIGHT_DIRECTIONAL;
	light[0].position.Set(0, 45, 30);
	light[0].color.Set(1, 1, 1);
	light[0].power = 2;
	light[0].kC = 1.f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;
	light[0].cosCutoff = cos(Math::DegreeToRadian(45));
	light[0].cosInner = cos(Math::DegreeToRadian(30));
	light[0].exponent = 3.f;
	light[0].spotDirection.Set(0.f, 1.f, 0.f);

	light[1].type = Light::LIGHT_POINT;
	light[1].position.Set(0, 25, -20);
	light[1].color.Set(1, 1, 1);
	light[1].power = 1;
	light[1].kC = 1.f;
	light[1].kL = 0.01f;
	light[1].kQ = 0.001f;
	light[1].cosCutoff = cos(Math::DegreeToRadian(45));
	light[1].cosInner = cos(Math::DegreeToRadian(30));
	light[1].exponent = 3.f;
	light[1].spotDirection.Set(0.f, -1.f, 0.f);

	light[2].type = Light::LIGHT_POINT;
	light[2].position.Set(0, 25, 120);
	light[2].color.Set(1, 1, 1);
	light[2].power = 1;
	light[2].kC = 1.f;
	light[2].kL = 0.01f;
	light[2].kQ = 0.001f;
	light[2].cosCutoff = cos(Math::DegreeToRadian(45));
	light[2].cosInner = cos(Math::DegreeToRadian(30));
	light[2].exponent = 3.f;
	light[2].spotDirection.Set(0.f, -1.f, 0.f);

	light[3].type = Light::LIGHT_POINT;
	light[3].position.Set(-50, 25, 45);
	light[3].color.Set(1, 1, 1);
	light[3].power = 1;
	light[3].kC = 1.f;
	light[3].kL = 0.01f;
	light[3].kQ = 0.001f;
	light[3].cosCutoff = cos(Math::DegreeToRadian(45));
	light[3].cosInner = cos(Math::DegreeToRadian(30));
	light[3].exponent = 3.f;
	light[3].spotDirection.Set(0.f, -1.f, 0.f);

	light[4].type = Light::LIGHT_POINT;
	light[4].position.Set(50, 25, 45);
	light[4].color.Set(1, 1, 1);
	light[4].power = 1;
	light[4].kC = 1.f;
	light[4].kL = 0.01f;
	light[4].kQ = 0.001f;
	light[4].cosCutoff = cos(Math::DegreeToRadian(45));
	light[4].cosInner = cos(Math::DegreeToRadian(30));
	light[4].exponent = 3.f;
	light[4].spotDirection.Set(0.f, -1.f, 0.f);

	//Make sure you pass uniform parameters after glUseProgram()
	glUniform1f(m_parameters[U_LIGHT0_TYPE], light[0].type);
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);
	glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF], light[0].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT0_COSINNER], light[0].cosInner);
	glUniform1f(m_parameters[U_LIGHT0_EXPONENT], light[0].exponent);

	glUniform1f(m_parameters[U_LIGHT1_TYPE], light[1].type);
	glUniform3fv(m_parameters[U_LIGHT1_COLOR], 1, &light[1].color.r);
	glUniform1f(m_parameters[U_LIGHT1_POWER], light[1].power);
	glUniform1f(m_parameters[U_LIGHT1_KC], light[1].kC);
	glUniform1f(m_parameters[U_LIGHT1_KL], light[1].kL);
	glUniform1f(m_parameters[U_LIGHT1_KQ], light[1].kQ);
	glUniform1f(m_parameters[U_LIGHT1_COSCUTOFF], light[1].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT1_COSINNER], light[1].cosInner);
	glUniform1f(m_parameters[U_LIGHT1_EXPONENT], light[1].exponent);

	glUniform1f(m_parameters[U_LIGHT2_TYPE], light[2].type);
	glUniform3fv(m_parameters[U_LIGHT2_COLOR], 1, &light[2].color.r);
	glUniform1f(m_parameters[U_LIGHT2_POWER], light[2].power);
	glUniform1f(m_parameters[U_LIGHT2_KC], light[2].kC);
	glUniform1f(m_parameters[U_LIGHT2_KL], light[2].kL);
	glUniform1f(m_parameters[U_LIGHT2_KQ], light[2].kQ);
	glUniform1f(m_parameters[U_LIGHT2_COSCUTOFF], light[2].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT2_COSINNER], light[2].cosInner);
	glUniform1f(m_parameters[U_LIGHT2_EXPONENT], light[2].exponent);

	glUniform1f(m_parameters[U_LIGHT3_TYPE], light[3].type);
	glUniform3fv(m_parameters[U_LIGHT3_COLOR], 1, &light[3].color.r);
	glUniform1f(m_parameters[U_LIGHT3_POWER], light[3].power);
	glUniform1f(m_parameters[U_LIGHT3_KC], light[3].kC);
	glUniform1f(m_parameters[U_LIGHT3_KL], light[3].kL);
	glUniform1f(m_parameters[U_LIGHT3_KQ], light[3].kQ);
	glUniform1f(m_parameters[U_LIGHT3_COSCUTOFF], light[3].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT3_COSINNER], light[3].cosInner);
	glUniform1f(m_parameters[U_LIGHT3_EXPONENT], light[3].exponent);

	glUniform1f(m_parameters[U_LIGHT4_TYPE], light[4].type);
	glUniform3fv(m_parameters[U_LIGHT4_COLOR], 1, &light[4].color.r);
	glUniform1f(m_parameters[U_LIGHT4_POWER], light[4].power);
	glUniform1f(m_parameters[U_LIGHT4_KC], light[4].kC);
	glUniform1f(m_parameters[U_LIGHT4_KL], light[4].kL);
	glUniform1f(m_parameters[U_LIGHT4_KQ], light[4].kQ);
	glUniform1f(m_parameters[U_LIGHT4_COSCUTOFF], light[4].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT4_COSINNER], light[4].cosInner);
	glUniform1f(m_parameters[U_LIGHT4_EXPONENT], light[4].exponent);
}

void Assignment3::initBox()
{
	meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1));
	meshList[GEO_FRONT]->textureID = LoadTGA("Image//Assignment3_Front.tga");
	meshList[GEO_BACK] = MeshBuilder::GenerateQuad("back", Color(1, 1, 1));
	meshList[GEO_BACK]->textureID = LoadTGA("Image//Assignment3_Back.tga");
	meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1));
	meshList[GEO_LEFT]->textureID = LoadTGA("Image//Assignment3_Left.tga");
	meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("right", Color(1, 1, 1));
	meshList[GEO_RIGHT]->textureID = LoadTGA("Image//Assignment3_Right.tga");
	meshList[GEO_TOP] = MeshBuilder::GenerateQuad("top", Color(1, 1, 1));
	meshList[GEO_TOP]->textureID = LoadTGA("Image//Assignment3_Up.tga");
	meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("down", Color(1, 1, 1));
	meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//Assignment3_Down.tga");
}

void Assignment3::initFerrisWheel()
{
	meshList[GEO_FERRISWHEEL] = MeshBuilder::GenerateOBJ("Tent", "OBJ//FerrisWheel.obj");
	meshList[GEO_FERRISWHEEL]->textureID = LoadTGA("Image//FerrisWheel_Texture.tga");
	meshList[GEO_CARRIAGE] = MeshBuilder::GenerateOBJ("Tent", "OBJ//Carriage.obj");
	meshList[GEO_CARRIAGE]->textureID = LoadTGA("Image//Carriage_Texture.tga");
}

void Assignment3::initTent()
{
	meshList[GEO_TENT] = MeshBuilder::GenerateOBJ("Tent", "OBJ//Tent.obj");
	meshList[GEO_TENT]->textureID = LoadTGA("Image//Tent_Texture.tga");
	meshList[GEO_TENT]->material.kSpecular.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_TENT]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_TENT]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
}

void Assignment3::initShelf()
{
	meshList[GEO_SHELF] = MeshBuilder::GenerateOBJ("Shelf", "OBJ//Shelf.obj");
	meshList[GEO_SHELF]->textureID = LoadTGA("Image//Shelf_Texture.tga");
	meshList[GEO_SHELF]->material.kSpecular.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_SHELF]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_SHELF]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
}

void Assignment3::initIceCream()
{
	meshList[GEO_ICECREAM] = MeshBuilder::GenerateOBJ("IceCream", "OBJ//IceCream.obj");
	meshList[GEO_ICECREAM]->textureID = LoadTGA("Image//IceCream_Texture.tga");

	meshList[GEO_ICECREAM1] = MeshBuilder::GenerateOBJ("IceCream1", "OBJ//IceCream.obj");
	meshList[GEO_ICECREAM1]->textureID = LoadTGA("Image//IceCream_Texture2.tga");

	meshList[GEO_ICECREAM2] = MeshBuilder::GenerateOBJ("IceCream2", "OBJ//IceCream.obj");
	meshList[GEO_ICECREAM2]->textureID = LoadTGA("Image//IceCream_Texture3.tga");
}

void Assignment3::initBeer()
{
	meshList[GEO_BEER] = MeshBuilder::GenerateOBJ("Beer", "OBJ//Beer.obj");
	meshList[GEO_BEER]->textureID = LoadTGA("Image//Beer_Full_Texture.tga");
	meshList[GEO_BEER]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_BEER]->material.kDiffuse.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_BEER]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_BEEER] = MeshBuilder::GenerateOBJ("Beer", "OBJ//Beer_Empty.obj");
	meshList[GEO_BEEER]->textureID = LoadTGA("Image//Beer_Empty_Texture.tga");
}

void Assignment3::initDrink()
{
	meshList[GEO_DRINK] = MeshBuilder::GenerateOBJ("Drink", "OBJ//Drink.obj");
	meshList[GEO_DRINK]->textureID = LoadTGA("Image//Drink_Texture.tga");
	meshList[GEO_DRINK]->material.kSpecular.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_DRINK]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_DRINK]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
}

void Assignment3::initKeg()
{
	meshList[GEO_KEG] = MeshBuilder::GenerateOBJ("KEG", "OBJ//Keg.obj");
	meshList[GEO_KEG]->textureID = LoadTGA("Image//Keg_Texture.tga");
	meshList[GEO_KEG]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_KEG]->material.kDiffuse.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_KEG]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
}

void Assignment3::RenderMesh(Mesh *mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
	if (enableLight)
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

	if (mesh->textureID > 0)
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	}
	else
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
	}
	mesh->Render();
	if (mesh->textureID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

static float ROT_LIMIT = 45.f;
static float SCALE_LIMIT = 5.f;

void Assignment3::Update(double dt)
{
	camera.Update(dt);
	FPS = 1 / dt;
	if (Application::IsKeyPressed('1')) //enable back face culling
		glEnable(GL_CULL_FACE);
	if (Application::IsKeyPressed('2')) //disable back face culling
		glDisable(GL_CULL_FACE);
	if (Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
	if (Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode

	//if (Application::IsKeyPressed('I'))
	//	light[0].position.y += (float)(LSPEED * dt);
	//if (Application::IsKeyPressed('K'))
	//	light[0].position.y -= (float)(LSPEED * dt);
	//if (Application::IsKeyPressed('J'))
	//	light[0].position.x -= (float)(LSPEED * dt);
	//if (Application::IsKeyPressed('L'))
	//	light[0].position.x += (float)(LSPEED * dt);
	//if (Application::IsKeyPressed('O'))
	//	light[0].position.z -= (float)(LSPEED * dt);
	//if (Application::IsKeyPressed('P'))
	//	light[0].position.z += (float)(LSPEED * dt);
	//if (Application::IsKeyPressed('Z'))
	//{
	//	//to do: switch light type to POINT and pass the information to shader
	//	light[0].type = Light::LIGHT_POINT;
	//	glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	//}
	//else if (Application::IsKeyPressed('X'))
	//{
	//	//to do: switch light type to DIRECTIONAL and pass the information to shader
	//	light[0].type = Light::LIGHT_DIRECTIONAL;
	//	glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	//}
	//else if (Application::IsKeyPressed('C'))
	//{
	//	//to do: switch light type to SPOT and pass the information to shader
	//	light[0].type = Light::LIGHT_SPOT;
	//	glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	//}

	if (Application::IsKeyPressed(VK_LBUTTON) && takenBeer == true)
	{
		drunk = true;
		textDrank = true;
	}
	else if (Application::IsKeyPressed('E') && takenBeer == false && camera.position.x > -2 && camera.position.x < 3 && camera.position.z < 10 && camera.position.z > 0)
	{
		takenBeer = true;
		holdBeer = true;
		textTaken = true;
	}
	if (drunk == true)
	{
		if (Application::IsKeyPressed('E') && takenBeer == true && ((camera.position.x >= -35.6f && camera.position.z >= 3) && (camera.position.x <= -25.8f && camera.position.z <= 17.4)))
		{
			drunk = false;
		}

		if ((camera.position.x >= -35.6f && camera.position.z >= 3) && (camera.position.x <= -25.8f && camera.position.z <= 17.4))
			textRefill = true;
	}

	if (Application::IsKeyPressed('E') && drunk == false && takenBeer == true && ((camera.position.x >= -35.6f && camera.position.z >= 3) && (camera.position.x <= -25.8f && camera.position.z <= 17.4)))
	{
		textDrunk = true;
	}
	else if (camera.position.x >= -25.8f || camera.position.z > 17.4)
	{
		textDrunk = false;
	}
	
	if (camera.position.x < -2 || camera.position.x > 3 || camera.position.z > 10)
		textTaken = false;

	if (Application::IsKeyPressed('W') || Application::IsKeyPressed('A') || Application::IsKeyPressed('S') || Application::IsKeyPressed('D'))
	{
		textDrank = false;
	}

	if (Application::IsKeyPressed('E'))
	{
		textRefill = false;
		textInstructions = false;
	}


	rotateAngle += (float)(10 * dt);
}

void Assignment3::Render()
{
	// Render VBO here
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	viewStack.LoadIdentity();
	viewStack.LookAt(camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z);
	modelStack.LoadIdentity();

	//RenderMesh(meshList[GEO_AXES], false);

	modelStack.PushMatrix();
	modelStack.Translate(0, -8, 10);
	modelStack.Scale(400, 400, 400);
	RenderMesh(meshList[GEO_QUAD], true);
	modelStack.PopMatrix();
		
	if (textInstructions == true)
	{
		modelStack.PushMatrix();
		modelStack.Translate(0, 10, 0);
		modelStack.Rotate(90, 0, 0, 1);
		modelStack.Rotate(90, 1, 0, 0);
		modelStack.Scale(5, 5, 5);
		RenderMesh(meshList[GEO_INSTRUCTIONS], false);
		modelStack.PopMatrix();
	}

	RenderLight();
	RenderBox();
	RenderFerrisWheel();
	RenderTent();
	RenderShelf();
	RenderDrink();
	RenderIceCream();
	RenderKeg();
	RenderBeer();

	std::stringstream MOO;
	MOO << "FPS : " << FPS;
	RenderTextOnScreen(meshList[GEO_TEXT], MOO.str(), Color(0, 1, 0), 2, 0, 15);

	std::stringstream MEOWx;
	MEOWx << "Position X : " << camera.position.x;
	RenderTextOnScreen(meshList[GEO_TEXT], MEOWx.str(), Color(0, 1, 0), 2, 0, 2.5f);

	std::stringstream MEOWy;
	MEOWy << "Position Z : " << camera.position.z;
	RenderTextOnScreen(meshList[GEO_TEXT], MEOWy.str(), Color(0, 1, 0), 2, 0, 1.5f);



	if (textDrunk == true)
		RenderTextOnScreen(meshList[GEO_TEXT], "You Have Refilled Your Beer", Color(0, 1, 1), 2, 12, 14);

	if (takenBeer == false && camera.position.x > -2 && camera.position.x < 3 && camera.position.z < 10 && camera.position.z > 0)
		RenderTextOnScreen(meshList[GEO_TEXT], "Press 'E' to Take Beer", Color(0, 1, 1), 2, 15, 16);

	if (takenBeer == true && drunk == false && textTaken == true && camera.position.x > -2 && camera.position.x < 3 && camera.position.z < 10 && camera.position.z > 0)
		RenderTextOnScreen(meshList[GEO_TEXT], "You Have Taken A Mug of Beer", Color(0, 1, 1), 2, 13, 15);

	if (textDrank == true)
		RenderTextOnScreen(meshList[GEO_TEXT], "You Have Drank That Beer", Color(0, 1, 1), 2, 13, 15);

	if (textRefill == true)
		RenderTextOnScreen(meshList[GEO_TEXT], "Press 'E' To Refill Beer", Color(0, 1, 1), 2, 13, 16);

}
void Assignment3::RenderText(Mesh* mesh, std::string text, Color color)
{
	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;

	glDisable(GL_DEPTH_TEST);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.0f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	glEnable(GL_DEPTH_TEST);
}

void Assignment3::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
{
	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;

	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Scale(size, size, size);
	modelStack.Translate(x, y, 0);

	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 0.5f + 0.5f, 0.5f, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	glEnable(GL_DEPTH_TEST);

	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
}

void Assignment3::Exit()
{
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}

void Assignment3::RenderLight()
{
	if (light[0].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(light[0].position.x, light[0].position.y, light[0].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if (light[0].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light[0].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT0_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
	}

	if (light[1].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(light[1].position.x, light[1].position.y, light[1].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if (light[1].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[1].position;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light[1].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT1_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[1].position;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace.x);
	}

	if (light[2].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(light[1].position.x, light[2].position.y, light[2].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT2_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if (light[2].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[2].position;
		glUniform3fv(m_parameters[U_LIGHT2_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light[2].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT2_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[2].position;
		glUniform3fv(m_parameters[U_LIGHT2_POSITION], 1, &lightPosition_cameraspace.x);
	}

	if (light[3].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(light[3].position.x, light[3].position.y, light[3].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT3_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if (light[3].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[3].position;
		glUniform3fv(m_parameters[U_LIGHT3_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light[3].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT3_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[3].position;
		glUniform3fv(m_parameters[U_LIGHT3_POSITION], 1, &lightPosition_cameraspace.x);
	}

	if (light[4].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(light[4].position.x, light[4].position.y, light[4].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT4_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if (light[4].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[4].position;
		glUniform3fv(m_parameters[U_LIGHT4_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light[4].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT4_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[4].position;
		glUniform3fv(m_parameters[U_LIGHT4_POSITION], 1, &lightPosition_cameraspace.x);
	}

	modelStack.PushMatrix();
	modelStack.Translate(light[0].position.x, light[0].position.y, light[0].position.z);
	RenderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(light[1].position.x, light[1].position.y, light[1].position.z);
	RenderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(light[2].position.x, light[2].position.y, light[2].position.z);
	RenderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(light[3].position.x, light[3].position.y, light[3].position.z);
	RenderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(light[4].position.x, light[4].position.y, light[4].position.z);
	RenderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();
}

void Assignment3::RenderBox()
{
	modelStack.PushMatrix();
	modelStack.Translate(499, 0, 0);
	modelStack.Rotate(90, 0, 0, 1);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_RIGHT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-499, 0, 0);
	modelStack.Rotate(180, 1, 0, 0);
	modelStack.Rotate(-90, 0, 0, 1);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_LEFT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 499);
	modelStack.Rotate(90, 0, 0, 1);
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_BACK], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, -499);
	modelStack.Rotate(90, 0, 0, 1);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_FRONT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, -499, 0);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_BOTTOM], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 499, 0);
	modelStack.Rotate(180, 1, 0, 0);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_TOP], false);
	modelStack.PopMatrix();
}

void Assignment3::RenderTent()
{
		modelStack.PushMatrix();
		modelStack.Translate(0, -7, -3);
		modelStack.Scale(10, 10, 10);
		RenderMesh(meshList[GEO_TENT], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(-43, -7, 43);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Scale(10, 10, 10);
		RenderMesh(meshList[GEO_TENT], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(0, -7, 87);
		modelStack.Rotate(180, 0, 1, 0);
		modelStack.Scale(10, 10, 10);
		RenderMesh(meshList[GEO_TENT], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(42, -7, 43);
		modelStack.Rotate(270, 0, 1, 0);
		modelStack.Scale(10, 10, 10);
		RenderMesh(meshList[GEO_TENT], true);
		modelStack.PopMatrix();
}

void Assignment3::RenderBeer()
{
	for (float f = -15; f < 0; f += 3)
	{
		modelStack.PushMatrix();
		modelStack.Translate(f, 4, -2.5f);
		modelStack.Rotate(90, 0, 270, 0);
		RenderMesh(meshList[GEO_BEER], true);
		modelStack.PopMatrix();
	}

	for (float f = 3; f < 18; f += 3)
	{
		modelStack.PushMatrix();
		modelStack.Translate(f, 4, -2.5f);
		modelStack.Rotate(90, 0, 270, 0);
		RenderMesh(meshList[GEO_BEER], true);
		modelStack.PopMatrix();
	}

	if (takenBeer == false)
	{	
		modelStack.PushMatrix();
		modelStack.Translate(0, 4, -2.5f);
		modelStack.Rotate(90, 0, 270, 0);
		RenderMesh(meshList[GEO_BEER], true);
		modelStack.PopMatrix();
	}
	else if (takenBeer == true &&  drunk == false)
	{
		glDisable(GL_DEPTH_TEST);
		Mtx44 ortho;
		ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
		projectionStack.PushMatrix();
		projectionStack.LoadMatrix(ortho);
		viewStack.PushMatrix();
		viewStack.LoadIdentity(); //No need camera for ortho mode
		modelStack.PushMatrix();
		modelStack.LoadIdentity(); //Reset modelStack

		modelStack.Translate(60, 3, -2);
		modelStack.Rotate(50, 0, 1, 0);
		modelStack.Scale(10, 10, 10);
		RenderMesh(meshList[GEO_BEER], true);

		projectionStack.PopMatrix();
		viewStack.PopMatrix();
		modelStack.PopMatrix();
	}
	else if (takenBeer == true && holdBeer == true && drunk == true)
	{
		glBlendFunc(1.5, 1);
		glDisable(GL_DEPTH_TEST);
		Mtx44 ortho;
		ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
		projectionStack.PushMatrix();
		projectionStack.LoadMatrix(ortho);
		viewStack.PushMatrix();
		viewStack.LoadIdentity(); //No need camera for ortho mode
		modelStack.PushMatrix();
		modelStack.LoadIdentity(); //Reset modelStack

		modelStack.Translate(60, 3, -2);
		modelStack.Rotate(50, 0, 1, 0);
		modelStack.Scale(10, 10, 10);
		RenderMesh(meshList[GEO_BEEER], true);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		projectionStack.PopMatrix();
		viewStack.PopMatrix();
		modelStack.PopMatrix();
	}
	glEnable(GL_DEPTH_TEST);
}

void Assignment3::RenderDrink()
{
	if (takenDrink == false)
	{
		modelStack.PushMatrix();
		modelStack.Translate(-42, 3.9f, 42);
		modelStack.Rotate(90, 0, 1, 0);
		RenderMesh(meshList[GEO_DRINK], true);
		modelStack.PopMatrix();
	}
	if (takenDrink == true)
	{
		glDisable(GL_DEPTH_TEST);
		Mtx44 ortho;
		ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
		projectionStack.PushMatrix();
		projectionStack.LoadMatrix(ortho);
		viewStack.PushMatrix();
		viewStack.LoadIdentity(); //No need camera for ortho mode
		modelStack.PushMatrix();
		modelStack.LoadIdentity(); //Reset modelStack

		modelStack.Translate(60, 3, 0);
		modelStack.Rotate(30, 1, 0, 0);
		modelStack.Rotate(50, 0, 1, 0);
		modelStack.Scale(10, 10, 10);
		RenderMesh(meshList[GEO_DRINK], true);

		projectionStack.PopMatrix();
		viewStack.PopMatrix();
		modelStack.PopMatrix();
	}
	glEnable(GL_DEPTH_TEST);
}

void Assignment3::RenderShelf()
{
	modelStack.PushMatrix();
	modelStack.Translate(0,-5,-45);
	modelStack.Rotate(270, 0, 1, 0);
	modelStack.Scale(5, 4, 2);
	RenderMesh(meshList[GEO_SHELF], true);
	modelStack.PopMatrix();
}

void Assignment3::RenderIceCream()
{
	modelStack.PushMatrix();
	modelStack.Translate(-5, 2, -45);
	//modelStack.Scale(2, 2, 2);
	RenderMesh(meshList[GEO_ICECREAM], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 2, -45);
	//modelStack.Scale(2, 2, 2);
	RenderMesh(meshList[GEO_ICECREAM1], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(5, 2, -45);
	//modelStack.Scale(2, 2, 2);
	RenderMesh(meshList[GEO_ICECREAM2], true);
	modelStack.PopMatrix();
}

void Assignment3::RenderKeg()
{
	modelStack.PushMatrix();
	modelStack.Translate(-33.6f, -3, -6);
	modelStack.Scale(5, 5, 5);
	//modelStack.Rotate(55, 0, 1, 0);
	RenderMesh(meshList[GEO_KEG], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-46, -3, 76.5);
	modelStack.Scale(5, 5, 5);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[GEO_KEG], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(33.6f, -3, 90);
	modelStack.Scale(5, 5, 5);
	modelStack.Rotate(180, 0, 1, 0);
	RenderMesh(meshList[GEO_KEG], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(44.6f, -3, 9.5);
	modelStack.Scale(5, 5, 5);
	modelStack.Rotate(270, 0, 1, 0);
	RenderMesh(meshList[GEO_KEG], true);
	modelStack.PopMatrix();
}

void Assignment3::RenderFerrisWheel()
{
	modelStack.PushMatrix();
	modelStack.Translate(-200, 80, 42);
	modelStack.Scale(9, 9, 9);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[GEO_FERRISWHEEL], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-100, 1, 150);
	modelStack.Scale(4, 4, 4);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[GEO_CARRIAGE], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-183, 300, 42.5f);
	modelStack.Scale(7, 7, 7);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[GEO_CARRIAGE], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-183, 20, 42.5f);
	modelStack.Scale(7, 7, 7);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[GEO_CARRIAGE], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-183, 95, 150);
	modelStack.Scale(7, 7, 7);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[GEO_CARRIAGE], true);
	modelStack.PopMatrix();
}