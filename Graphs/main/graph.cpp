#include "graph.h"


Graph::Graph()
{	
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			matrix[i][j] = 0;
		}
	}
}

void Graph::addVertex(std::string v1)
{
	vertexes[vertexCount++] = v1;
}

int Graph::getVertexInd(std::string name)
{
	for (int i = 0; i < SIZE; i++)
	{
		if (vertexes[i] == name)
		{
			return i;
		}
	}
	return -1;
}

void Graph::addEdge(std::string v1, std::string v2)
{
	matrix[getVertexInd(v1)][getVertexInd(v2)] = 1;
	matrix[getVertexInd(v2)][getVertexInd(v1)] = 1;
}


bool Graph::IsEdgeExist(int v1, int v2)
{
	return matrix[v1][v2] ? 1 : 0;
}
bool Graph::IsVertexExist(std::string v1)
{
	for (int i = 0; i < vertexCount; i++)
	{
		if (vertexes[i] == v1)
			return 1;
		return 0;
	}
}

void Graph::findFriends(std::string start)
{
	std::string source = start;
	bool visited[SIZE];
	for (int i = 0; i < SIZE; i++)
		visited[i] = false;
	InnerDepth(start, visited, linkCount, source);
}


void Graph::InnerDepth(std::string current, bool visited[], int linkCount, std::string source)
{
	if (linkCount != 4)
	{
		if (linkCount != 0)
		{
			std::cout << source << " -> " << current << std::endl;
		}
		visited[getVertexInd(current)] = true;
		for (int i = 0; i < SIZE; i++)
		{
			if (IsEdgeExist(i, getVertexInd(current)) && !visited[i])
			{
				InnerDepth(vertexes[i], visited, linkCount + 1, source);
			}
		}

	}
	else
	{
		return;
	}
}


