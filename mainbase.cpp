#include <stdio.h>
#include<stdlib.h>
#include <glew.h>
#include <glfw3.h>
#include<Windows.h>
#include<math.h>
#include<time.h>
//Dimensiones de la ventana
const int WIDTH = 800, HEIGHT = 600;

int main()
{
	float rgb[] = { 0, 1, 0 };
	float numMaximoColor = 0;
	clock_t tiempoActual, tiempoAnterior;
	float tiempoSegundos = 0;
	GLint ret;
	//Inicialización de GLFW
	if (!glfwInit())
	{
		printf("Falló inicializar GLFW");
		glfwTerminate();
		return 1;
	}
	//Asignando variables de GLFW y propiedades de ventana
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//para solo usar el core profile de OpenGL y no tener retrocompatibilidad
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//CREAR VENTANA
	GLFWwindow *mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Primer ventana", NULL, NULL);
	GLFWwindow *secondWindow = glfwCreateWindow(WIDTH, HEIGHT, "segunda ventana", NULL, NULL);

	if (!mainWindow && !secondWindow)
	{
		printf("Fallo en crearse la ventana con GLFW");
		glfwTerminate();
		return 1;
	}
	//Obtener tamaño de Buffer
	int BufferWidth, BufferHeight;
	glfwGetFramebufferSize(mainWindow, &BufferWidth, &BufferHeight);
	int BufferWidth2, BufferHeight2;
	glfwGetFramebufferSize(secondWindow, &BufferWidth2, &BufferHeight2);
	//asignar el contexto


	//permitir nuevas extensiones
	glewExperimental = GL_TRUE;

	glfwMakeContextCurrent(mainWindow);

	if (glewInit() != GLEW_OK)
	{
		printf("Falló inicialización de GLEW");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}
	glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_FRONT_LEFT, GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE, &ret);
	printf("Green size buffer: %i \n", ret);
	numMaximoColor = (float) (pow(2, ret));
	printf("colores: %f \n", numMaximoColor);
	// Asignar valores de la ventana y coordenadas
	//Asignar Viewport
	glViewport(0, 0, BufferWidth, BufferHeight);
	printf("Version de Opengl: %s \n",glGetString(GL_VERSION));
	printf("Marca: %s \n", glGetString(GL_VENDOR));
	printf("Renderer: %s \n", glGetString(GL_RENDERER));
	printf("Shaders: %s \n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	//Loop mientras no se cierra la ventana
	tiempoAnterior = clock();
	while (!glfwWindowShouldClose(mainWindow) && !glfwWindowShouldClose(secondWindow))
	{
		glfwMakeContextCurrent(mainWindow);

		//Recibir eventos del usuario
		glfwPollEvents();

		tiempoActual = clock();
		tiempoSegundos = (float)(tiempoActual - tiempoAnterior) / CLOCKS_PER_SEC;
		if (tiempoSegundos >= 2.0) {
			rgb[0] = (float)((rand() % (int)numMaximoColor) / (numMaximoColor - 1));
			rgb[1] = (float)((rand() % (int)numMaximoColor) / (numMaximoColor - 1));
			rgb[2] = (float)((rand() % (int)numMaximoColor) / (numMaximoColor - 1));
			tiempoAnterior = tiempoActual;
		}
			
			//cont = 0;		
		//Sleep(1000);

		//Limpiar la ventana
		glClearColor(rgb[0], rgb[1], rgb[2], 1.0f);
		//glClearColor(rgb[0], rgb[1], rgb[2], 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(mainWindow);

		glfwMakeContextCurrent(secondWindow);

		glClearColor(0.5f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(secondWindow);

		
	}


	return 0;
}