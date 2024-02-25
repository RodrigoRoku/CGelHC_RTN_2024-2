//Práctica 2 semestre 2024-2: índices, mesh, proyecciones, transformaciones geométricas
#include <stdio.h>
#include <string.h>
#include<cmath>
#include<vector>
#include <glew.h>
#include <glfw3.h>
//glm
#include<glm.hpp>
#include<gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp>
//clases para dar orden y limpieza al código
#include"Mesh.h"
#include"Shader.h"
#include"Window.h"
//Dimensiones de la ventana
const float toRadians = 3.14159265f/180.0; //grados a radianes
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<MeshColor*> meshColorList;
std::vector<Shader>shaderList;
//Vertex Shader
static const char* vShader = "shaders/shader.vert";
static const char* fShader = "shaders/shader.frag";
static const char* vShaderColor = "shaders/shadercolor.vert";
static const char* fShaderColor = "shaders/shadercolor.frag";




//shaders nuevos se crearían acá

static const char* vShaderRojo = "shaders/redShader.vert";
static const char* fShaderRojo = "shaders/redShader.frag";

static const char* vShaderVerde = "shaders/greenShader.vert";
static const char* fShaderVerde = "shaders/greenShader.frag";

static const char* vShaderAzul = "shaders/blueShader.vert";
static const char* fShaderAzul = "shaders/blueShader.frag";

static const char* vShaderCafe = "shaders/brownShader.vert";
static const char* fShaderCafe = "shaders/brownShader.frag";

static const char* vShaderVerdeOscuro = "shaders/darkGreenShader.vert";
static const char* fShaderVerdeOscuro = "shaders/darkGreenShader.frag";

float angulo = 0.0f;

//color café en RGB : 0.478, 0.255, 0.067

//Pirámide triangular regular
void CreaPiramide()
{

	unsigned int indices[] = { 
		0,1,2,
		1,3,2,
		3,0,2,
		1,0,3
		
	};
	GLfloat vertices[] = {
		-0.5f, -0.5f,0.0f,	//0
		0.5f,-0.5f,0.0f,	//1
		0.0f,0.5f, -0.25f,	//2
		0.0f,-0.5f,-0.5f,	//3

	};
	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj1);
}

//Vértices de un cubo
void CrearCubo()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

GLfloat cubo_vertices[] = {
	// front
	-0.5f, -0.5f,  0.5f,
	0.5f, -0.5f,  0.5f,
	0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	// back
	-0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f, -0.5f
};
Mesh *cubo = new Mesh();
cubo->CreateMesh(cubo_vertices, cubo_indices,24, 36);
meshList.push_back(cubo);
}

