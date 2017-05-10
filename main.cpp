#include <iostream>
#include <vector>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include <SOIL/SOIL.h>
// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other includes
#include "shader.h"
#include "2dmesh.h"


// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);


//globals
bool animate = true;
bool left = true;
bool right = false;
bool zoomin = false;
bool zoomout = false;

bool increaseh = false;
bool decreaceh = false;

bool wave = true;

bool iphase = false;
bool dphase = false;

bool iamp = false;
bool damp = false;

bool iint = false;
bool dint = false;


// Window dimensions
const GLuint WIDTH = 720, HEIGHT = 720;

// The MAIN function, from here we start the application and run the game loop
int main()
{
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Island", 0, 0);
	glfwMakeContextCurrent(window);

	// Set the required callback functions
	glfwSetKeyCallback(window, key_callback);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	glewInit();

	// Define the viewport dimensions
	glViewport(0, 0, WIDTH, HEIGHT);

	// Enable Depth Test
	glEnable(GL_DEPTH_TEST);


	// Build and compile our shader program
	Shader ourShader("island.vert", "island.frag");


	/// Set up vertex data (and buffer(s)) and attribute pointers
	std::vector<float> vertices = Gen2DMesh(256);
	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_DYNAMIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// TexCoord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0); // Unbind VAO


	/// Load and create a texture 
	GLuint texture1;
	GLuint texture2;
	GLuint texture3;
	GLuint texture4;
	// ====================
	// Texture 1
	// ====================
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
											// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Load, create texture and generate mipmaps
	int width, height;
	unsigned char* image = SOIL_load_image("water.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
									 
	// ===================
	// Texture 2
	// ===================
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Load, create texture and generate mipmaps
	image = SOIL_load_image("heightmap.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// ===================
	// Texture 3
	// ===================
	glGenTextures(1, &texture3);
	glBindTexture(GL_TEXTURE_2D, texture3);
	// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Load, create texture and generate mipmaps
	image = SOIL_load_image("grassland.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// ===================
	// Texture 4
	// ===================
	glGenTextures(1, &texture4);
	glBindTexture(GL_TEXTURE_2D, texture4);
	// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Load, create texture and generate mipmaps
	image = SOIL_load_image("snowland.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	
	// Camera Parameters
	glm::vec3 eye = glm::vec3(2.0f, 2.0f, 2.0f);
	glm::vec3 lookat = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

	
	GLfloat pos = 0.0f;
	GLfloat zoom = 2.0f;
	GLfloat islandheight = 0.0;
	GLfloat phase = 0.0;
	GLfloat wamp = 0.01;
	GLfloat wint = 1.0;
	GLfloat phasespeed = 0.01;

	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// Bind Textures using texture units
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture1"), 0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture2"), 1);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, texture3);
		glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture3"), 2);
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, texture4);
		glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture4"), 3);

		// Activate shader
		ourShader.Use();

		// Create transformations
		glm::mat4 transform;
		glm::mat4 projection;
		glm::mat4 view;


		if (animate)
		{
			if (left)
			{
				if (pos == 360)
					pos = 0;
				pos = pos + 0.25;
			}
			if (right)
			{
				if (pos == 0)
					pos = 360;
				pos = pos - 0.25;
			}
		}	

		if (wave)
		{
			phase += phasespeed;
		}

		if (iphase)
			phasespeed += 0.001;
		if (dphase)
			phasespeed -= 0.001;

		if (iamp)
			wamp += 0.005;
		if (damp)
			if (wamp > 0)
				wamp -= 0.005;

		if (iint)
			wint += 0.1;
		if (dint)
			if (wint > 1)
				wint -= 0.1;

		if (zoomin)
			if (zoom > 0.05)
				zoom = zoom - 0.05;
		if (zoomout)
			zoom = zoom + 0.05;

		if (increaseh)
			islandheight += 0.001;
		if (decreaceh)
			if(islandheight > 0)
				islandheight -= 0.001;


		eye = glm::vec3(glm::sin(glm::radians(pos))*zoom, 1.0f , glm::cos(glm::radians(pos))*zoom);	
		view = glm::lookAt(eye, lookat, up);
		projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);	

		transform = glm::rotate(transform, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

		glUniform1f(glGetUniformLocation(ourShader.Program, "islandmult"), islandheight);
		glUniform1f(glGetUniformLocation(ourShader.Program, "phase"), phase);
		glUniform1f(glGetUniformLocation(ourShader.Program, "wamp"), wamp);
		glUniform1f(glGetUniformLocation(ourShader.Program, "wint"), wint);
	

		// Get matrix's uniform location and set matrix
		GLint transformLoc = glGetUniformLocation(ourShader.Program, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		GLint projLoc = glGetUniformLocation(ourShader.Program, "projection");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		// Draw container
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, vertices.size()/5);
		glBindVertexArray(0);

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}
	// Properly de-allocate all resources once they've outlived their purpose
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	//glDeleteBuffers(1, &EBO);
	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();
	return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key == GLFW_KEY_L && action == GLFW_PRESS)
		animate = false;
	if (key == GLFW_KEY_K && action == GLFW_PRESS)
		animate = true;

	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
	{
		left = true;
		right = false;
		animate = true;
	}
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
	{
		left = false;
		right = true;
		animate = true;
	}
	if (key == GLFW_KEY_LEFT && action == GLFW_RELEASE)
	{
		animate = false;
	}
	if (key == GLFW_KEY_RIGHT && action == GLFW_RELEASE)
	{
		animate = false;
	}

	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
	{
		zoomin = true;
	}
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
	{
		zoomout = true;
	}
	if (key == GLFW_KEY_UP && action == GLFW_RELEASE)
	{
		zoomin = false;
	}
	if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE)
	{
		zoomout = false;
	}

	if (key == GLFW_KEY_P && action == GLFW_PRESS)
		wave = false;
	if (key == GLFW_KEY_O && action == GLFW_PRESS)
		wave = true;

	if (key == GLFW_KEY_KP_ADD && action == GLFW_PRESS)
	{
		increaseh = true;
	}
	if (key == GLFW_KEY_KP_SUBTRACT && action == GLFW_PRESS)
	{
		decreaceh = true;
	}
	if (key == GLFW_KEY_KP_ADD && action == GLFW_RELEASE)
	{
		increaseh = false;
	}
	if (key == GLFW_KEY_KP_SUBTRACT && action == GLFW_RELEASE)
	{
		decreaceh = false;
	}

	if (key == GLFW_KEY_Q && action == GLFW_PRESS)
	{
		iphase = true;
	}
	if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		dphase = true;
	}
	if (key == GLFW_KEY_Q && action == GLFW_RELEASE)
	{
		iphase = false;
	}
	if (key == GLFW_KEY_W && action == GLFW_RELEASE)
	{
		dphase = false;
	}

	if (key == GLFW_KEY_A && action == GLFW_PRESS)
	{
		iamp = true;
	}
	if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{
		damp = true;
	}
	if (key == GLFW_KEY_A && action == GLFW_RELEASE)
	{
		iamp = false;
	}
	if (key == GLFW_KEY_S && action == GLFW_RELEASE)
	{
		damp = false;
	}

	if (key == GLFW_KEY_Z && action == GLFW_PRESS)
	{
		iint = true;
	}
	if (key == GLFW_KEY_X && action == GLFW_PRESS)
	{
		dint = true;
	}
	if (key == GLFW_KEY_Z && action == GLFW_RELEASE)
	{
		iint = false;
	}
	if (key == GLFW_KEY_X && action == GLFW_RELEASE)
	{
		dint = false;
	}
}
