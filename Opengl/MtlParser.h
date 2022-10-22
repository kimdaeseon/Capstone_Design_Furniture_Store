#include <sstream>
#include <iostream>
#include "Vertex.h"


class MtlParser {
public:
	Vertex ambient;
	Vertex diffuse;
	Vertex specular;
	
	void parse(const char* line) {
		float x, y, z;
		char lineHeader[128];
		sscanf(line, "\t %s %f %f %f", lineHeader, &x, &y, &z);
		if (strcmp(lineHeader, "Ka") == 0) {
			cout << "Ka" << x << " " << y << " " << z << endl;
			ambient.X = x;
			ambient.Y = y;
			ambient.Z = z;
		}
		else if (strcmp(lineHeader, "Kd") == 0) {
			cout << "Kd" << x << " " << y << " " << z << endl;
			diffuse.X = x;
			diffuse.Y = y;
			diffuse.Z = z;
		}
		else if (strcmp(lineHeader, "Ks") == 0) {
			cout << "Ks" << x << " " << y << " " << z << endl;
			specular.X = x;
			specular.Y = y;
			specular.Z = z;
		}
	}
};