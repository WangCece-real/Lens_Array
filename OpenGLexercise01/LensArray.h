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

#pragma region 成员函数
public:
	LensArray(glm::vec3 _position, int _xNum, int _yNum, float _span, float _focuslength, string _typeName);

	//对某透镜设置成像处理
	void imagingSingle(int _xNum, int _yNum, vector<glm::vec3> &data);
	void imagingSingle(int _xNum, int _yNum, vector<glm::vec3> &data, glm::vec3 _center);

	//设置某个透镜的位置
	void setPosition(int _xNum, int _yNum, glm::vec3 _position);

	//设置某个透镜的焦距
	void setFocusLength(int _xNum, int _yNum, float _focuslength);

	//画成像结果
	void draw(Shader * _shader);

	//画透镜位置
	void drawlp(Shader * _shader);
	
	~LensArray();

private:

	void setlp();
	//void m_InitLArr(int _xNum, int _yNum, float _span);

	//判断输入的坐标是否正确
	//void m_isRight(int _xNum, int _yNum);

	//更新透镜的成像数据
	//void m_Update();
#pragma endregion

#pragma region 成员变量
public:
	//透镜阵列位置,左下角
	glm::vec3 m_ArrayPosition;

	//重建透镜位置
	glm::vec3 m_RebuildArrayPosition;
	//透镜阵列容器:外：x，内：y
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

