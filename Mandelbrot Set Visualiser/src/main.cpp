#include "lib.h"

void framebuffer_resize_callback(GLFWwindow* window, int fbW, int fbH) {
	glViewport(0, 0, fbW, fbH);
}

float c_x = 0.0f;
float c_y = 0.001f;
float zoom = 1.02f;

int MAX_ITERATION = 40;
int REAL_MAX = 5500;
int counter = 10;

float Zin_scale = 0.98f;
float Zout_scale = 1.02f;

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		c_y = c_y + 0.002 * zoom;
		//if after UP_KEY center goes out of bound hard set to 1.0
		if (c_y > 1.0f) {
			c_y = 1.0f;
		}
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		c_y = c_y - 0.002 * zoom;
		//if after DOWN_KEY center goes out of bound hard set to -1.0
		if (c_y < -1.0f) {
			c_y = -1.0f;
		}
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		c_x = c_x - 0.002 * zoom;
		//if after LEFT_KEY center goes out of bound hard set to -1.0
		if (c_x < -1.0f) {
			c_x = -1.0f;
		}
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		c_x = c_x + 0.002 * zoom;
		//if after LEFT_KEY center goes out of bound hard set to -1.0
		if (c_x > 1.0f) {
			c_x = 1.0f;
		}
	}

	//zoom out
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		zoom = zoom * Zout_scale;

		//zoom out limit
		if (zoom > 1.0f)
		{
			zoom = 1.0f;
		}
	}

	//zoom in
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		zoom = zoom * Zin_scale;

		//zoom-in limit
		if (zoom < 0.00001f)
		{
			zoom = 0.00001f;
		}
	}

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		std::cout << "MAX ITERATIONS : " << MAX_ITERATION << std::endl;
		MAX_ITERATION += counter;
		if (MAX_ITERATION > REAL_MAX) {
			MAX_ITERATION = REAL_MAX;
		}
	}

	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		std::cout << "MAX ITERATIONS : " << MAX_ITERATION << std::endl;
		MAX_ITERATION -= counter;
		if (MAX_ITERATION < 20) {
			MAX_ITERATION = 20;
		}
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		std::cout << "\t\tCOUNTER : " << counter << std::endl;
		counter -= 10;
		if (counter < 10) {
			counter = 10;
		}
	}

	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		std::cout << "\t\tCOUNTER : " << counter << std::endl;
		counter += 10;
		if (counter > 500) {
			counter = 500;
		}
	}


}

//function to load shaders
bool loadShaders(GLuint& shaderProgram) {
	bool loadSuccess = true;
	GLint success;
	char infoLog[512];

	std::string line = "";
	std::string src = "";

	std::ifstream fin;

	//VERTEX SHADER
	fin.open("res/shaders/vertex_shader.glsl"); //load file
	if (fin.is_open()) {
		while (std::getline(fin, line)) {
			src += line + "\n";
		}
	}
	else {
		std::cout << "ERROR::LOADSHADERS::COULD_NOT_OPEN_VERTEX_FILE\n";
		loadSuccess = false;
	}
	//std::cout << src << std::endl;
	fin.close();

	//creates vertexShader in background
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const GLchar* vertSRC = src.c_str();//it only accepts c-style strings
	glShaderSource(vertexShader, 1, &vertSRC, NULL);
	glCompileShader(vertexShader);

	//error check vertexShader compilation
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::LOADSHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		loadSuccess = false;
	}
	line = "";
	src = "";


	//FRAGMENT SHADER

	fin.open("res/shaders/fragment_shader.glsl"); //load file
	if (fin.is_open()) {
		while (std::getline(fin, line)) {
			src += line + "\n";
		}
	}
	else {
		std::cout << "ERROR::LOADSHADERS::COULD_NOT_OPEN_FRAGMENT_FILE\n";
		loadSuccess = false;
	}
	//std::cout << src << std::endl;
	fin.close();


	//creates fragmentShader in background
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const GLchar* fragSRC = src.c_str();//it only accepts c-style strings
	glShaderSource(fragmentShader, 1, &fragSRC, NULL);
	glCompileShader(fragmentShader);

	//error check fragmentShader compilation
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::LOADSHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		loadSuccess = false;
	}

	//PROGRAM SHADER
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glValidateProgram(shaderProgram);

	//error check shaderProgram linking
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::LOADSHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		loadSuccess = false;
	}


	//End
	glUseProgram(0);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return loadSuccess;
}

void pass_float_input_to_shader(GLuint& shaderProgram, std::string& u_input, double input) {
	glUniform1f(glGetUniformLocation(shaderProgram, u_input.c_str()), input);
}

int main() {

	//INIT GLFW
	glfwInit();
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	//CREATE WINDOW
	const int square_win_size = 1920;
	const int WINDOW_WIDTH = square_win_size;
	const int WINDOW_HEIGHT = square_win_size;


	//glfw window creation
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "mandel-wut-?", NULL, NULL);

	if (window == NULL) {
		std::cout << "Failed to create GLFW window\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);

	//INIT GLEW(NEEDS WINDOW AND OPENGL context
	glewExperimental = GL_TRUE;

	//error
	if (glewInit() != GLEW_OK) {
		std::cout << "ERROR::MAIN.CPP::GLEW_INIT_FAILED\n";
		glfwTerminate();
	}

	//load shaders
	GLuint shaderProgram;
	loadShaders(shaderProgram);


	float vertices[] = {
		-1.0f, -1.0f, -0.0f,
		 1.0f,  1.0f, -0.0f,
		-1.0f,  1.0f, -0.0f,
		 1.0f, -1.0f, -0.0f
	};

	//Index buffer
	GLuint indices[] = {
		0, 1, 2,  // first Triangle
		0, 3, 1   // second Triangle
	};


	//Setting up the buffers

	//VAO
	/*
	* VAO is a buffer which remembers all of the vertex buffers(VBOs) we want to use and their memory layout
	*/

	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//VBO
	GLuint VBO;//stores ID of buffer
	glGenBuffers(1, &VBO);//generate 1 buffer and put resulting ID into VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);//set it as the current buffer in OpenGL's state machine by "binding" , saying we want to use this buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);// copy the vertices into the currently bound buffer(VBO) , or simply give this buffer data to OpenGL


	//IBO
	GLuint IBO;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	glEnableVertexArrayAttrib(VAO, 0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);



	//MAIN LOOP
	while (!glfwWindowShouldClose(window)) {
		//input
		processInput(window);


		//DRAW--
		//Clear
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Draw

		glUseProgram(shaderProgram);

		std::string u_zoom = "u_zoom";
		std::string u_cx = "u_cx";
		std::string u_cy = "u_cy";
		std::string MAX_ITERATIONS = "MAX_ITERATIONS";

		pass_float_input_to_shader(shaderProgram, u_zoom, zoom);
		pass_float_input_to_shader(shaderProgram, u_cx, c_x);
		pass_float_input_to_shader(shaderProgram, u_cy, c_y);

		glUniform1i(glGetUniformLocation(shaderProgram, MAX_ITERATIONS.c_str()), MAX_ITERATION);


		glBindVertexArray(VAO);//Bind VAO to current context

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		//swap front and back buffers
		glfwSwapBuffers(window);

		glfwPollEvents();
		glFlush();
	}

	//END OF PROGRAM
	glfwDestroyWindow(window);
	glfwTerminate();

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	//glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);
	return 0;
}