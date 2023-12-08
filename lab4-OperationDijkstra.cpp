#include <cmath>
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <string.h>
#include <vector>

using namespace std;

#define INF 1000005

// my node numbered from 0;
int cnt;
int Src = 0;
int len_arr[1000][1000];
vector<float> dis;
vector<bool> visited;

void init();
void dijkastra(int end);
int findMin();

int main(void)
{
    // freopen("test.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);

    init();
    string cmd;
    while (cin >> cmd)
    {
        if (cmd == "INSERT_LOCATIONS")
        {
            cin >> cnt;
        }
        else if (cmd == "INSERT_DISTANCE")
        {
            int to, from, distance;
            cin >> to >> from >> distance;
            to--;
            from--;
            len_arr[to][from] = len_arr[from][to] = distance;
        }
        else if (cmd == "CALCULATE")
        {
            int cal_pos;
            cin >> cal_pos;
            cal_pos--;
            dijkastra(cal_pos);
        }
        else if (cmd == "TERMINATE")
            break;
    }
}

void dijkastra(int end)
{
    visited.clear();
    dis.clear();
    for (int i = 0; i < cnt; ++i)
    {
        dis.push_back(INF);
        visited.push_back(false);
    }

    dis[Src] = 0;
    for (int i = 0; i < cnt; ++i)
    {
        int choose = findMin();
        if (choose != -1)
        {
            visited[choose] = true;
            for (int j = 0; j < cnt; ++j)
            {
                if (!visited[j])
                {
                    int tmp = dis[choose] + len_arr[choose][j];
                    if (tmp < dis[j])
                        dis[j] = tmp;
                }
            }
        }
    }
    cout << dis[end] << endl;
}

int findMin()
{
    int Min_idx = -1;
    int Min_len = INF;
    for (int i = 0; i < cnt; ++i)
    {
        if (dis[i] < Min_len && !visited[i])
        {
            Min_len = dis[i];
            Min_idx = i;
        }
    }
    return Min_idx;
}

void init()
{
    for (int i = 0; i < 1000; ++i)
        for (int j = 0; j < 1000; ++j)
            len_arr[i][j] = INF;
}