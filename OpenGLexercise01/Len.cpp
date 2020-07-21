#include "Len.h"

Len::Len(glm::vec3 _position, float _folength)
{
	this->m_Position = _position;
	this->m_RebuildPosition = _position;
	this->m_foLength = _folength;
	this->m_Image.reserve(10000);
	//��ʼ��͸����������
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

//׼�����ؽ�����
void Len::calcRebuildData()
{
	//���о���仯
	for (vector<glm::vec3>::iterator it = this->m_Image.begin(); it != this->m_Image.end(); it++)
	{
		it->z = 2.0f * (this->m_Position.z + 2 * m_foLength) - it->z;
	}
	//��ʼ��VAO
	glBindVertexArray(VAO);

	//��ʼ��VBO���Ұ����ݴ���VBO��
	glGenBuffers(1, &VBO2);
	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*this->m_Image.size(), &m_Image[0], GL_STATIC_DRAW);

	//���ݴ�VBO��VAO
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

	//VAO �� 0 ��λ�� �� 1 ��λ�� �Ǿ����ϵ
	//���VAO
	glBindVertexArray(0);

}


//��ʼ������
void Len::setImage()
{

	//��ʼ��VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//��ʼ��VBO���Ұ����ݴ���VBO��
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*this->m_Image.size(), &m_Image[0], GL_STATIC_DRAW);

	//���ݴ�VBO��VAO
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

	//VAO �� 0 ��λ�� �� 1 ��λ�� �Ǿ����ϵ
	//���VAO
	glBindVertexArray(0);

}


//����ԭ���ݣ����������������
void Len::lenImaging(vector<glm::vec3> &_object)
{
	/*
	�������ؽ����̵ĳ������ݼ���
	*/
	this->m_Type = "MODE_R";
	for (vector<glm::vec3>::iterator it = _object.begin(); it != _object.end(); it++)
	{
		//������͸���ĳ���
		this->m_Image.push_back(calcImaging(*it));
	}
	if (m_Image.empty())
	{
		cout << "����Ϊ�գ��޷��ؽ�" << endl;
	}
	else
	{
		this->setImage();

	}

}


void Len::lenImaging(vector<glm::vec3> &_object, glm::vec3  &_center)
{
	/*
		�����ڳ�����̵ĳ������ݼ���
	*/
	this->m_Type = "MODE_I";
	//�ؽ�͸����λ��
	this->calcRebuildPosition(_center);

	//cout <<"���÷�Χ" << m_Area << endl;
	float negX = m_Position.x - m_Area;
	float optX = m_Position.x + m_Area;
	float negY = m_Position.y - m_Area;
	float optY = m_Position.y + m_Area;

	for (vector<glm::vec3>::iterator it = _object.begin(); it != _object.end(); it++)
	{
		if (it->z >= _center.z && it->x >= negX && it->x <= optX &&	it->y >= negY && it->y <= optY)
		{
			//������͸���ĳ���
			this->m_Image.push_back(calcImaging(*it));
			//cout << "�������ڳ���ĵ����꣺(" << it->x << " " << it->y << " " << it->z << endl;;
		}
		//if (it->z <= _center.z)
		//{
		//	cout << "��������꣺(" << it->x << " " << it->y << " " << it->z << ")" << endl;

		//}
	}
	if (m_Image.empty())
	{
		cout << "����Ϊ�գ��޷�����" << endl;
	}
	else
	{
		this->setImage();
		this->calcRebuildData();
	}

}

//����lenImaging����
glm::vec3 Len::calcImaging(glm::vec3 & _data)
{
	glm::vec3 Image;

	// ratio = U/V ���/���
	//����任������ͬ������ô����������������ܲ���Ҫ���

	float objDistance = _data.z - m_Position.z;
	if (objDistance < 0) objDistance = -objDistance;
	float ratio;
	if (objDistance > m_foLength)	ratio = objDistance / m_foLength - 1;
	//Ӧ����else ����
	else
	{
		//ratio = 1 - objDistance / m_foLength;
		cout << "���С�ڽ��࣬�޷�����" << endl;
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
		cout << "����������͸��λ�ò���" << endl;
		this->m_RebuildPosition.z = m_Position.z - 4 * this->m_foLength;
	}
	//cout << "ԭ͸��λ��" << endl;
	//cout << m_Position.x << ", " << m_Position.y << ", " << m_Position.z << endl;
	//cout << "�ؽ�͸��λ��" << endl;
	//cout << m_RebuildPosition.x << ", " << m_RebuildPosition.y << ", " << m_RebuildPosition.z << endl;
}

//�����������
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
	//����VAO
	glBindVertexArray(VAO);
	//�趨���ݣ�λ�� ��ɫ��
	glUniform1i(glGetUniformLocation(_shader->ID, "flag"), 0);
	//��ͼ
	glDrawArrays(GL_TRIANGLE_STRIP, 0, this->m_Image.size());
	glBindVertexArray(0);			//���

}

void Len::draw_Mirror(Shader * _shader)
{
	//����VAO
	glBindVertexArray(VAO);
	//�趨���ݣ�λ�� ��ɫ��
	glUniform1i(glGetUniformLocation(_shader->ID, "flag"), 1);
	//��ͼ
	glDrawArrays(GL_TRIANGLE_STRIP, 0, this->m_Image.size());
	glBindVertexArray(0);			//���

}

Len::~Len()
{
}
