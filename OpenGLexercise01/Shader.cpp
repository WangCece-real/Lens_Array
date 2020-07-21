#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>


using namespace std;

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	ifstream vertexFile;		//fstream
	ifstream fragmentFile;
	stringstream vertexSStream;		//sstream
	stringstream fragmentSStream;

	//打开文件不代表是已经导入内存你的内容，只是在声明在使用这个文件
	vertexFile.open(vertexPath);
	fragmentFile.open(fragmentPath);

	//查出错：逻辑错误还是物理错误
	vertexFile.exceptions(ifstream::failbit || ifstream::badbit);
	fragmentFile.exceptions(ifstream::failbit || ifstream::badbit);


	//查看是否文件打开成功
	try
	{
		if (!vertexFile.is_open()|| !fragmentFile.is_open() )
		{
			//打开文件出错，丢出一个exception
			throw exception("open file error");
		}
		//将文件读入？
		vertexSStream << vertexFile.rdbuf();
		fragmentSStream << fragmentFile.rdbuf();

		vertexString = vertexSStream.str();	//可以直接转成string
		fragmentString = fragmentSStream.str();

		vertexSource = vertexString.c_str();		//转成静态str，const str
		fragmentSource = fragmentString.c_str();

		//cout << vertexString << endl;
		//cout << fragmentString << endl;
		//cout << vertexSource << endl;
		//cout << fragmentSource << endl;
		unsigned int vertex, fragment;

		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vertexSource,NULL);
		glCompileShader(vertex);
		checkCompileErrors(vertex, "VERTEX");

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fragmentSource, NULL);
		glCompileShader(fragment);
		checkCompileErrors(fragment, "FRAGMENT");

		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		checkCompileErrors(ID, "PROGRAM");
		
		glDeleteShader(vertex);		//进行link操作之后，vertex，fragment都不在使用了
		glDeleteShader(fragment);


		//printf(vertexSource);
		//printf(fragmentSource);
	}
	catch (const std::exception& ex)
	{
		printf(ex.what());
	}
}

void Shader::use() {
	glUseProgram(ID);
}

void Shader::setUniform3f(const char * paramNameString, glm::vec3 param)
{
	glUniform3f(glGetUniformLocation(ID, paramNameString), param.x, param.y, param.z);
}

void Shader::setUniform1f(const char * paramNameString, float param)
{
	glUniform1f(glGetUniformLocation(ID, paramNameString), param);
}

void Shader::setUniform1i(const char * paramNameString, int slot)
{ 
	glUniform1i(glGetUniformLocation(ID, paramNameString), slot);
}

void Shader::checkCompileErrors(unsigned int ID, std::string type) {

	int success;
	char infoLog[512];

	if (type != "PROGRAM")
	{
		glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(ID, 512, NULL, infoLog);
			cout << "shader compile error:" << infoLog << endl;
		}
	}
	else
	{
		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(ID, 512, NULL, infoLog);
			cout << "program compile error:" << infoLog << endl;

		}
	}
}
//void Shader::test() {
//
//	printf("test test test");
//}
//
//Shader::~Shader()
//{
//}
