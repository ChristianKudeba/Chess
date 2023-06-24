#include"Test.h"

Test::Test()
{
	int const boardHeight = 8;
	int const boardWidth = 8;
	int const bufferAttribNum = 8;
	
	// Sets the board vertices
	//GLfloat vertices[bufferAttribNum * (boardHeight + 1) * (boardWidth + 1)]{};
	for (int i = 0; i < (boardHeight + 1); ++i) { // columns
		for (int j = 0; j < (boardWidth + 1); ++j) { // rows
			vertices[(bufferAttribNum * ((boardWidth + 1) * i + j))] = 0.1f * float(j - boardWidth / 2); // xPos
			vertices[(bufferAttribNum * ((boardWidth + 1) * i + j)) + 1] = 0.1f * float(i - boardHeight / 2); // yPos
			vertices[(bufferAttribNum * ((boardWidth + 1) * i + j)) + 2] = 0.0f;  // zPos
			vertices[(bufferAttribNum * ((boardWidth + 1) * i + j)) + 3] = 1.0f * float((i + j) % 2);  // R
			vertices[(bufferAttribNum * ((boardWidth + 1) * i + j)) + 4] = 1.0f * float((i + j) % 2);  // G
			vertices[(bufferAttribNum * ((boardWidth + 1) * i + j)) + 5] = 1.0f * float((i + j) % 2);  // B
			vertices[(bufferAttribNum * ((boardWidth + 1) * i + j)) + 6] = 1.0f * float(j);  // Texture xCoord
			vertices[(bufferAttribNum * ((boardWidth + 1) * i + j)) + 7] = 1.0f * float(i);  // Texture yCoord
		}
	}

	// Sets the triangle indices. 2 traingles per square. Goes left to right, bottom to top.
	//GLuint indices[6 * boardHeight * boardWidth]{};
	int n = 0;
	for (int m = 0; m < (boardHeight * boardWidth); ++m)
	{
		if (((m + n + 1) % (boardWidth + 1)) == 0) // if m represents an "edge" vertex
		{
			n++;
		}

		indices[6 * m] = m + n;
		indices[6 * m + 1] = m + n + boardWidth + 2;
		indices[6 * m + 2] = m + n + boardWidth + 1;
		indices[6 * m + 3] = m + n;
		indices[6 * m + 4] = m + n + boardWidth + 2;
		indices[6 * m + 5] = m + n + 1;
	}
}


GLfloat* Test::getVertices()
{
	return vertices;
}

GLuint* Test::getIndices()
{
	return indices;
}