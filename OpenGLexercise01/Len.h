#pragma once
#include <iostream>
#include <string>
using namespace std;
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

#include "Shader.h"

class Len
{


#pragma region 成员函数
public:
	Len(glm::vec3 _position, float _folength);
	//设置范围
	void setArea(float _area);
	//设置颜色
	//void setColor(float _red, float _green, float blue);

	void lenImaging(vector<glm::vec3> &_data);	//_typename: MODE_R 重建

	void lenImaging(vector<glm::vec3> &_data, glm::vec3  &_center);	//_typename: MODE_I 成像

	//画出像的数据
	void draw(Shader * _shader);

	~Len();

private:
	//用于lenImaging 调用，逐点计算成像位置
	glm::vec3 calcImaging(glm::vec3 & _data);
	//初始化VAO，VBO为渲染 成像 做准备，在载入数据之后
	void setImage();

	//计算重建透镜的位置
	void calcRebuildPosition(glm::vec3 &_center);
	//准备好重建数据
	void calcRebuildData();

	void draw_Data(Shader * _shader);

	void draw_Mirror(Shader * _shader);

#pragma endregion

#pragma region 成员变量
public:
	//透镜的位置
	glm::vec3 m_Position;
	//透镜的焦距
	float m_foLength;

	//所成的像数据
	vector<glm::vec3> m_Image;

	//重建透镜的位置
	glm::vec3 m_RebuildPosition;

private:
	//透镜的作用范围
	float m_Area = 1.0f;

	//成像颜色
	glm::vec3 m_ImageColor = glm::vec3(1.0f,1.0f,1.0f);
	//VAO, VBO
	unsigned int VAO, VBO, VBO2;

	string m_Type;
#pragma endregion

	
};

