#pragma once
#include "Entity.h"

class Camera : public Entity
{
public:
	Camera();
	~Camera();
	glm::mat4 getViewMatrix();
};

