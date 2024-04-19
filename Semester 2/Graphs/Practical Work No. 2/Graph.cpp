#include "Graph.h"

void UnDirectedGraph::InitializeEdges(int vertex)
{
	map<const int, vector<int>>::iterator it = this->edges.find(vertex);
	if (it == this->edges.end())
	{
		this->edges[vertex] = vector<int>();
	}
}

bool UnDirectedGraph::FindVertex(vector<int> vector, int vertex)
{
	for (int& current_vertex : vector)
	{
		if (current_vertex == vertex)
		{
			return true;
		}
	}
	return false;
}

vector<tuple<int, int>> UnDirectedGraph::IterateEdgesHelper()
{
	EdgesIterator it_edges(this->edges);
	vector<tuple<int, int>> edges_copy;
	while (it_edges.Valid())
	{
		try 
		{
			tuple<int, int> edge = it_edges.Next();
			edges_copy.push_back(edge);
		}
		catch (out_of_range)
		{
			break;
		}
	}
	vector<tuple<int, int>> unique_edges;
	for (tuple<int, int> edge : edges_copy) 
	{
		int first_vertex = get<0>(edge);
		int second_vertex = get<1>(edge);
		if (first_vertex > second_vertex)
			swap(first_vertex, second_vertex);
		tuple<int, int> possible_edge = make_pair(first_vertex, second_vertex);
		bool unique = true;
		for (tuple<int, int>unique_edge : unique_edges)
		{
			if (unique_edge == possible_edge)
			{
				unique = false;
			}
		}
		if (unique == true) 
		{
			unique_edges.push_back(edge);
		}
	}
	return unique_edges;
}

UnDirectedGraph::UnDirectedGraph()
{
	this->number_of_vertices = 0;
	this->number_of_edges = 0;
}

UnDirectedGraph::UnDirectedGraph(UnDirectedGraph& other)
{
	this->number_of_vertices = other.number_of_vertices;
	this->number_of_edges = other.number_of_edges;
	for (int vertex : other.vertices)
	{
		this->vertices.push_back(vertex);
	}
	for (pair<const int, vector<int>>& pair : other.edges)
	{
		for (int vertex : pair.second)
		{
			this->edges[pair.first].push_back(vertex);
		}
	}
	for (pair<const tuple<int, int>, int>& pair : other.costs)
	{
		this->costs[pair.first] = pair.second;
	}
}

void UnDirectedGraph::AddVertex(int vertex)
{
	if (this->FindVertex(this->vertices, vertex) == true)
	{
		throw exception("Vertex has been found in the graph!\n");
	}
	else
	{
		this->vertices.push_back(vertex);
		this->number_of_vertices++;
	}
}

void UnDirectedGraph::AddEdge(int first_vertex, int second_vertex)
{
	this->InitializeEdges(first_vertex);
	this->InitializeEdges(second_vertex);
	if (this->FindVertex(this->edges[first_vertex], second_vertex) == true)
	{
		throw exception("Edge exists in the graph!\n");
	}
	try
	{
		this->AddVertex(first_vertex);
	}
	catch (const std::exception&)
	{

	}
	try
	{
		this->AddVertex(second_vertex);
	}
	catch (const std::exception&)
	{

	}
	this->edges[first_vertex].push_back(second_vertex);
	this->edges[second_vertex].push_back(first_vertex);
	this->number_of_edges++;
}

void UnDirectedGraph::DeleteVertex(int vertex)
{
	if (this->FindVertex(this->vertices, vertex) == false)
	{
		throw exception("Vertex not found!\n");
	}
	map<const int, vector<int>>::iterator it = this->edges.find(vertex);
	if (it != this->edges.end())
	{
		vector<int> vec = it->second;
		this->number_of_edges -= vec.size();
		this->edges.erase(it);
	}
	for (pair<const int, vector<int>>& pair : this->edges)
	{
		vector<int>::iterator it_vec = find(pair.second.begin(), pair.second.end(), vertex);
		if (it_vec != pair.second.end())
		{
			pair.second.erase(it_vec);
		}
	}
	vector<int>::iterator it_vec_graph = find(this->vertices.begin(), this->vertices.end(), vertex);
	if (it_vec_graph != this->vertices.end())
	{
		this->vertices.erase(it_vec_graph);
		this->number_of_vertices--;
	}
}

void UnDirectedGraph::DeleteEdge(int first_vertex, int second_vertex)
{
	map<const int, vector<int>>::iterator it_edges = this->edges.find(first_vertex);
	if (it_edges == this->edges.end())
	{
		throw exception("Edge not found!\n");
	}
	if (this->FindVertex(this->edges[first_vertex], second_vertex) == false)
	{
		throw exception("Edge not found!\n");
	}
	this->edges[first_vertex].erase(find(this->edges[first_vertex].begin(), this->edges[first_vertex].end(), second_vertex));
	this->edges[second_vertex].erase(find(this->edges[second_vertex].begin(), this->edges[second_vertex].end(), first_vertex));
	if (this->edges[first_vertex].size() == 0)
	{
		this->edges.erase(first_vertex);
	}
	if (this->edges[second_vertex].size() == 0)
	{
		this->edges.erase(second_vertex);
	}
	this->number_of_edges--;
}

