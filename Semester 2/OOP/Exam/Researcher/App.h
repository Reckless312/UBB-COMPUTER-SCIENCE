#pragma once

#include "Researcher.h"

class App
{
private:
    vector<Researcher*> res;
    MyModel* model;
    void Read();
public:
    App();
    ~App();
};