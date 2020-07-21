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
	//���캯��
	Ball(glm::vec3 _center, float _radius);

	//��ʼ��Ball
	void setBall();

	////ָ����ľ�
	//void setLongitude(int _longitude);
	////ָ�����γ
	//void setLatitude(int _latitude);


	//���������ɫR,G,B
	void setColor(float _red, float _green, float _blue);

	//����
	void draw(Shader * shader);

	~Ball();

	//����λ��
	glm::vec3 m_Center;
	//��İ뾶
	float m_Radius;
	//���ϵ������
	vector<glm::vec3> m_Data;


private:
	//��ľ�����
	int m_Longitude = 160;
	//���γ����
	int m_Latitude = 160;

	//VAO, VBO
	unsigned int VAO;
	unsigned int VBO;

	//����������ݣ����뵽m_Data��
	void initData();

	//�����ɫ
	glm::vec3 objColor;
	//���λ�þ���(��ʱ������)
	//glm::mat4 modelMat;

};

