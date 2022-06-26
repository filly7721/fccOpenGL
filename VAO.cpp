#include "VAO.h"

VAO::VAO()
{
	glGenVertexArrays(1, &ID);

}

void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents,
	GLenum type, GLsizeiptr stride, void* offset)
{
	Bind();

	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);

	UnBind();
}

void VAO::Bind()
{
	glBindVertexArray(ID);
}

void VAO::UnBind()
{
	glBindVertexArray(0);
}

void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}
