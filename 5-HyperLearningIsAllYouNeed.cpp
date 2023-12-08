#include <bits/stdc++.h>

using namespace std;

struct Fruit
{
    Fruit(){};
    Fruit(string _name) : name(_name){};
    string name;
    vector<int> hyperFeatures;
    int lastHyper;
};

struct GradBinHyperWeight
{
    int feature_Idx;
    double grad_Slider;
    int bin_Threshold;

    GradBinHyperWeight(int fe = 0, int gra = 0, int bin = 0)
        : feature_Idx(fe), grad_Slider(gra), bin_Threshold(bin){};
    bool shouldBackward(Fruit &f) const
    {
        return f.hyperFeatures[feature_Idx] < bin_Threshold;
    }
    void applyGradSlider(Fruit &f) const
    {
        f.hyperFeatures[feature_Idx] = (int)((double)f.hyperFeatures[feature_Idx] * grad_Slider);
    }
};

void MySort(int, int, int);

vector<GradBinHyperWeight> nodearr;
vector<Fruit> FruArr;

int main(void)
{
    // freopen("test.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);

    int FruitNum, HyperNum;
    cin >> FruitNum >> HyperNum;
    for (int i = 0; i < FruitNum; ++i)
    {
        string name;
        cin >> name;
        FruArr.push_back(Fruit(name));
        for (int j = 0; j < HyperNum; ++j)
        {
            int hyper;
            cin >> hyper;
            FruArr.back().hyperFeatures.push_back(hyper);
        }
    }

    int o;
    cin >> o;
    nodearr.push_back(GradBinHyperWeight(-1, -1, -1));
    for (int i = 0; i < o; ++i)
    {
        int var_1, var_2, var_3;
        cin >> var_1 >> var_2 >> var_3;
        nodearr.push_back(GradBinHyperWeight(var_1, var_2, var_3));
    }
    MySort(0, FruArr.size(), 1);
    for (auto it : FruArr)
        cout << it.name << " " << it.lastHyper << endl;
}

void MySort(int l, int r, int mth)
{
    if (l < r && mth < nodearr.size())
    {
        for (int it = l; it < r; ++it)
        {
            nodearr[mth].applyGradSlider(FruArr[it]);
            FruArr[it].lastHyper = FruArr[it].hyperFeatures[nodearr[mth].feature_Idx];
        }

        vector<Fruit> L_Arr;
        vector<Fruit> R_Arr;

        int i = 0, j = 0;
        for (int it = l; it < r; ++it)
        {
            if (nodearr[mth].shouldBackward(FruArr[it]))
            {
                L_Arr.push_back(FruArr[it]);
                i++;
            }
            else
            {
                R_Arr.push_back(FruArr[it]);
                j++;
            }
        }

        for (auto idx = l; idx < r;)
        {
            for (auto it : L_Arr)
                FruArr[idx++] = it;
            for (auto it : R_Arr)
                FruArr[idx++] = it;
        }

        MySort(l, l + i, mth * 2);
        MySort(l + i, r, mth * 2 + 1);
    }
}