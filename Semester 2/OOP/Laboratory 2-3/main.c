#define _CRTDBG_MAP_ALLOC
#include "UI.h"
#include <crtdbg.h>
#include <stdlib.h>
#include "Tests.h"

int main(void)
{
	int program_on = 1;
	if (program_on == 1)
	{
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
		UI ui;
		Repository* repo;
		Service serv;
		History* history;
		repo = createRepository(1);
		history = createHistory();
		Medicine* redo_meds = get_Meds(history->redo);
		Medicine* undo_meds = get_Meds(history->undo);
		serv = createService(repo, history);
		ui = createUI(serv);
		generate_10_medicines(repo);
		start_ui(ui);
		destroyRepository(repo);
		destroyHistory(history);
		free(redo_meds);
		free(undo_meds);
		_CrtDumpMemoryLeaks();
	}
	else
	{
		tests();
	}
}