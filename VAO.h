#ifndef  VAO_CLASS_H
#define VAO_CLASSS_H

#include<glad/glad.h>
#include"VBO.h"

class VAO {

public:
	GLuint ID;

	VAO();

	void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents ,GLenum type, GLsizeiptr stride, void* offset);
	void Bind();
	void UnBind();
	void Delete();

};

#endif