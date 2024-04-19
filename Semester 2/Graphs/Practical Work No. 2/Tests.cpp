#include "Tests.h"

void Tests::First_Test()
{
	UnDirectedGraph graph;
	P3 p3(graph);
	for (int i = 0; i < 9; i++)
	{
		graph.AddVertex(i);
	}
	graph.AddEdge(0, 1);
	graph.AddEdge(1, 2);
	graph.AddEdge(4, 5);
	graph.AddEdge(5, 6);
	p3.UpdateGraph(graph);
	p3.ConnectedComponents();
	cout << "\n";
}

void Tests::Second_Test()
{
	UnDirectedGraph graph;
	P3 p3(graph);
	for (int i = 0; i < 50; i++)
	{
		graph.AddVertex(i);
	}
	graph.AddEdge(0, 1);
	graph.AddEdge(1, 2);
	graph.AddEdge(4, 5);
	graph.AddEdge(9, 10);
	graph.AddEdge(13, 15);
	graph.AddEdge(5, 6);
	graph.AddEdge(46, 47);
	graph.AddEdge(25, 32);
	graph.AddEdge(1, 34);
	graph.AddEdge(10, 12);
	graph.AddEdge(13, 14);
	graph.AddEdge(17, 19);
	graph.AddEdge(19, 20);
	graph.AddEdge(21, 22);
	graph.AddEdge(26, 28);
	p3.UpdateGraph(graph);
	p3.ConnectedComponents();
	cout << endl;
}

void Tests::TestAll()
{
	First_Test();
	Second_Test();
}
