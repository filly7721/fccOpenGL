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

	Shader outliningProgram("outlining.vert", "outlining.frag");

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	shaderProgram.Activate();
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);


	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CCW);

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	Model model("models/crow/scene.gltf");

	double prevTime = 0.0f, crntTime = 0.0f, timeDiff;
	unsigned int frameCount = 0;


	//main while loop
	while (!glfwWindowShouldClose(window)) {

		crntTime = glfwGetTime();
		timeDiff = crntTime - prevTime;
		frameCount++;
		if (timeDiff >= 1.0 / 60) {
			std::string FPS = std::to_string(frameCount / timeDiff);
			std::string ms = std::to_string((timeDiff / frameCount) * 1000);
			std::string newTitle = "YOUTUBE OPENGL - " + FPS + "FPS / " + ms + " ms";
			glfwSetWindowTitle(window, newTitle.c_str());
			prevTime = crntTime;
			frameCount = 0;
			//take camera controls every 1/60 second;
			camera.Inputs(window);
		}
		//set bg color
		glClearColor(0.07f, 0.13, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		
		//set up camera  FOV and Range
		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		model.Draw(shaderProgram, camera);

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