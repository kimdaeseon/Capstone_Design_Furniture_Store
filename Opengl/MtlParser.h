#include <sstream>
#include <iostream>
using namespace std;

#include "Vertex.h"
#include "Parser.h"

class MtlParser : public Parser {
public:
	Vertex ambient;
	Vertex diffuse;
	Vertex specular;
	
	void parse(const char* line) final {
		float x, y, z;
		char lineHeader[128];
		sscanf(line, "\t %s %f %f %f", lineHeader, &x, &y, &z);
		if (strcmp(lineHeader, "Ka") == 0) {
			ambient.X = x;
			ambient.Y = y;
			ambient.Z = z;
		}
		else if (strcmp(lineHeader, "Kd") == 0) {
			diffuse.X = x;
			diffuse.Y = y;
			diffuse.Z = z;
		}
		else if (strcmp(lineHeader, "Ks") == 0) {
			specular.X = x;
			specular.Y = y;
			specular.Z = z;
		}
	}
};