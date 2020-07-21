#include "Ball.h"



Ball::Ball(glm::vec3 _center, float _radius)
{
	this->m_Center = _center;
	this->m_Radius = _radius;
	this->m_Data.reserve(20000);
	this->initData();
	this->setBall();
}

//初始化球
void Ball::setBall()
{

	//初始化modelMat 控制位置大小
	//this->modelMat = glm::translate(glm::mat4(1.0f), this->m_Center);
	//this->modelMat = glm::scale(this->modelMat, glm::vec3(this->m_Radius));

	//计算位置，存入m_Data再传到VBO
	for (vector<glm::vec3>::iterator it = m_Data.begin(); it != m_Data.end() ; it++)
	{
		*(it) *= this->m_Radius;
		*(it) += this->m_Center;
	}

	//初始颜色
	this->setColor(1, 1, 1);

	//初始化VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//初始化VBO，并向GL_ARRAY_BUFFER 传数据
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)* m_Data.size(), &m_Data[0], GL_STATIC_DRAW);

	//通过GL_ARRAY_BUFFER 传数据到 顶点数组中
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

	//解绑VAO
	glBindVertexArray(0);
}

//指定球的经
//void Ball::setLongitude(int _longitude)
//{
//	this->m_Longitude = _longitude;
//}
//
////指定球的纬
//void Ball::setLatitude(int _latitude)
//{
//	this->m_Latitude = _latitude;
//}

//生成球的数据
void Ball::initData()
{
	float ballX;
	float ballY;
	float ballZ;
	for (int i = 0; i < m_Longitude; i++)
	{
		//cout << "第 "<<i +1<<" 条带子" << endl;
		m_Data.push_back(glm::vec3(0, 1.0f, 0));//上顶点
		//画一条带子，总共有m_Longitude条
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
		m_Data.push_back(glm::vec3(0, -1.0f, 0));//下顶点
	}

}


void Ball::setColor(float _red, float _green, float _blue)
{
	objColor.x = _red;
	objColor.y = _green;
	objColor.z = _blue;
}

//画球，在渲染循环里面
void Ball::draw(Shader *shader)
{
	glUniform3f(glGetUniformLocation(shader->ID, "objColor"), objColor.x, objColor.y, objColor.z);
	//glUniformMatrix4fv(glGetUniformLocation(shader->ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(this->modelMat));
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, this->m_Data.size());
	glBindVertexArray(0);			//解绑

}


Ball::~Ball()
{
}
