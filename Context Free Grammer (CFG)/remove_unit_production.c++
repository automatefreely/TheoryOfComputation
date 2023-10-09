#include <bits/stdc++.h>

using namespace std;

vector<char> non_terminals = {
    'S',
    'A',
    'B',
    'C',
    'D',
};
vector<char> terminal = {'a', 'b'};
map<char, vector<string>> grammer;
bool is_terminal(char s)
{
    for (auto a : terminal)
    {
        if (a == s)
            return true;
    }
    return false;
}

bool is_non_terminal(char s)
{
    for (auto a : non_terminals)
    {
        if (a == s)
            return true;
    }
    return false;
}

void print_grammer()
{
    for (auto a : grammer)
    {
        cout << a.first << " -> ";
        for (auto b : a.second)
        {
            cout << b << " | ";
        }
        cout << endl;
    }
}

void __remove_unit_prod(char input, string output)
{
    auto it = find(grammer[input].begin(), grammer[input].end(), output);
    grammer[input].erase(it);
}

pair<char, string> get_unit_prod()
{
    for (auto a : grammer)
    {
        for (auto b : a.second)
        {
            if (b.length() == 1 && is_non_terminal(b[0]))
            {
                return {a.first, b};
            }
        }
    }
    return {'\0', ""};
}

void remove_unit_prod()
{
    pair<char, string> unit_prod = get_unit_prod();
    while (unit_prod.first != '\0')
    {
        char input = unit_prod.first;
        string output = unit_prod.second;
        __remove_unit_prod(input, output);
        for (auto a : grammer[output[0]])
        {
            grammer[input].push_back(a);
        }
        unit_prod = get_unit_prod();
    }
}

int main()
{
    // Add the grammer here in the form of grammer['S'].push_back("AB"); 
    // if S -> AB is a production rule
    grammer['S'].push_back("AB");
    grammer['A'].push_back("a");
    grammer['B'].push_back("C");
    grammer['C'].push_back("a");
    grammer['C'].push_back("D");
    grammer['D'].push_back("b");

    print_grammer();
    remove_unit_prod();
    cout << endl;
    print_grammer();
    cout << endl;
    return 0;
}