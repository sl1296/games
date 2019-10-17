#include<bits/stdc++.h>
using namespace std;
char mp[8][8]={
    "0222000",
    "2022200",
    "2222200",
    "0220200",
    "0220200",
    "0000000",
    "0000000"
};
char add[8][8]={
    "..t....",
    ".......",
    "+++++..",
    "..t....",
    ".t..t..",
    ".......",
    "......."
};
int bh[8][8];
int cx[18],cy[18],ccx[18][18],cn[18];
bool vis[10][10];
int xx[5]={-1,0,0,0,1};
int yy[5]={0,-1,0,1,0};
void dfs(int x,int y,int id,bool hv){
    vis[x][y]=true;
    ccx[id][cn[id]++]=bh[x][y];
    if(hv)
    for(int i=0;i<5;++i){
        if(add[x][y]=='1'&&(i==1||i==3)||add[x][y]=='-'&&(i==0||i==4))continue;
        int tx=x+xx[i];
        int ty=y+yy[i];
        if(tx<0||tx>6||ty<0||ty>6||vis[tx][ty]||(mp[tx][ty]!='1'&&mp[tx][ty]!='2'))continue;
        dfs(tx,ty,id,(add[tx][ty]=='+'));
    }
}
int main(){
    int c=0;
    bool now[18],cal[18];
    for(int i=0;i<7;++i){
        for(int j=0;j<7;++j){
            if(mp[i][j]!='0'){
                cx[c]=i;
                cy[c]=j;
                now[c]=(mp[i][j]=='2');
                bh[i][j]=c;
                ++c;
            }
        }
    }
    c=0;
    for(int i=0;i<7;++i){
        for(int j=0;j<7;++j){
            if(mp[i][j]!='0'){
                memset(vis,false,sizeof(vis));
                dfs(i,j,c,true);
                ++c;
            }
        }
    }
    for(int i=0;i<18;++i){
        ccx[i][cn[i]++]=17;
        ccx[i][cn[i]++]=15;
        ccx[i][cn[i]++]=13;
        ccx[i][cn[i]++]=1;
        sort(ccx[i],ccx[i]+cn[i]);
        cn[i]=unique(ccx[i],ccx[i]+cn[i])-ccx[i];
    }
    printf("c=%d\n",c);
    for(int i=0;i<18;++i){
        printf("i=%d n=%d\n",i,cn[i]);
        for(int j=0;j<cn[i];++j)printf("%d ",ccx[i][j]);
        printf("\n");
    }
    int mx=1e7,ff;
    for(int i=0;i<(1<<18);++i){
        if(i%1000000==0)printf("i=%d\n",i);
        for(int j=0;j<18;++j)cal[j]=now[j];
        int cnt=0;
        for(int j=0;j<18;++j){
            if(i&(1<<j)){
                for(int k=0;k<cn[j];++k){
                    cal[ccx[j][k]]=!cal[ccx[j][k]];
                }
                ++cnt;
            }
        }
        bool ch=true;
        for(int j=0;j<18;++j)if(cal[j]){ch=false;break;}
        if(ch && cnt<mx){
            mx=cnt;
            ff=i;
            printf("mx=%d\n",mx);
        }
    }
    c=0;
    for(int i=0;i<7;++i){
        for(int j=0;j<7;++j){
            if(mp[i][j]>48){
                if(ff&(1<<c))printf("%d %d\n",i+1,j+1);
                ++c;
            }
        }
    }
}
