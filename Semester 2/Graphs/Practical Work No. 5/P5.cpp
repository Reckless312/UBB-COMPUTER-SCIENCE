#include "P5.h"


P5::P5(UnDirectedGraph& graph)
{
	this->graph = graph;
	for (auto vertex : this->graph.vertices)
	{
		this->Vertices.insert(vertex);
	}
	bronKerbosch();
}

void P5::bronKerbosch()
{
	struct stack_frame
	{
		set<int> CurrentClique, PossibleVertices, AlreadyCheckedVertices;
		map<int, vector<int>>::iterator it;
	};
	stack<stack_frame> stack;
	stack.push({ {}, this->Vertices, {}, this->graph.edges.begin()});
	while (!stack.empty())
	{
		stack_frame& top_of_stack = stack.top();
		if (top_of_stack.PossibleVertices.empty() && top_of_stack.AlreadyCheckedVertices.empty())
		{
			this->allCliques.push_back(top_of_stack.CurrentClique);
			stack.pop();
		}
		else if (top_of_stack.it == this->graph.edges.end())
		{
			stack.pop();
		}
		else
		{
			int vertex = top_of_stack.it->first;
			if (top_of_stack.PossibleVertices.find(vertex) != top_of_stack.PossibleVertices.end())
			{
				stack_frame newCall;
				newCall.CurrentClique = top_of_stack.CurrentClique;
				newCall.CurrentClique.insert(vertex);
				for (int outbound : top_of_stack.it->second)
				{
					if (top_of_stack.PossibleVertices.find(outbound) != top_of_stack.PossibleVertices.end())
					{
						newCall.PossibleVertices.insert(outbound);
					}
					if (top_of_stack.AlreadyCheckedVertices.find(outbound) != top_of_stack.AlreadyCheckedVertices.end())
					{
						newCall.AlreadyCheckedVertices.insert(outbound);
					}
				}
				newCall.it = next(top_of_stack.it);
				stack.push(newCall);
				top_of_stack.PossibleVertices.erase(vertex);
			}
			top_of_stack.AlreadyCheckedVertices.insert(vertex);
			top_of_stack.it++;
		}
	}
}

set<int> P5::MaxClique()
{
	int max_ = 0;
	set<int> maxCliq;
	for (const auto& clique : this->allCliques)
	{
		int size = clique.size();
		if (size > max_)
		{
			max_ = size;
			maxCliq = clique;
		}
	}
	return maxCliq;
}
