#include "Model.h"
using namespace ENGINE;

Model::Model(Mesh * mesh)
{
	size = mesh->index.size();

	//Generate OpenGL Buffers and bind them
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &point);
	glBindBuffer(GL_ARRAY_BUFFER, point);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);

	//push data to GPU
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * mesh->point.size(), &((mesh->point)[0]), GL_STATIC_DRAW);

	//setup attribute pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 12 * 4, (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 12 * 4, (void*)12);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 12 * 4, (void*)24);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 12 * 4, (void*)32);

	//generate index buffers
	glGenBuffers(1, &index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * mesh->index.size(), &((mesh->index)[0]), GL_STATIC_DRAW);

	//Disable everything we enabled here
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);

	//disable buffers
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Model::~Model()
{
	//cleanup buffers and such
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &index);
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &vao);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &point);
}

void Model::Render()
{
	//Render the model on the screen

	//Bind everything
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, point);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);

	//enable vertex attrib arrays
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);

	//draw call
	glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, (void*)0);

	//disable things
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
}
