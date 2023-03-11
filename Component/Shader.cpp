//
// Created by S213 on 2/21/2023.
//

#include "Shader.h"
#include "iostream"
#include "fstream"
#include "sstream"
#include "GLEW/glew.h"
#include "GLFW/glfw3.h"

using namespace std;

Shader::Shader(const std::string vertexPath, const std::string fragmentPath)
{
    ifstream vertex;
    ifstream frag;
    stringstream vertexStream;
    stringstream fragStream;
    vertex.exceptions(ifstream::failbit | ifstream::badbit);
    frag.exceptions(ifstream::failbit | ifstream::badbit);
    vertex.open(vertexPath);
    frag.open(fragmentPath);
    try
    {
        if (!vertex.is_open() || !frag.is_open())
        {
            throw "open File error";
        }
        vertexStream << vertex.rdbuf();
        fragStream << frag.rdbuf();
        vertexStr = vertexStream.str();
        fragStr = fragStream.str();
        vertexSource = vertexStr.c_str();
        fragSource = fragStr.c_str();

        unsigned int vertexID, fragID;

        vertexID = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexID, 1, &vertexSource, nullptr);
        glCompileShader(vertexID);
        CheckCompileErrors(vertexID,"VERTEX");

        fragID = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragID, 1, &fragSource, nullptr);
        glCompileShader(fragID);
        CheckCompileErrors(fragID,"FRAGMENT");

        ID = glCreateProgram();
        glAttachShader(ID, vertexID);
        glAttachShader(ID, fragID);
        glLinkProgram(ID);
        CheckCompileErrors(ID,"PROGRAM");

        glDeleteShader(vertexID);
        glDeleteShader(fragID);
    }
    catch (const char *ex)
    {
        printf(ex);
    }

}

void Shader::Use()
{
    glUseProgram(ID);

}

void Shader::CheckCompileErrors(unsigned int ID, std::string type)
{
    int success;
    char infoLog[512];
    if(type!="PROGRAM")
    {
        glGetShaderiv(ID,GL_COMPILE_STATUS,&success);
        if(!success)
        {
            glGetShaderInfoLog(ID,512,nullptr,infoLog);
            cout<<"Shader Error:"<<infoLog<<endl;
        }
    }
    else
    {
        glGetProgramiv(ID,GL_LINK_STATUS,&success);
        if(!success)
        {
            glGetProgramInfoLog(ID,512, nullptr,infoLog);
            cout<<"Program Error:"<<infoLog<<endl;
        }
    }

}