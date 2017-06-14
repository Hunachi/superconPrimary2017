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
vector<pair<unsigned long long,int>> big[30],small[30];
vector<pair<unsigned long long ,pair<int,int>>> comp[30];

void out(unsigned long long j){
    char c;
    for(int k : base){
        if((j >> (k * 2)) & 1){
            c = (char)('A' + k);
            cout << c;
        }
        if((j >> (k * 2 + 1)) & 1){
            c = (char)('a' + k);
            cout << c;
        }
    }
    cout << endl;
    return;
}

bool check(unsigned long long j){
    for(int k : base)
    {
        bool b = (bool)(j >> (k * 2) & 1);
        bool c = (bool)(j >> (k * 2 + 1)& 1);
        if(c != b)
        {
            return false;
        }
    }
    return true;
}

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
                seed_bit[i] = ((seed_bit[i])|(1 << (j * 2)));
                seed_bit[i] = ((seed_bit[i])|(1 << (j * 2 + 1)));
                //comp[j].push_back(i);
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
        for (int j : base) {
            if (que[i][0][j] && que[i][1][j])
            {
                comp[j].push_back(make_pair(seed_bit[i],make_pair(i,-1)));
                big[j].push_back(make_pair(seed_bit[i],i));
                small[j].push_back(make_pair(seed_bit[i],i));
            }
            else if (que[i][0][j])
            {
                big[j].push_back(make_pair(seed_bit[i],i));
            }
            else if (que[i][1][j])
            {
                small[j].push_back(make_pair(seed_bit[i],i));
            }
        }
    }

    for(int i : base) {
        for (pair<unsigned long long,int> j : big[i]) {
            unsigned long long a = 0, b = 0;
            int c = 52;
            int s = 0;
            //if (!small[i].empty())s = small[i][0];
            for (pair<unsigned long long , int> k : small[i]) {
                /*for (int l : base) {
                    if (que[k.second][0][l] && que[k.second][1][l]) {
                    } else if (que[k][0][l]) {
                        a = ((k.first) | (1 << (j * 2)));
                    } else if (que[k][1][j]) {
                        a = ((seed_bit[k]) | (1 << (j * 2 + 1)));
                    }
                }*/
                b = (j.first | k.first);
                b -= j.first;
                int o = 0;
                for (int l = 0; l < 52; ++l) {
                    if ((b >> l) & 1) {
                        o++;
                    }
                }
                if (o > 0 && o < c) {
                    c = o;
                    s = k.second;
                }
            }
            if (!small[i].empty()) {
                comp[i].push_back(make_pair((j.first | seed_bit[s]),make_pair(j.second,s)));
            }
        }
    }

    //cout << seed_.size()<< "saizu" << endl;
}


int fun(){
    int ans = INF;
    vector<int> answer_0;
    for(int i : base){
        for(pair<unsigned long long ,pair<int,int>> j : comp[i]){
            int ans_1 = INF;
            vector<int> answer_1;
            if(j.second.second == -1){
                ans_1 = 1;
                answer_1.push_back(j.second.first);
            }else{
                ans_1 = 2;
                answer_1.push_back(j.second.first);
                answer_1.push_back(j.second.second);
            }
            unsigned long long bit_2 = j.first;
            set<pair<int,int>> a;
            for(int k : base){
                if(((bit_2 >> (k * 2))& 1) && ((bit_2 >> (k * 2 + 1))& 1) )continue;
                if(((bit_2 >> (k * 2))& 1) ){
                    a.insert(make_pair(k , 0));
                }else if(((bit_2 >> (k * 2 + 1))& 1) ){
                    a.insert(make_pair(k, 1));
                }
            }

            while(!a.empty()){
                auto it = a.begin();
                pair<int,int> k = *it;
                //cout << k.first << " a " ;
                a.erase(make_pair(k.first,k.second));
                int seed_num = 0;
                pair<unsigned long long ,int> b;
                if(k.second == 1){
                    b = big[k.first][0];
                    seed_num = b.second;
                }else if(k.second == 0){
                    //small
                    b = small[k.first][0];
                    seed_num = b.second;
                }
                //b  = comp[k.first][0];
                answer_1.push_back(seed_num);
                unsigned long long bit_3 = ( b.first | bit_2) ;
                bit_3 = bit_3 - bit_2;
                if(bit_3 == (unsigned long long)0){
                    break;
                }
                //cout << "out" << endl;
                //out(bit_3);

                for(int l : base){
                    if( l == k.first )continue;
                    if(((bit_3 >> (l * 2))& 1) && ((bit_3 >> (l * 2 + 1))& 1) ){
                        a.erase(make_pair(l , 0));
                        a.erase(make_pair(l , 1));
                        //continue;
                    }else{
                    if(((bit_3 >> (l * 2))& 1) ){
                        int p = a.erase(make_pair(l , 1));
                        if( !p ){
                            a.insert(make_pair(l , 0));
                        }
                    }else if(((bit_3 >> (l * 2 + 1))& 1) ){
                        int p = a.erase(make_pair(l , 0));
                        if( !p ){
                            a.insert(make_pair(l, 1));
                        }
                    }
                    }
                }
                bit_2 = (b.first | bit_2);
            }

            //answer_1.pop_back();
            //cout << ans << " " << (answer_1.size()) << endl;
            if(ans > (answer_1.size())){
                //cout << ans << " " << (answer_1.size()) << endl;
                ans = answer_1.size();
                answer_0.clear();
                copy(answer_1.begin(),answer_1.end(),back_inserter(answer_0));
            }
            answer_1.clear();

        }

    }
    unsigned long long ans_bit = 0,ans_bit_0 = 0;
    for(int b : answer_0){
        ans_bit = (ans_bit | seed_bit[b]);
        //cout << b << " ";
        //out(seed_bit[b]);
    }
    if(check(ans_bit)) {
        cout << ans << endl;
        if (answer_0.size() == 1) {
            cout << answer_0[0] + 1 << " " << answer_0[0] + 1 << " !" << endl;
            return 1;
        }
        int count = -1;
        for(int b : answer_0){
            ans_bit_0 = (ans_bit_0 | seed_bit[b]);
            if(count == -1){
                cout << b + 1<< " ";
            }else if(count == 0){
                cout << b + 1<< " ";
                out((seed_bit[b] | seed_bit[answer_0[0]]));
            }else{
                cout << b + 1 << " " << n + count << " ";
                out(ans_bit_0);
            }
            count++;
        }
        cout << n + count << " " << n + count << " !" << endl;
    }
    return ans;
    //cout << " check = " << check(ans_bit) << endl;
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
        fun();
    }
    return 0;
}
