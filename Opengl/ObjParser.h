#pragma once
#pragma warning(disable:4996)

#include <vector>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

#include "Vertex.h"
#include "Face.h"


const int scale = 150;

class ObjParser {
public:
	void parse(const char* line) {
		prasingWithTexture(line);
	}

	void calculateFace() {
		try {
			for (unsigned int i = 0; i < vertexIndices.size(); i++) {
				pushFaces(vertexIndices[i], vertex, this->realVertex);
			}
			for (unsigned int i = 0; i < uvIndices.size(); i++) {
				pushFaces(uvIndices[i], texture, this->realTexture);
			}
			for (unsigned int i = 0; i < normalIndices.size(); i++) {
				pushFaces(normalIndices[i], normal, this->realNormal);
			}

			moveZeroPoint();
		}
		catch(string err) {
			return;
		}
	}

	vector<Vertex> vertex;
	vector<Vertex> normal;
	vector<Vertex> texture;

	vector<Vertex> skeleton;

	vector<vector<int>> vertexIndices;
	vector<vector<int>> uvIndices;
	vector<vector<int>> normalIndices;

	vector<Face> realVertex;
	vector<Face> realNormal;
	vector<Face> realTexture;
private:

	void prasingWithTexture(const char* line) {
		float x, y, z;
		char lineHeader[128];
		sscanf(line, "%s %f %f %f", lineHeader, &x, &y, &z);
		if (strcmp(lineHeader, "v") == 0) {
			Vertex tempVertex;
			tempVertex.X = x / scale;
			tempVertex.Y = -y / scale;
			tempVertex.Z = z / scale;
			vertex.push_back(tempVertex);
		}
		else if (strcmp(lineHeader, "b") == 0) {
			Vertex tempVertex;
			tempVertex.X = x / scale;
			tempVertex.Y = -y / scale;
			tempVertex.Z = z / scale;
			skeleton.push_back(tempVertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			Vertex tempVertex;
			tempVertex.X = x;
			tempVertex.Y = y;
			texture.push_back(tempVertex);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			Vertex tempVertex;
			tempVertex.X = x / 255;
			tempVertex.Y = y / 255;
			tempVertex.Z = z / 255;
			normal.push_back(tempVertex);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			unsigned int vertexIndex, uvIndex, normalIndex;

			vector<string> faces = this->split(line, ' ');
			int numberOfFaces = faces.size() - 1;

			vector<int> tempVertexIndices = { numberOfFaces };
			vector<int> tempUvIndices = { numberOfFaces };
			vector<int> tempNormalIndices = { numberOfFaces };

			for (int i = 1; i < faces.size(); i++) {
				vector<string> indices = split(faces[i], '/');

				int index;

				if (indices[0].compare("")) {
					stringstream s(indices[0]);
					s >> index;
					tempVertexIndices.push_back(index);
				} 
				if (indices[1].compare("")) {
					stringstream s(indices[1]);
					s >> index;
					tempUvIndices.push_back(index);
				}
				if (indices[2].compare("")) {
					stringstream s(indices[2]);
					s >> index;
					tempNormalIndices.push_back(index);
				}
				
			}

			if(tempVertexIndices.size() != 1) vertexIndices.push_back(tempVertexIndices);
			if (tempUvIndices.size() != 1) uvIndices.push_back(tempUvIndices);
			if (tempNormalIndices.size() != 1) normalIndices.push_back(tempNormalIndices);
		}
	}

	vector<string> split(string str, char Delimiter) {
		istringstream iss(str);             // istringstream�� str�� ��´�.
		string buffer;                      // �����ڸ� �������� ����� ���ڿ��� ������� ����

		vector<string> result;

		// istringstream�� istream�� ��ӹ����Ƿ� getline�� ����� �� �ִ�.
		while (getline(iss, buffer, Delimiter)) {
			result.push_back(buffer);               // ����� ���ڿ��� vector�� ����
		}

		return result;
	}

	void pushFaces(vector<int> indices, vector<Vertex> vertex, vector<Face>& resultVector) {
		Face tempFace;
		tempFace.setNumberOfVertex(indices[0]);

		for (int i = 1; i < indices.size(); i++) {
			unsigned int vertexIndex = indices[i];
			Vertex tempVertex = vertex[vertexIndex - 1];
			tempFace.pushBack(tempVertex);
		}

		resultVector.push_back(tempFace);
	}

	void moveZeroPoint() {
		Vertex zero = getMiddle();
		Vertex temp;

		for (int i = 0; i < realVertex.size(); i++) {
			for (int j = 0; j < realVertex[i].getNumberOfVertex(); j++) {
				temp = Vertex();
				temp.X = realVertex[i].getVertex(j).X - zero.X;
				temp.Y = realVertex[i].getVertex(j).Y - zero.Y;
				temp.Z = realVertex[i].getVertex(j).Z - zero.Z;

				realVertex[i].setVertex(j, temp);
			}
		}
	}

	Vertex getMiddle() {

		Vertex result = Vertex();
		Vertex temp;

		int count = 0;

		result.X = 0; result.Y = 0; result.Z = 0;
		for (int i = 0; i < realVertex.size(); i++) {
			for (int j = 0; j < realVertex[i].getNumberOfVertex(); j++) {
				temp = realVertex[i].getVertex(j);
				result.X = result.X + temp.X;
				result.Y = result.Y + temp.Y;
				result.Z = result.Z + temp.Z;
				count++;
			}
		}

		result.X /= (float)count;
		result.Y /= (float)count;
		result.Z /= (float)count;

		return result;

	}
};