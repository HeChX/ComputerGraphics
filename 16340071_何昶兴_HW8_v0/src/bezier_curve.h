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
	void renderPoint();		// ����������γɵĵ㼰�����ɵ�ֱ��
	void renderCurve();		// ������������ϵĵ�
	void dynamicDisplay(vector<glm::vec2> vertex, float animation);		// ��̬�����������ɹ���
	long int factorial(int x);		// �׳�
	
public:
	vector<glm::vec2> point;		// ���������������ĵ������
	float vertices[100];			// ���������������ķ�ʽ���洢
	float curveVertices[9999];		// bezier�����ϵĵ������
	float dynamicVertices[9999];	// ��̬���ֹ����еĵ������
	int curvePointCount = 0;		// bezier�����ϵĵ������
};

#endif