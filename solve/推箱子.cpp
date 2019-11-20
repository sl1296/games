#include<bits/stdc++.h>
using namespace std;
char mp[20][20]={
"#########",
"###.A.###",
"#.A.X.A.#",
"#.#AXA#.#",
"#.X.#.X.#",
"###.S.###",
"#########"
};
const int x=7,y=9,b=4;
struct point{
    int x,y;
    bool operator< (const point &p) const{
        if(x!=p.x)return x<p.x;
        return y<p.y;
    }
};
struct node{
    point box[b];
    int x,y,pre;
    char op;
    bool operator< (const node &p) const{
        for(int i=0;i<b;++i){
            if(box[i].x!=p.box[i].x)return box[i].x<p.box[i].x;
            if(box[i].y!=p.box[i].y)return box[i].y<p.box[i].y;
        }
        if(x!=p.x)return x<p.x;
        return y<p.y;
    }
    bool check(){
        if(mp[x][y]!='A')return false;
        for(int i=0;i<b;i++)if(mp[box[i].x][box[i].y]!='A')return false;
        return true;
    }
};
map<node,bool> vis;
int xx[4]={0,0,-1,1};
int yy[4]={-1,1,0,0};
char zz[5]="LRUD";
int main(){
    node st;
    int c=0;
    st.pre=-1;
    st.op=0;
    for(int i=0;i<x;++i){
        for(int j=0;j<y;++j){
            if(mp[i][j]=='S'){
                st.x=i;
                st.y=j;
                mp[i][j]='.';
            }else if(mp[i][j]=='X'){
                st.box[c].x=i;
                st.box[c].y=j;
                c++;
                mp[i][j]='.';
            }
        }
    }
    vector<node> q;
    int s=0;
    q.push_back(st);
    vis[st]=true;
    while(s<q.size()){
        st=q[s++];
        for(int i=0;i<4;++i){
            int tx=st.x+xx[i];
            int ty=st.y+yy[i];
            if(mp[tx][ty]=='#')continue;
            int sel=-1;
            for(int j=0;j<b;j++){
                if(st.box[j].x==tx&&st.box[j].y==ty){
                    sel=j;
                    break;
                }
            }
            if(sel==-1){
                node add=st;
                add.x=tx;
                add.y=ty;
                if(!vis[add]){
                    vis[add]=true;
                    add.pre=s-1;
                    add.op=zz[i];
                    q.push_back(add);
                    if(add.check())goto en;
                }
            }else{
                int ttx=tx+xx[i];
                int tty=ty+yy[i];
                if(mp[ttx][tty]=='#')continue;
                int wa=-1;
                for(int j=0;j<b;j++){
                    if(st.box[j].x==ttx&&st.box[j].y==tty){
                        wa=j;
                        break;
                    }
                }
                if(wa!=-1)continue;
                node add=st;
                add.box[sel].x=ttx;
                add.box[sel].y=tty;
                add.x=tx;
                add.y=ty;
                sort(add.box,add.box+b);
                if(!vis[add]){
                    vis[add]=true;
                    add.pre=s-1;
                    add.op=zz[i];
                    q.push_back(add);
                    if(add.check())goto en;
                }
            }
        }
    }
    en:
    string ret="";
    int now=q.size()-1;
    while(1){
        if(now==0)break;
        ret=q[now].op+ret;
        now=q[now].pre;
    }
    printf("%s\n",ret.c_str());
    return 0;
}
