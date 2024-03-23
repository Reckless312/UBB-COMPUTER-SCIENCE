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
	for (string vertex : other.vertices)
	{
		vertices.push_back(vertex);
	}
	for (auto& pair : other.edges)
	{
		for (string vertex : pair.second)
		{
			edges[pair.first].push_back(vertex);
		}
	}
	for (auto& pair : other.cost)
	{
		cost[pair.first] = pair.second;
	}
}

void DirectedGraph::InitializeEdge(string vertex)
{
	auto check_error = this->edges.find(vertex);
	if (check_error == this->edges.end())
	{
		this->edges[vertex] = vector <string>();
	}
}

void DirectedGraph::InitializeInDegree(string vertex)
{
	auto check_error = this->InDegree.find(vertex);
	if (check_error == this->InDegree.end())
	{
		this->InDegree[vertex] = vector<string>();
	}
}

void DirectedGraph::AddVertex(string vertex)
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

void DirectedGraph::AddEdge(string start, string end)
{
	InitializeEdge(start);
	InitializeInDegree(end);
	if (FindInVector(this->edges[start], end) == false)
	{
		this->edges[start].push_back(end);
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
	this->InDegree[end].push_back(start);
}

void DirectedGraph::DeleteVertex(string vertex)
{
	if (FindInVector(this->vertices, vertex) == false)
	{
		throw exception("Vertex not found!\n");
	}

	auto check_appearance = this->edges.find(vertex);
	if (check_appearance != this->edges.end()) {
		for (auto& map : this->edges) {
			auto& vector = map.second;
			if (FindInVector(vector, vertex)) {
				vector.erase(remove(vector.begin(), vector.end(), vertex), vector.end());
				this->number_of_edges -= 1;
			}
		}
		this->edges.erase(check_appearance);
	}

	auto inDegreeCheck = this->InDegree.find(vertex);
	if (inDegreeCheck != this->InDegree.end()) {
		for (auto& map : this->InDegree) {
			auto& vector = map.second;
			if (FindInVector(vector, vertex)) {
				vector.erase(remove(vector.begin(), vector.end(), vertex), vector.end());
			}
		}
		this->InDegree.erase(inDegreeCheck);
	}

	auto it = find(this->vertices.begin(), this->vertices.end(), vertex);
	if (it != this->vertices.end()) {
		this->vertices.erase(it);
		this->number_of_vertices -= 1;
	}
}

void DirectedGraph::DeleteEdge(string start, string end)
{
	auto check_appearance = this->edges.find(start);
	if (check_appearance == this->edges.end())
	{
		throw exception("Edge not found!\n");
	}
	if (FindInVector(this->edges[start], end) == false)
	{
		throw exception("Edge not found!\n");
	}
	auto checkInDegree = this->InDegree.find(end);
	if (checkInDegree != this->InDegree.end())
	{
		auto& vector = this->InDegree[end];
		vector.erase(remove(vector.begin(), vector.end(), start), vector.end());
	}
	this->edges[start].erase(remove(this->edges[start].begin(), this->edges[start].end(), end), this->edges[start].end());
	if (this->edges[start].size() == 0)
	{
		this->edges.erase(start);
	}
	this->number_of_edges -= 1;
}

void DirectedGraph::PlaceCost(string start, string end, int cost)
{
	bool found = false;
	tuple<string, string> tup(start, end);
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
	string line;
	getline(file, line);
	stringstream first_line(line);
	string first_word, second_word;
	int supposed_number_of_vertices, supposed_number_of_edges;
	first_line >> first_word;
	first_line >> second_word;
	supposed_number_of_vertices = stoi(first_word);
	supposed_number_of_edges = stoi(second_word);
	while (getline(file, line))
	{
		stringstream current_line(line);
		string starting_vertex, ending_vertex, edge_cost;
		current_line >> starting_vertex;
		current_line >> ending_vertex;
		current_line >> edge_cost;
		AddEdge(starting_vertex, ending_vertex);
		PlaceCost(starting_vertex, ending_vertex, stoi(edge_cost));
	}
	file.close();
	if (supposed_number_of_edges != this->number_of_edges || supposed_number_of_vertices != this->number_of_vertices)
	{
		throw exception("Different sizes!\n");
	}
}

vector<tuple<string, string>> DirectedGraph::IterateEdgesHelper(void)
{
	DirectedGraphIteratorEdges iterator_edges(this->edges);
	vector<tuple<string, string>> EdgesIterate;
	while (iterator_edges.Valid())
	{
		try
		{
			tuple<string, string> edge = iterator_edges.Next();
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

DirectedGraphIteratorBounds DirectedGraph::IterateOutbounds(string vertex)
{
	return DirectedGraphIteratorBounds(this->edges[vertex], vertex);
}

DirectedGraphIteratorBounds DirectedGraph::IterateInbounds(string vertex)
{
	return DirectedGraphIteratorBounds(this->InDegree[vertex], vertex);
}

bool DirectedGraph::CheckEdge(string starting_vertex, string ending_vertex)
{
	auto it = this->edges.find(starting_vertex);
	if (it == this->edges.end())
	{
		return false;
	}
	for (string vertex : this->edges[starting_vertex])
	{
		if (vertex == ending_vertex)
		{
			return true;
		}
	}
	return false;
}
int DirectedGraph::DegreeIn(string vertex)
{
	if (this->InDegree.find(vertex) != this->InDegree.end())
	{
		return this->InDegree[vertex].size();
	}
	return 0;
}
int DirectedGraph::DegreeOut(string vertex)
{
	if (this->edges.find(vertex) != this->edges.end())
	{
		return this->edges[vertex].size();
	}
	return 0;
}
vector<string> DirectedGraph::GetEndPoints(string vertex)
{
	auto it = this->edges.find(vertex);
	if (it == this->edges.end())
	{
		throw exception("No starting edge found!\n");
	}
	vector<string> endpoint;
	for (string vertex : this->edges[vertex])
	{
		endpoint.push_back(vertex);
	}
	return endpoint;
}
int DirectedGraph::GetCost(string start, string end)
{
	auto it = this->cost.find(make_pair(start, end));
	if (it == this->cost.end())
	{
		throw exception("No starting edge found!\n");
	}
	return this->cost[make_pair(start, end)];
}

void DirectedGraph::ChangeCost(string start, string end, int new_cost)
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

bool DirectedGraph::FindInVector(vector<string> vector, string ElementToCheck)
{
	for (string& ElementInVector : vector)
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
		string number = to_string(i);
		this->AddVertex(number);
	}
	while (this->GetNumberOfEdges() < edges)
	{
		int random_number_1 = dist(rng);
		int random_number_2 = dist(rng);
		try
		{
			this->AddEdge(to_string(random_number_1), to_string(random_number_2));
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
