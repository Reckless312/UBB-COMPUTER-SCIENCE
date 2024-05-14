#include "Bellman-Ford.h"

Bellman_Ford_Algorithm::Bellman_Ford_Algorithm(DirectedGraph graph, int vertex, int vertex2)
{
	this->graph = graph;
	this->starting_vertex = vertex;
	this->destination_vertex = vertex2;
	int number_of_vertices = this->graph.GetNumberOfVertices();
	this->distance = new int*[number_of_vertices];
	for (int i = 0; i < number_of_vertices; i++)
	{
		distance[i] = new int[number_of_vertices];
	}
}


//vector<int> Bellman_Ford_Algorithm::Relax()
//{
//	vector<int> walk;
//	for (int i = 0; i < this->graph.GetNumberOfVertices(); i++)
//	{
//		for (int j = 0; j < this->graph.GetNumberOfVertices(); j++)
//		{
//			this->distance[i][j] = numeric_limits<int>::max();
//		}
//	}
//	this->distance[starting_vertex][0] = 0;
//	for (int i = 1; i < this->graph.GetNumberOfVertices(); i++)
//	{
//		for (int j = 0; j < this->graph.GetNumberOfVertices(); j++)
//		{
//			this->distance[j][i] = this->distance[j][i - 1]; // Initialize the distance for the current iteration
//		}
//		try
//		{
//			DirectedGraphIteratorEdges edge(this->graph.OutBoundEdges);
//			while (edge.Valid())
//			{
//				auto vertex_and_outbounds = edge.Next();
//				int first = get<0>(vertex_and_outbounds), second = get<1>(vertex_and_outbounds);
//				if (distance[first][i - 1] != numeric_limits<int>::max() && this->distance[first][i - 1] + this->graph.GetCost(first, second) < this->distance[second][i])
//				{
//					this->distance[second][i] = this->distance[first][i - 1] + this->graph.GetCost(first, second);
//				}
//			}
//		}
//		catch (const std::exception&)
//		{
//
//		}
//	}
//	//lost code, this part is backtracking to find the full path and reverse it
//}