#include "Graph.h"

DirectedGraph:: DirectedGraph()
{
	number_of_vertices = 0;
	number_of_edges = 0;
}

DirectedGraph::DirectedGraph(DirectedGraph& other)
{
	number_of_vertices = other.number_of_vertices;
	number_of_edges = other.number_of_edges;
	file = other.file;
	for (int vertex : other.vertices)
	{
		vertices.push_back(vertex);
	}
	for (auto& pair : other.OutBoundEdges)
	{
		for (int vertex : pair.second)
		{
			OutBoundEdges[pair.first].push_back(vertex);
		}
	}
	for (auto& pair : other.cost)
	{
		cost[pair.first] = pair.second;
	}
}

void DirectedGraph::InitializeOutBoundsEdges(int vertex)
{
	auto check_error = this->OutBoundEdges.find(vertex);
	if (check_error == this->OutBoundEdges.end())
	{
		this->OutBoundEdges[vertex] = vector <int>();
	}
}

void DirectedGraph::InitializeInBoundsEdges(int vertex)
{
	auto check_error = this->InBoundEdges.find(vertex);
	if (check_error == this->InBoundEdges.end())
	{
		this->InBoundEdges[vertex] = vector<int>();
	}
}

void DirectedGraph::AddVertex(int vertex)
{
	if (FindInVector(this->vertices, vertex) == false)
	{
		this->vertices.push_back(vertex);
		this->number_of_vertices += 1;
	}
	else
	{
		throw exception("Vertex already added!\n");
	}
}

void DirectedGraph::AddEdge(int start, int end)
{
	InitializeOutBoundsEdges(start);
	InitializeInBoundsEdges(end);
	if (FindInVector(this->OutBoundEdges[start], end) == false)
	{
		this->OutBoundEdges[start].push_back(end);
		this->number_of_edges += 1;
	}
	else
	{
		throw exception("OutPoint already added!\n");
	}
	try
	{
		AddVertex(start);
	}
	catch (exception)
	{
			
	}
	try
	{
		AddVertex(end);
	}
	catch (exception)
	{

	}
	this->InBoundEdges[end].push_back(start);
}

void DirectedGraph::DeleteVertex(int vertex)
{
	if (FindInVector(this->vertices, vertex) == false)
	{
		throw exception("Vertex not found!\n");
	}

	auto check_appearance = this->OutBoundEdges.find(vertex);
	if (check_appearance != this->OutBoundEdges.end()) {
		for (auto& map : this->OutBoundEdges) {
			auto& vector = map.second;
			if (FindInVector(vector, vertex)) {
				vector.erase(remove(vector.begin(), vector.end(), vertex), vector.end());
				this->number_of_edges -= 1;
			}
		}
		this->OutBoundEdges.erase(check_appearance);
	}

	auto inDegreeCheck = this->InBoundEdges.find(vertex);
	if (inDegreeCheck != this->InBoundEdges.end()) {
		for (auto& map : this->InBoundEdges) {
			auto& vector = map.second;
			if (FindInVector(vector, vertex)) {
				vector.erase(remove(vector.begin(), vector.end(), vertex), vector.end());
			}
		}
		this->InBoundEdges.erase(inDegreeCheck);
	}

	auto it = find(this->vertices.begin(), this->vertices.end(), vertex);
	if (it != this->vertices.end()) {
		this->vertices.erase(it);
		this->number_of_vertices -= 1;
	}
}

void DirectedGraph::DeleteEdge(int start, int end)
{
	auto check_appearance = this->OutBoundEdges.find(start);
	if (check_appearance == this->OutBoundEdges.end())
	{
		throw exception("Edge not found!\n");
	}
	if (FindInVector(this->OutBoundEdges[start], end) == false)
	{
		throw exception("Edge not found!\n");
	}
	auto checkInDegree = this->InBoundEdges.find(end);
	if (checkInDegree != this->InBoundEdges.end())
	{
		auto& vector = this->InBoundEdges[end];
		vector.erase(remove(vector.begin(), vector.end(), start), vector.end());
	}
	this->OutBoundEdges[start].erase(remove(this->OutBoundEdges[start].begin(), this->OutBoundEdges[start].end(), end), this->OutBoundEdges[start].end());
	if (this->OutBoundEdges[start].size() == 0)
	{
		this->OutBoundEdges.erase(start);
	}
	this->number_of_edges -= 1;
}

void DirectedGraph::PlaceCost(int start, int end, int cost)
{
	bool found = false;
	tuple<int, int> tup(start, end);
	for (auto& KeyValueInMap : this->cost)
	{
		if (KeyValueInMap.first == tup)
		{
			found = true;
		}
	}
	if (found == true)
	{
		throw exception("The edge already has a price!\n");
	}
	this->cost[tup] = cost;
}

