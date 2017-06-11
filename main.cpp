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
bool used[3000] = {0},used_[3000] = {0};


void output( int vec[3000] ){
    int i = 1;
    string ans;
    string a,a_;
    a = seed[vec[0]];
    while( vec[i] == -1 ){
        a_ = seed[vec[i]];
        for( int i = 0; i < a.size(); ++i ){
            strcat(ans,a[i]);
        }
        for( int i = 0; i < a_.size(); ++i ){
            strcat(ans,a_[i]);
        }
        //kaburikesu sort
        printf("%d %d %c\n",vec[i-1],vec[i],ans);
    }
    if( i > 1 ){
        printf("%d %d %c\n",n+i,n+i,'!');
    }else{
        printf("%d %d %s\n",vec[0],vec[0],a);
    }
}

void hunachi(){

    for( int i = 0; i < 26 ; ++i ){
        if( mem[i] == 0 ){
            base.push_back(i);
        }else{
            base_.push_back(i);
        }
    }
    for( int i = 0; i < n ; ++i ){
        int flag = true;
        for( int j = 0; j < base_.size(); ++j ){
            if( que[i][0][j] > 0 ){
                flag = false;
            }
        }
        if( flag ){
            seed_.push_back(i);
        }
    }

    for( int i = 0; i < seed_.size() ; ++i ){
        for( int j = 0; j < 26 ; ++j ){
            if( que[seed_[i]][0][j] || que[seed_[i]][1][j] ){
                box[j][2].push_back(i);
            }else if( que[seed_[i]][0][j] ){
                box[j][0].push_back(i);
            }else if( que[seed_[i]][1][j] ){
                box[j][1].push_back(i);
            }
        }
    }
    /*
    int box_count[30] = {0};
    */
    int num_min = seed_.size();
    int cnt = 0;
    //while(1){
        int ans[3000] = {0};
        set<int> small,big,comp;
        for( int i = 0 ; i < 26 ; ++i ){
            if( box[i][2].size() > 0 ){
                //int sel = box[i][2][0];
                small.insert(i);
                while( small.size() || big.size() ){
                    int num = ( small.size() == 0 ) ? small.begin : big.begin();
                    int sel,sel_;
                    bool two = false;
                    if( box[num][2].size() > 0 ){
                        sel = box[num][2][0];
                        ans[cnt] = num;
                        cnt++;
                    }else{
                        two =true;
                        sel = box[num][0][0];
                        ans[cnt] = sel;
                        cnt++;
                        sel_ = box[num][1][0];
                        ans[cnt] = sel;
                        cnt++;
                    }
                    for( int j = 0 ; j < 26 ; ++j ){
                        if( que[sel][0][j] && que[sel][1][j] ){
                            small.erase(j);
                            big.erase(j);
                            comp.insert(j);
                        }else if( que[sel][0][j] ){
                            if( small.erase(j) )continue;
                            small.insert(j);
                        }else if( que[sel][1][j] ){
                            if( big.erase(j) )continue;
                            big.insert(j);
                        }
                    }
                    if( two ){
                        for( int j = 0 ; j < 26 ; ++j ){
                            if( que[sel_][0][j] && que[sel_][1][j] ){
                                small.erase(j);
                                big.erase(j);
                                comp.insert(j);
                            }else if( que[sel_][0][j] ){
                                if( small.erase(j) )continue;
                                small.insert(j);
                            }else if( que[sel_][1][j] ){
                                if( big.erase(j) )continue;
                                big.insert(j);
                            }
                        }
                    }
                }
                comp.clear();
                output(ans);
                cnt = 0;

            }
        }
    //}
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
    }
    return 0;
}
