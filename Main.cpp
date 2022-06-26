#include"Mesh.h"
#include"Model.h"

const unsigned int width = 800;
const unsigned int height = 800;

int main() {

	//initalise GLFW
	glfwInit();

	//specify to GLFW the OpenGL Version used
	//in this case, its 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//specify our profile
	//in this case, its core
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	

	//create a GLFWWindow of size 800*800 and name "OPENGL"
	GLFWwindow* window = glfwCreateWindow(width, height, "OpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create Window" << std::endl;
		glfwTerminate();
		return -1;
	}
	//make the window the current context
	glfwMakeContextCurrent(window);

	//load glad to configure OpenGL
	gladLoadGL();

	//specify the viewport
	glViewport(0, 0, width, height);


	//Link the shaders
	Shader shaderProgram("default.vert","default.frag");

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	shaderProgram.Activate();
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);


	glEnable(GL_DEPTH_TEST);

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	Model Ground("models/ground/scene.gltf");
	Model Trees("models/trees/scene.gltf");

	//main while loop
	while (!glfwWindowShouldClose(window)) {

		//set bg color
		glClearColor(0.85f, 0.85, 0.90f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		//set up camera for controls and FOV and Range
		camera.Inputs(window);
		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		Ground.Draw(shaderProgram, camera);
		Trees.Draw(shaderProgram, camera);
		glfwSwapBuffers(window);

		//take care of all GLFW events
		glfwPollEvents();
	}

	//delete generated objects
	shaderProgram.Delete();
	//terminate program
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}