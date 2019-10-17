#include<bits/stdc++.h>
using namespace std;
char mp[7][7]={
"001100",
"001200",
"212121",
"121222",
"002100",
"001200"
};
char add[7][7]={
"001000",
"002000",
"01ab10",
"20cd20",
"000100",
"002200"
};
bool vis[16][1048576];
struct node{
    char a[6][6];
    int lock,step,pre,cz;
};
int getstate(node &p){
    int c=0,r=0;
    for(int i=0;i<6;++i){
        for(int j=0;j<6;++j){
            if(p.a[i][j]>49){
                r|=(1<<c);
            }
            if(p.a[i][j]>48)++c;
        }
    }
    return r;
}
bool check(node &p){
    if(p.lock<15)return false;
    for(int i=0;i<6;++i){
        for(int j=0;j<6;++j){
            if(p.a[i][j]==50)return false;
        }
    }
    return true;
}
int xx[5]={-1,0,0,0,1};
int yy[5]={0,-1,0,1,0};
int main(){
    vector<node> q;
    int ss=0;
    node st;
    for(int i=0;i<6;++i)for(int j=0;j<6;++j)st.a[i][j]=mp[i][j];
    st.step=0;
    st.pre=st.cz=-1;
    st.lock=0;
    q.push_back(st);
    while(ss<q.size()){
        node now=q[ss];
        for(int i=0;i<6;++i){
            for(int j=0;j<6;++j){
                if(now.a[i][j]==48)continue;
                if((i==2||i==3)&&(j==2||j==3)&&(now.lock&(1<<(add[i][j]-'a')))==0)continue;
                node ch=now;
                for(int k=0;k<5;++k){
                    if(add[i][j]=='1'&&(k==0||k==4)||add[i][j]=='2'&&(k==1||k==3))continue;
                    if((i+xx[k]==2||i+xx[k]==3)&&(j+yy[k]==2||j+yy[k]==3)&&(now.lock&(1<<(add[i+xx[k]][j+yy[k]]-'a')))==0){
                        ch.lock|=(1<<(add[i+xx[k]][j+yy[k]]-'a'));
                    }else{
                        if(ch.a[i+xx[k]][j+yy[k]]=='1')ch.a[i+xx[k]][j+yy[k]]='2';
                        else if(ch.a[i+xx[k]][j+yy[k]]=='2')ch.a[i+xx[k]][j+yy[k]]='1';
                    }
                }
                int id=getstate(ch);
                ch.cz=i*6+j;
                ch.pre=ss;
                ++ch.step;
                if(!vis[ch.lock][id]){
                    vis[ch.lock][id]=true;
                    q.push_back(ch);
                    if(check(ch))goto en;
                }
            }
        }
        ++ss;
    }
    en:
    int now=q.size()-1;
    do{
        printf("%d %d\n",q[now].cz/6+1,q[now].cz%6+1);
        now=q[now].pre;
    }while(q[now].pre!=-1);
    return 0;
}
