#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum Camera_Movement {
	FORWARD,
	BACKWORD,
	LEFT,
	RIGHT
};

const float YAW			= -90.0f;
const float PITCH		= 0.0f;
const float SPEED		= 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM        = 60.0f;

class Camera
{
public:
	Camera(glm::vec3 _position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 _worldUp = glm::vec3(0.0f, 1.0f, 0.0f), float _yaw = YAW, float _pitch = PITCH);

	glm::mat4 getViewMatrix();

	void processKeyBoard(Camera_Movement direction, float deltaTime);

	void processMouseMovement(float xoffset, float yoffset);

	void processMouseScroll(float yoffset);

	glm::vec3 getPosition();

	glm::vec3 getFront();

	float getZoom();

	void setYaw(float y);

	float getYaw();
private:
	void updateCameraVectors();

	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	float yaw;
	float pitch;

	float movementSpeed;
	float mouseSensitivity;
	float zoom;
};

