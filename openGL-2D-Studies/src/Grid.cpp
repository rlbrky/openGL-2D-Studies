#include "Grid.h"

Grid::Grid(): gridShader(new Shader()) {
	gridIndexCount = 0;
}

int Grid::createGrid(int segmentCount) {

	float distance = 1.0f / segmentCount;
	gridIndexCount = (segmentCount * 2 + 1)*4;

	std::vector<glm::vec3> vertices(gridIndexCount);
	std::vector<unsigned int> indices(gridIndexCount);

	for (int i = -segmentCount, j = 0; i <= segmentCount; i++, j++) {
		glm::vec3 v0, v1, v2, v3;
		v0.x = i * distance; v0.y = -1.0f; v0.z = 1.0f;
		v1.x = i * distance; v1.y = 1.0f; v1.z = 1.0f;
		v2.y = i * distance; v2.x = -1.0f; v2.z = 1.0f;
		v3.y = i * distance; v3.x = 1.0f; v3.z = 1.0f;

		vertices[j * 4] = v0;
		vertices[j * 4 + 1] = v1;
		vertices[j * 4 + 2] = v2;
		vertices[j * 4 + 3] = v3;

		indices[j * 4] = j * 4;
		indices[j * 4+1] = j * 4+1;
		indices[j * 4+2] = j * 4+2;
		indices[j * 4 + 3] = j * 4 + 3;
	}
	gridShader->CreateFromFiles(gridVertexLocation,gridFragmentLocation);

	//BU iþlemler yerine mesh renderer yazmak daha iyi olacaktýr.
	glGenVertexArrays(1, &vertexArrayObjectId);
	glBindVertexArray(vertexArrayObjectId);

	glGenBuffers(1, &vertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &indexBufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(glm::vec3), 0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(vertexArrayObjectId);
	
	return vertexArrayObjectId;
}

int Grid::GetGridIntexCount() {
	return gridIndexCount;
}

/*void Line::setTransform(const glm::mat3& Transform) {
	glUniformMatrix3fv(shaderGetUniformTransformLocation(), 1, false, &Transform[0][0]);
}*/

Grid::~Grid() {
	glDeleteVertexArrays(1, &vertexArrayObjectId);
	glDeleteBuffers(1, &indexBufferId);
	/*glDeleteBuffers(1, &vertexBufferId); */
}