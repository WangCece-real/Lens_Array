#include "LensArray.h"





LensArray::LensArray(glm::vec3 _position, int _xNum, int _yNum, float _span, float _focuslength, string _typeName)
{
	 //xy平面构造一个透镜阵列
	m_X = _xNum;
	m_Y = _yNum;
	this->m_ArrayPosition = _position;
	this->m_RebuildArrayPosition = _position;
	this->m_RebuildArrayPosition.z = _position.z + 4 * _focuslength;
	this->m_lensArrayData.reserve(_xNum);
	this->m_Typename = _typeName;

	for (int i = 0; i < _xNum; i++)
	{
		vector<Len> tempV;
		for (int j = 0; j < _yNum; j++)
		{
			Len tempL(glm::vec3(i * _span + _position.x, j * _span + _position.y, _position.z), _focuslength);
			tempL.setArea(_span / 2);
			tempV.push_back(tempL);
		}
		this->m_lensArrayData.push_back(tempV);
		tempV.clear();
	}
	setlp();
}

void LensArray::imagingSingle(int _xNum, int _yNum, vector<glm::vec3>& data)
{
	if (_xNum < this->m_lensArrayData.size() && _yNum < this->m_lensArrayData[0].size())
	{
		if (this->m_Typename == "MODE_I")
		{
			cout << "成像透镜需要输入物体中心" << endl;
			return;
		}
		this->m_lensArrayData[_xNum][_yNum].lenImaging(data);
	}
	else
	{
		cout << "(" << _xNum << ", " << _yNum << ") 成像数据无法计算" << endl;
	}
}

void LensArray::imagingSingle(int _xNum, int _yNum, vector<glm::vec3>& data, glm::vec3 _center)
{
	if (_xNum < this->m_lensArrayData.size() && _yNum < this->m_lensArrayData[0].size())
	{
		if (this->m_Typename == "MODE_R")
		{
			cout << "重建透镜不需要输入物体中心" << endl;
			return;
		}
		this->m_lensArrayData[_xNum][_yNum].lenImaging(data,_center);
	}
	else
	{
		cout << "(" << _xNum << ", " << _yNum << ") 成像数据无法计算" << endl;
	}

}

void LensArray::setPosition(int _xNum, int _yNum, glm::vec3 _position)
{
	if (_xNum < this->m_lensArrayData.size() && _yNum < this->m_lensArrayData[0].size())
	{
		if (m_Typename == "MODE_I")
		{
			cout << "成像模式不能调整透镜位置哦~" << endl;
		}
		this->m_lensArrayData[_xNum][_yNum].m_Position = _position;
	}
	else
	{
		cout << "(" << _xNum << ", " << _yNum << ") 出错" << endl;
	}
}

void LensArray::setFocusLength(int _xNum, int _yNum, float _focuslength)
{
	if (_xNum < this->m_lensArrayData.size() && _yNum < this->m_lensArrayData[0].size())
	{
		if (m_Typename == "MODE_I")
		{
			cout << "成像模式不能调整透镜焦距哦~" << endl;
		}
		this->m_lensArrayData[_xNum][_yNum].m_foLength = _focuslength;
	}
	else
	{
		cout << "(" << _xNum << ", " << _yNum << ") 出错" << endl;
	}

}

void LensArray::draw(Shader * _shader)
{
	for (vector<vector<Len>>::iterator it = this->m_lensArrayData.begin(); it != this->m_lensArrayData.end(); it++)
	{
		for (vector<Len>::iterator itl = it->begin(); itl != it->end(); itl++)
		{
			itl->draw(_shader);
		}

	}
}

void LensArray::drawlp(Shader * _shader)
{
	glm::mat4 lensLocation;
	if (this->m_Typename == "MODE_I")
	{
		glUniform3f(glGetUniformLocation(_shader->ID, "objColor"), 1.0f, 1.0f, 1.0f);
	}
	else
	{
		glUniform3f(glGetUniformLocation(_shader->ID, "objColor"), 1.0f, 1.0f, 0);
	}

	for (vector<vector<Len>>::iterator it = this->m_lensArrayData.begin(); it != this->m_lensArrayData.end(); it++)
	{
		for (vector<Len>::iterator itl = it->begin(); itl != it->end(); itl++)
		{
			lensLocation = glm::translate(glm::mat4(1.0f), itl->m_Position);
			lensLocation = glm::scale(lensLocation, glm::vec3(0.03f, 0.03f, 0.03f));
			glUniformMatrix4fv(glGetUniformLocation(_shader->ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(lensLocation));
			glBindVertexArray(ImageVAO);		//每次使用绑上一个VAO，
			glDrawArrays(GL_TRIANGLES, 0, 36);

			//lensLocation = glm::translate(glm::mat4(1.0f), itl->m_RebuildPosition);
			//lensLocation = glm::scale(lensLocation, glm::vec3(0.03f, 0.03f, 0.03f));
			//glUniformMatrix4fv(glGetUniformLocation(_shader->ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(lensLocation));
			//glUniform3f(glGetUniformLocation(_shader->ID, "objColor"), 1.0f, 1.0f, 0);
			//glBindVertexArray(ImageVAO);		//每次使用绑上一个VAO，
			//glDrawArrays(GL_TRIANGLES, 0, 36);

		}
	}

}

LensArray::~LensArray()
{
}

void LensArray::setlp()
{
	//成像透镜中心VBO
	glGenVertexArrays(1, &ImageVAO);
	glBindVertexArray(ImageVAO);
	glGenBuffers(1, &ImageVBO);
	glBindBuffer(GL_ARRAY_BUFFER, ImageVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->lp), lp, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glBindVertexArray(0);

}

