//
// Created by S213 on 3/6/2023.
//

#ifndef EXECRISE2_CAMERA_H
#define EXECRISE2_CAMERA_H

#include "glm/glm.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"
#include "../include/glm/gtc/type_ptr.hpp"
class Camera
{
public:
    Camera(glm::vec3 pos,glm::vec3  dirUp,float pitchNum, float yawNum);
    glm::mat4 UpdateCamera();
    void Move(glm::vec3 moveDelta);
    void Rotate(float xDelta,float yDelta);
    glm::vec3 position;
    glm::vec3 forword;
    glm::vec3 right;
    glm::vec3 up;
private:

    float pitch;
    float yaw;

};


#endif //EXECRISE2_CAMERA_H
