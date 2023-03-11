//
// Created by S213 on 3/9/2023.
//

#ifndef EXECRISE2_MATERIAL_H
#define EXECRISE2_MATERIAL_H

#include "Shader.h"
#include "../include/glm/glm.hpp"

class Material
{
public:
    Material(Shader *shader, glm::vec3 ambient = glm::vec3(1.0f, 1.0f, 1.0f),
              int diffuse = 0, int specular = 0,
             float shininess = 256.0f);

    glm::vec3 Mat_Ambient = glm::vec3(0.0f);
     int Mat_diffuse = 0;
    int Mat_specular = 0;
    float Mat_Shininess=0.0F;
    Shader* Mat_Shader = nullptr;
};


#endif //EXECRISE2_MATERIAL_H
