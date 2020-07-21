#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ConvexLens
{//͹͸������
public:
	ConvexLens(glm::vec3 _position, float _focalLength);
	~ConvexLens();

	float positionX;
	float positionY;
	float positionZ;
	float focalLength;



};

