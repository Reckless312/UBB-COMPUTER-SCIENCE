#pragma once
#include "GraphIteratorEdges.h"
#include "GraphIteratorVertices.h"
#include "GraphIteratorBounds.h"

class DirectedGraph
{
	friend class DirectedGraphIteratorEdges;
	friend class DirectedGraphIteratorVertices;
	friend class DirectedGraphIteratorBounds;
private:
	int number_of_vertices;
	int number_of_edges;
	vector <int> vertices;
	map <int, vector <int>> OutBoundEdges;
	map <tuple<int, int>, int> cost;
	map <int, vector<int>> InBoundEdges;
	string file;

	void InitializeOutBoundsEdges(int vertex);
	void InitializeInBoundsEdges(int vertex);
	bool FindInVector(vector<int> vector, int ElementToCheck);
	vector<tuple<int, int>> IterateEdgesHelper(void);
public:
	DirectedGraph(void);
	DirectedGraph(DirectedGraph& other);
	void AddVertex(int vertex);
	void AddEdge(int start, int end);
	void DeleteVertex(int vertex);
	void DeleteEdge(int start, int end);
	void SaveFile(string file_name = "SavedGraph.txt");
	DirectedGraphIteratorVertices IterateVertices(void);
	bool CheckEdge(int starting_vertex, int ending_vertex);
	int DegreeIn(int vertex);
	int DegreeOut(int vertex);
	vector<int> GetEndPoints(int vertex);
	int GetCost(int start, int end);
	void ChangeCost(int start, int end, int new_cost);
	int GetNumberOfVertices(void);
	int GetNumberOfEdges(void);
	void PlaceCost(int start, int end, int cost);
	void RandomGraph(int vertices, int edges);
	DirectedGraphIteratorBounds IterateInbounds(int vertex);
	DirectedGraphIteratorBounds IterateOutbounds(int vertex);
	void SetFileName(string name);
	void ReadFile(void);
};
