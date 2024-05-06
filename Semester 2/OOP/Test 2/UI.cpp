#include "UI.h"

void UI::Start()
{
	string bd1="Sedan", bd2="Sedan", bd3="Convertible";
	string en1="Electric", en2="Electric", en3="Turbo";
	int aut1=10, aut2=4;
	this->serv.addCar(bd1, en1, aut1);
	this->serv.addCar(bd2, en2, aut2);
	this->serv.addCar(bd3, en3);
	cout << "Welcome to the application!\n";
	while (true)
	{
		cout << "Select command:\n";
		cout << "1.Add a new car\n";
		cout << "2.See cars\n";
		cout << "3.Save to a file\n";
		cout << "0.Exit\n";
		string command;
		cin >> command;
		if (command == "1")
		{
			cout << "Select body style -> Sedan / Convertible\n";
			string choice;
			cin >> choice;
			cout << "Select engine type -> Electric / Turbo\n";
			string choice2;
			cin >> choice2;
			if (choice == "Sedan")
			{
				if (choice2 == "Electric")
				{
					cout << "Select autonomy\n";
					int aut;
					cin >> aut;
					this->serv.addCar(choice, choice2, aut);
					double price = 8000 + 3000 + aut * 0.01;
					cout << "The price is " << price << endl;
				}
				else if (choice2 == "Turbo")
				{
					this->serv.addCar(choice, choice2);
					double price = 8000 + 3000 + 100;
					cout << "The price is " << price << endl;
				}
				else
				{
					cout << "Invalid\n";
				}
			}
			else if (choice == "Convertible")
			{
				if (choice2 == "Electric")
				{
					cout << "Select autonomy\n";
					int aut;
					cin >> aut;
					this->serv.addCar(choice, choice2, aut);
					double p = aut * 0.01;
					double price = 9000 + 3000 + p;
					cout << "The price is " << price << endl;
				}
				else if (choice2 == "Turbo")
				{
					this->serv.addCar(choice, choice2);
					double price = 9000 + 3000 + 100;
					cout << "The price is " << price << endl;
				}
				else
				{
					cout << "Invalid\n";
				}
			}
			else
			{
				cout << "Invalid!\n";
			}
		}
		else if (command == "2")
		{
			vector<Car> cars = this->serv.ShowCars();
			for (Car car : cars)
			{
				Engine* eng = car.GetEngine();
				cout << "Body Style: " << car.Getstyle()<< " and a total price: " << car.computePrice() << endl;
				cout << eng->toString() << endl << endl;
			}
		}
		else if (command == "3")
		{
			cout << "Insert maximum price\n";
			int max_price;
			cin >> max_price;
			vector<Car> cars = this->serv.getCarsWithMaxPrice(max_price);
			cout << "Select file name\n";
			string file_name;
			cin >> file_name;
			this->serv.writeToFile(file_name, cars);
		}
		else if(command =="0")
		{
			break;
		}
		else
		{
			cout << "Invalid command!\n";
		}
	}
}
