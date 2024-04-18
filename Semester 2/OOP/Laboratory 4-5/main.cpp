#define _CRTDBG_MAP_ALLOC
#include "UI.h"
#include "Tests.h"

int main(void)
{
	/*{
		UI ui;
		ui.Start();
	}
	_CrtDumpMemoryLeaks();*/
	Tests test;
	test.TestAll();
}