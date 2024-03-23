#include "Graph.h"

int main(void)
{
	DirectedGraph graph;
	while (true)
	{
		try
		{
			cout << "Please write the desired file: "<<endl;
			string file_name;
			cin >> file_name;
			graph.SetFileName(file_name);
			graph.ReadFile();
		}
		catch (const std::exception& e)
		{
			cout<<e.what();
		}
		break;
	}
	cout << "Graph Initialized!\n" << "Welcome to the application!\n";
	while (true)
	{
		cout << "Select command:\n";
		cout<< "Get number of vertices / 1\n";
		cout << "Iterate the set of vertices / 2\n";
		cout << "Check edge between two vertices / 3\n";
		cout << "Get the indegree of a vertex / 4 \n";
		cout << "Get the outdegree of a vertex / 5 \n";
		cout << "Iterate outbound edges / 6\n";
		cout << "Iterate inbound edges / 7\n";
		cout << "Get cost of an edge / 8\n";
		cout << "Modify cost of an edge / 9\n";
		cout << "Add a vertex / 10\n";
		cout << "Add an edge / 11 \n";
		cout << "Delete a vertex / 12\n";
		cout << "Delete an edge / 13\n";
		cout << "Read a file / 14\n";
		cout << "Write in a file / 15\n";
		cout << "Create a random graph / 16\n";
		cout << "Exit / 0\n";
		string command;
		cin >> command;
		if (command == "1")
		{
			cout << "Number of vertices: " << graph.GetNumberOfVertices() << endl;
		}
		else if (command == "2")
		{
			try
			{
				DirectedGraphIteratorVertices iterator = graph.IterateVertices();
				while (iterator.Valid())
				{
					cout << "Vertice: " << iterator.Next() << endl;
				}
			}
			catch (out_of_range)
			{

			}
		}
		else if (command == "3")
		{
			string start, end;
			cin >> start >> end;
			if (graph.CheckEdge(start, end) == true)
			{
				cout << "Edge found!\n";
			}
			else
			{
				cout << "Edge not found!\n";
			}
		}
		else if (command == "4")
		{
			string vertex;
			cin >> vertex;
			cout << "Indegree: " << graph.DegreeIn(vertex) << endl;
		}
		else if (command == "5")
		{
			string vertex;
			cin >> vertex;
			cout << "Outdegree: " << graph.DegreeOut(vertex) << endl;
		}
		else if (command == "6")
		{
			try
			{
				string vertex;
				cin >> vertex;
				DirectedGraphIteratorBounds iterator = graph.IterateOutbounds(vertex);
				while (iterator.Valid())
				{
					auto edge = iterator.Next();
					cout << "Start: " << get<0>(edge) << " End: " << get<1>(edge) << endl;
				}
			}
			catch (out_of_range)
			{

			}
		}
		else if (command == "7")
		{
			try
			{
				string vertex;
				cin >> vertex;
				DirectedGraphIteratorBounds iterator = graph.IterateInbounds(vertex);
				while (iterator.Valid())
				{
					auto edge = iterator.Next();
					cout << "To: " << get<0>(edge) << " From: " << get<1>(edge) << endl;
				}
			}
			catch (out_of_range)
			{

			}
		}
		else if (command == "8")
		{
			try
			{
				string start, end;
				cin >> start >> end;
				cout << "Cost of edge: " << graph.GetCost(start, end) << endl;
			}
			catch (const std::exception& e)
			{
				cout << e.what();
			}
		}
		else if (command == "9")
		{
			try
			{
				string start, end;
				int cost;
				cin >> start >> end >> cost;
				graph.PlaceCost(start, end, cost);
				cout << "Cost modified!\n";
			}
			catch (const std::exception& e)
			{
				cout << e.what();
			}
		}
		else if (command == "10")
		{
			string vertex;
			cin >> vertex;
			try
			{
				graph.AddVertex(vertex);
			}
			catch (const std::exception& e)
			{
				cout << e.what();
			}
		}
		else if (command == "11")
		{
			string start, end;
			cin >> start >> end;
			try
			{
				graph.AddEdge(start, end);
			}
			catch (const std::exception& e)
			{
				cout << e.what();
			}
		}
		else if (command == "12")
		{
			string vertex;
			cin >> vertex;
			try
			{
				graph.DeleteVertex(vertex);
			}
			catch (const std::exception& e)
			{
				cout << e.what();
			}
		}
		else if (command == "13")
		{
			string start, end;
			cin >> start >> end;
			try
			{
				graph.DeleteEdge(start, end);
			}
			catch (const std::exception& e)
			{
				cout << e.what();
			}
		}
		else if (command == "14")
		{
			DirectedGraph copy_graph;
			while (true)
			{
				try
				{
					cout << "Please write the desired file: " << endl;
					string file_name;
					cin >> file_name;
					copy_graph.SetFileName(file_name);
					copy_graph.ReadFile();
				}
				catch (const std::exception& e)
				{
					cout<<e.what();
				}
				break;
			}
			graph = copy_graph;
		}
		else if (command == "15")
		{
			string file_name;
			cin >> file_name;
			graph.SaveFile(file_name);
		}
		else if (command == "16")
		{
			int vertices, edges;
			cin >> vertices >> edges;
			DirectedGraph random_graph;
			random_graph.RandomGraph(vertices, edges);
			graph = random_graph;
		}
		else if (command == "0")
		{
			break;
		}
		else
		{
			cout << "Invalid command!\n";
		}
		cout << endl;
	}
}