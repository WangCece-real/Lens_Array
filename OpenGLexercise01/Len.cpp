#include "Len.h"

Len::Len(glm::vec3 _position, float _folength)
{
	this->m_Position = _position;
	this->m_RebuildPosition = _position;
	this->m_foLength = _folength;
	this->m_Image.reserve(10000);
	//初始化透镜，包括：
}

void Len::setArea(float _area)
{
	this->m_Area = _area;
}

//void Len::setColor(float _red, float _green, float _blue)
//{
//	this->m_ImageColor.x = _red;
//	this->m_ImageColor.y = _green;
//	this->m_ImageColor.z = _blue;
//	
//}

//准备好重建数据
void Len::calcRebuildData()
{
	//进行镜像变化
	for (vector<glm::vec3>::iterator it = this->m_Image.begin(); it != this->m_Image.end(); it++)
	{
		it->z = 2.0f * (this->m_Position.z + 2 * m_foLength) - it->z;
	}
	//初始化VAO
	glBindVertexArray(VAO);

	//初始化VBO并且把数据传入VBO中
	glGenBuffers(1, &VBO2);
	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*this->m_Image.size(), &m_Image[0], GL_STATIC_DRAW);

	//数据从VBO到VAO
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

	//VAO 的 0 号位置 和 1 号位置 是镜像关系
	//解绑VAO
	glBindVertexArray(0);

}


//初始化数据
void Len::setImage()
{

	//初始化VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//初始化VBO并且把数据传入VBO中
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*this->m_Image.size(), &m_Image[0], GL_STATIC_DRAW);

	//数据从VBO到VAO
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

	//VAO 的 0 号位置 和 1 号位置 是镜像关系
	//解绑VAO
	glBindVertexArray(0);

}


//输入原数据，计算出成像后的数据
void Len::lenImaging(vector<glm::vec3> &_object)
{
	/*
	用于在重建过程的成像数据计算
	*/
	this->m_Type = "MODE_R";
	for (vector<glm::vec3>::iterator it = _object.begin(); it != _object.end(); it++)
	{
		//逐点计算透镜的成像
		this->m_Image.push_back(calcImaging(*it));
	}
	if (m_Image.empty())
	{
		cout << "数据为空，无法重建" << endl;
	}
	else
	{
		this->setImage();

	}

}


void Len::lenImaging(vector<glm::vec3> &_object, glm::vec3  &_center)
{
	/*
		用于在成像过程的成像数据计算
	*/
	this->m_Type = "MODE_I";
	//重建透镜的位置
	this->calcRebuildPosition(_center);

	//cout <<"作用范围" << m_Area << endl;
	float negX = m_Position.x - m_Area;
	float optX = m_Position.x + m_Area;
	float negY = m_Position.y - m_Area;
	float optY = m_Position.y + m_Area;

	for (vector<glm::vec3>::iterator it = _object.begin(); it != _object.end(); it++)
	{
		if (it->z >= _center.z && it->x >= negX && it->x <= optX &&	it->y >= negY && it->y <= optY)
		{
			//逐点计算透镜的成像
			this->m_Image.push_back(calcImaging(*it));
			//cout << "可以用于成像的点坐标：(" << it->x << " " << it->y << " " << it->z << endl;;
		}
		//if (it->z <= _center.z)
		//{
		//	cout << "物体点坐标：(" << it->x << " " << it->y << " " << it->z << ")" << endl;

		//}
	}
	if (m_Image.empty())
	{
		cout << "数据为空，无法成像" << endl;
	}
	else
	{
		this->setImage();
		this->calcRebuildData();
	}

}

//用于lenImaging调用
glm::vec3 Len::calcImaging(glm::vec3 & _data)
{
	glm::vec3 Image;

	// ratio = U/V 物距/相距
	//物像变换比例不同这是怎么解决？？？？，可能不需要解决

	float objDistance = _data.z - m_Position.z;
	if (objDistance < 0) objDistance = -objDistance;
	float ratio;
	if (objDistance > m_foLength)	ratio = objDistance / m_foLength - 1;
	//应该是else 出错
	else
	{
		//ratio = 1 - objDistance / m_foLength;
		cout << "物距小于焦距，无法成像" << endl;
		return glm::vec3(0,0,0);
	}

	Image = m_Position - (_data - m_Position) / ratio;

	return Image;
}

void Len::calcRebuildPosition(glm::vec3 & _center)
{
	if (_center.z < this->m_Position.z)
	{
		this->m_RebuildPosition.z = m_Position.z + 4 * this->m_foLength;
	}
	else
	{
		cout << "输入物体在透镜位置不对" << endl;
		this->m_RebuildPosition.z = m_Position.z - 4 * this->m_foLength;
	}
	//cout << "原透镜位置" << endl;
	//cout << m_Position.x << ", " << m_Position.y << ", " << m_Position.z << endl;
	//cout << "重建透镜位置" << endl;
	//cout << m_RebuildPosition.x << ", " << m_RebuildPosition.y << ", " << m_RebuildPosition.z << endl;
}

//画出像的数据
void Len::draw(Shader * _shader)
{
	if (this->m_Type == "MODE_I")
	{
		glUniform3f(glGetUniformLocation(_shader->ID, "objColor"), 1.0f, 0, 0);

		this->draw_Data(_shader);
		this->draw_Mirror(_shader);
	}
	else
	{
		glUniform3f(glGetUniformLocation(_shader->ID, "objColor"), 0, 0, 1.0f);
		this->draw_Data(_shader);
	}

}

void Len::draw_Data(Shader *_shader)
{
	//绑上VAO
	glBindVertexArray(VAO);
	//设定数据：位置 颜色等
	glUniform1i(glGetUniformLocation(_shader->ID, "flag"), 0);
	//画图
	glDrawArrays(GL_TRIANGLE_STRIP, 0, this->m_Image.size());
	glBindVertexArray(0);			//解绑

}

void Len::draw_Mirror(Shader * _shader)
{
	//绑上VAO
	glBindVertexArray(VAO);
	//设定数据：位置 颜色等
	glUniform1i(glGetUniformLocation(_shader->ID, "flag"), 1);
	//画图
	glDrawArrays(GL_TRIANGLE_STRIP, 0, this->m_Image.size());
	glBindVertexArray(0);			//解绑

}

Len::~Len()
{
}
