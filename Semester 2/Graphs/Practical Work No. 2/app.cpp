#include "P3.h"

#include "Tests.h"

void print_options();

int main(void)
{
	/*UnDirectedGraph graph;
	while (true)
	{
		cout << "Provide a file:\n";
		string file_name;
		cin >> file_name;
		graph.SetFileName(file_name);
		try
		{
			graph.ReadFile();
		}
		catch (const std::exception& e)
		{
			cout << e.what();
			return 1;
		}
		break;
	}
	cout << "\nGraph Initialized!\n";
	int command, first_vertex, second_vertex, vertex, new_cost, number_of_vertices, number_of_edges, exit = -1;
	UnDirectedGraph copy_graph, random_graph;
	string file_name;
	P3 p3(graph);
	while (true)
	{
		print_options();
		cin >> command;
		switch (command)
		{
		case 0:
			exit = 0;
			break;
		case 1:
			cout << "Number of vertices: " << graph.GetNumberOfVertices() << endl;
			break;
		case 2:
			try
			{
				VerticesIterator iterator = graph.IterateVertices();
				while (iterator.Valid())
				{
					cout << "Vertice: " << iterator.Next() << endl;
				}
			}
			catch (out_of_range)
			{

			}
			break;
		case 3:
			cin >> first_vertex >> second_vertex;
			if (graph.CheckEdge(first_vertex, second_vertex) == true)
			{
				cout << "Edge found!\n";
			}
			else
			{
				cout << "Edge not found!\n";
			}
			break;
		case 4:
			cin >> vertex;
			cout << "Degree: " << graph.GetDegree(vertex) << endl;
			break;
		case 5:
			try
			{
				cin >> vertex;
				VertexEdgeIterator iterator2 = graph.IterateEdgesOfAVertex(vertex);
				while (iterator2.Valid())
				{
					tuple<int, int> edge = iterator2.Next();
					cout << "Start: " << get<0>(edge) << " End: " << get<1>(edge) << endl;
				}
			}
			catch (out_of_range)
			{

			}
			break;
		case 6:
			try
			{
				cin >> first_vertex >> second_vertex;
				cout << "Cost of edge: " << graph.GetCost(first_vertex, second_vertex) << endl;
			}
			catch (const std::exception& e)
			{
				cout << e.what();
			}
			break;
		case 7:
			try
			{
				cin >> first_vertex >> second_vertex >> new_cost;
				graph.ChangeCost(first_vertex, second_vertex, new_cost);
				cout << "Cost modified!\n";
			}
			catch (const std::exception& e)
			{
				cout << e.what();
			}
			break;
		case 8:
			int vertex;
			cin >> vertex;
			try
			{
				graph.AddVertex(vertex);
			}
			catch (const std::exception& e)
			{
				cout << e.what();
			}
			break;
		case 9:
			cin >> first_vertex >> second_vertex;
			try
			{
				graph.AddEdge(first_vertex, second_vertex);
			}
			catch (const std::exception& e)
			{
				cout << e.what();
			}
			break;
		case 10:
			cin >> vertex;
			try
			{
				graph.DeleteVertex(vertex);
			}
			catch (const std::exception& e)
			{
				cout << e.what();
			}
			break;
		case 11:
			cin >> first_vertex >> second_vertex;
			try
			{
				graph.DeleteEdge(first_vertex, second_vertex);
			}
			catch (const std::exception& e)
			{
				cout << e.what();
			}
			break;
		case 12:
			while (true)
			{
				try
				{
					cout << "Please write the desired file: " << endl;
					cin >> file_name;
					copy_graph.SetFileName(file_name);
					copy_graph.ReadFile();
				}
				catch (const std::exception& e)
				{
					cout << e.what();
				}
				break;
			}
			graph = copy_graph;
			break;
		case 13:
			cin >> file_name;
			graph.SaveFile(file_name);
			break;
		case 14:
			cin >> number_of_vertices >> number_of_edges;
			try
			{
				random_graph.RandomGraph(number_of_vertices, number_of_edges);
			}
			catch (const std::exception& e)
			{
				cout << e.what();
			}
			graph = random_graph;
			break;
		case 15:
			p3.UpdateGraph(graph);
			p3.ConnectedComponents();
			break;
		default:
			break;
		}
		if (exit == 0)
		{
			break;
		}
	}*/
	Tests test;
	test.TestAll();
}

void print_options()
{
	cout << "Select command:\n";
	cout << "Get number of vertices / 1\n";
	cout << "Iterate the set of vertices / 2\n";
	cout << "Check edge between two vertices / 3\n";
	cout << "Get the degree of a vertex / 4 \n";
	cout << "Iterate edges of a vertex / 5\n";
	cout << "Get cost of an edge / 6\n";
	cout << "Modify cost of an edge / 7\n";
	cout << "Add a vertex / 8\n";
	cout << "Add an edge / 9 \n";
	cout << "Delete a vertex / 10\n";
	cout << "Delete an edge / 11\n";
	cout << "Read a file / 12\n";
	cout << "Write in a file / 13\n";
	cout << "Create a random graph / 14\n";
	cout << "Connected components / 15 \n";
	cout << "Exit / 0\n";
}