//
// Created by S213 on 3/6/2023.
//

#include "Camera.h"
#include "iostream"
Camera::Camera(glm::vec3 pos,glm::vec3  dirUp,float pitchNum, float yawNum) : position(pos),up(dirUp)
{
    float pitchAngle = glm::radians(pitchNum);
    float yawAngle = glm::radians(yawNum);
    pitch = pitchAngle;
    yaw = yawAngle;
    UpdateCamera();
}

void Camera::Move(glm::vec3 moveDelta)
{
    position+=moveDelta;
}

void Camera::Rotate(float xDelta,float yDelta)
{
    yaw += glm::radians( xDelta);
    pitch +=  glm::radians( -yDelta);
    if (yaw >= 89)yaw = 89;
    if (pitch >= 0.99F)pitch = 0.99F;
    if (yaw <= -89)yaw = -89;
    if (pitch <= -0.99F)pitch = -0.99F;
}

glm::mat4 Camera::UpdateCamera()
{
    glm::vec3 indexForword;
    indexForword.x = cos(pitch) * cos(yaw);
    indexForword.y = sin(pitch);
    indexForword.z = cos(pitch) * sin(yaw);
    forword = glm::normalize(indexForword);
    right = glm::normalize( glm::cross(forword,up));
    return glm::lookAt(position,position+forword,up);
}
