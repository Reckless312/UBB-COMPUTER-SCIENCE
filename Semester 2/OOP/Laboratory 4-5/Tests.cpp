#include "Tests.h"
#include <assert.h>

void Tests::TestAddCorrectElement(void)
{
	cout << "TestAddCorrectElement\n";
	this->admin.AddDog("Cane Corso", "Bella", 3, "www.site.com");
	tuple <Dog*, int> DogsAndLength = this->admin.GetCopyDogs();
	assert(get<1>(DogsAndLength) == 1);
	cout << "New dog added!\n\n";
	delete[] get<0>(DogsAndLength);
}

void Tests::TestAddCorrectResize(void)
{
	cout << "TestAddCorrectResize\n";
	this->admin.AddDog("Cane Corso", "Bella", 2, "www.site.com");
	tuple <Dog*, int> DogsAndLength = this->admin.GetCopyDogs();
	assert(get<1>(DogsAndLength) == 2);
	cout << "New dog added!\n\n";
	delete[] get<0>(DogsAndLength);
}

void Tests::TestAddAlreadyAdded(void)
{
	cout << "TestAddAlreadyAdded\n";
	try
	{
		this->admin.AddDog("Cane Corso", "Bella", 3, "www.site.com");
	}
	catch (const std::exception& e)
	{
		cout << e.what();
	}
	cout << "Exception caught!\n\n";
}

void Tests::TestAddWithIncorrectParameters(void)
{
	cout << "TestAddAlreadyAdded\n";
	try
	{
		this->admin.AddDog("Cane Corso2", "Bella", 3, "www.site.com");
	}
	catch (const std::exception& e)
	{
		cout << e.what();
	}
	try
	{
		this->admin.AddDog("Cane Corso", "Bell3", 3, "www.site.com");
	}
	catch (const std::exception& e)
	{
		cout << e.what();
	}
	try
	{
		this->admin.AddDog("Cane Corso", "Bella", -2, "www.site.com");
	}
	catch (const std::exception& e)
	{
		cout << e.what();
	}
	cout << "Exception caught!\n\n";
}

void Tests::TestDeleteElement(void)
{
	cout << "TestDeleteElement\n";
	this->admin.DeleteDog("Cane Corso", "Bella", 3, "www.site.com");
	tuple <Dog*, int> DogsAndLength = this->admin.GetCopyDogs();
	assert(get<1>(DogsAndLength) == 1);
	cout << "Dog removed!\n\n";
	delete[] get<0>(DogsAndLength);
}

void Tests::TestDeleteNotFoundElement(void)
{
	cout << "TestDeleteNotFoundElement\n";
	try
	{
		this->admin.DeleteDog("Cane Corso", "Bella", 3, "www.site.com");
	}
	catch (const std::exception& e)
	{
		cout << e.what();
	}
	cout << "Exception caught!\n\n";
}

void Tests::TestUpdateElement(void)
{
	cout << "TestUpdateElement\n";
	this->admin.UpdateDog("Cane Corso", "Bella", 2, "www.site.com", "Bella", 1, "www.site.com");
	cout << "Dog changed!\n\n";
}

void Tests::TestUpdateNotFoundElement(void)
{
	cout << "TestUpdateNotFoundElement\n";
	try
	{
		this->admin.UpdateDog("Cane Corso", "Bella", 2, "www.site.com", "Bella", 1, "www.site.com");
	}
	catch (const std::exception& e)
	{
		cout << e.what();
	}
	cout << "Exception caught!\n\n";
}

void Tests::TestGenerateElements(void)
{
	cout << "TestGenerateElements\n";
	this->admin.GenerateEntities();
	tuple <Dog*, int> DogsAndLength = this->admin.GetCopyDogs();
	assert(get<1>(DogsAndLength) == 10);
	cout << "10 dogs added!\n\n";
	delete[] get<0>(DogsAndLength);
}

void Tests::TestPrintElements(void)
{
	cout << "TestPrintElements\n";
	tuple <Dog*, int> DogsAndLength = this->admin.GetCopyDogs();
	for (int i = 0, length = get<1>(DogsAndLength); i < length; i++)
	{
		cout << get<0>(DogsAndLength)[i].__String__() << endl;
	}
	delete[] get<0>(DogsAndLength);
	cout << "Elements correctly printed!\n\n";
}

void Tests::TestNoElements(void)
{
	cout << "TestNoElements\n";
	this->admin.DeleteDog("Cane Corso", "Bella", 1, "www.site.com");
	try
	{
		tuple <Dog*, int> DogsAndLength = this->admin.GetCopyDogs();
	}
	catch (const std::exception& e)
	{
		cout << e.what();
	}
	cout << "Exception caught!\n\n";
}

void Tests::TestChangeBreed(void)
{
	cout << "TestChangeBreed\n";
	Dog dog("Cane Corso", "Bella", 3, "www.site.com");
	dog.SetBreed("German Shepherd");
	assert(dog.GetBreed() == "German Shepherd");
	cout << "SetBreed Function works\n\n";
}

