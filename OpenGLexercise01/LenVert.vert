#version 330 core		//�汾��
//	input
layout(location = 0) in vec3 aPos;          
layout(location = 1) in vec3 bPos;

//	output ���Shader�����������������shader������������͡����ֶ���ͬ
out vec3 FragPos;
//out vec3 Normal;
//out vec2 TexCoord;

//uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

uniform int flag;

void main() {
	
	if(flag == 0 )
	{
		gl_Position = projMat * viewMat * vec4(aPos.xyz, 1.0f);
		FragPos = vec4(aPos.xyz, 1.0).xyz;
	}
	else
	{
		gl_Position = projMat * viewMat * vec4(bPos.xyz, 1.0f);
		FragPos = vec4(bPos.xyz, 1.0).xyz;
	}

//	gl_Position = projMat * viewMat * vec4(aPos.xyz, 1.0f);
//	FragPos = vec4(aPos.xyz, 1.0).xyz;
} 

