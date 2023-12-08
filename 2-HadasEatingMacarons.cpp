#include <bits/stdc++.h>

using namespace std;

typedef struct _Node
{
    int num;
    int lable;
    struct _Node *next;
} Node;

Node *cutted;
Node *ptr_arr[11];
int target = 0;

void init();
void removePlate(Node *cur_plate);
void selectPlate(Node *cur_plate);
void eatMacarons();
void putBack();
void Show();

int main(void)
{
    init();
    for (int t = 0; t < 100; ++t)
    {
        target = (target % 10) + 1;
        Node *cur_plate = ptr_arr[target];
        removePlate(cur_plate);
        selectPlate(cur_plate);
        eatMacarons();
        putBack();
    }
    Show();
}

void init()
{
    for (int i = 1; i <= 10; ++i)
    {
        int num;
        scanf("%d", &num);

        ptr_arr[i] = new Node;
        ptr_arr[i]->lable = i;
        ptr_arr[i]->num = num;
    }
    for (int i = 1; i <= 10; ++i)
    {
        if (i == 10)
            ptr_arr[i]->next = ptr_arr[1];
        else
            ptr_arr[i]->next = ptr_arr[i + 1];
    }
}

void removePlate(Node *cur_plate)
{
    Node *next = cur_plate;
    cutted = cur_plate->next;
    for (int i = 0; i < 3; ++i)
        next = next->next;

    cur_plate->next = next->next;
    next->next = NULL;
}

void selectPlate(Node *cur_plate)
{
    Node *next = cur_plate;
    Node *minNode = NULL;
    Node *maxNode = NULL;
    int routeMin = 0;
    int routeMax = 0;
    int min_num = -1;
    int max_num = -1;
    int cur_num = cur_plate->num;
    for (int i = 1; i <= 6; ++i)
    {
        int tmp = i;
        if (i > 3)
            tmp = 7 - i;
        else
            tmp = i;

        next = next->next;
        if (next->num < cur_num) // candidate
        {
            if (next->num > min_num)
            {
                min_num = next->num;
                minNode = next;
                routeMin = tmp;
            }
            else if (next->num == min_num && tmp < routeMin)
            {
                routeMin = tmp;
                minNode = next;
            }
        }
        if (next->num > max_num)
        {
            max_num = next->num;
            maxNode = next;
            routeMax = tmp;
        }
        else if (next->num == max_num && tmp < routeMax)
        {
            routeMax = tmp;
            maxNode = next;
        }
    }
    if (minNode)
        target = minNode->lable;
    else
        target = maxNode->lable;
}

void eatMacarons()
{
    if (ptr_arr[target]->num < ptr_arr[target]->lable)
        ptr_arr[target]->num += 50;
    ptr_arr[target]->num -= ptr_arr[target]->lable;
}

void putBack()
{
    Node *prev = cutted, *next;
    for (Node *cur = cutted->next; cur != NULL;)
    {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }

    next = ptr_arr[target]->next;
    ptr_arr[target]->next = prev;
    cutted->next = next;
}

void Show()
{
    Node *cur = ptr_arr[target];
    for (int i = 1; i <= 10; ++i)
    {
        cout << cur->lable << " / " << cur->num << endl;
        cur = cur->next;
    }
}
