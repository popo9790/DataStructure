#include <bits/stdc++.h>

using namespace std;

#define INF 10000000.0

class people
{
public:
    string getName()
    {
        return name;
    }
    string getType()
    {
        return type;
    }
    void setName(string _name)
    {
        name = _name;
    }
    void setType(string _type)
    {
        type = _type;
    }
    vector<int> path;

private:
    string name;
    string type;
};

people peoarr[500];
int mess_arr[500][500];
float len_arr[500][500];
float dis[500];
int cnt = 0;
int Src, Hq;

void init();
void dijkastra();
bool checkAvail(int, int);
int choose_ver(vector<bool>);
double rnd(double);
double createDis(double);

int main(void)
{
    // freopen("test.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);
    init();
    string cmd;
    while (cin >> cmd)
    {
        if (cmd == "INSERT")
        {
            string type, name;
            cin >> type >> name;
            peoarr[cnt].setName(name);
            peoarr[cnt].setType(type);
            if (type == "SOURCE")
                Src = cnt;
            if (type == "HQ")
                Hq = cnt;
            cnt++;
        }
        else if (cmd == "INSERT_EDGE")
        {
            int to, from, mess;
            cin >> to >> from >> mess;
            to--;
            from--;
            if (checkAvail(to, from))
            {
                mess_arr[to][from] = mess_arr[from][to] = mess;
                len_arr[to][from] = len_arr[from][to] = rnd(createDis(mess));
            }
        }
        else if (cmd == "ANALYZE")
            dijkastra();
    }
}

void dijkastra()
{
    int mess_cnt = 0;
    vector<bool> visited(cnt);

    for (int it = 0; it < cnt; ++it)
        dis[it] = len_arr[Src][it];

    visited[Src] = true;
    dis[Src] = 0;
    peoarr[Src].path.push_back(Src);

    for (int it = 0; it < cnt; ++it)
    {
        int choose = choose_ver(visited);
        if (choose != -1)
        {
            if (peoarr[choose].path.size() == 0)
            {
                peoarr[choose].path = peoarr[Src].path;
                peoarr[choose].path.push_back(choose);
            }
            visited[choose] = true;

            for (int k = 0; k < cnt; ++k)
            {
                if (!visited[k])
                {
                    float distance = dis[choose] + len_arr[choose][k];
                    if (distance < dis[k])
                    {
                        dis[k] = distance;
                        peoarr[k].path = peoarr[choose].path;
                        peoarr[k].path.push_back(k);
                    }
                    else if (distance == dis[k] && dis[k] != INF)
                    {
                        for (int j = 0; j < peoarr[choose].path.size(); ++j)
                        {
                            if (peoarr[choose].path[j] < peoarr[k].path[j])
                            {
                                peoarr[k].path = peoarr[choose].path;
                                peoarr[k].path.push_back(k);
                                break;
                            }
                            else if (peoarr[choose].path[j] > peoarr[k].path[j])
                                break;
                        }
                    }
                }
            }
        }
    }

    for (auto it : peoarr[Hq].path)
    {
        cout << peoarr[it].getName();
        if (it != Hq)
            cout << " -> ";
        else
            cout << endl;
    }

    for (int it = 0; it < peoarr[Hq].path.size() - 1; ++it)
        mess_cnt += mess_arr[peoarr[Hq].path[it]][peoarr[Hq].path[it + 1]];

    cout << mess_cnt << endl;
    cout << dis[Hq] << endl;
}

int choose_ver(vector<bool> visited)
{
    double Min = INF;
    int Min_idx = -1;
    for (int i = 0; i < cnt; ++i)
    {
        if (dis[i] < Min && !visited.at(i))
        {
            Min = dis[i];
            Min_idx = i;
        }
    }
    return Min_idx;
}

double rnd(double tmp)
{
    tmp = round((tmp * 100)) / 100;
    return tmp;
}

double createDis(double tmp)
{
    if (tmp == INF || tmp == 0)
        return INF;
    else
        return 1000.0 / tmp;
}

bool checkAvail(int a, int b)
{
    if (peoarr[a].getType() == "SOURCE" && peoarr[b].getType() == "SPY")
        return false;
    if (peoarr[a].getType() == "SPY" && peoarr[b].getType() == "SPY")
        return false;
    if (peoarr[a].getType() == "CIV" && peoarr[b].getType() == "HQ")
        return false;
    if (peoarr[b].getType() == "SOURCE" && peoarr[a].getType() == "SPY")
        return false;
    if (peoarr[b].getType() == "CIV" && peoarr[a].getType() == "HQ")
        return false;
    return true;
}

void init()
{
    for (int i = 0; i < 500; ++i)
    {
        dis[i] = INF;
        for (int j = 0; j < 500; ++j)
        {
            len_arr[i][j] = len_arr[j][i] = INF;
            mess_arr[i][j] = mess_arr[j][i] = INF;
        }
    }
}
