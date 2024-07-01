#include "App.h"
#include <fstream>
#include <sstream>
void App::Read()
{
    ifstream f("researchers.txt");
    while (!f.eof())
    {
        string line;
        getline(f, line);
        stringstream ss(line);
        vector<string> tok;
        string word;
        while (getline(ss, word, ','))
        {
            tok.push_back(word);
        }
        if (tok.size() == 2)
        {
            Researcher* resercher = new Researcher(*this->model, tok[0], tok[1]);
            resercher->show();
            this->res.push_back(resercher);
        }
    }
}

App::App()
{
    this->model = new MyModel();
    this->Read();
}

App::~App()
{
    for (auto q : this->res)
    {
        delete q;
    }
    delete this->model;
}
