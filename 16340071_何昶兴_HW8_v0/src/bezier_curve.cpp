#include "bezier_curve.h"

BezierCurve::BezierCurve() {

}

void BezierCurve::Render() {
	renderPoint();
	renderCurve();
}

void BezierCurve::renderPoint() {
	// ���������ת�������鴢��
	for (int i = 0, len = point.size(); i < len; i++) {
		vertices[2 * i] = point[i].x;
		vertices[2 * i + 1] = point[i].y;
	}

	// ���Ƶ��ֱ��
	unsigned int VBO, VAO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 2 * sizeof(float) * point.size(), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glPointSize(8.0f);
	glDrawArrays(GL_POINTS, 0, point.size());

	if (point.size() > 1) {
		glPointSize(1.0f);
		glDrawArrays(GL_LINE_STRIP, 0, point.size());
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void BezierCurve::renderCurve() {
	// ����bezier�����ϵĵ������
	curvePointCount = 0;
	if (point.size() > 1) {
		for (float t = 0; t < 1; t += 0.001) {
			float cx = 0, cy = 0;
			for (int i = 0, n = point.size() - 1; i <= n; i++) {
				float bernstein = factorial(n) / (factorial(i) * factorial(n - i)) * pow(t, i) * pow(1 - t, n - i);
				cx += point[i].x * bernstein;
				cy += point[i].y * bernstein;
			}
			curveVertices[curvePointCount * 2] = cx;
			curveVertices[curvePointCount * 2 + 1] = cy;
			curvePointCount++;
		}
	}

	// ����bezier����
	unsigned int curveVBO, curveVAO;
	glGenBuffers(1, &curveVBO);
	glBindBuffer(GL_ARRAY_BUFFER, curveVBO);
	glBufferData(GL_ARRAY_BUFFER, 2 * sizeof(float) * curvePointCount, curveVertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, curveVBO);
	glGenVertexArrays(1, &curveVAO);
	glBindVertexArray(curveVAO);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glPointSize(1.0f);
	glDrawArrays(GL_POINTS, 0, curvePointCount);

	glDeleteVertexArrays(1, &curveVAO);
	glDeleteBuffers(1, &curveVBO);
}

void BezierCurve::renderDynamic(float animation) {
	dynamicDisplay(point, animation);
}

void BezierCurve::dynamicDisplay(vector<glm::vec2> vertex, float animation) {
	int size = vertex.size();
	if (size <= 1) return;

	// ���㶯̬���ֹ����еĵ������
	vector<glm::vec2> nextVertices = vector<glm::vec2>();
	for (int i = 0; i < size - 1; i++) {
		float x = (1 - animation) * vertex[i].x + animation * vertex[i + 1].x;
		float y = (1 - animation) * vertex[i].y + animation * vertex[i + 1].y;
		dynamicVertices[i * 2] = x;
		dynamicVertices[i * 2 + 1] = y;
		nextVertices.push_back(glm::vec2(x, y));
	}

	// ���������������ĵ�������Լ������ɵ�ֱ��
	unsigned int dynamicVAO, dynamicVBO;
	glGenBuffers(1, &dynamicVBO);
	glBindBuffer(GL_ARRAY_BUFFER, dynamicVBO);
	glBufferData(GL_ARRAY_BUFFER, 2 * sizeof(float) * nextVertices.size(), dynamicVertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, dynamicVBO);
	glGenVertexArrays(1, &dynamicVAO);
	glBindVertexArray(dynamicVAO);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glPointSize(5.0f);
	glDrawArrays(GL_POINTS, 0, nextVertices.size());

	glPointSize(1.0f);
	glDrawArrays(GL_LINE_STRIP, 0, nextVertices.size());

	glDeleteVertexArrays(1, &dynamicVAO);
	glDeleteBuffers(1, &dynamicVBO);

	// �ݹ���ã�������һ��
	dynamicDisplay(nextVertices, animation);
}

long int BezierCurve::factorial(int x) {
	if (x == 0) return 1;
	int result = 1;
	for (int i = 1; i <= x; i++) {
		result *= i;
	}
	return result;
}