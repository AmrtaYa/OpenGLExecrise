//
// Created by S213 on 3/9/2023.
//

#include "Material.h"
#include "../include/GLEW/glew.h"

Material::Material(Shader *shader, glm::vec3 ambient,  int diffuse, int specular, float shininess)
        : Mat_Shader(shader), Mat_Ambient(ambient), Mat_diffuse(diffuse), Mat_specular(specular),
          Mat_Shininess(shininess)
{
    glUniform3f(glGetUniformLocation(shader->ID, "material.ambient"), ambient.x, ambient.y, ambient.z);
    // glUniform3f(glGetUniformLocation(shader->ID, "material.diffuse"),diffuse.x, diffuse.y, diffuse.z);
    glUniform1i(glGetUniformLocation(shader->ID, "material.diffuse"), diffuse);
   // glBindTexture(glGetUniformLocation(shader->ID, "material.diffuse"),diffuse);
    glUniform1i(glGetUniformLocation(shader->ID, "material.specular"),specular);
    glUniform1f(glGetUniformLocation(shader->ID, "material.shininess"), shininess);
}
