//pr�ctica 3: Modelado Geom�trico y C�mara Sint�tica.
#include <stdio.h>
#include <string.h>
#include<cmath>
#include<vector>
#include <glew.h>
#include <glfw3.h>
#include<math.h>
//glm
#include<glm.hpp>
#include<gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp>
#include <gtc\random.hpp>
//clases para dar orden y limpieza al c�digo
#include"Mesh.h"
#include"Shader.h"
#include"Sphere.h"
#include"Window.h"
#include"Camera.h"

//tecla E: Rotar sobre el eje X
//tecla R: Rotar sobre el eje Y
//tecla T: Rotar sobre el eje Z


using std::vector;

//Dimensiones de la ventana
const float toRadians = 3.14159265f/180.0; //grados a radianes
const float PI = 3.14159265f;
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;
Camera camera;
Window mainWindow;
vector<Mesh*> meshList;
vector<Shader>shaderList;
//Vertex Shader
static const char* vShader = "shaders/shader.vert";
static const char* fShader = "shaders/shader.frag";
static const char* vShaderColor = "shaders/shadercolor.vert";
Sphere sp = Sphere(1.0, 20, 20); //recibe radio, slices, stacks




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
	Mesh* cubo = new Mesh();
	cubo->CreateMesh(cubo_vertices, cubo_indices, 24, 36);
	meshList.push_back(cubo);
}

// Pir�mide triangular regular
void CrearPiramideTriangular()
{
	unsigned int indices_piramide_triangular[] = {
			0,1,2,
			1,3,2,
			3,0,2,
			1,0,3

	};
	GLfloat vertices_piramide_triangular[] = {
		-0.5f, -0.5f,0.0f,	//0
		0.5f,-0.5f,0.0f,	//1
		0.0f,0.5f, -0.288f,	//2
		0.0f,-0.5f,-0.866f,	//3

		//Cara inferior en tiene 1 de base, 1 de atura y 0.5 de profundidad
		//cara frontal tiene 1 de base y uno de altura
	};
	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices_piramide_triangular, indices_piramide_triangular, 12, 12);
	meshList.push_back(obj1);

}

void CrearPiramideTriangularInvertida()
{
	unsigned int indices_piramide_triangular[] = {
			0,1,2,
			1,3,2,
			3,0,2,
			1,0,3

	};
	GLfloat vertices_piramide_triangular[] = {
		0.0f, 0.5f,0.866f,	//0
		0.5f,0.5f,0.0f,	//1
		0.8f,0.0f, 0.8f,	//2
		0.0f,-0.5f,0.288f,	//3

		//Cara inferior en tiene 1 de base, 1 de atura y 0.5 de profundidad
		//cara frontal tiene 1 de base y uno de altura
	};
	Mesh* obj2 = new Mesh();
	obj2->CreateMesh(vertices_piramide_triangular, indices_piramide_triangular, 12, 12);
	meshList.push_back(obj2);

}


