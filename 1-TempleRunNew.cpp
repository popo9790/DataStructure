#include <bits/stdc++.h>

using namespace std;

queue<int> loot_miss;
queue<int> loot;
stack<string> route;

void Show();

int main(void)
{
    int cnt = 0;
    string input;
    while ((cin >> input) && !cin.eof())
    {
        if (!input.compare("TL"))
            route.push("TR");
        else if (!input.compare("TR"))
            route.push("TL");

        if (input[0] == 'M')
            cnt = 4;
        if (input[0] == 'G')
        {
            loot.push(2);
            if (!cnt)
                loot_miss.push(2);
            else
                cnt--;
        }
        else if (input[0] == 'S')
        {
            loot.push(1);
            if (!cnt)
                loot_miss.push(1);
            else
                cnt--;
        }
    }
    Show();
}

void Show()
{
    int len = route.size();
    int val = 0;
    int tmp = 0;
    for (int i = 0; i < len; ++i)
    {
        cout << route.top();
        if (i == len - 1)
            puts("");
        else
            cout << "->";
        route.pop();
    }

    len = loot_miss.size();
    for (int i = 1; i <= len; ++i)
    {
        tmp += loot_miss.front();
        loot_miss.pop();
        if (i % 3 == 0)
        {
            if (tmp == 6)
                val += 500;
            else if (tmp == 5)
                val += 300;
            else if (tmp == 4)
                val += 150;
            else if (tmp == 3)
                val += 50;
            tmp = 0;
        }
    }
    cout << val << endl;

    val = 0;
    tmp = 0;
    len = loot.size();
    for (int i = 1; i <= len; ++i)
    {
        tmp += loot.front();
        loot.pop();
        if (i % 3 == 0)
        {
            if (tmp == 6)
                val += 500;
            else if (tmp == 5)
                val += 300;
            else if (tmp == 4)
                val += 150;
            else if (tmp == 3)
                val += 50;
            tmp = 0;
        }
    }
    cout << val << endl;
}