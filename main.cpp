#include<bits/stdc++.h>
using namespace std;

int n;
char seed[1010][30] = {0}; //種
int que[1010][2][30] = {0}; //種.toInt
bool mem[30] = {0}; //trueの場合使ってはいけない

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

vector<int> base,base_;
vector<int> seed_;
vector<int> box[30][3];
unsigned long long seed_bit[3000] = {0};
const int INF = 30000;
map< unsigned long long , int > pattern;

void hunachi() {
    cout << "hunachi" << endl;
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

    cout << "bit_b" << endl;
    for (int i = 0; i < seed_.size(); ++i) {
        for (int j = 0; j < 26; ++j) {
            if (que[seed_[i]][0][j] && que[seed_[i]][1][j]) {
                seed_bit[i] = ((seed_bit[i])|(3<<(j*2)));
                box[j][2].push_back(i);
            } else if (que[seed_[i]][0][j]) {
                seed_bit[i] = ((seed_bit[i])|(1 << (j * 2)));
                box[j][0].push_back(i);
            } else if (que[seed_[i]][1][j]) {
                seed_bit[i] = ((seed_bit[i])|(1 << (j * 2 + 1)));
                box[j][1].push_back(i);
            }
        }
        //printf("%llu\n",seed_bit[i]);
    }
    cout << seed_.size()<< "saizu" << endl;
}

int f_ezn( unsigned long long now , int before ) {

    cout << "f_zen0" << endl;

    bool flag = true;
    int ans = INF;
    if(before > seed_.size()){
        return INF;
    }
    auto c = pattern.find(now);
    cout << endl << pattern[now] << endl;
    if(pattern.end() != c){
        cout << "used = " << now << endl;
        return pattern[now];
    }

    cout << "f_zen1" << endl;

    if(now != (unsigned long long)0) {
        for (int i = 0; i < 26; ++i) {
            bool a = (bool) ((now >> (i * 2)) & (unsigned long long) 1);
            bool b = (bool) ((now >> (i * 2 + 1)) & (unsigned long long) 1);
            cout << a << " " << b << endl;
            if (a != b) {
                flag = false;
                break;
            }
            //cout << "f_zen2" << endl;
        }
    }else{
        flag = false;
    }
    if (flag) {
        pattern[now] = 1;
        return 1;
    }
    cout << "f_zen3" << now << endl;
    int b = INF;//f_ezn(now, before + 1);
    for(int  i = (before); i < seed_.size(); ++i ){
        cout << "f_zen4" << endl;
        unsigned long long sel_next = (now | seed_bit[i]);
        if(sel_next == now) {
            continue;
        }
        //auto che = pattern.find(sel_next);
        //if(che != pattern.end()) {
            int a = f_ezn(sel_next, before + 1);
            printf("%d\n",i);
            ans = min(a, b);
            if (ans == a) {
                cout << ans << endl;
                pattern[now] = ans;
            }
        //}
    }
    cout << "f_zen5" << endl;
    return ans;
}

void check(int score){
    cout << "check" << endl;
    int sco = score;
    unsigned long long a = 0,save = 0;
    for(int i = 0; i < seed_.size(); ++i){
        auto c = pattern.find(seed_bit[seed_[i]]);
        if(c == pattern.end()) {
            continue;
        }
        if(pattern[seed_bit[seed_[i]]] == sco){
            //fir = base[i];
            if(sco == 1){
                printf("%d %d !\n",seed_[i],seed_[i]);
            }
            save = seed_bit[i];
            break;
        }
    }
    sco--;
    while(sco>0) {
        for (int i = 0; i < seed_.size(); ++i) {
            a = (save | seed_bit[i]);
            auto c = pattern.find(seed_bit[seed_[i]]);
            if (c == pattern.end()) {
                continue;
            }
            if (pattern[a] == sco) {
                if(sco == (score-1)){
                    printf("%d",seed_[i]);
                }else{
                    printf("%d %d",seed_[i],(n + score - sco));
                }
                for(int j = 0; j < 26 ; j++){
                    if((save<<(j*2))&1){
                        printf("%c",(char)('A'+j));
                    }
                    if((save<<(j*+1))&1){
                        printf("%c",(char)('a'+j));
                    }
                }
                cout << endl;
                //fir = base[i];
                save = a;
                break;
            }
        }
        sco--;
    }
    if(sco > 1)printf("%d %d !\n",n + score,n + score);
    return;
}

void zentan(){
    cout << "zentan" << endl;
    int a = f_ezn(0, 0);
    if(a==INF){
        cout << "NG" << endl;
        return;
    }
    //cout << a << endl;
    check(a);
    return;
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
        cout << "go" << endl;
        zentan();
        cout << "fin" << endl;
    }



    return 0;
}
