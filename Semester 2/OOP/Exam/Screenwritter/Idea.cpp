#include "Idea.h"
#include <sstream>

vector<string> Idea::tokenize(string str, char delimitator)
{
    stringstream ss(str);
    vector<string> result;
    string line;
    while (getline(ss, line, delimitator))
    {
        result.push_back(line);
    }
    return result;
}

std::istream& operator>>(istream& is, Idea& idea)
{
    string line;
    vector<string> tok;
    getline(is, line);
    tok = idea.tokenize(line, ',');
    if (tok.size() != 4)
    {
        return is;
    }
    idea.description = tok[0];
    idea.status = tok[1];
    idea.creator = tok[2];
    idea.act = stoi(tok[3]);
    return is;
}

std::ostream& operator<<(ostream& os, const Idea& idea)
{
    return os << idea.description << "," << idea.status << "," << idea.creator << "," << to_string(idea.act) << "\n";
}