/*
Crear cilindro, cono y esferas con arreglos din�micos vector creados en el Semestre 2023 - 1 : por S�nchez P�rez Omar Alejandro
*/
void CrearCilindro(int res, float R) {

	//constantes utilizadas en los ciclos for
	int n, i;
	//c�lculo del paso interno en la circunferencia y variables que almacenar�n cada coordenada de cada v�rtice
	GLfloat dt = 2 * PI / res, x, z, y = -0.5f;

	vector<GLfloat> vertices;
	vector<unsigned int> indices;

	//ciclo for para crear los v�rtices de las paredes del cilindro
	for (n = 0; n <= (res); n++) {
		if (n != res) {
			x = R * cos((n)*dt);
			z = R * sin((n)*dt);
		}
		//caso para terminar el c�rculo
		else {
			x = R * cos((0)*dt);
			z = R * sin((0)*dt);
		}
		for (i = 0; i < 6; i++) {
			switch (i) {
			case 0:
				vertices.push_back(x);
				break;
			case 1:
				vertices.push_back(y);
				break;
			case 2:
				vertices.push_back(z);
				break;
			case 3:
				vertices.push_back(x);
				break;
			case 4:
				vertices.push_back(0.5);
				break;
			case 5:
				vertices.push_back(z);
				break;
			}
		}
	}

	//ciclo for para crear la circunferencia inferior
	for (n = 0; n <= (res); n++) {
		x = R * cos((n)*dt);
		z = R * sin((n)*dt);
		for (i = 0; i < 3; i++) {
			switch (i) {
			case 0:
				vertices.push_back(x);
				break;
			case 1:
				vertices.push_back(-0.5f);
				break;
			case 2:
				vertices.push_back(z);
				break;
			}
		}
	}

	//ciclo for para crear la circunferencia superior
	for (n = 0; n <= (res); n++) {
		x = R * cos((n)*dt);
		z = R * sin((n)*dt);
		for (i = 0; i < 3; i++) {
			switch (i) {
			case 0:
				vertices.push_back(x);
				break;
			case 1:
				vertices.push_back(0.5);
				break;
			case 2:
				vertices.push_back(z);
				break;
			}
		}
	}

	//Se generan los indices de los v�rtices
	for (i = 0; i < vertices.size(); i++) indices.push_back(i);

	//se genera el mesh del cilindro
	Mesh *cilindro = new Mesh();
	cilindro->CreateMeshGeometry(vertices, indices, vertices.size(), indices.size());
	meshList.push_back(cilindro);
}

//funci�n para crear un cono
void CrearCono(int res,float R) {

	//constantes utilizadas en los ciclos for
	int n, i;
	//c�lculo del paso interno en la circunferencia y variables que almacenar�n cada coordenada de cada v�rtice
	GLfloat dt = 2 * PI / res, x, z, y = -0.5f;
	
	vector<GLfloat> vertices;
	vector<unsigned int> indices;

	//caso inicial para crear el cono
	vertices.push_back(0.0);
	vertices.push_back(0.5);
	vertices.push_back(0.0);
	
	//ciclo for para crear los v�rtices de la circunferencia del cono
	for (n = 0; n <= (res); n++) {
		x = R * cos((n)*dt);
		z = R * sin((n)*dt);
		for (i = 0; i < 3; i++) {
			switch (i) {
			case 0:
				vertices.push_back(x);
				break;
			case 1:
				vertices.push_back(y);
				break;
			case 2:
				vertices.push_back(z);
				break;
			}
		}
	}
	vertices.push_back(R * cos(0) * dt);
	vertices.push_back(-0.5);
	vertices.push_back(R * sin(0) * dt);


	for (i = 0; i < res+2; i++) indices.push_back(i);

	//se genera el mesh del cono
	Mesh *cono = new Mesh();
	cono->CreateMeshGeometry(vertices, indices, vertices.size(), res + 2);
	meshList.push_back(cono);
}

//funci�n para crear pir�mide cuadrangular unitaria
void CrearPiramideCuadrangular()
{
	vector<unsigned int> piramidecuadrangular_indices = {
		0,3,4,
		3,2,4,
		2,1,4,
		1,0,4,
		0,1,2,
		0,2,4

	};
	vector<GLfloat> piramidecuadrangular_vertices = {
		0.5f,-0.5f,0.5f,
		0.5f,-0.5f,-0.5f,
		-0.5f,-0.5f,-0.5f,
		-0.5f,-0.5f,0.5f,
		0.0f,0.5f,0.0f,
	};
	Mesh *piramide = new Mesh();
	piramide->CreateMeshGeometry(piramidecuadrangular_vertices, piramidecuadrangular_indices, 15, 18);
	meshList.push_back(piramide);
}



void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);

	Shader* shader2 = new Shader();
	shader2->CreateFromFiles(vShaderColor, fShader);
	shaderList.push_back(*shader2);
}

float distanciaEntrePuntos(float a1, float a2, float a3, float b1, float b2, float b3) {
	float h, sum;
	sum = pow((b1 - a1), 2) + pow((b2 - a2), 2) + pow((b3 -a3), 2);
	h = sqrt(sum);
	
	return h;

}


