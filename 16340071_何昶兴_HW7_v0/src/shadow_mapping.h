#ifndef _SHADOWMAPPING_H_
#define _SHADOWMAPPING_H_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "shader.h"
#include "camera.h"

class ShadowMapping {
public:
	ShadowMapping() {};
	ShadowMapping(Shader shader, Shader depthShader, Shader lightShader, const unsigned int width, const unsigned int height);
	void inititalize(Shader shader, Shader depthShader, Shader lightShader, const unsigned int width, const unsigned int height);
	void setPlane();
	void setDepthMap();
	void loadTexture(const char *path);
	void renderLight();
	void renderScene(const Shader &shader);
	void render(GLFWwindow *window);
	void deleteBuffer();
	void renderGUI();
	void renderCube();

	Camera camera;
	bool enableCamera = false;

private:
	Shader shader;
	Shader depthShader;
	Shader lightShader;

	int width, height;
	const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;

	unsigned int lightVAO;
	unsigned int lightVBO;

	unsigned int planeVAO;
	unsigned int planeVBO;
	unsigned int cubeVAO = 0;
	unsigned int cubeVBO = 0;
	unsigned int quadVAO = 0;
	unsigned int quadVBO;
	unsigned int depthMapFBO;
	unsigned int depthMap;
	unsigned int woodTexture;

	glm::vec3 lightPos = glm::vec3(-2.0f, 4.0f, -1.0f);
	glm::mat4 lightProjection = glm::mat4(1.0f);
	glm::mat4 lightView = glm::mat4(1.0f);
	glm::mat4 lightSpaceMatrix = glm::mat4(1.0f);
	float near_plane = 1.0f, far_plane = 7.5f;

	//GUI相关变量
	int mappingType = 1;

	float ambientStrength = 0.1;
	float specularStrength = 0.5;
	int shininess = 32;
	
	bool lightMove = false;

	float lightX = 0.5f;
	float lightY = 1.0f;
	float lightZ = 1.5f;

	float lightVertices[108] = {
		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,

		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,

		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
	};
};

#endif
