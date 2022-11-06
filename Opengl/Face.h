#include "Vertex.h"
#include <vector>
using namespace std;

class Face {
public:
	Vertex getVertex(int index) {
		return this->vector[index];
	}
	
	void setVertex(int index, Vertex vertex) {
		this->vector[index] = vertex;
	}

	int getNumberOfVertex() {
		return this->numberOfVertex;
	}

	void setNumberOfVertex(int numberOfVertex) {
		this->numberOfVertex = numberOfVertex;
	}

	void pushBack(Vertex vertex) {
		this->vector.push_back(vertex);
	}
private:
	int numberOfVertex;
	vector<Vertex> vector;
};