#include "Camera.h"

Camera::Camera(glm::vec3 _position, glm::vec3 _worldUp, float _yaw, float _pitch) :
	front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), zoom(ZOOM)
{
	position = _position;
	worldUp = _worldUp;
	yaw = _yaw;
	pitch = _pitch;
	updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(position, position + front, up);
}

#include <iostream>

void Camera::processKeyBoard(Camera_Movement direction, float deltaTime)
{
	float velocity = movementSpeed * deltaTime;
	if (direction == FORWARD) {
		position += front * velocity;
	}
	if (direction == BACKWORD) {
		position -= front * velocity;
	}
	if (direction == LEFT) {
		position -= right * velocity;
	}
	if (direction == RIGHT) {
		position += right * velocity;
	}
}

void Camera::processMouseMovement(float xoffset, float yoffset)
{
	xoffset *= mouseSensitivity;
	yoffset *= mouseSensitivity;

	yaw += xoffset;
	pitch += yoffset;
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	updateCameraVectors();
}

void Camera::processMouseScroll(float yoffset)
{
	zoom -= (float)yoffset;
	if (zoom < 1.0f)
		zoom = 1.0f;
	if (zoom > 90.0f)
		zoom = 90.0f;
}

glm::vec3 Camera::getPosition()
{
	return position;
}

glm::vec3 Camera::getFront()
{
	return front;
}

float Camera::getZoom()
{
	return zoom;
}

void Camera::updateCameraVectors()
{
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}
