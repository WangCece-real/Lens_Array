#pragma once
#include <iostream>
using namespace std;

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Len.h"

#include <vector>
#include <string>

class LensArray
{

#pragma region ��Ա����
public:
	LensArray(glm::vec3 _position, int _xNum, int _yNum, float _span, float _focuslength, string _typeName);

	//��ĳ͸�����ó�����
	void imagingSingle(int _xNum, int _yNum, vector<glm::vec3> &data);
	void imagingSingle(int _xNum, int _yNum, vector<glm::vec3> &data, glm::vec3 _center);

	//����ĳ��͸����λ��
	void setPosition(int _xNum, int _yNum, glm::vec3 _position);

	//����ĳ��͸���Ľ���
	void setFocusLength(int _xNum, int _yNum, float _focuslength);

	//��������
	void draw(Shader * _shader);

	//��͸��λ��
	void drawlp(Shader * _shader);
	
	~LensArray();

private:

	void setlp();
	//void m_InitLArr(int _xNum, int _yNum, float _span);

	//�ж�����������Ƿ���ȷ
	//void m_isRight(int _xNum, int _yNum);

	//����͸���ĳ�������
	//void m_Update();
#pragma endregion

#pragma region ��Ա����
public:
	//͸������λ��,���½�
	glm::vec3 m_ArrayPosition;

	//�ؽ�͸��λ��
	glm::vec3 m_RebuildArrayPosition;
	//͸����������:�⣺x���ڣ�y
	vector<vector<Len>> m_lensArrayData;

	int m_X, m_Y;
private:
	string m_Typename;
	unsigned int ImageVAO;
	unsigned int ImageVBO;
	float lp[108] = {
		// positions        
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

#pragma endregion
};

