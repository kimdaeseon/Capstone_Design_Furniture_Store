#include "Vertex.h"
#include <vector>
using namespace std;

class Face {
public:
	Vertex getVertex(int index) {
		return this->vector[index];
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