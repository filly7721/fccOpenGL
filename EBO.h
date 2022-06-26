#ifndef  EBO_CLASS_H
#define EBO_CLASSS_H

#include<glad/glad.h>
#include<vector>
class EBO {

public:
	GLuint ID;

	EBO(std::vector<GLuint> indices);

	void Bind();
	void UnBind();
	void Delete();

};

#endif
