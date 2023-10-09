#include <bits/stdc++.h>

using namespace std;

bool is_terminal(char s)
{
    return (s == 'a' || s == 'b' || s == '\0');
}

bool is_non_terminal(char s)
{
    return (s == 'S');
}
map<char, vector<string>> grammer;

bool check_grammer(string &s, int pos, string derivation)
{
    // cout<<s<<" "<<pos<<" "<<derivation<<endl;
    if (derivation.size() > 2 * s.size())
    {
        return false;
    }

    if (pos >= s.size() && derivation.size() <= pos)
    {
        return true;
    }
    if (is_terminal(derivation[pos]) && s[pos] != derivation[pos])
    {
        return false;
    }
    if (s[pos] == derivation[pos])
    {
        return check_grammer(s, pos + 1, derivation);
    }
    bool possible = false;
    for (auto a : grammer[derivation[pos]])
    {
        string new_derivation = derivation;
        new_derivation.replace(pos, 1, a);
        bool check = check_grammer(s, pos, new_derivation);
        possible |= check;
        if (possible)
            break;
    }
    return possible;
}

string __derive(int pos, string derivation, int size)
{
    // cout<<derivation<<" "<<pos<<" "<<size<<" "<<derivation.size()<<endl;
    if (derivation.size() > 2 * size)
    {
        return "wrong";
    }
    if (derivation.size() == size)
    {
        int all_terminal = 1;
        for (auto a : derivation)
        {
            if (!is_terminal(a))
            {
                all_terminal = 0;
            }
        }
        if (all_terminal)
            return derivation;
    }
    if (is_terminal(derivation[pos]))
    {
        return __derive(pos + 1, derivation, size);
    }
    string ans = "wrong";
    for (auto a : grammer[derivation[pos]])
    {
        string new_derivation = derivation;
        new_derivation.replace(pos, 1, a);
        string s = __derive(pos, new_derivation, size);
        if (s != "wrong")
        {
            ans = s;
            break;
        }
    }
    return ans;
}

string generate_string(int n)
{
    string derivaton = "S";
    cout << __derive(0, "S", n);
    return "sss";
}

int main()
{
    grammer['S'].push_back("aSa");
    grammer['S'].push_back("bSb");
    grammer['S'].push_back("a");
    grammer['S'].push_back("b");
    grammer['S'].push_back("");

    string s;
    cin >> s;

    cout << (check_grammer(s, 0, "S") ? "YES" : "NO") << endl;
    // generate_string(4);

    return 0;
}