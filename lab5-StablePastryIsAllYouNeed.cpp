#include <bits/stdc++.h>

using namespace std;

typedef long long lli;

lli INF = __INT32_MAX__;

struct food
{
    food(){};
    food(string name) : name(name), prev_idx(-1), cur_idx(-1), v(0){};
    string name;
    lli prev_idx;
    lli cur_idx;
    lli v;

    void CalVolatilty()
    {
        if (prev_idx == -1 || cur_idx == -1)
            return;

        lli tmp = abs(prev_idx - cur_idx);
        v += tmp;
    }
};

struct price
{
    price(lli vec_idx, lli pr) : vec_idx(vec_idx), pr(pr){};
    lli vec_idx;
    lli pr;

    bool operator<(const price &rhs) const
    {
        return this->pr < rhs.pr;
    }
};

vector<food> fo_arr;
set<price> pr_arr;

int main(void)
{
    // freopen("test.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);

    lli n, m;
    cin >> n >> m;
    for (lli i = 0; i < m; ++i)
    {
        string name;
        cin >> name;
        fo_arr.push_back(food(name));
    }

    for (lli i = 0; i < n; ++i)
    {
        pr_arr.clear();
        for (lli j = 0; j < m; ++j)
        {
            lli _price;
            cin >> _price;
            pr_arr.insert(price(j, _price));
        }

        int cnt = 0;
        for (auto it = pr_arr.begin(); it != pr_arr.end(); ++it)
        {
            lli idx = it->vec_idx;
            fo_arr[idx].prev_idx = fo_arr[idx].cur_idx;
            fo_arr[idx].cur_idx = cnt++;
            fo_arr[idx].CalVolatilty();
        }
    }

    lli min_v = INF;
    vector<food>::iterator ans;
    for (auto it = fo_arr.begin(); it != fo_arr.end(); ++it)
    {
        if (it->v < min_v)
        {
            min_v = it->v;
            ans = it;
        }
    }
    cout << ans->name << endl;
}