#ifndef _BEZIERCURVE_H_
#define _BEZIERCURVE_H_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class BezierCurve {
public:
	BezierCurve();
	void Render();
	void renderDynamic(float);

private:
	void renderPoint();		// 绘制鼠标点击形成的点及其连成的直线
	void renderCurve();		// 计算绘制曲线上的点
	void dynamicDisplay(vector<glm::vec2> vertex, float animation);		// 动态呈现曲线生成过程
	long int factorial(int x);		// 阶乘
	
public:
	vector<glm::vec2> point;		// 用来保存鼠标点击后的点的坐标
	float vertices[100];			// 将点的坐标用数组的方式来存储
	float curveVertices[9999];		// bezier曲线上的点的坐标
	float dynamicVertices[9999];	// 动态呈现过程中的点的坐标
	int curvePointCount = 0;		// bezier曲线上的点的数量
};

#endif