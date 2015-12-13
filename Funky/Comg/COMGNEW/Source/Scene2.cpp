#include "Scene2.h"
#include "GL\glew.h"
#include "Mtx44.h"
#include "Application.h"
#include "shader.hpp"

Scene2::Scene2()
{

}

Scene2::~Scene2()
{

}

void Scene2::Init()
{
	totalAngle = 90;
	rotateAngle = 5;
	translateX = 5;
	scaleAll = 5; 

	// Set background color to dark blue
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Init VBO here

	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	// Generate buffers
	glGenBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glGenBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);

	// An array of 3 vectors which represents 3 vertices
	static const GLfloat vertex_buffer_data[] = {
		0.0f, 1.0f, 0.0f,   //1st vertex
		-1.0f, -1.0f, 0.0f,  //2nd vertex
		1.0f, -1.0f, 0.0f, //3rd vertex
	};

	// Set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);	
	// Transfer vertices to OpenGL
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);
	
	static const GLfloat color_buffer_data[] = {
		1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data, GL_STATIC_DRAW);

	//Load vertex and fragment shaders
	m_programID = LoadShaders(
		"Shader//TransformVertexShader.vertexshader",
		"Shader//SimpleFragmentShader.fragmentshader");

	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");

	//Use our shader
	glUseProgram(m_programID);
}

void Scene2::Update(double dt)
{
	if (Application::IsKeyPressed(VK_SPACE))
	{
		if (rotateAngle >= 90)
		{
			rotateAngle = 0;
		}
		else
		{
			rotateAngle += (float)(10 * dt);
		}

		translateX += (float)(10 * dt);
		if (translateX > 40)
		{
			translateX = -40;
		}

		scaleAll += (float)(2 * dt);
		if (scaleAll > 5)
		{
			scaleAll = 0;
		}
	}
}

void Scene2::Render()
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
	projection.SetToOrtho(-40, 40, -30, 30, -10, 10);


	

	// Clear color buffer every frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Render VBO here
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	//This is 1st triangle
	scale.SetToScale(5, 5, 5);
	rotate.SetToRotation(rotateAngle, 0, 0, 1);
	translate.SetToTranslation(0, 0, 0);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3); // Draw the triangle


	//This is 2nd Triangle
	scale.SetToScale(1, 1, 1);
	rotate.SetToRotation(100, 0, 0, 1);
	translate.SetToTranslation(translateX, 20, 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);


	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3); // Draw the triangle


	//This is 3rd Triangle
	scale.SetToScale(scaleAll, scaleAll, scaleAll);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(0, -20, 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);


	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3); // Draw the triangle

	//Draw the triangle
	//glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void Scene2::Exit()
{
	// Cleanup VBO here
	glDeleteBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glDeleteBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}