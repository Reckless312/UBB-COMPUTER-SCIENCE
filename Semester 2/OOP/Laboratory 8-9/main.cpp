#include "GUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    TextFileRepository* repo_1 = new TextFileRepository{ "TextFile.txt" };
    TextFileRepository* repo_2 = new TextFileRepository{ "TextFileAdoption.txt" };
    Administrator admin{ repo_1 };
    User user{ repo_2 };
    GUI gui{ admin, user };
    gui.show();
    return a.exec();
}
