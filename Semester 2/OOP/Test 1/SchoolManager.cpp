#include "SchoolManager.h"

void Manager::generate_5_schools(void)
{
	string name = "Avram_Iancu", name1 = "George_Cosbuc", name2 = "Alexandru_Vaida_Voieod", name3 = "Romulus_Guga", name4 = "Colegiul_Transilvania";
	address addr, addr1, addr2, addr3, addr4;
	addr.longitude = 46.77, addr1.longitude = 46.77, addr2.longitude = 46.77, addr3.longitude = 46.53, addr4.longitude = 46.54;
	addr.latitude = 23.60, addr1.latitude = 23.58, addr2.latitude = 23.63, addr3.latitude = 24.57, addr4.latitude = 24.57;
	date dat, dat1, dat2, dat3, dat4;
	dat.year = "2023", dat1.year = "2023", dat2.year = "2023", dat3.year = "2023", dat4.year = "2023";
	dat.month = "04", dat1.month = "04", dat2.month = "05", dat3.month = "04", dat4.month = "03";
	dat.day = "15", dat1.day = "08", dat2.day = "23", dat3.day = "04", dat4.day = "03";
	bool visited = true, vis1 =false, vis2 = false, vis3 = false, vis4 = false;
	School schol1(name, addr, dat, visited);
	School schol2(name1, addr1, dat1, vis1);
	School schol3(name2, addr2, dat2, vis2);
	School schol4(name3, addr3, dat3, vis3);
	School schol5(name4, addr4, dat4, vis4);
	this->Repository.add(schol1);
	this->Repository.add(schol2);
	this->Repository.add(schol3);
	this->Repository.add(schol4);
	this->Repository.add(schol5);
}

DynamicVector<School> Manager::show_by_name(void)
{
	DynamicVector<School> copy = this->Repository;
	sort(&copy[0], &copy[copy.getSize()], SchoolNameComparison());
	return copy;
}

void Manager::remove_school(string name, address adr)
{
	/*
	* Initiate a school object and set it's attributes
	* Calls remove in repo
	*/
	School s;
	s.SetAddress(adr);
	s.SetName(name);
	this->Repository.remove(s);
}

void Manager::mark(date dat)
{
	/*DynamicVector<School> mark;
	DynamicVector<School> repo = this->Repository;
	for (int i = 0; i < this->Repository.getSize(); i++)
	{
		if (repo.elems[i].GetCurrentDate().year < dat.year)
		{
			if (repo.elems[i].GetCurrentDate().month < dat.month)
			{
				if (repo.elems[i].GetCurrentDate().day < dat.day)
				{
					repo.elems[i].SetVisited();
				}
			}
		}
		else
		{
			mark.add(repo.elems[i]);
		}
	}*/
}
