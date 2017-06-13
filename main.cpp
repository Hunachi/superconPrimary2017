#include<bits/stdc++.h>
using namespace std;

int n;
char seed[2010][30] = {0}; //種
int que[2010][2][30] = {0}; //種.toInt
bool mem[30] = {0}; //trueの場合使ってはいけない
vector<int> base,base_;
vector<int> seed_;
unsigned long long seed_bit[3000] = {0};
const int INF = 30000;

void hunachi() {
    //cout << "hunachi" << endl;
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

    //cout << "bit_b" << endl;
    for (int i  : seed_)
    {
        for (int j = 0; j < 26; ++j)
        {
            if (que[i][0][j] && que[i][1][j]) {
                seed_bit[i] = ((seed_bit[i]) | (3 << (j * 2)));
            }
            else if (que[i][0][j])
            {
                seed_bit[i] = ((seed_bit[i]) | (1 << (j * 2)));
            }
            else if (que[i][1][j])
            {
                seed_bit[i] = ((seed_bit[i]) | (1 << (j * 2 + 1)));
            }
        }
        //printf("%llu\n",seed_bit[i]);
    }
    //cout << seed_.size()<< "saizu" << endl;
}

void output(){
    unsigned long long k = 0;
    int m = 0;
    /////////////////////////////////
    if(seed_.size() != 1) {
        for (int i = 1; i < seed_.size(); i++) {
            m++;
            unsigned long long x = 0;
            if (i > 1) {
                x = (k | seed_bit[seed_[i]]);
                if (x == k) {
                    m--;
                    continue;
                }
                k = x;
            }
            if (i == 1) {
                x = (seed_bit[seed_[0]] | seed_bit[seed_[1]]);
                if (x == k) {
                    m--;
                    continue;
                }
                k = x;
            }
            bool flag = false;
            for (int j = 0; j < 26; j++) {
                bool a = false, b = false;
                if (k >> (j * 2) & 1) {
                    a = true;
                }
                if (k >> (j * 2 + 1) & 1) {
                    b = true;
                }
                if (a != b) {
                    flag = true;
                }
            }
            if (!flag) {
                //cout << n+m << " " << n+m << " !" << endl;
                //cout << "m = " << m+1 << endl;
                break;
            }
        }
    }
    k = 0;
    /////////////////////////////////
    cout << m << endl;
    if(seed_.size() == 1){
        cout << seed_[0]+1 << seed_[0]+1 << " !" << endl;
        cout << "m = " << m+1 << endl;
        return;
    }
    for(int i = 1; i < seed_.size(); i++){
        m ++;
        unsigned long long x = 0;
        if(i > 1){
            x = (k | seed_bit[seed_[i]]);
            if(x==k){
                m--;
                continue;
            }
            k = x;
            cout << seed_[i]+1 << " " << n+m-1 << " ";
        }
        if(i == 1){
            x = (seed_bit[seed_[0]] | seed_bit[seed_[1]]);
            if(x==k){
                m--;
                continue;
            }
            k = x;
            cout << seed_[0]+1 << " " << seed_[1] << " ";
        }
        for(int j = 0; j < 26; j++){
            if(k >> (j * 2) & 1){
                char c = (char)('A' + j);
                cout << c;
            }
            if(k >> (j * 2 + 1) & 1){
                char c = (char)('a' + j);
                cout << c;
            }
        }
        cout << endl;
        bool flag = false;
        for(int j = 0; j < 26; j++){
            bool a = false,b = false;
            if(k >> (j * 2) & 1){
                a = true;
            }
            if(k >> (j * 2 + 1) & 1){
                b = true;
            }
            if(a != b){
                flag = true;
            }
        }
        if(!flag){
            cout << n+m << " " << n+m << " !" << endl;
            return;
        }
    }
}

bool judge()
{
    bool updated[1010] = {0};
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
        //scanf("%s",seed);
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
        output();
    }
    return 0;
}
