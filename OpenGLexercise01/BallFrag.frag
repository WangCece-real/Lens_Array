#version 330 core    
in vec3 FragPos;

out vec4 FragColor;    

//uniform sampler2D ourTexture;
//uniform sampler2D ourFace;

uniform vec3 objColor;
//uniform vec3 ambientColor;

uniform vec3 cameraPos;


void main() {		
	
	vec3 finalResult = vec3(0, 0, 0);
	//vec3 uNormal = normalize(Normal);
	//vec3 dirToCamera = normalize(cameraPos - FragPos);

	//finalResult += material.ambient * texture(material.diffuse, TexCoord).rgb;
	finalResult += objColor;

	FragColor = vec4( finalResult, 1.0f) ;
	//FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);

}