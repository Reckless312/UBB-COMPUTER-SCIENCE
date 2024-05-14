#include "P4.h"

vector<int> P4::PredecessorCount()
{
	vector<int> sorted;
	queue<int> q;
	map<int, int> count;
	for (int i = 0; i < this->graph.GetNumberOfVertices(); i++)
	{
		count[i] = this->graph.DegreeIn(i);
		if (count[i] == 0)
		{
			q.push(i);
		}
	}
	while (!q.empty())
	{
		int vertex = q.front();
		q.pop();
		sorted.push_back(vertex);
		DirectedGraphIteratorBounds bound = this->graph.IterateOutbounds(vertex);
		try
		{
			while (bound.Valid())
			{
				int connected_vertex = get<1>(bound.Next());
				count[connected_vertex] -= 1;
				if (count[connected_vertex] == 0)
				{
					q.push(connected_vertex);
				}
			}
		}
		catch (const std::exception&)
		{

		}
	}
	if (sorted.size() < this->graph.GetNumberOfVertices())
	{
		cout << "Not a DAG!\n";
		return vector<int>();
	}
	return sorted;
}

vector<int> P4::GetHighestCostPath(vector<int> sorted, int starting_vertex, int ending_vertex)
{
	vector<int> path;
	int V = this->graph.GetNumberOfVertices();
	int* dist = new int[V];
	int* pred = new int[V];
	for (int i = 0; i < V; i++)
	{
		dist[i] = numeric_limits<int>::min();
		pred[i] = -1;
	}
	dist[starting_vertex] = 0;
	for (int vertex : sorted)
	{
		try
		{
			DirectedGraphIteratorBounds bound = this->graph.IterateOutbounds(vertex);
			while (bound.Valid())
			{
				int connected_vertex = get<1>(bound.Next());
				if (dist[vertex] + this->graph.GetCost(vertex, connected_vertex) > dist[connected_vertex])
				{
					dist[connected_vertex] = dist[vertex] + this->graph.GetCost(vertex, connected_vertex);
					pred[connected_vertex] = vertex;
				}
			}
		}
		catch (const std::exception&)
		{

		}
	}
	int current_vertex = ending_vertex;
	path.push_back(ending_vertex);
	while (pred[current_vertex] != -1)
	{
		path.push_back(pred[current_vertex]);
		current_vertex = pred[current_vertex];
	}
	if (*(path.end() - 1) != starting_vertex)
	{
		cout << "Can't reach the vertex!\n";
		return vector<int>();
	}
	cout << "The highest cost is: " << dist[ending_vertex] << endl;
	reverse(path.begin(), path.end());
	return path;
}
