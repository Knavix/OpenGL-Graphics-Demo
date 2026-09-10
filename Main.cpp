#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.h"
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height);



int main() {
	// glfwInit()
	// initialized glfw so we can use it's funtions
	glfwInit();

	// establishes what version of opengl I we are using
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	
	// establishes the profile we're using which is which package of opengl( "CORE" means modern openGL)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	// Creates the GLFW window
	GLFWwindow* window = glfwCreateWindow(800, 800, "Graphics Demo", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to open GLFW Window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// assigns the context to our window we're working on
	glfwMakeContextCurrent(window);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Initialized GLAD and loads pointers to OpenGL funtions - needed before can call any openGL funcion
	gladLoadGL();

	Shader myShader("shader.vs", "shader.fs");

	// like the 'screen gui' for our window
	glViewport(0, 0, 800, 800);

	// Vertex info to be placed and drawn
	float vertices1[] = {
		// positions			// colors			// texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,  // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f,	  0.0f, 0.0f, 0.0f,   0.0f, 1.0f  // top left
	};


	float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};


	glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
	};


	//Indices order to draw vertices
	unsigned int indices[] = {
		0, 1, 3,	// first triangle
		1, 2, 3		// second triangle
	};

	// Creates unsigned ints EBO, VBO, and VAO
	// uses GenBuffers(), and GenVertexArrays() to tell openGL how many of each is wanted and
	// stores the ID of each in the address of each unsigned int
	unsigned int EBO, VBO, VAO;
	glGenBuffers(1, &EBO);
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

	// Tells openGL which VAO is currently in use
	glBindVertexArray(VAO);

	// Tell openGL which VBO is currently selected
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Copies vertex data from RAM to the GPU 0 static tells it, it won't change
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Tells openGL which Elemmentel Buffer is currently selected
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	// Copies vertex data from RAM to the GPU 0 static tells it, it won't change
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Tells openGL how to interpret the attributes passed in by the buffer objects
	// the attribute location of the sahder (layout (location = 0)), the number of values (commas) in a singular object(vertex), the datatype,
	// bool value of if wanted to normalize values, stride (distance in bytes between vertices, and offset from a point of the array
	// 0 being the beginning
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	// Enables vertex attribute at location 0 so openGl uses it during rendering.
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(6 * sizeof(float)));
	//glEnableVertexAttribArray(2);

	// creating a texture 1
	unsigned int texture1;
	glGenTextures(1, &texture1);

	// binding (selecting) the texture
	glBindTexture(GL_TEXTURE_2D, texture1);
	
	// Texture settings
	// setting the texture wrapping and filtering options on the bound object
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// settings for texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// reading in image, creating textrue, generating mipmaps
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("rubix-cube.png", &width, &height, &nrChannels, 0);
	
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		std::cout << "Width: " << width << "\nHeight: " << height;
	}
	else {
		std::cout << "Failed to load texture\n" << std::endl;
		std::cout << width << "   " << height;
	}
	// Good practice to free image after generating texture and it's corresponding mipmap
	stbi_image_free(data);

	myShader.use();
	//glUniform1i(glGetUniformLocation(myShader.ID, "texture1"), 0);
	myShader.setInt("texture1", 0);
	//myShader.setInt("texture2", 1);

	glEnable(GL_DEPTH_TEST);


	// -----------------Main window loop-----------------------
	while (!glfwWindowShouldClose(window)) {
		
		processInput(window);
		
		// sets the color of the window that we want
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// clears the default buffer with garbage initialized values
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Binding textures to corresponding units
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);

		myShader.use();

		glm::mat4 transModel = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection;

		transModel = glm::rotate(transModel, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		transModel = glm::rotate(transModel, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -5.0f));
		projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
	
		unsigned int transformLoc = glGetUniformLocation(myShader.ID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transModel));


		int modelLoc = glGetUniformLocation(myShader.ID, "transModel");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(transModel));

		int viewLoc = glGetUniformLocation(myShader.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		myShader.setMat4("projection", projection);
		int num = -1;
		float i = 0.0f;

		view = glm::translate(view, glm::vec3(0.0f, 1, -5.0f));


		// selects the VAO idk: why needs to be called every time(think it's every frame)
		glBindVertexArray(VAO);
		
		for (unsigned int i = 0; i < 10; i++) {
			glm::mat4 transModel = glm::mat4(1.0f);
			transModel = glm::translate(transModel, cubePositions[i]);
			float angle = 20.0f * i;
			transModel = glm::rotate(transModel, (float)glfwGetTime() *glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			myShader.setMat4("transModel", transModel);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		glDrawArrays(GL_TRIANGLES, 0, 6);

		// swaps the buffers so that the new one can be displayed
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteTextures(1, &texture1);
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);

}