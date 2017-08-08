#pragma once
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

class Entity
{
public:
	Entity();
	~Entity();

	glm::mat4 transform;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	glm::mat4* getTransform();
	glm::vec3* getPosition();
	glm::vec3* getScale();
	glm::vec3* getRotation();

	void setPosition(const float x, const float y, const float z);
	void setPosition(const glm::vec3* finalPosition);
	void setRotation(const float x, const float y, const float z);
	void setRotation(const glm::vec3* finalRotation);
	void setScale(const float x, const  float y, const float z);
	void setScale(const glm::vec3* finalScale);
	void setUniformScale(const float uniformScale);

	void incrementPosition(const float deltaX, const float deltaY, const float deltaZ);
	void incrementPosition(const glm::vec3* deltaPosition);
	void incrementRotation(const float deltaRotationX, const float deltaRotationY, const float deltaRotationZ);
	void incrementRotation(const glm::vec3* deltaRotation);
	void incrementScale(const float deltaScaleX, const float deltaScaleY, const float deltaScaleZ);
	void incrementScale(const glm::vec3* deltaScale);

	void moveTowards(const glm::vec3* destinationPoint, const float stepSize);
	void alignTowards(const glm::vec3* alignmentPoint, const float rotationStepSize);

	void moveAwayFrom(const glm::vec3* avoidancePoint, const float stepSize);
	void alignAwayFrom(const glm::vec3 alignmentAvoidancePoint, const float rotationStepSize);

	void growTowards(const glm::vec3* scaleGoal, const float growthStepSize);

	void scrubRotation(void);
private:
	inline float reduceWhileAbove(float reductedValue, const float limit);
	inline float increaseWhileBelow(float increasedValue, const float limit);
	const float kMaxDegrees = 360.0f;
};