bool UnDirectedGraph::CheckEdge(int first_vertex, int second_vertex)
{
	map<int, vector<int>>::iterator it = this->edges.find(first_vertex);
	if (it == this->edges.end())
	{
		return false;
	}
	for (int vertex : this->edges[first_vertex])
	{
		if (vertex == second_vertex)
		{
			return true;
		}
	}
	return false;
}

void UnDirectedGraph::PlaceCost(int first_vertex, int second_vertex, int cost)
{
	tuple<int, int> edge(first_vertex, second_vertex);
	if (this->costs.find(edge) != this->costs.end())
	{
		throw exception("Edge already has a cost!\n");
	}
	this->costs[edge] = cost;
}

int UnDirectedGraph::GetNumberOfVertices()
{
	return this->number_of_vertices;
}

int UnDirectedGraph::GetNumberOfEdges()
{
	return this->number_of_edges;
}

int UnDirectedGraph::GetDegree(int vertex)
{
	if (this->edges.find(vertex) != this->edges.end())
	{
		return this->edges[vertex].size();
	}
	return 0;
}

vector<int> UnDirectedGraph::GetConnectedPointOfVertex(int vertex)
{
	if (this->edges.find(vertex) == this->edges.end())
	{
		throw exception("No edges found!\n");
	}
	vector<int> points;
	for (int vertex : this->edges[vertex])
	{
		points.push_back(vertex);
	}
	return points;
}

int UnDirectedGraph::GetCost(int first_vertex, int second_vertex)
{
	if (this->CheckEdge(first_vertex, second_vertex) == false)
	{
		throw exception("No edge found!\n");
	}
	return this->costs[make_pair(first_vertex, second_vertex)];
}

void UnDirectedGraph::ChangeCost(int first_vertex, int second_vertex, int new_cost)
{
	if (this->CheckEdge(first_vertex, second_vertex) == false)
	{
		throw exception("No edge found!\n");
	}
	this->costs[make_pair(first_vertex, second_vertex)] = new_cost;
}

void UnDirectedGraph::RandomGraph(int number_of_vertices, int number_of_edges)
{
	this->SetFileName("random.txt");
	if (number_of_vertices * number_of_vertices < number_of_edges)
	{
		return;
	}
	mt19937 rng(random_device{}());
	uniform_int_distribution<int> dist(0, number_of_vertices - 1);
	for (int i = 0; i < number_of_vertices; i++)
	{
		this->AddVertex(i);
	}
	while (this->GetNumberOfEdges() < number_of_edges)
	{
		int random_number_1 = dist(rng);
		int random_number_2 = dist(rng);
		try
		{
			this->AddEdge(random_number_1, random_number_2);
		}
		catch (exception)
		{
			
		}
	}
	for (tuple<int, int> edge : this->IterateEdgesHelper())
	{
		int random_number = dist(rng);
		PlaceCost(get<0>(edge), get<1>(edge), random_number);
	}

}

void UnDirectedGraph::AddFromFileVertex(int vertex)
{
	this->vertices.push_back(vertex);
}

void UnDirectedGraph::AddFromFileEdge(int first_vertex, int second_vertex)
{
	this->InitializeEdges(first_vertex);
	this->InitializeEdges(second_vertex);
	this->edges[first_vertex].push_back(second_vertex);
	this->edges[second_vertex].push_back(first_vertex);
}

void UnDirectedGraph::PlaceFromFileCost(int first_vertex, int second_vertex, int cost)
{
	tuple<int, int> Key(first_vertex, second_vertex);
	this->costs[Key] = cost;
}

void UnDirectedGraph::ReadFile()
{
	ifstream file(this->file_name);
	if (!file.is_open())
	{
		throw exception("No file found!\n");
	}
	file >> this->number_of_vertices >> this->number_of_edges;
	for (int i = 0; i < this->number_of_vertices; i++)
	{
		this->AddFromFileVertex(i);
	}
	int first_vertex, second_vertex, cost;
	while (file >> first_vertex >> second_vertex >> cost)
	{
		this->AddFromFileEdge(first_vertex, second_vertex);
		this->PlaceFromFileCost(first_vertex, second_vertex, cost);
	}
	file.close();
}

void UnDirectedGraph::SaveFile(string file_name)
{
	ofstream file(file_name);
	file << this->number_of_vertices << " " << this->number_of_edges << endl;
	for (tuple<int, int> pair : IterateEdgesHelper())
	{
		file << get<0>(pair) << " " << get<1>(pair) << endl;
	}
	file.close();
}

VerticesIterator UnDirectedGraph::IterateVertices()
{
	return VerticesIterator(this->vertices);
}

VertexEdgeIterator UnDirectedGraph::IterateEdgesOfAVertex(int vertex)
{
	return VertexEdgeIterator(this->edges[vertex], vertex);
}

void UnDirectedGraph::SetFileName(string name)
{
	this->file_name = name;
}
