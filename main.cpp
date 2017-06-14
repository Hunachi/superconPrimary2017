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
//vector<unsigned long long> comp_bit[30][2];
vector<int> answer,answer2;
int ans = INF;
map<unsigned long long, int> save;

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
                //TODO
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
    unsigned long long ans_bit = 0;
    cout << ans << endl;
    for(int b : answer_0){
        ans_bit = (ans_bit | seed_bit[b]);
        cout << b << " ";
        out(seed_bit[b]);
    }
    cout << " check = " << check(ans_bit) << endl;
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
    }
}*/


/*
void mya(){
    int ans = seed_.size();
    set<int> a;
    for(int i = 0; i < base.size(); i++)
    {
        int p = base[i];
        int num = 0;
        if(comp_num[p][num].empty())num++;
        int ans_;
        //cout << "i " << p << endl;
        for(int h = num ; h < 2; h++ )
        {
            //cout << "h " << h << endl;
            int count = 0;
            for (unsigned long long j : comp_bit[p][h])
            {
                answer.push_back(p);
                //cout << j << " = j"<< endl;
                ans_= h + 1;
                if(ans_ == 2)
                {
                    //cout << p << " ans = " << count <<endl;
                    if(comp_num[p][h].size() <= count){
                        continue;
                    }
                    //cout << comp_num[p][h][count].first << " " << comp_num[p][h][count].second<< " ";
                    answer.push_back(comp_num[p][h][count].second);
                    answer.push_back(comp_num[p][h][count].first);
                }
                else
                {
                    answer.push_back(comp_num[p][h][count].second);
                }
                for (int k : base)
                {
                    bool b = (bool) (j >> (k * 2) & 1);
                    bool c = (bool) (j >> (k * 2 + 1) & 1);
                    if (c != b)
                    {
                        if (b)
                        {
                            a.insert(k * 2);
                        }
                        if (c)
                        {
                            a.insert(k * 2 + 1);
                        }
                    }
                }
                unsigned long long p1 = j;

                bool flags = true;
                ///cout << a.size() << " = a.size()" << endl;
                while (!a.empty() && flags)
                {
                    ans_++;
                    auto kk = a.begin();
                    int k = *kk;
                    //cout << " k " << k << endl;
                    a.erase(k);
                    int c = k / 2;
                    int saisho = 52;
                    int ans_nu = -1;
                    //cout << "front of k = " ;
                    if ((k % 2) == 1)
                    {
                        //cout << "big" << c <<endl;
                        for (int l : big[c])
                        {
                            unsigned long long p2 = (p1 | seed_bit[l]);
                            p2 = (p2 - p1);
                            int o = __builtin_popcount(p2);
                            //cout << o << endl;
                            if (o < saisho)
                            {
                                //cout << o << " o " << endl;
                                saisho = o;
                                ans_nu = l;
                            }
                        }
                    }
                    else
                    {
                        for (int l : small[c])
                        {
                            unsigned long long p2 = (p1 | seed_bit[l]);
                            p2 = p2 - p1;
                            int o = __builtin_popcount(p2);
                            if (o < saisho)
                            {

                                //cout << " o " << o << endl;
                                saisho = o;
                                ans_nu = l;
                            }
                        }
                    }
                    if(ans_nu == -1)
                    {
                        //存在しない
                        //cout << "NG" << c << endl;
                        flags = false;
                        a.clear();
                    }
                    unsigned long long p3,p4;
                    p3 = (seed_bit[ans_nu] | p1);
                    p4 = p3;
                    answer.push_back(ans_nu);
                    p3 = p3 - p1;
                    for (int z : base)
                    {
                        if ((p3 >> (z * 2)) & 1)
                        {
                            bool aa = (bool)a.erase(z * 2);
                            if(!aa){
                                a.insert(z * 2);
                            }
                        }
                        if ((p3 >> (z * 2 + 1)) & 1)
                        {
                            bool aa = (bool)a.erase(z * 2 + 1);
                            if(!aa){
                                a.insert(z * 2 + 1);
                            }
                        }
                    }
                    //cout << ans_nu << endl;
                    p1 = p4;
                }
                if(ans_ <= ans && flags)
                {
                    ans = ans_;
                    copy(answer.begin(),answer.end(),back_inserter(answer2));
                }
                for(int o : answer){
                    cout << o << " ";
                }
                cout << endl;
                answer.clear();
                a.clear();
                count++;
            }
        }
    }
    cout << "m = " << ans << endl;
    unsigned long long j = 0;
    for(int i : answer2){
        //cout << i << " " ;
        out(seed_bit[i]);
        j = (j | seed_bit[i]);
    }
    for(int i = 0; i < 26; i++){
        if((j >> (i * 2))&1){
            cout << "1 ";
        }else{
            cout << "0 ";
        }
        if((j >> (i * 2 + 1))&1){
            cout << "1" << endl;
        }else{
            cout << "0" << endl;
        }
    }
}
*/

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
