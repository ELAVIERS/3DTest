#include "CubeRenderer.h"
#include "Vertex.h"
#include <cstddef>

GLuint CubeRenderer::_vao;
GLuint CubeRenderer::_vbo;

#define VERT(X, Y, Z, NX, NY, NZ) { Vector3F(X.f, Y.f, Z.f), Vector3F(NX.f, NY.f, NZ.f) }
#define TRI(X1, Y1, Z1, X2, Y2, Z2, X3, Y3, Z3, NX, NY, NZ) \
	VERT(X1, Y1, Z1, NX, NY, NZ), VERT(X2, Y2, Z2, NX, NY, NZ), VERT(X3, Y3, Z3, NX, NY, NZ)

const Vertex_P3_N3 verts[36] = {
	//Bottom
	TRI(-1, -1, -1,		-1, -1, 1,		1, -1, -1,		0, -1, 0),
	TRI(1, -1, 1,		1, -1, -1,		-1, -1, 1,		0, -1, 0),

	//Top
	TRI(-1, 1, -1,		1, 1, -1,		-1, 1, 1,		0, 1, 0),
	TRI(1, 1, 1,		-1, 1, 1,		1, 1, -1,		0, 1, 0),

	//Front
	TRI(-1, -1, -1,		1, -1, -1,		-1, 1, -1,		0, 0, -1),
	TRI(1, 1, -1,		-1, 1, -1,		1, -1, -1,		0, 0, -1),

	//Right
	TRI(1, -1, -1,		1, -1, 1,		1, 1, -1,		1, 0, 0),
	TRI(1, 1, 1,		1, 1, -1,		1, -1, 1,		1, 0, 0),

	//Back
	TRI(1, -1, 1,		-1, -1, 1,		1, 1, 1,		0, 0, 1),
	TRI(-1, 1, 1,		1, 1, 1,		-1, -1, 1,		0, 0, 1),

	//Left
	TRI(-1, -1, 1,		-1, -1, -1,		-1, 1, 1,		-1, 0, 0),
	TRI(-1, 1, -1,		-1, 1, 1,		-1, -1, -1,		-1, 0, 0)
};

void CubeRenderer::Create() {
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);

	glBindVertexArray(_vao);

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), &verts, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex_P3_N3), (GLvoid*)offsetof(Vertex_P3_N3, position));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex_P3_N3), (GLvoid*)offsetof(Vertex_P3_N3, normal));

}

void CubeRenderer::Bind() {
	glBindVertexArray(_vao);
}

void CubeRenderer::Render() {
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