void Tests::TestCheckComparisonOperator(void)
{
	cout << "TestCheckComparisonOperator\n";
	Dog dog_1("Cane Corso", "Bella", 3, "www.site.com");
	Dog dog_2("German Shepherd", "Bella", 3, "www.site.com");
	Dog dog_3("Cane Corso", "Rocky", 3, "www.site.com");
	Dog dog_4("Cane Corso", "Bella", 2, "www.site.com");
	Dog dog_5("Cane Corso", "Bella", 3, "www.site_2.com");
	Dog dog_6("Cane Corso", "Bella", 3, "www.site.com");
	bool compare_1 = dog_1 == dog_2;
	bool compare_2 = dog_1 == dog_3;
	bool compare_3 = dog_1 == dog_4;
	bool compare_4 = dog_1 == dog_5;
	bool compare_5 = dog_1 == dog_6;
	assert(compare_1 == false);
	assert(compare_2 == false);
	assert(compare_3 == false);
	assert(compare_4 == false);
	assert(compare_5 == true);
	cout << "Operator '==' works!\n\n";
}

void Tests::TestFilterEmptyAdoptionList(void)
{
	cout << "TestFilterEmptyAdoptionList!\n";
	try
	{
		tuple<Dog*, int> Empty;
		this->user_of_app.FilterNotAdopted(Empty);
	}
	catch (const std::exception&)
	{
		cout << "Exception caught!\n";
	}
	cout << "Function works corectly if no dog in the adoption list!\n\n";
}

void Tests::TestAdopt5Dogs(void)
{
	cout << "TestAdopt5Dogs\n";
	tuple <Dog*, int> DogsAndLength = this->admin.GetCopyDogs();
	for (int i = 0, length = 5; i < length; i++)
	{
		this->user_of_app.AddDog(get<0>(DogsAndLength)[i]);
	}
	cout << "Five dogs adopted!\n\n";
}

void Tests::TestFilterDogs(void)
{
	cout << "TestFilterDogs\n";
	cout << "Test without filter\n";
	tuple<Dog*, int> NoFilter = this->user_of_app.FilterDogs(this->admin.GetCopyDogs());
	assert(10 == get<1>(NoFilter));
	cout << "10 dogs found!\n";
	for (int i = 0; i < 10; i++)
	{
		cout << get<0>(NoFilter)[i].__String__() << endl;
	}
	delete[] get<0>(NoFilter);
	cout << "Test with filter\n";
	tuple<Dog*, int> WithFilter = this->user_of_app.FilterDogs(this->admin.GetCopyDogs(), "Cane Corso", 4);
	assert(1 == get<1>(WithFilter));
	cout << "1 dog found!\n";
	cout << get<0>(WithFilter)[0].__String__() << endl;
	cout << "Test no element found after filter\n";
	try
	{
		tuple<Dog*, int> WithFilter = this->user_of_app.FilterDogs(this->admin.GetCopyDogs(), "Cane Corso", 1);
	}
	catch (const std::exception&)
	{
		cout << "Exception caught!\n";
	}
	cout << "Test no element inside parameter\n";
	tuple<Dog*, int> Nothing;
	try
	{
		tuple<Dog*, int> WithFilter = this->user_of_app.FilterDogs(Nothing, "Cane Corso", 1);
	}
	catch (const std::exception&)
	{
		cout << "Exception caught!\n";
	}
	cout << "Filtering works!\n\n";
	delete[] get<0>(WithFilter);
}

void Tests::TestFilterAlreadyAdopted(void)
{
	cout << "TestFilterAlreadyAdopted\n";
	cout << "When the center is not empty...\n";
	tuple <Dog*, int> DogsAndLength = this->admin.GetCopyDogs();
	Dog* dog = new Dog[10];
	for (int i = 0, length = 10; i < length; i++)
	{
		dog[i] = get<0>(DogsAndLength)[i];
	}
	tuple <Dog*, int> FilterAdopted = this->user_of_app.FilterNotAdopted(make_pair(dog, 10));
	assert(get<1>(FilterAdopted) == 5);
	cout << "5 dogs filtered!\n";
	cout << "When the center is empty...\n"; 
	cout << "Adopting the rest of the dogs...\n";
	for (int i = 5, length = 10; i < length; i++)
	{
		this->user_of_app.AddDog(get<0>(DogsAndLength)[i]);
	}
	dog = new Dog[10];
	for (int i = 0, length = 10; i < length; i++)
	{
		dog[i] = get<0>(DogsAndLength)[i];
	}
	delete[] get<0>(FilterAdopted);
	try
	{
		tuple <Dog*, int> FilteredAdopted2 = this->user_of_app.FilterNotAdopted(make_pair(dog, 10));
	}
	catch (const std::exception&)
	{
		cout << "Exception caught!\n";
	}
	delete[] dog;
	cout << "FilterNotAdopted works!\n\n";
}

void Tests::TestAll(void)
{
	TestAddCorrectElement();
	TestAddCorrectResize();
	TestAddAlreadyAdded();
	TestAddWithIncorrectParameters();
	TestDeleteElement();
	TestDeleteNotFoundElement();
	TestUpdateElement();
	TestUpdateNotFoundElement();
	TestNoElements();
	TestGenerateElements();
	TestPrintElements();
	TestChangeBreed();
	TestCheckComparisonOperator();
	TestFilterEmptyAdoptionList();
	TestAdopt5Dogs();
	TestFilterDogs();
	TestFilterAlreadyAdopted();
	cout << "Test Over!\n";
}


