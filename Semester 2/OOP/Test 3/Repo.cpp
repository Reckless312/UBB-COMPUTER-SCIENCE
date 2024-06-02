#include "Repo.h"

void Repo::Read()
{
	ifstream f("doc.txt");
	if (f.is_open() == false)
	{
		return;
	}
	string line;
	while (getline(f, line))
	{
		if (line.empty())
		{
			continue;
		}
		istringstream ss(line);
		string a, b, c;
		getline(ss, a, '|');
		getline(ss, b, '|');
		getline(ss, c);
		Document doc(a, b, c);
		this->storage.push_back(doc);
	}
	f.close();
}
