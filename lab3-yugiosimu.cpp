#include <iostream>
#include <string>

using namespace std;

// club = 0, dia = 1, heart = 2;

typedef struct _node
{
    int val;
    struct _node *left, *right;
} Node;

int heart_val = 0;
Node *make_Node(int);
void Cover_dia(Node *, int);
void Cover_hea(Node *);
int calculate(Node *);

int main(void)
{
    // freopen("test.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);

    string input;
    Node *dummy = make_Node(-1);
    while (cin >> input)
    {
        if (input == "Spade")
            break;
        if (input == "Clubs")
        {
            if (!dummy->left)
                dummy->left = make_Node(1);
            else if (!dummy->right)
                dummy->right = make_Node(1);
        }
        else if (input == "Diamond")
        {
            int lhs = 9999;
            int rhs = lhs;
            if (dummy->left)
                lhs = dummy->left->val;
            if (dummy->right)
                rhs = dummy->right->val;

            if (lhs != 9999 || rhs != 9999)
            {
                if (lhs <= rhs)
                    Cover_dia(dummy, 0);
                else
                    Cover_dia(dummy, 1);
            }
        }
        else if (input == "Heart")
            if (dummy->left != NULL && dummy->right != NULL)
                Cover_hea(dummy);
    }
    cout << heart_val << endl;
}

Node *make_Node(int val)
{
    Node *a = new Node;
    a->val = val;
    a->left = NULL;
    a->right = NULL;
    return a;
}

void Cover_dia(Node *root, int mode)
{
    Node *new_card = make_Node(3);
    if (mode == 0) // change left
    {
        new_card->left = root->left;
        root->left = new_card;
    }
    else // change right
    {
        new_card->right = root->right;
        root->right = new_card;
    }
}

void Cover_hea(Node *root)
{
    int val = calculate(root->left) - calculate(root->right);
    heart_val += val;
    Node *new_card = make_Node(val);

    new_card->left = root->left;
    new_card->right = root->right;

    root->right = NULL;
    root->left = new_card;
}

int calculate(Node *root)
{
    int ans = 0;
    if (root)
        ans = root->val + calculate(root->left) + calculate(root->right);
    return ans;
}