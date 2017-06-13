//
// Created by hanah on 6/13/2017.
//

#include<bits/stdc++.h>
using namespace std;

int n;
char seed[2010][30] = {0}; //種
int que[2010][2][30] = {0}; //種.toInt
bool mem[30] = {0}; //trueの場合使ってはいけない
vector<int> base,base_;
vector<int> seed_;
unsigned long long seed_bit[3000] = {0};
int INF = 30000;
vector<int> big[30],small[30],comp[30];
vector<pair<int,int>> comp_num[30][2];
vector<unsigned long long> comp_bit[30][2];
vector<int> answer;

void hunachi() {

    for (int i = 0; i < 26; ++i) {
        if (mem[i] == 0) {
            base.push_back(i);
        } else {
            base_.push_back(i);
        }
    }

    for (int i = 0; i < n; ++i) {
        int flag = true;
        for (int j = 0; j < base_.size(); ++j) {
            if (que[i][0][base_[j]] > 0 || que[i][1][base_[j]] > 0) {
                flag = false;
            }
        }
        if (flag) {
            seed_.push_back(i);
        }
    }

    for (int i  : seed_)
    {
        for (int j : base)
        {
            if (que[i][0][j] && que[i][1][j]) {
                seed_bit[i] = ((seed_bit[i])|(3 << (j * 2)));
                comp[j].push_back(i);
            }
            else if (que[i][0][j])
            {
                seed_bit[i] = ((seed_bit[i])|(1 << (j * 2)));
            }
            else if (que[i][1][j])
            {
                seed_bit[i] = ((seed_bit[i])|(1 << (j * 2 + 1)));
            }
        }
    }

    int count = 0;

    for (int i  : seed_)
    {
        for (int j : base)
        {
            if (que[i][0][j] && que[i][1][j])
            {
                comp_num[j][0].push_back(make_pair(-1,j));
                big[j].push_back(i);
                small[j].push_back(i);
                break;
            }
            else if (que[i][0][j])
            {
                big[j].push_back(i);
                break;
            }
            else if (que[i][1][j])
            {
                small[j].push_back(i);
                break;
            }
        }

    }
    //cout << seed_.size()<< "saizu" << endl;
}

void prepare(){
    for(int i : base) {
        for (int j : big[i]) {
            unsigned long long a = 0, b = 0;
            int c = 52;
            int s = 0;
            if (!small[i].empty())s = small[i][0];
            for (int k : small[i]) {
                for (int l : base) {
                    if (que[k][0][l] && que[k][1][l]) {
                    } else if (que[k][0][l]) {
                        a = ((seed_bit[k]) | (1 << (j * 2)));
                    } else if (que[k][1][j]) {
                        a = ((seed_bit[k]) | (1 << (j * 2 + 1)));
                    }
                }
                b = (seed_bit[j] | a);
                b -= seed_bit[j];
                int o = 0;
                for (int l = 0; l < 52; ++l) {
                    if ((b >> l) & 1) {
                        o++;
                    }
                }
                if (o < c) {
                    c = o;
                    s = k;
                    comp_bit[i][1].push_back((seed_bit[j] | seed_bit[o]));
                }
            }
            comp_num[i][1].push_back(make_pair(j, s));
        }
    }
    /*
    for(int i : base){
        cout << i <<" : "<< endl;
        cout << "comp 1 = " ;
        for(pair<int,int> j : comp_num[i][0]){
            cout << j.second<< " ";
        }
        cout << endl << "comp 2 = ";
        for(pair<int,int> j : comp_num[i][1]){
            cout << j.first << "." << j.second << " ";
        }
        cout << endl << "big = ";
        for(int j : big[i]){
            cout << j << " ";
        }
        cout << endl << "small = ";
        for(int j : small[i]){
            cout << j << " ";
        }
        cout << endl;
    }*/
}

void narahara(){
    for(int i : base){

    }
}

bool judge()
{
    bool updated[2010] = {0};
    int kind[2][30] = {0};
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            for(int k = 0; k < 26; k++)
            {
                kind[j][k] += que[i][j][k];
            }
        }
    }
    bool flag;
    while(1)
    {
        flag = false;
        for(int i = 0; i < 26; i++)
        {
            if(kind[0][i] == 0 || kind[1][i] == 0)
            {
                kind[0][i] = kind[1][i] = -1;
                mem[i] = true;
                flag = true;
            }
        }
        if(!flag)
        {
            for(int i = 0; i < 26; i++)
            {
                if(kind[0][i] > 0 || kind[1][i] > 0)
                {
                    return true;
                }
            }
            return false;
        }
        for(int i = 0; i < n; i++)
        {
            if(updated[i])
            {
                continue;
            }
            for(int j = 0; j < 26; j++)
            {
                if(mem[j] && (que[i][0][j] == 1 || que[i][1][j] == 1))
                {
                    for(int l = 0; l < 26; l++)
                    {
                        kind[0][l] -= que[i][0][l];
                        kind[1][l] -= que[i][1][l];
                    }
                    updated[i] = true;
                    break;
                }
            }
        }
    }
}

int main()
{
    scanf("%d",&n);
    for(int i = 0; i < n; i++)
    {
        scanf("%s",seed[i]);
    }
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < strlen(seed[i]); j++)
        {
            if(isupper(seed[i][j]))
            {
                que[i][0][seed[i][j] - 'A']++;
            }
            else
            {
                que[i][1][seed[i][j] - 'a']++;
            }
        }
    }
    if(!judge())
    {
        printf("NO\n");
    }
    else
    {
        printf("YES\n");
        hunachi();
        prepare();
    }
    return 0;
}
