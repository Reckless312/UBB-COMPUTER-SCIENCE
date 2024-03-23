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
	vector <string> vertices;
	map <string, vector <string>> edges;
	map <tuple<string, string>, int> cost;
	map <string, vector<string>> InDegree;
	string file;

	void InitializeEdge(string vertex);
	void InitializeInDegree(string vertex);
	bool FindInVector(vector<string> vector, string ElementToCheck);
	vector<tuple<string, string>> IterateEdgesHelper(void);
public:
	DirectedGraph(void);
	DirectedGraph(DirectedGraph& other);
	void AddVertex(string vertex);
	void AddEdge(string start, string end);
	void DeleteVertex(string vertex);
	void DeleteEdge(string start, string end);
	void SaveFile(string file_name = "SavedGraph.txt");
	DirectedGraphIteratorVertices IterateVertices(void);
	bool CheckEdge(string starting_vertex, string ending_vertex);
	int DegreeIn(string vertex);
	int DegreeOut(string vertex);
	vector<string> GetEndPoints(string vertex);
	int GetCost(string start, string end);
	void ChangeCost(string start, string end, int new_cost);
	int GetNumberOfVertices(void);
	int GetNumberOfEdges(void);
	void PlaceCost(string start, string end, int cost);
	void RandomGraph(int vertices, int edges);
	DirectedGraphIteratorBounds IterateInbounds(string vertex);
	DirectedGraphIteratorBounds IterateOutbounds(string vertex);
	void SetFileName(string name);
	void ReadFile(void);
};
