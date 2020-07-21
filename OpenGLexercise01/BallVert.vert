#version 330 core		//版本号
//	input
layout(location = 0) in vec3 aPos;          


//	output 输出Shader的输出变量，和输入shader的输入变量类型、名字都相同
out vec3 FragPos;
//out vec3 Normal;
//out vec2 TexCoord;

//uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

void main() {
	//位置变换
//	gl_Position = projMat * viewMat * modelMat * vec4(aPos.xyz, 1.0f);
//	FragPos = (modelMat * vec4(aPos.xyz, 1.0)).xyz;
	gl_Position = projMat * viewMat * vec4(aPos.xyz, 1.0f);
	FragPos = vec4(aPos.xyz, 1.0).xyz;
} 

