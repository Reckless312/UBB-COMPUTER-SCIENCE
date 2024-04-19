#include "P3.h"

P3::P3(UnDirectedGraph& graph)
{
	this->graph = graph;
}

void P3::UpdateGraph(UnDirectedGraph& graph)
{
	/*
	* Updates the current graph;
	*/
	this->graph = graph;
}

void P3::ConnectedComponents()
{
	/*
	* Shows all connected components of the graph
	*/
	bool* visited = new bool[this->graph.GetNumberOfVertices()];
	for (int v = 0; v < this->graph.GetNumberOfVertices(); v++)
	{
		visited[v] = false;
	}
	for (int v = 0; v < this->graph.GetNumberOfVertices(); v++)
	{
		if (visited[v] == false)
		{
			DFS(v, visited);
			cout << "\n";
		}
	}
	delete[] visited;
}

void P3::DFS(int vertex, bool visited[])
{
	/*
	* Explores all connected vertices of a given vertex
	*/
	stack <int> stack;
	stack.push(vertex);
	while (!stack.empty())
	{
		int current_vertex = stack.top();
		stack.pop();
		if (!visited[current_vertex])
		{
			cout << current_vertex << " ";
			visited[current_vertex] = true;
		}
		map<int, vector<int>>::iterator it = this->graph.edges.find(current_vertex);
		if (it != this->graph.edges.end())
		{
			for (int connected_vertex : it->second)
			{
				if (!visited[connected_vertex])
					stack.push(connected_vertex);
			}
		}
	}
}
