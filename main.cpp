#include<bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
typedef pair<int,pii> pipii;

int n;
char seed[2010][30] = {0};
vector<pii> que[2010];
bool mem[30] = {0};
int updated[2010] = {0};
queue<int> Q;

void solve()
{
    while(1)
    {
        vector<int> need;
        for(int i = 0; i < n; i++)
        {
            if(updated[i] != 1)
            {
                need.push_back(i);
            }
        }
        /*for(int i = 0; i < n; i++)
        {
            printf(" %d\n",updated[i]);
        }*/
        /*for(int i = 0; i < need.size(); i++)
        {
            printf("  %d",need[i]);
        }printf("\n");*/
        vector<int> from[2][30];
        int visit[2010] = {0};
        int sum[2][30] = {0};
        pipii MAX = make_pair(0,make_pair(0,0));
        for(int i = 0; i < need.size(); i++)
        {
            for(int j = 0; j < que[need[i]].size(); j++)
            {
                from[que[need[i]][j].first][que[need[i]][j].second].push_back(need[i]);
                sum[que[need[i]][j].first][que[need[i]][j].second]++;
            }
        }
        /*for(int i = 0; i < 2; i++)
        {
            for(int j = 0; j < 26; j++)
            {
                for(int k = 0; k < from[i][j].size(); k++)
                {
                    printf(" %d",from[i][j][k]);

                }printf("\n");
            }
        }*/
        vector<int> can_erase[2][30];
        for(int i = 0; i < 2; i++)
        {
            for(int j = 0; j < 26; j++)
            {
                if(sum[i][j] == 1)
                {//printf("{%d %d}\n",i,j);
                    int rest[2][30] = {0};
                    Q.push(from[i][j][0]);
                    while(!Q.empty())
                    {
                        int now = Q.front();
                        Q.pop();
                        //printf(" %d",now);
                        if(visit[now] == i * 26 + j + 1)
                        {
                            continue;
                        }
                        visit[now] = i * 26 + j + 1;
                        can_erase[i][j].push_back(now);
                        for(int k = 0; k < que[now].size(); k++)
                        {
                            rest[que[now][k].first][que[now][k].second]++;
                            if(sum[que[now][k].first][que[now][k].second] - rest[que[now][k].first][que[now][k].second] == 0)
                            {
                                for(int l = 0; l < from[(que[now][k].first + 1) % 2][que[now][k].second].size(); l++)
                                {
                                    Q.push(from[(que[now][k].first + 1) % 2][que[now][k].second][l]);
                                }
                            }
                        }
                    }//printf("\n");
                    if(can_erase[i][j].size() == need.size())
                    {
                        updated[from[i][j][0]] = -1;
                    }
                    else if(MAX.first < can_erase[i][j].size())
                    {
                        MAX = make_pair(can_erase[i][j].size(),make_pair(i,j));
                    }
                }
            }
        }
        if(MAX.first == 0)
        {
            for(int i = 0; i < n + 1; i++)
            {
                if(i == n)
                {
                    if(need.size() == 1)
                    {
                        printf("1\n");
                        printf("%d %d !\n",need[0],need[0]);
                        return;
                    }
                    int cross[2][26] = {0};
                    for(int j = 0; j < que[need[0]].size(); j++)
                    {
                        cross[que[need[0]][j].first][que[need[0]][j].second]++;
                    }
                    printf("%d\n",need.size());
                    for(int j = 1; j < need.size() + 1; j++)
                    {
                        if(j == 1)
                        {
                            printf("%d %d ",need[0] + 1,need[1] + 1);
                        }
                        else if(j == need.size())
                        {
                            printf("%d %d !\n",n + need.size() - 1,n + need.size() - 1);
                            continue;
                        }
                        else
                        {
                            printf("%d %d ",n + j - 1,need[j] + 1);
                        }
                        for(int k = 0; k < que[need[j]].size(); k++)
                        {
                            cross[que[need[j]][k].first][que[need[j]][k].second]++;
                        }
                        for(int k = 0; k < 26; k++)
                        {
                            for(int l = 1; l >= 0; l--)
                            {
                                if(cross[l][k] != 0)
                                {
                                    printf("%c",'A' + k + l * ('a' - 'A'));
                                }
                            }
                        }
                        printf("\n");
                    }
                    return;
                }
                if(updated[i] == 0)
                {
                    updated[i] = 1;
                    break;
                }
            }
        }
        else
        {
            for(int i = 0; i < can_erase[MAX.second.first][MAX.second.second].size(); i++)
            {
                updated[can_erase[MAX.second.first][MAX.second.second][i]] = 1;
            }
        }
    }
    return;
}

bool judge()
{
    int kind[2][30] = {0};
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < que[i].size(); j++)
        {
            kind[que[i][j].first][que[i][j].second]++;
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
            if(updated[i] == 1)
            {
                continue;
            }
            for(int j = 0; j < que[i].size(); j++)
            {
                if(mem[que[i][j].second])
                {
                    for(int k = 0; k < que[i].size(); k++)
                    {
                        kind[que[i][k].first][que[i][k].second]--;
                    }
                    updated[i] = 1;
                    break;
                }
            }
        }
    }
    return true;
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
                que[i].push_back(make_pair(0,seed[i][j] - 'A'));
            }
            else
            {
                que[i].push_back(make_pair(1,seed[i][j] - 'a'));
            }
        }
    }
    if(!judge())
    {
        printf("NO\n");
        return 0;
    }
    printf("Yes\n");
    solve();
    /*for(int i = 0; i < n; i++)
    {
        printf(" %d\n",updated[i]);
    }*/
    return 0;
}


/*
2
aAbcC
ab
*/