void DirectedGraph::ReadFile(void)
{
	ifstream file(this->file);
	if (!file.is_open())
	{
		throw exception("No file found!\n");
	}
	int supposed_number_of_vertices, supposed_number_of_edges;
	file >> supposed_number_of_vertices >> supposed_number_of_edges;
	int starting_vertex, ending_vertex, edge_cost;
	while (file >> starting_vertex >> ending_vertex >> edge_cost)
	{
		AddEdge(starting_vertex, ending_vertex);
		PlaceCost(starting_vertex, ending_vertex, edge_cost);
	}
	file.close();
	if (supposed_number_of_edges != this->number_of_edges || supposed_number_of_vertices != this->number_of_vertices)
	{
		throw exception("Different sizes!\n");
	}
}

vector<tuple<int, int>> DirectedGraph::IterateEdgesHelper(void)
{
	DirectedGraphIteratorEdges iterator_edges(this->OutBoundEdges);
	vector<tuple<int, int>> EdgesIterate;
	while (iterator_edges.Valid())
	{
		try
		{
			tuple<int, int> edge = iterator_edges.Next();
			EdgesIterate.push_back(edge);
		}
		catch (out_of_range)
		{
			break;
		}

	}
	return EdgesIterate;
}

void DirectedGraph::SaveFile(string file_name)
{
	ofstream file(file_name);
	file << this->number_of_vertices << " " << this->number_of_edges << endl;
	for (auto edge : IterateEdgesHelper())
	{
		file << get<0>(edge) << " " << get<1>(edge) << " " << this->cost[edge] << endl;
	}
	file.close();
}

DirectedGraphIteratorVertices DirectedGraph::IterateVertices(void)
{
	return DirectedGraphIteratorVertices(this->vertices);
}

DirectedGraphIteratorBounds DirectedGraph::IterateOutbounds(int vertex)
{
	return DirectedGraphIteratorBounds(this->OutBoundEdges[vertex], vertex);
}

DirectedGraphIteratorBounds DirectedGraph::IterateInbounds(int vertex)
{
	return DirectedGraphIteratorBounds(this->InBoundEdges[vertex], vertex);
}

bool DirectedGraph::CheckEdge(int starting_vertex, int ending_vertex)
{
	auto it = this->OutBoundEdges.find(starting_vertex);
	if (it == this->OutBoundEdges.end())
	{
		return false;
	}
	for (int vertex : this->OutBoundEdges[starting_vertex])
	{
		if (vertex == ending_vertex)
		{
			return true;
		}
	}
	return false;
}
int DirectedGraph::DegreeIn(int vertex)
{
	if (this->InBoundEdges.find(vertex) != this->InBoundEdges.end())
	{
		return this->InBoundEdges[vertex].size();
	}
	return 0;
}
int DirectedGraph::DegreeOut(int vertex)
{
	if (this->OutBoundEdges.find(vertex) != this->OutBoundEdges.end())
	{
		return this->OutBoundEdges[vertex].size();
	}
	return 0;
}
vector<int> DirectedGraph::GetEndPoints(int vertex)
{
	auto it = this->OutBoundEdges.find(vertex);
	if (it == this->OutBoundEdges.end())
	{
		throw exception("No starting edge found!\n");
	}
	vector<int> endpoint;
	for (int vertex : this->OutBoundEdges[vertex])
	{
		endpoint.push_back(vertex);
	}
	return endpoint;
}
int DirectedGraph::GetCost(int start, int end)
{
	auto it = this->cost.find(make_pair(start, end));
	if (it == this->cost.end())
	{
		throw exception("No starting edge found!\n");
	}
	return this->cost[make_pair(start, end)];
}

void DirectedGraph::ChangeCost(int start, int end, int new_cost)
{
	auto it = this->cost.find(make_pair(start, end));
	if (it == this->cost.end())
	{
		throw exception("No starting edge found!\n");
	}
	this->cost[make_pair(start, end)] = new_cost;
}

int DirectedGraph::GetNumberOfVertices(void)
{
	return this->number_of_vertices;
}
int DirectedGraph::GetNumberOfEdges(void)
{
	return this->number_of_edges;
}

bool DirectedGraph::FindInVector(vector<int> vector, int ElementToCheck)
{
	for (int& ElementInVector : vector)
	{
		if (ElementInVector == ElementToCheck)
		{
			return true;
		}
	}
	return false;
}

void DirectedGraph::RandomGraph(int vertices, int edges)
{
	this->file = "random.txt";
	if (vertices * vertices < edges)
	{
		return;
	}
	mt19937 rng(random_device{}());
	uniform_int_distribution<int> dist(1, vertices);
	for (int i = 1; i <= vertices; i++)
	{
		this->AddVertex(i);
	}
	while (this->GetNumberOfEdges() < edges)
	{
		int random_number_1 = dist(rng);
		int random_number_2 = dist(rng);
		try
		{
			this->AddEdge(random_number_1, random_number_2);
		}
		catch (exception)
		{
			;
		}
	}
	for (auto edge : IterateEdgesHelper())
	{
		int random_number = dist(rng);
		PlaceCost(get<0>(edge), get<1>(edge), random_number);
	}
}

void DirectedGraph::SetFileName(string name)
{
	this->file = name;
}
