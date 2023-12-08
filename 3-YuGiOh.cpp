#include <iostream>
#include <string.h>

using namespace std;

typedef struct _node
{
    int data;
    struct _node *left, *right;
} Node;

Node *dummy;
int nodecnt = 0;

Node *makeNode(int data);
void Sacrific56(Node *root, int mode, int data);
void Sacrific78(Node *root, int data);
void show(Node *root);
void FreeNode(Node *root);

int main(void)
{
    // freopen("test.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);
    char cammand[10];
    int star, dmgCnt = 0;
    bool endGame = false;
    dummy = makeNode(-1);

    while (scanf("%s -> %d*", cammand, &star) != EOF && !endGame)
    {
        switch (cammand[0])
        {
        case 'T':
            endGame = true;
            break;
        case 'S':
            nodecnt++;
            if (star <= 4)
            {
                if (dummy->left == NULL)
                    dummy->left = makeNode(star);
                else
                    dummy->right = makeNode(star);
            }
            else if (star == 5 || star == 6)
            {
                int lhs = 999, rhs = 999;
                if (dummy->left)
                    lhs = dummy->left->data;
                if (dummy->right)
                    rhs = dummy->right->data;
                if (lhs > rhs)
                    Sacrific56(dummy, 1, star);
                else
                    Sacrific56(dummy, 0, star);
            }
            else if (star == 7 || star == 8)
                Sacrific78(dummy, star);
            break;
        case 'A':
            if (dummy->left)
                dmgCnt += dummy->left->data;
            if (dummy->right)
                dmgCnt += dummy->right->data;
            break;
        }
    }
    show(dummy);
    cout << endl;
    cout << dmgCnt << endl;
}

Node *makeNode(int data)
{
    Node *root = new Node;
    root->data = data;
    root->left = NULL;
    root->right = NULL;
    return root;
}

void Sacrific56(Node *root, int mode, int data)
{
    Node *new_monster = makeNode(data);
    if (!mode) // left
    {
        new_monster->left = dummy->left;
        dummy->left = new_monster;
    }
    else // right
    {
        new_monster->right = dummy->right;
        dummy->right = new_monster;
    }
}

void Sacrific78(Node *root, int data)
{
    Node *new_monster = makeNode(data);
    new_monster->left = dummy->left;
    new_monster->right = dummy->right;

    dummy->left = new_monster;
    dummy->right = NULL;
}

void show(Node *root)
{
    if (root)
    {
        if (root->data >= 0)
        {
            nodecnt--;
            printf("%d*", root->data);
            if (nodecnt != 0)
                cout << " ";
        }
        show(root->left);
        show(root->right);
    }
}

void FreeNode(Node *root)
{
    if (root)
    {
        show(root->left);
        show(root->right);
        delete root;
    }
}