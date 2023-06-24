#ifndef TEST_CLASS_H
#define TEST_CLASS_H

#include<glad/glad.h>
#include<stb/stb_image.h>
#include"Texture.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

class Test
{
public:
	// Reference ID
	//GLuint ID;
	// Constructor
	Test();

	// getter functions
	GLfloat* getVertices();
	GLuint* getIndices();

private:
	GLfloat vertices[8*9*9]{};
	GLuint indices[6 * 8 * 8]{};
};

#endif