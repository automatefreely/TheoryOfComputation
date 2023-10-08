#include <bits\stdc++.h>
using namespace std;


/*
    check_nfa function takes in a NFA, input string and final states and returns true if the input string is accepted by the NFA
    and false otherwise.
    The NFA is represented as a 3D vector of vectors. The first dimension represents the states of the NFA, the second dimension
    represents the input symbols and the third dimension represents the states that the NFA can go to from the current state on
    reading the input symbol.
    The input string is represented as a vector of integers. The integers represent the input symbols. For example, if the input
    string is "ab", then the vector will be {0, 1}.
    The final states are represented as a vector of integers. The integers represent the final states. For example, if the final
    states are 1 and 2, then the vector will be {1, 2}.
*/
bool check_nfa(vector<vector<vector<int>>> &nfa, vector<int> &in_string, vector<int> &final_states)
{
    vector<int> current_states = {0};

    for (auto c : in_string)
    {

        vector<int> new_states = {};
        for (auto a : current_states)
        {
            for (auto b : nfa[a][c])
            {
                new_states.push_back(b);
            }
        }
        current_states = new_states;
    }
    for (auto a : current_states)
    {
        for (auto b : final_states)
        {
            if (a == b)
                return true;
        }
    }
    return false;
}

int main()
{
    vector<vector<vector<int>>> v = {
        {{1, 2}, {}, {}},
        {{1}, {2}, {}},
        {{3}, {}, {}},
        {{}, {2}, {}},
    };

    vector<int> final_states = {1, 2};

    string s;
    cin >> s;
    vector<int> input_string;
    for (int i = 0; i < s.size(); ++i)
    {
        input_string.push_back(s[i] == 'a' ? 0 : 1);
    }

    cout << (check_nfa(v, input_string, final_states) ? "YES" : "NO") << endl;
    return 0;
}