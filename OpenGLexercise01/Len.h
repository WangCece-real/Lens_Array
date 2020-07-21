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


#pragma region ��Ա����
public:
	Len(glm::vec3 _position, float _folength);
	//���÷�Χ
	void setArea(float _area);
	//������ɫ
	//void setColor(float _red, float _green, float blue);

	void lenImaging(vector<glm::vec3> &_data);	//_typename: MODE_R �ؽ�

	void lenImaging(vector<glm::vec3> &_data, glm::vec3  &_center);	//_typename: MODE_I ����

	//�����������
	void draw(Shader * _shader);

	~Len();

private:
	//����lenImaging ���ã����������λ��
	glm::vec3 calcImaging(glm::vec3 & _data);
	//��ʼ��VAO��VBOΪ��Ⱦ ���� ��׼��������������֮��
	void setImage();

	//�����ؽ�͸����λ��
	void calcRebuildPosition(glm::vec3 &_center);
	//׼�����ؽ�����
	void calcRebuildData();

	void draw_Data(Shader * _shader);

	void draw_Mirror(Shader * _shader);

#pragma endregion

#pragma region ��Ա����
public:
	//͸����λ��
	glm::vec3 m_Position;
	//͸���Ľ���
	float m_foLength;

	//���ɵ�������
	vector<glm::vec3> m_Image;

	//�ؽ�͸����λ��
	glm::vec3 m_RebuildPosition;

private:
	//͸�������÷�Χ
	float m_Area = 1.0f;

	//������ɫ
	glm::vec3 m_ImageColor = glm::vec3(1.0f,1.0f,1.0f);
	//VAO, VBO
	unsigned int VAO, VBO, VBO2;

	string m_Type;
#pragma endregion

	
};