int main()
{
	mainWindow = Window(1000, 600);
	mainWindow.Initialise();
	//Cilindro y cono reciben resoluci�n (slices, rebanadas) y Radio de circunferencia de la base y tapa

	CrearCubo();//�ndice 0 en MeshList
	CrearPiramideTriangular();//�ndice 1 en MeshList
	CrearCilindro(20, 1.0f);//�ndice 2 en MeshList
	CrearCono(25, 2.0f);//�ndice 3 en MeshList
	CrearPiramideCuadrangular();//�ndice 4 en MeshList
	CrearPiramideTriangularInvertida();//indice 5
	CreateShaders();
	
	//Funcion P/ calcular distancia entre los puntos (longitudes de cada lado
	float	x1 = 0.0, y1 = -0.5,  z1 = 0.0 ,  //Vertice frontal derecho
			x2 = -0.5, y2 = -0.5, z2 = 0.0,  //V�rtice frontal izquierdo
			x3 = 0.0, y3 = 0.3,  z3 = -0.288,
			raiz = 0;	 //Vertice Trasero	
	float dist[3] = {0,0,0};

	dist[0] = distanciaEntrePuntos(x1,y1,z1,x2,y2,z2);
	dist[1] = distanciaEntrePuntos(x1, y1, z1, x3, y3, z3);
	dist[2] = distanciaEntrePuntos(x3, y3, z3, x2, y2, z2);
	printf("%.3f \n %.3f \n %.3f \n", dist[0], dist[1], dist[2] );

	/*C�mara se usa el comando: glm::lookAt(vector de posici�n, vector de orientaci�n, vector up));
	En la clase Camera se reciben 5 datos:
	glm::vec3 vector de posici�n,
	glm::vec3 vector up,
	GlFloat yaw rotaci�n para girar hacia la derecha e izquierda
	GlFloat pitch rotaci�n para inclinar hacia arriba y abajo
	GlFloat velocidad de desplazamiento,
	GlFloat velocidad de vuelta o de giro
	Se usa el Mouse y las teclas WASD y su posici�n inicial est� en 0,0,1 y ve hacia 0,0,-1.
	*/

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.3f, 0.3f);

	
	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	GLuint uniformView = 0;//REcibe la camara
	GLuint uniformColor = 0;//REcibe RGB p/ aplicarle color a las geometrias
	glm::mat4 projection = glm::perspective(glm::radians(60.0f)	,mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);
	//glm::mat4 projection = glm::ortho(-1, 1, -1, 1, 1, 10);
	
	//Loop mientras no se cierra la ventana
	sp.init(); //inicializar esfera
	sp.load();//enviar la esfera al shader

	glm::mat4 model(1.0);//Inicializar matriz de Modelo 4x4

	glm::vec3 color = glm::vec3(0.0f,0.0f,0.0f); //inicializar Color para enviar a variable Uniform;

	while (!mainWindow.getShouldClose())
	{

		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;
		//Recibir eventos del usuario
		glfwPollEvents();
		//C�mara
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		//Limpiar la ventana
		glClearColor(0.0f, 0.2f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad
		shaderList[0].useShader();
		uniformModel = shaderList[0].getModelLocation();
		uniformProjection = shaderList[0].getProjectLocation();
		uniformView = shaderList[0].getViewLocation();
		uniformColor = shaderList[0].getColorLocation();
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));


		//Fondo
		//Alto 4.0 (-2.0, 2.0), base 4.0 (-2,2), de la cara frontal al centro de Z hay (desde 0, -2.88, La longitud en z es de  3.464

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.0f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		color = glm::vec3(0.0f, 0.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color)); //para cambiar el color del objetos
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[1]->RenderMesh();

		

		//Cara Frontal
		// NIVEL INFERIOR---------------------------------------------------------------------------
		 //Tamanio  en x 1.15(-.575, 0.575) -- 0.1 de espacio etre triangulos, 0.1 de separacion con la base
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.275f, -1.99));
		model = glm::scale(model, glm::vec3(1.15f, 1.15f, 1.15f));
		color = glm::vec3(0.6f, 0.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color)); //para cambiar el color del objetos
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[1]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1.25f, -1.275f, -1.99));
		model = glm::scale(model, glm::vec3(1.15f, 1.15f, 1.15f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[1]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1.25f, -1.275f, -1.99));
		model = glm::scale(model, glm::vec3(1.15f, 1.15f, 1.15f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[1]->RenderMesh();


		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.625f, -1.175f, -1.995f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, 30 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.15f, 1.15f, 1.15f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[1]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.625f, -1.175f, -1.995f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, 30 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.15f, 1.15f, 1.15f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[1]->RenderMesh();

		//sEGUNDO NIVEL---------------------------------------------------------------------------
		//Tama�o en y = 1.15 (-0.575,0.575)
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.625f, -0.075f, -2.35f));
		model = glm::scale(model, glm::vec3(1.15f, 1.15f, 1.15f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[1]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.625f, -0.075f, -2.35f));
		model = glm::scale(model, glm::vec3(1.15f, 1.15f, 1.15f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[1]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.025f, -2.35f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, 30 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.15f, 1.15f, 1.15f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[1]->RenderMesh();

		//TERCER NIVEL

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 1.125f, -2.7f));
		model = glm::scale(model, glm::vec3(1.15f, 1.15f, 1.15f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[1]->RenderMesh();
		// NIVEL INFERIOR ---------------------------------------------------------------------------------------------------------
		

		//LATERAL DERECHA
		//Tamanio  en "x" 1.15(-.575, 0.575) -- 0.1 de espacio etre triangulos, 0.1 de separacion con la base, el centro no est� en 0.0, piensa que est�s empujado el borde frontal de x cuando pienses en profundidad

		color = glm::vec3(0.0f, 0.6f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color)); 

		

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1.375f, -1.275f, -2.15f)); //z es como tu x de la cara frontal, moverlo solo empuja hacia adelante o hacia atr�s. x es como la z tienes que moverlo Para meter la piramide
		model = glm::scale(model, glm::vec3(1.15f, 1.15f, 1.15f));			//El valor final de x es 0 por lo que x va de 2 a 0, segun los primeros calculos que hice x debe variar aprox .62 
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[1]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.705f, -1.275f, -3.25f));
		model = glm::scale(model, glm::vec3(1.15f, 1.15f, 1.15f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[1]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.085f, -1.275f, -4.35f));
		model = glm::scale(model, glm::vec3(1.15f, 1.15f, 1.15f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[1]->RenderMesh();

		// invertidas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1.35f, -1.275f, -3.55f));
		model = glm::scale(model, glm::vec3(1.15f, 1.15f, 1.15f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[5]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.65f, -1.275f, -4.625f));
		model = glm::scale(model, glm::vec3(1.15f, 1.15f, 1.15f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[5]->RenderMesh();
		// SEGUNDO NIVEL

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.7f, -0.075f, -2.525f));
		model = glm::scale(model, glm::vec3(1.15f, 1.15f, 1.15f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[1]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.1f, -0.075f, -3.65f));
		model = glm::scale(model, glm::vec3(1.15f, 1.15f, 1.15f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[1]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.7f, -0.075f, -3.95f));
		model = glm::scale(model, glm::vec3(1.15f, 1.15f, 1.15f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[5]->RenderMesh();

		//Tercer Nivel

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.1f, 1.125f, -2.9f));
		model = glm::scale(model, glm::vec3(1.15f, 1.15f, 1.15f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[1]->RenderMesh();

		//LATERAL DERECHA
		//primer nivel
		color = glm::vec3(0.0f, 0.0f, 0.6f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1.375f, -1.275f, -2.15f)); 
		model = glm::scale(model, glm::vec3(1.15f, 1.15f, 1.15f));			
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[1]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.705f, -1.275f, -3.25f));
		model = glm::scale(model, glm::vec3(1.15f, 1.15f, 1.15f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[1]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.085f, -1.275f, -4.35f));
		model = glm::scale(model, glm::vec3(1.15f, 1.15f, 1.15f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[1]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1.35f, -1.275f, -3.55f));
		model = glm::scale(model, glm::vec3(-1.15f, 1.15f, 1.15f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[5]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.65f, -1.275f, -4.625f));
		model = glm::scale(model, glm::vec3(-1.15f, 1.15f, 1.15f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[5]->RenderMesh();
		// SEGUNDO NIVEL
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.7f, -0.075f, -2.525f));
		model = glm::scale(model, glm::vec3(1.15f, 1.15f, 1.15f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[1]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.1f, -0.075f, -3.65f));
		model = glm::scale(model, glm::vec3(1.15f, 1.15f, 1.15f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[1]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.7f, -0.075f, -3.95f));
		model = glm::scale(model, glm::vec3(-1.15f, 1.15f, 1.15f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[5]->RenderMesh();

		//Tercer Nivel
		
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.1f, 1.125f, -2.9f));
		model = glm::scale(model, glm::vec3(1.15f, 1.15f, 1.15f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[1]->RenderMesh();

		//CARA INFERIOR
		color = glm::vec3(0.6f, 0.0f, 0.6f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//PRIMER NIVEL
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1.275f, -1.475f, -2.05));
		model = glm::scale(model, glm::vec3(1.15f, 1.15f, 1.15f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[1]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.025f, -1.475f, -2.05));
		model = glm::scale(model, glm::vec3(1.15f, 1.15f, 1.15f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[1]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1.225f, -1.475f, -2.05));
		model = glm::scale(model, glm::vec3(1.15f, 1.15f, 1.15f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[1]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.65f, -1.475f, -3.10));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.15f, 1.15f, 1.15f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[1]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.60f, -1.475f, -3.10));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.15f, 1.15f, 1.15f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[1]->RenderMesh();

		//SEGUNDO NIVEL

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.65f, -1.475f, -3.2f));
		model = glm::scale(model, glm::vec3(1.15f, 1.15f, 1.15f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[1]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.6f, -1.475f, -3.2f));
		model = glm::scale(model, glm::vec3(1.15f, 1.15f, 1.15f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[1]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.025f, -1.475f, -4.2f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.15f, 1.15f, 1.15f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[1]->RenderMesh();
		
		//TERCER NIVEL

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.025f, -1.475f, -4.35f));
		model = glm::scale(model, glm::vec3(1.15f, 1.15f, 1.15f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[1]->RenderMesh();

		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.0f, 2.5f, -2.88f));
		////model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));

		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//meshList[1]->RenderMesh();



		//Ejercicio clase
		////base
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.0f, -1.6f, -2.0f));
		//model = glm::scale(model, glm::vec3(5.0f, 1.0f, 5.0f));
		//color = glm::vec3(0.0f, 0.3f, 0.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color)); //para cambiar el color del objetos
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//meshList[0]->RenderMesh();

		////TECHO
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.0f, 0.7f, -2.0f));
		//model = glm::scale(model, glm::vec3(1.3f, 1.2f, 1.3f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model)); 
		//color = glm::vec3(0.0f, 0.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color)); //para cambiar el color del objetos
		//meshList[4]->RenderMesh();

		////PAREDES
		//model = glm::mat4(1.0); 
		//model = glm::translate(model, glm::vec3(0.0f, -0.5f, -2.0f)); // dimensiones  en x (-0.5,0.5) y (-1.1,0.1) z(-2.5,-1.5)
		//model = glm::scale(model, glm::vec3(1.0f, 1.2f, 1.0f)); 
		//color = glm::vec3(1.0f, 0.0f, 0.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color)); //para cambiar el color del objetos
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model)); 
		////glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection)); 
		//meshList[0]->RenderMesh(); 

		////FRENTE
		////Ventana 1
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(-0.25f, -0.15f, -1.8f));
		//model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.7f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(0.0f, 1.0f, 0.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color)); //para cambiar el color del objetos
		//meshList[0]->RenderMesh();

		////Ventana 2
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.25f, -0.15f, -1.80f));
		//model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.7f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//meshList[0]->RenderMesh();

		////Puerta 
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.0f, -0.83f, -1.8f));
		//model = glm::scale(model, glm::vec3(0.3f, 0.5f, 0.7f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//meshList[0]->RenderMesh();

		////Laterales

		////Ventana 1
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.0f, -0.15f, -2.25f));
		//model = glm::scale(model, glm::vec3(1.05f, 0.3f, 0.3f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//meshList[0]->RenderMesh();

		////Ventana 2
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.0f, -0.15f, -1.75f));
		//model = glm::scale(model, glm::vec3(1.05f, 0.3f, 0.3f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//meshList[0]->RenderMesh();


		////Arboles
		////P triangular tiene base con longitud/altura de 0.5, altura de 0.25

		////Follaje
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(-0.9f, -0.5f, -2.0f));
		//model = glm::scale(model, glm::vec3(0.5f, 0.6f, 0.5f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(0.0f, 0.5f, 0.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color)); //para cambiar el color del objetos
		//meshList[4]->RenderMesh();

		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.9f, -0.5f, -2.0f));
		//model = glm::scale(model, glm::vec3(0.5f, 0.6f, 0.5f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//meshList[4]->RenderMesh();

		////Troncos
		//
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(-0.9f, -0.95f, -2.0f));
		//model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		//color = glm::vec3(0.478, 0.255, 0.067);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color)); //para cambiar el color del objetos
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//meshList[0]->RenderMesh();
		//

		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.9f, -0.95f, -2.0f));
		//model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//meshList[0]->RenderMesh();

		////ventana trasera

		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.0f, -0.5f, -2.5f));
		//color = glm::vec3(0.0f, 0.0f, 1.0f);
		//model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.1f));
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color)); //para cambiar el color del objetos
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//sp.render();

		//model = glm::mat4(1.0);
		////Traslaci�n inicial para posicionar en -Z a los objetos
		//model = glm::translate(model, glm::vec3(0.0f, -0.5f, -4.0f));
		////otras transformaciones para el objeto
		////model = glm::scale(model, glm::vec3(0.5f,0.5f,0.5f));
		//model = glm::rotate(model, glm::radians(mainWindow.getrotax()), glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, glm::radians(mainWindow.getrotay()), glm::vec3(0.0f, 1.0f, 0.0f));  //al presionar la tecla Y se rota sobre el eje y
		//model = glm::rotate(model, glm::radians(mainWindow.getrotaz()), glm::vec3(0.0f, 0.0f, 1.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));		
		////la l�nea de proyecci�n solo se manda una vez a menos que en tiempo de ejecuci�n
		////se programe cambio entre proyecci�n ortogonal y perspectiva
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		//color = glm::vec3(1.0f, 0.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color)); //para cambiar el color del objetos
		////meshList[0]->RenderMesh(); //dibuja cubo y pir�mide triangular
		////meshList[4]->RenderMeshGeometry(); //dibuja las figuras geom�tricas cilindro, cono, pir�mide base cuadrangular
		//sp.render(); //dibuja esfera
		
		
		
		////ejercicio: Instanciar primitivas geom�tricas para recrear el dibujo de la pr�ctica pasada en 3D,
		////se requiere que exista piso y la casa tiene una ventana azul circular justo en medio de la pared trasera y solo 1 puerta frontal.
		//model = glm::mat4(1.0f);
		//color=glm::vec3(0.0f,1.0f,0.0f);
		////Opcional duplicar esta traslaci�n inicial para posicionar en -Z a los objetos en el mismo punto
		////model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.0f));
		//model = glm::translate(model, glm::vec3(0.0f, 0.75f, -2.5f));
		//model = glm::rotate(model, glm::radians(mainWindow.getrotax()), glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, glm::radians(mainWindow.getrotay()), glm::vec3(0.0f, 1.0f, 0.0f));  //al presionar la tecla Y se rota sobre el eje y
		//model = glm::rotate(model, glm::radians(mainWindow.getrotaz()), glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 1.0f));
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color)); 
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		//meshList[2]->RenderMeshGeometry();
		//

		glUseProgram(0);
		mainWindow.swapBuffers();
	}
	return 0;
}

//uSAR PARA ROTAR elementos con teclas
//model = glm::rotate(model, glm::radians(mainWindow.getrotax()), glm::vec3(1.0f, 0.0f, 0.0f));
//model = glm::rotate(model, glm::radians(mainWindow.getrotay()), glm::vec3(0.0f, 1.0f, 0.0f));  //al presionar la tecla Y se rota sobre el eje y
//model = glm::rotate(model, glm::radians(mainWindow.getrotaz()), glm::vec3(0.0f, 0.0f, 1.0f));
//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		