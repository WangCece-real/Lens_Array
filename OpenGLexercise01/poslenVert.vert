#version 330 core		//�汾��
//	input
layout(location = 0) in vec3 aPos;          
//layout(location = 2) in vec3 lPos;

//	output ���Shader�����������������shader������������͡����ֶ���ͬ
out vec3 FragPos;
//out vec3 Normal;
//out vec2 TexCoord;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

//uniform int flag;

void main() {
	//λ�ñ任
	gl_Position = projMat * viewMat * modelMat * vec4(aPos.xyz, 1.0f);

	FragPos = vec4(aPos.xyz, 1.0).xyz;
} 

