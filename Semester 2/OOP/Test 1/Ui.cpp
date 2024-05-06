#include "Ui.h"

void UI::start(void)
{
	this->man.generate_5_schools();
	while (true)
	{
		cout << "Show all schools by name /1 \n";
		cout << "Remove a school /2\n";
		cout << "Exit / 0\n";
		string command;
		cin >> command;
		if (command == "1")
		{
			DynamicVector<School> copy = this->man.show_by_name();
			for (int i = 0; i < copy.getSize(); i++)
			{
				cout << copy[i].__str__() << endl;
			}
		}
		else if (command == "2")
		{
			string name;
			address adr;
			cin >> name >> adr.longitude >> adr.latitude;
			try
			{
				this->man.remove_school(name, adr);
				cout << "Removed\n";
			}
			catch (const std::exception& e)
			{
				cout << e.what();
			}
		}
		else if (command == "0")
		{
			break;
		}
	}
}
