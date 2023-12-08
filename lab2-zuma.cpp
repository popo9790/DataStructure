#include <forward_list>
#include <iostream>
#include <list>
#include <string>

using namespace std;

int n, m;
list<char> bead;

void solve(list<char>::iterator dis);

int main(void)
{
    char tar;
    cin >> n >> m >> tar;
    n++;
    for (int i = 1; i <= n; ++i)
    {
        char tmp;
        if (i != m + 1)
        {
            cin >> tmp;
            bead.emplace_back(tmp);
        }
        else
            bead.emplace_back(tar);
    }

    list<char>::iterator dis = bead.begin();
    for (int i = 2; i <= m + 1; ++i)
        dis++;

    solve(dis);
    int ans = 1;
    for (auto i = bead.begin(); i != bead.end(); ++i, ++ans)
    {
        cout << *i;
        if (ans == bead.size())
            cout << '\n';
        else
            cout << ' ';
    }
    cout << bead.size() << endl;
}

void solve(list<char>::iterator dis)
{
    list<char>::iterator start;
    list<char>::iterator end;
    char color = *dis;
    int count = -1;
    bool check = false;

    for (start = dis; *start == color; start--)
        if (*start == color)
            count++;

    for (end = dis; end != bead.end() && *end == color; end++)
        if (*end == color)
            count++;

    if (*start == *end)
        check = true;

    start++;
    if (count >= 3)
    {
        bead.erase(start, end);
        if (color == 'B')
        {
            for (int i = 0; i < count; ++i)
                bead.emplace_front(color);
            end--;
            bead.reverse();
        }
        else if (color == 'G')
        {
            for (int i = 0; i < count * 2; ++i)
                bead.emplace_back(color);
        }
        if (check)
            solve(end);
    }
    return;
}
