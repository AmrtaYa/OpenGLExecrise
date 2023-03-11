//
// Created by S213 on 2/21/2023.
//

#ifndef EXECRISE2_SHADER_H
#define EXECRISE2_SHADER_H
#include "iostream"

class Shader
{
public:
    Shader(const std::string vertexPath, const std::string fragmentPath);
    const char* vertexSource;
    const char* fragSource;
    unsigned int ID;
    void Use();
private:
    std::string vertexStr;
    std::string fragStr; void CheckCompileErrors(unsigned  int ID,std::string type);

};


#endif //EXECRISE2_SHADER_H