void CrearLetrasyFiguras()
{
	int numVertices = 0;
	GLfloat vertices_letras[] = {	
			//X			Y			Z			R		G		B
		//R
		//rectanglo vertical Izq
			-0.6f,		0.4f,		0.0f,		0.0f,	0.0f,	1.0f,
			-0.6f,		-0.3f,		0.0f,		0.0f,	0.0f,	1.0f,
			-0.5f,		-0.3f,		0.0f,		0.0f,	0.0f,	1.0f,

			-0.6f,		0.4f,		0.0f,		0.0f,	0.0f,	1.0f,
			-0.5f,		-0.3f,		0.0f,		0.0f,	0.0f,	1.0f,
			-0.5f,		0.4f,		0.0f,		0.0f,	0.0f,	1.0f,

		//rectanglo vertical Der
			-0.4f,		0.4f,		0.0f,		0.0f,	0.0f,	1.0f,
			-0.4f,		0.1f,		0.0f,		0.0f,	0.0f,	1.0f,
			-0.3f,		0.1f,		0.0f,		0.0f,	0.0f,	1.0f,

			-0.4f,		0.4f,		0.0f,		0.0f,	0.0f,	1.0f,
			-0.3f,		0.1f,		0.0f,		0.0f,	0.0f,	1.0f,
			-0.3f,		0.4f,		0.0f,		0.0f,	0.0f,	1.0f,

		//rectanglo Horizontal Sup
			-0.6f,		0.3f,		0.0f,		0.0f,	0.0f,	1.0f,
			-0.6f,		0.4f,		0.0f,		0.0f,	0.0f,	1.0f,
			-0.4f,		0.3f,		0.0f,		0.0f,	0.0f,	1.0f,

			-0.4f,		0.3f,		0.0f,		0.0f,	0.0f,	1.0f,
			-0.6f,		0.4f,		0.0f,		0.0f,	0.0f,	1.0f,
			-0.4f,		0.4f,		0.0f,		0.0f,	0.0f,	1.0f,

			//rectanglo horizontal inf

			-0.6f,		0.1f,		0.0f,		0.0f,	0.0f,	1.0f,
			-0.6f,		0.2f,		0.0f,		0.0f,	0.0f,	1.0f,
			-0.4f,		0.1f,		0.0f,		0.0f,	0.0f,	1.0f,
												
			-0.4f,		0.1f,		0.0f,		0.0f,	0.0f,	1.0f,
			-0.6f,		0.2f,		0.0f,		0.0f,	0.0f,	1.0f,
			-0.4f,		0.2f,		0.0f,		0.0f,	0.0f,	1.0f,

			//linea Diagonal

			-0.5f,		0.1f,		0.0f,		0.0f,	0.0f,	1.0f,
			-0.4f,		0.1f,		0.0f,		0.0f,	0.0f,	1.0f,
			-0.4f,		-0.3f,		0.0f,		0.0f,	0.0f,	1.0f,

			-0.4f,		0.1f,		0.0f,		0.0f,	0.0f,	1.0f,
			-0.3f,		-0.3f,		0.0f,		0.0f,	0.0f,	1.0f,
			-0.4f,		-0.3f,		0.0f,		0.0f,	0.0f,	1.0f,

		//T
			//rectanglo vertical
			-0.05f,		0.3f,		0.0f,		0.0f,	1.0f,	1.0f,
			-0.05f,		-0.3f,		0.0f,		0.0f,	1.0f,	1.0f,
			0.05f,		-0.3f,		0.0f,		0.0f,	1.0f,	1.0f,
			0.05f,		0.3f,		0.0f,		0.0f,	1.0f,	1.0f,
			0.05f,		-0.3f,		0.0f,		0.0f,	1.0f,	1.0f,
			-0.05f,		0.3f,		0.0f,		0.0f,	1.0f,	1.0f,

			//rectanglo horizontal
			- 0.2f,		0.3f,		0.0f,		0.0f,	1.0f,	1.0f,
			-0.2f,		0.4f,		0.0f,		0.0f,	1.0f,	1.0f,
			0.2f,		0.3f,		0.0f,		0.0f,	1.0f,	1.0f,
			0.2f,		0.3f,		0.0f,		0.0f,	1.0f,	1.0f,
			-0.2f,		0.4f,		0.0f,		0.0f,	1.0f,	1.0f,
			0.2f,		0.4f,		0.0f,		0.0f,	1.0f,	1.0f,

			//N

			//rectanglo vertical Izq
			0.3f,		0.4f,		0.0f,		1.0f,	0.0f,	1.0f,
			0.3f,		-0.3f,		0.0f,		1.0f,	0.0f,	1.0f,
			0.4f,		-0.3f,		0.0f,		1.0f,	0.0f,	1.0f,

			0.3f,		 0.4f,		0.0f,		1.0f,	0.0f,	1.0f,
			0.4f,		-0.3f,		0.0f,		1.0f,	0.0f,	1.0f,
			0.4f,		0.4f,		0.0f,		1.0f,	0.0f,	1.0f,

			//rectanglo vertical Der

			0.6f,		0.4f,		0.0f,		1.0f,	0.0f,	1.0f,
			0.6f,		-0.3f,		0.0f,		1.0f,	0.0f,	1.0f,
			0.7f,		-0.3f,		0.0f,		1.0f,	0.0f,	1.0f,

			0.6f,		0.4f,		0.0f,		1.0f,	0.0f,	1.0f,
			0.7f,		-0.3f,		0.0f,		1.0f,	0.0f,	1.0f,
			0.7f,		0.4f,		0.0f,		1.0f,	0.0f,	1.0f,

			//linea Diagonal

			0.4f,		0.4f,		0.0f,		1.0f,	0.0f,	1.0f,
			0.4f,		0.15f,		0.0f,		1.0f,	0.0f,	1.0f,
			0.6f,		-0.3f,		0.0f,		1.0f,	0.0f,	1.0f,

			0.4f,		0.4f,		0.0f,		1.0f,	0.0f,	1.0f,
			0.6f,		-0.05f,		0.0f,		1.0f,	0.0f,	1.0f,
			0.6f,		-0.3f,		0.0f,		1.0f,	0.0f,	1.0f


			/*-1.0f,	-1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
			*								 0.0f,	1.0f,	1.0f,
			1.0f,	-1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
			1.0f,	1.0f,		0.5f,			0.0f,	0.0f,	1.0f,*/
			/*1.0f,	1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
			-1.0f,  1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
			-1.0f,	-1.0f,		0.5f,			1.0f,	0.0f,	0.0f,*/
			
	};

	numVertices = (sizeof(vertices_letras) / sizeof(vertices_letras[0]));

	MeshColor *letras = new MeshColor();
	letras->CreateMeshColor(vertices_letras, numVertices);
	meshColorList.push_back(letras); //0

	printf("Tamanio: \n %d", (sizeof(vertices_letras)/sizeof(vertices_letras[0])));

	GLfloat vertices_triangulorojo[] = {
		//X			Y			Z			R		G		B
		-1.0f,	-1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
		1.0f,	-1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.0f,	1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
		
	};

	MeshColor* triangulorojo = new MeshColor();
	triangulorojo->CreateMeshColor(vertices_triangulorojo, 18);
	meshColorList.push_back(triangulorojo);//1

	GLfloat vertices_cuadradoverde[] = {
		//X			Y			Z			R		G		B
		-0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		-0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		-0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,

	};

	MeshColor* cuadradoverde = new MeshColor();
	cuadradoverde->CreateMeshColor(vertices_cuadradoverde, 36);
	meshColorList.push_back(cuadradoverde);//2

	GLfloat vertices_trianguloazul[] = {
		//X			Y			Z			R		G		B
		-1.0f,	-1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
		1.0f,	-1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
		0.0f,	1.0f,		0.5f,			0.0f,	0.0f,	1.0f,

	};

	MeshColor* trianguloazul = new MeshColor();
	trianguloazul->CreateMeshColor(vertices_trianguloazul, 18);
	meshColorList.push_back(trianguloazul);//3

	GLfloat vertices_trianguloverde[] = {
		//X			Y			Z			R		G		B
		-1.0f,	-1.0f,		0.5f,			0.0f,	0.5f,	0.0f,
		1.0f,	-1.0f,		0.5f,			0.0f,	0.5f,	0.0f,
		0.0f,	1.0f,		0.5f,			0.0f,	0.5f,	0.0f,



	};

	MeshColor* trianguloverde = new MeshColor();
	trianguloverde->CreateMeshColor(vertices_trianguloverde, 18);
	meshColorList.push_back(trianguloverde);//4

	GLfloat vertices_cuadradorojo[] = {
		//X			Y			Z			R		G		B
		-0.5f,	-0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.5f,	-0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		-0.5f,	-0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		-0.5f,	0.5f,		0.5f,			1.0f,	0.0f,	0.0f,

	};

	MeshColor* cuadradorojo = new MeshColor();
	cuadradorojo->CreateMeshColor(vertices_cuadradorojo, 36);
	meshColorList.push_back(cuadradorojo);//5

	GLfloat vertices_cuadradoverde2[] = {
		//X			Y			Z			R		G		B
		-0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		-0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		-0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,

	};

	MeshColor* cuadradoverde2 = new MeshColor();
	cuadradoverde2->CreateMeshColor(vertices_cuadradoverde2, 36);
	meshColorList.push_back(cuadradoverde2);//6

	GLfloat vertices_cuadradocafe[] = {
		//X			Y			Z			R		G		B
		-0.5f,	-0.5f,		0.5f,			0.478f,	0.255f,	0.067f,
		0.5f,	-0.5f,		0.5f,			0.478f,	0.255f,	0.067f,
		0.5f,	0.5f,		0.5f,			0.478f,	0.255f,	0.067f,
		-0.5f,	-0.5f,		0.5f,			0.478f,	0.255f,	0.067f,
		0.5f,	0.5f,		0.5f,			0.478f,	0.255f,	0.067f,
		-0.5f,	0.5f,		0.5f,			0.478f,	0.255f,	0.067f,

	};

	MeshColor* cuadradocafe = new MeshColor();
	cuadradocafe->CreateMeshColor(vertices_cuadradocafe, 36);
	meshColorList.push_back(cuadradocafe);//7


}


