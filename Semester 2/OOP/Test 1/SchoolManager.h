#pragma once
#include "DynamicVectorFromTeams.h"

class Manager {
private:
	DynamicVector<School> Repository;
public:
	void generate_5_schools(void);
	DynamicVector<School> show_by_name(void);
	void remove_school(string name, address adr);
	void mark(date dat);
};