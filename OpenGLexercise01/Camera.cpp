#include "Camera.h"




Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldup){
	Position = position;
	WorldUp = worldup;
	Forward = glm::normalize(target - position);
	Right = glm::cross(Forward, WorldUp);
	Up = glm::normalize(glm::cross(Forward, Right));


}
Camera::Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldup) {
	/*
	Forward：表示相机面对的方向
	*/
	Position = position;
	WorldUp = worldup;
	Pitch = pitch;
	Yaw = yaw;
	Forward.x = glm::cos(pitch) * glm::sin(yaw);
	Forward.y = glm::sin(pitch);
	Forward.z = glm::cos(pitch) * glm::cos(yaw);
	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross(Right, Forward));

}


Camera::~Camera()
{
}

glm::mat4 Camera::GetViewMatrix(){

	return glm::lookAt(Position, Position + Forward, WorldUp);
}

glm::mat4 Camera::ClickChangeViewMatrix(int flag)
{

	switch (flag)
	{
	case(1): Position = glm::vec3(-30.0f, 0, 0); Pitch = 0; Yaw = glm::radians(90.0f); break;
	case(2): Position = glm::vec3(0, 0, 20.0f);  Pitch = 0; Yaw = glm::radians(-180.0f); break;
	case(3): Position = glm::vec3(30.0f, 0, 0);  Pitch = 0; Yaw = glm::radians(-90.0f); break;
	case(4): Position = glm::vec3(0, 0, -20.0f); Pitch = 0; Yaw = 0; break;
	default:
		break;
	}
	UpdateCameraVectors();
	return glm::lookAt(Position, Position + Forward, WorldUp);
}

glm::mat4 Camera::SeeResult(int flag, glm::vec3 resultposition)
{
	switch (flag)
	{
	case(5):
		Position.x = resultposition.x - 5.0f;	//左视图
		Position.y = resultposition.y;
		Position.z = resultposition.z;
		Pitch = 0; Yaw = glm::radians(90.0f); break;
	case(6):
		Position.x = resultposition.x;	//俯视图
		Position.y = resultposition.y + 5.0f;
		Position.z = resultposition.z;
		Pitch = glm::radians(-89.9f) ; Yaw = glm::radians(180.0f); break;	
	case(7):
		Position.x = resultposition.x;	//正视图
		Position.y = resultposition.y;
		Position.z = resultposition.z + 5.0f;
		Pitch = 0; Yaw = glm::radians(180.0f); break;	
	case(0):
		Position.x = resultposition.x - 5.0f;	
		Position.y = resultposition.y + 5.0f;
		Position.z = resultposition.z + 5.0f;
		Pitch = glm::radians(-35.0f); Yaw = glm::radians(135.0f); break;

	default:
		break;
	}
	UpdateCameraVectors();
	return glm::lookAt(Position, Position + Forward, WorldUp);
}


void Camera::UpdateCameraVectors() {
	Forward.x = glm::cos(Pitch) * glm::sin(Yaw);
	Forward.y = glm::sin(Pitch);
	Forward.z = glm::cos(Pitch) * glm::cos(Yaw);
	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross(Right, Forward));
}

void Camera::ProcessMouseMovement(float deltaX, float deltaY) {
	Pitch -= deltaY * SenseX;
	Yaw -= deltaX * SenseY;
	UpdateCameraVectors();
}

void Camera::UpdareCameraPos() {
	Position += (Forward * speedZ + Right * speedX + Up * speedY) * 0.1f;
}