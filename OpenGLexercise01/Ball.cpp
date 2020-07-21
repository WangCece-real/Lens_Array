#include "Ball.h"



Ball::Ball(glm::vec3 _center, float _radius)
{
	this->m_Center = _center;
	this->m_Radius = _radius;
	this->m_Data.reserve(20000);
	this->initData();
	this->setBall();
}

//��ʼ����
void Ball::setBall()
{

	//��ʼ��modelMat ����λ�ô�С
	//this->modelMat = glm::translate(glm::mat4(1.0f), this->m_Center);
	//this->modelMat = glm::scale(this->modelMat, glm::vec3(this->m_Radius));

	//����λ�ã�����m_Data�ٴ���VBO
	for (vector<glm::vec3>::iterator it = m_Data.begin(); it != m_Data.end() ; it++)
	{
		*(it) *= this->m_Radius;
		*(it) += this->m_Center;
	}

	//��ʼ��ɫ
	this->setColor(1, 1, 1);

	//��ʼ��VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//��ʼ��VBO������GL_ARRAY_BUFFER ������
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)* m_Data.size(), &m_Data[0], GL_STATIC_DRAW);

	//ͨ��GL_ARRAY_BUFFER �����ݵ� ����������
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

	//���VAO
	glBindVertexArray(0);
}

//ָ����ľ�
//void Ball::setLongitude(int _longitude)
//{
//	this->m_Longitude = _longitude;
//}
//
////ָ�����γ
//void Ball::setLatitude(int _latitude)
//{
//	this->m_Latitude = _latitude;
//}

//�����������
void Ball::initData()
{
	float ballX;
	float ballY;
	float ballZ;
	for (int i = 0; i < m_Longitude; i++)
	{
		//cout << "�� "<<i +1<<" ������" << endl;
		m_Data.push_back(glm::vec3(0, 1.0f, 0));//�϶���
		//��һ�����ӣ��ܹ���m_Longitude��
		for (int la = 1; la < m_Latitude; la++)
		{
			
			for (int j = 0; j < 2; j++)
			{
				ballX = glm::sin(PI / m_Latitude * la) * glm::cos((i + j) * 2 * PI / m_Longitude);
				ballY = glm::cos(PI / m_Latitude * la);
				ballZ = glm::sin(PI / m_Latitude * la) * glm::sin((i + j) * 2 * PI / m_Longitude);
				m_Data.push_back(glm::vec3(ballX, ballY, ballZ));
			}
		}
		m_Data.push_back(glm::vec3(0, -1.0f, 0));//�¶���
	}

}


void Ball::setColor(float _red, float _green, float _blue)
{
	objColor.x = _red;
	objColor.y = _green;
	objColor.z = _blue;
}

//��������Ⱦѭ������
void Ball::draw(Shader *shader)
{
	glUniform3f(glGetUniformLocation(shader->ID, "objColor"), objColor.x, objColor.y, objColor.z);
	//glUniformMatrix4fv(glGetUniformLocation(shader->ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(this->modelMat));
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, this->m_Data.size());
	glBindVertexArray(0);			//���

}


Ball::~Ball()
{
}
