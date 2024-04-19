#pragma once

#include "EdgesIterator.h"
#include "VertexEdgeIterator.h"
#include "VerticesIterator.h"
#include <random>
#include <set>

class P3;

class UnDirectedGraph
{
	friend class EdgesIterator;
	friend class VertexEdgesIterator;
	friend class VerticesIterator;
	friend class P3;
private:
	int number_of_vertices;
	int number_of_edges;
	vector <int> vertices;
	map <int, vector <int>> edges;
	map <tuple<int, int>, int> costs;
	string file_name;

	void InitializeEdges(int vertex);
	bool FindVertex(vector<int> vector, int vertex);
	vector<tuple<int, int>> IterateEdgesHelper();
public:
	UnDirectedGraph();
	UnDirectedGraph(UnDirectedGraph& other);

	void AddVertex(int vertex);
	void AddEdge(int first_vertex, int second_vertex);
	void DeleteVertex(int vertex);
	void DeleteEdge(int first_vertex, int second_vertex);
	bool CheckEdge(int first_vertex, int second_vertex);
	void PlaceCost(int first_vertex, int second_vertex, int cost);

	int GetNumberOfVertices();
	int GetNumberOfEdges();
	int GetDegree(int vertex);
	vector<int> GetConnectedPointOfVertex(int vertex);
	int GetCost(int first_vertex, int second_vertex);
	
	void ChangeCost(int first_vertex, int second_vertex, int new_cost);

	void RandomGraph(int number_of_vertices, int number_of_edges);

	void AddFromFileVertex(int vertex);
	void AddFromFileEdge(int first_vertex, int second_vertex);
	void PlaceFromFileCost(int first_vertex, int second_vertex, int cost);
	void ReadFile();
	void SaveFile(string file_name = "SavedGraph.txt");
	
	VerticesIterator IterateVertices();
	VertexEdgeIterator IterateEdgesOfAVertex(int vertex);
	void SetFileName(string name);
};
