#pragma once
#include <iostream>
#include <string>

#define SIZE 10

class Graph
{
private:
	int linkCount = 0;
	std::string vertexes[SIZE];
	int vertexCount = 0;
	int matrix[SIZE][SIZE];
	bool IsEdgeExist(int v1, int v2);
	bool IsVertexExist(std::string v1);

	int getVertexInd(std::string name);
	void InnerDepth(std::string current, bool visited[], int linkCount, std::string source);

public:
	Graph();
	void addVertex(std::string v1);
	void addEdge(std::string v1, std::string v2);
	void findFriends(std::string v1);


};
