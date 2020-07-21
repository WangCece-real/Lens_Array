#pragma once

#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	std::string vertexString;
	std::string fragmentString;
	const char* vertexSource;		//用来存放源代码的字符串
	const char* fragmentSource;

	enum Slot
	{
		DIFFUSE,
		SPECULAR
	};
	//~Shader();
	//void test();
	unsigned int ID;	//Shader Program ID
	void use();
	void setUniform3f(const char* paramNameString, glm::vec3 param);
	void setUniform1f(const char* paramNameString, float param);
	void setUniform1i(const char* paramNameString, int slot);
private:
	void checkCompileErrors(unsigned int ID, std::string type);
};

#endif // !SHADER_H