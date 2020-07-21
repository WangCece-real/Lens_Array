#pragma once
#include<iostream>
using namespace std;
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

#include "Shader.h"

#define PI 3.14159


class Ball
{
public:
	//构造函数
	Ball(glm::vec3 _center, float _radius);

	//初始化Ball
	void setBall();

	////指定球的经
	//void setLongitude(int _longitude);
	////指定球的纬
	//void setLatitude(int _latitude);


	//设置球的颜色R,G,B
	void setColor(float _red, float _green, float _blue);

	//画球
	void draw(Shader * shader);

	~Ball();

	//球心位置
	glm::vec3 m_Center;
	//球的半径
	float m_Radius;
	//球上点的数据
	vector<glm::vec3> m_Data;


private:
	//球的经线数
	int m_Longitude = 160;
	//球的纬线数
	int m_Latitude = 160;

	//VAO, VBO
	unsigned int VAO;
	unsigned int VBO;

	//生成球的数据，存入到m_Data中
	void initData();

	//球的颜色
	glm::vec3 objColor;
	//球的位置矩阵(暂时不用了)
	//glm::mat4 modelMat;

};