void CreateShaders()
{

	Shader *shader1 = new Shader(); //shader para usar índices: objetos: cubo y  pirámide
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);

	Shader *shader2 = new Shader();//shader para usar color como parte del VAO: letras 
	shader2->CreateFromFiles(vShaderColor, fShaderColor);
	shaderList.push_back(*shader2);

	//Crear Shader de color y añadir a la lista de shaders
	Shader* shader3 = new Shader();
	shader3->CreateFromFiles(vShaderRojo, fShaderRojo);
	shaderList.push_back(*shader3);//2

	Shader* shader4 = new Shader();
	shader4->CreateFromFiles(vShaderVerde, fShaderVerde);
	shaderList.push_back(*shader4);//3

	Shader* shader5 = new Shader();
	shader5->CreateFromFiles(vShaderAzul, fShaderAzul);
	shaderList.push_back(*shader5);//4

	Shader* shader6 = new Shader();
	shader6->CreateFromFiles(vShaderCafe, fShaderCafe);
	shaderList.push_back(*shader6);//5

	Shader* shader7 = new Shader();
	shader7->CreateFromFiles(vShaderVerdeOscuro, fShaderVerdeOscuro);
	shaderList.push_back(*shader7);//6
}


int main()
{
	mainWindow = Window(800, 600);
	mainWindow.Initialise();
	CreaPiramide(); //índice 0 en MeshList
	CrearCubo();//índice 1 en MeshList
	CrearLetrasyFiguras(); //usa MeshColor, índices en MeshColorList
	CreateShaders();
	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	int opcion = 0, shader = 0, cont = 0;; //modificar para renderizar diferentes elementos en pantalla. 
	//Projection: Matriz de Dimensión 4x4 para indicar si vemos en 2D( orthogonal) o en 3D) perspectiva
	glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
	//glm::mat4 projection = glm::perspective(glm::radians(60.0f)	,mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);
	
	//Model: Matriz de Dimensión 4x4 en la cual se almacena la multiplicación de las transformaciones geométricas.
	glm::mat4 model(1.0); //fuera del while se usa para inicializar la matriz con una identidad
	
	//Loop mientras no se cierra la ventana


	opcion = 2; //1) Letras 2) Casa con pirámides y cubos

	//shader = 2;//2) Rojo, 3) verde, 4) azul, 5)Cafe 6) verdeOscuro

	while (!mainWindow.getShouldClose())
	{
		//Recibir eventos del usuario
		glfwPollEvents();
		//Limpiar la ventana
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad

		switch(opcion)
		{

				case 1:
					shaderList[1].useShader();
					uniformModel = shaderList[1].getModelLocation();
					uniformProjection = shaderList[1].getProjectLocation();
					glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));

					model = glm::mat4(1.0);
					model = glm::translate(model, glm::vec3(0.0f,0.0f,-4.0f));
					glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
					meshColorList[0]->RenderMeshColor();
					break;

				case 2:


					//Techo 	Centro en (0,0), base = 1, altura = 1
					shaderList[4].useShader();
					uniformModel = shaderList[4].getModelLocation();
					uniformProjection = shaderList[4].getProjectLocation();
					model = glm::mat4(1.0);
					model = glm::translate(model, glm::vec3(0.0f, 0.4f, -4.0f));
					model = glm::scale(model, glm::vec3(1.0f, 0.8f, 0.8f));
					glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
					glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
					meshList[0]->RenderMesh();

					//Pared 
					shaderList[2].useShader();
					uniformModel = shaderList[2].getModelLocation();
					uniformProjection = shaderList[2].getProjectLocation();
					model = glm::mat4(1.0);
					model = glm::translate(model, glm::vec3(0.0f, -0.5f, -5.0f));
					model = glm::scale(model, glm::vec3(0.8f, 1.0f, 0.8f));
					glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
					glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
					meshList[1]->RenderMesh();

					//Ventana 1
					shaderList[3].useShader();
					uniformModel = shaderList[3].getModelLocation();
					uniformProjection = shaderList[3].getProjectLocation();
					glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));

					model = glm::mat4(1.0);
					model = glm::translate(model, glm::vec3(-0.2f, -0.25f, -4.0f));
					model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.2f));
					glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
					meshList[1]->RenderMesh();

					//Ventana 2
					model = glm::mat4(1.0);
					model = glm::translate(model, glm::vec3(0.2f, -0.25f, -4.0f));
					model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.2f));
					glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
					meshList[1]->RenderMesh();

					//Puerta
					model = glm::mat4(1.0);
					model = glm::translate(model, glm::vec3(0.0f, -0.85f, -4.0f));
					model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.2f));
					glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
					meshList[1]->RenderMesh();

					//Follaje 1
					shaderList[6].useShader();
					uniformModel = shaderList[6].getModelLocation();
					uniformProjection = shaderList[6].getProjectLocation();
					glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));

					model = glm::mat4(1.0);
					model = glm::translate(model, glm::vec3(-0.7f, -0.5f, -4.0f));
					model = glm::scale(model, glm::vec3(0.4f, 0.6f, 1.0f));
					glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
					meshList[0]->RenderMesh();

					//Follaje 2

					model = glm::mat4(1.0);
					model = glm::translate(model, glm::vec3(0.7f, -0.5f, -4.0f));
					model = glm::scale(model, glm::vec3(0.4f, 0.6f, 1.0f));
					glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
					meshList[0]->RenderMesh();


					//Tronco 1

					shaderList[5].useShader();
					uniformModel = shaderList[5].getModelLocation();
					uniformProjection = shaderList[5].getProjectLocation();
					glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));

					model = glm::mat4(1.0);
					model = glm::translate(model, glm::vec3(-0.7f, -0.9f, -5.0f));
					model = glm::scale(model, glm::vec3(0.2f, 0.2f, 1.0f));
					glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
					meshList[1]->RenderMesh();

					//Tronco 2

					model = glm::mat4(1.0);
					model = glm::translate(model, glm::vec3(0.7f, -0.9f, -5.0f));
					model = glm::scale(model, glm::vec3(0.2f, 0.2f, 1.0f));
					glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
					meshList[1]->RenderMesh();


					break;
			default:
				break;
		}
		

		/*if (cont == 70) {
			cont = 0;
			shader++;
			if (shader > 6) {
				shader = 2;
			}
			
		}*/

		cont++;

		glUseProgram(0);
		mainWindow.swapBuffers();

	}
	return 0;
}
// inicializar matriz: glm::mat4 model(1.0);
// reestablecer matriz: model = glm::mat4(1.0);
//Traslación
//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));
//////////////// ROTACIÓN //////////////////
//model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
////////////////  ESCALA ////////////////
//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
///////////////////// T+R////////////////
/*model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
*/
/////////////R+T//////////
/*model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
*/