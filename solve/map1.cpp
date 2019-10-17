#include<bits/stdc++.h>
using namespace std;
char mp[20][20];
char add[20][20];
int dp[3][20][1048576];
pair<int,int> pre[3][20][1048576];
int cz[3][20][1048576];
bool vis[3][20][1048576];
int num[20];
vector<pair<int,int> > from,to;
int x,y;
int oo;
int getstate(int a){
    int ret=0,cc=0;
    for(int i=0;i<2;++i){
        for(int j=0;j<y;++j){
            if(mp[a+i][j]=='2')ret|=(1<<cc),++cc;
            else if(mp[a+i][j]=='1')++cc;
        }
    }
    return ret;
}
void setstate(int a,int b){
    int cc=0;
    for(int i=0;i<2;++i){
        for(int j=0;j<y;++j){
            if(mp[a+i][j]=='1'||mp[a+i][j]=='2')mp[a+i][j]=((b>>cc)&1)+'1',++cc;
        }
    }
}
bool check(int a){
    for(int i=0;i<y;++i){
        if(mp[a][i]=='2'&&add[a][i]!='t')return false;
    }
    return true;
}
int xx[5]={-1,0,0,0,1};
int yy[5]={0,-1,0,1,0};
void run(int a,int b){
    int cc=0;
    for(int i=0;i<y;++i){
        if(mp[a][i]=='1'||mp[a][i]=='2'){
            if((b>>cc)&1){
                bool ch=false;
                for(int j=0;j<5;++j){
                    if(add[a][i]=='h'&&(j==0||j==4)||add[a][i]=='s'&&(j==1||j==3)||add[a+xx[j]][i+yy[j]]=='q'&&j!=2)continue;
                    if(add[a+xx[j]][i+yy[j]]=='t'){
                        if(!ch){
                            if(oo==0){
                                if(mp[a+xx[j]][i+yy[j]]=='1')oo=2;else oo=1;
                            }
                            else if(oo==1)oo=2;
                            else oo=1;
                            ch=true;
                        }
                        continue;
                    }
                    if(mp[a+xx[j]][i+yy[j]]=='1')mp[a+xx[j]][i+yy[j]]='2';
                    else if(mp[a+xx[j]][i+yy[j]]=='2')mp[a+xx[j]][i+yy[j]]='1';
                }
            }
            ++cc;
        }
    }
}
int cnt(int a){
    int r=0;
    while(a){
        if(a&1)++r;
        a>>=1;
    }
    return r;
}
void out(int a,int b){
//    printf("%d %d :",a,b);
    int cc=0,r=0;
    for(int i=0;i<y;++i){
        if(mp[a][i]=='1'||mp[a][i]=='2'){
            if((b>>cc)&1)printf("(%d,%d)",a,i+1),++r;
            ++cc;
        }
    }
    if(r)printf("\n");
}
bool choo;
int main(){
    while(~scanf("%d%d",&x,&y)){
        from.clear();to.clear();
        memset(dp,0,sizeof(dp));
        for(int i=0;i<3;++i)for(int j=0;j<20;++j)for(int k=0;k<1048576;++k)pre[i][j][k]=make_pair(-1,-1);
        memset(cz,0,sizeof(cz));
        memset(vis,false,sizeof(vis));
        memset(mp,0,sizeof(mp));
        memset(num,0,sizeof(num));
        memset(add,0,sizeof(add));
        choo=true;
        for(int i=1;i<=x;++i){
            scanf("%s",mp[i]);
            for(int j=0;j<y;++j){
                if(mp[i][j]=='1'||mp[i][j]=='2'){
                    ++num[i];
                    if(add[i][j]=='t'&&mp[i][j]=='2')choo=false;
                }
            }
        }
        for(int i=1;i<=x;++i){
            scanf("%s",add[i]);
        }
        oo=0;
        int tmp=getstate(0);
        from.push_back(make_pair(0,tmp));
        dp[0][0][tmp]=0;pre[0][0][tmp]=make_pair(-1,-1);
//        printf("tmp=%d\n",tmp);
        for(int i=1;i<=x;++i){
//            printf("i=%d\n",i);
            for(int j=0;j<from.size();++j){
//                printf("j=%d\n",from[j]);
                setstate(i-1,from[j].second);
                oo=from[j].first;
                for(int k=0;k<(1<<num[i]);++k){
//                    printf("op:%d\n",k);
                    run(i,k);
                    if(check(i-1)&&(i<x||(check(i)&&(oo==1||oo==0&&choo)))){
                        tmp=getstate(i);
//                        printf("++ state=%d cnt=%d\n",tmp,k);
                        if(!vis[oo][i][tmp]){
                            vis[oo][i][tmp]=true;
                            to.push_back(make_pair(oo,tmp));
                            dp[oo][i][tmp]=dp[from[j].first][i-1][from[j].second]+cnt(k);
                            pre[oo][i][tmp]=from[j];
                            cz[oo][i][tmp]=k;
//                            printf("%d %d %d %d\n",i,tmp,pre[i][tmp],cz[i][tmp]);
                        }else{
                            if(dp[from[j].first][i-1][from[j].second]+cnt(k)<dp[oo][i][tmp]){
                                dp[oo][i][tmp]=dp[from[j].first][i-1][from[j].second]+cnt(k);
                                pre[oo][i][tmp]=from[j];
                                cz[oo][i][tmp]=k;
//                                printf("%d %d %d %d\n",i,tmp,pre[i][tmp],cz[i][tmp]);
                            }
                        }
                    }
                    run(i,k);
//                    printf("ch:%d\n",cz[2][58]);
                }
            }
            from=to;
            to.clear();
        }
//        printf("ch:%d\n",cz[2][58]);
        int ans=1e7;
        pair<int,int> id;
        for(int i=0;i<from.size();++i){
            if(dp[from[i].first][x][from[i].second]<ans){
                ans=dp[from[i].first][x][from[i].second];
                id=from[i];
            }
        }
        printf("step=%d\n",ans);
        for(int i=x;i;--i){
//            printf("x=%d id=%d\n",x,id);
            out(i,cz[id.first][i][id.second]);
            id=pre[id.first][i][id.second];
        }
    }
    return 0;
}
/*
3
3
122
221
122
*/
