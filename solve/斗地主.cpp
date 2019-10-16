#include<bits/stdc++.h>
using namespace std;
#define NOD 40000000
//3-17
int typen[15]={0,1,1,1,1,1,2,2,2,2,2,1,0};
struct out{
    int type,a,b,c,d;
    //0  =0
    //1  =1  a
    //2  =2  a
    //3  =3  a
    //4  =3+1  a  b
    //5  =3+2  a  b
    //6  =1/  a  b
    //7  =2/  a  b
    //8  =3/  a  b
    //9  =3*2+1+1  a  b  c  d
    //10  =3*2+2+2  a  b  c  d
    //11  =4  a
    //12  =w*2
};
struct node{
    short a[2],id;
    short x[2][18];
    out pre;
    bool operator < (const node &p) const{
        if(id!=p.id)return id<p.id;
        if(a[0]!=p.a[0])return a[0]<p.a[0];
        if(a[1]!=p.a[1])return a[1]<p.a[1];
        for(int i=3;i<18;i++)if(x[0][i]!=p.x[0][i])return x[0][i]<p.x[0][i];
        for(int i=3;i<18;i++)if(x[1][i]!=p.x[1][i])return x[1][i]<p.x[1][i];
        if(pre.type!=p.pre.type)return pre.type<p.pre.type;
        if(typen[pre.type]>0 && pre.a!=p.pre.a)return pre.a<p.pre.a;
        if(typen[pre.type]>1 && pre.b!=p.pre.b)return pre.a<p.pre.b;
        return false;
    }
//    void out(){
//        printf("id=%d pre:type=%d %d %d %d %d\n",id,pre.type,pre.a,pre.b,pre.c,pre.d);
//        for(int i=0;i<2;i++){
//            printf("%d:",a[i]);
//            for(int j=3;j<18;j++)printf("%d ",x[i][j]);
//            printf("\n");
//        }
//    }
};
int check(node &pd){
    if(pd.a[0]==0 || pd.a[1]==0)return true;
    return false;
}
map<node,int> ma;
vector<node> ve;
queue<int> qu,qu2;
vector<int> ee[NOD];
vector<out> edge[NOD];
int cnt=1;
int sg[NOD];
//int dfs(int x){
//    int len[NOD]={0};
////    printf("dfs x=%d\n",x);
//    if(x==-1)return 0;
//    if(x==0)return 1;
//    if(sg[x]>-1)return sg[x];
//    int sz=ee[x].size();
////    printf("size=%d\n",sz);
//    for(int i=0;i<sz;i++){
//        cal[i]=dfs(ee[x][i]);
//        len[cal[i]]=1;
//    }
////    for(int i=0;i<sz;i++)printf("%d ",ee[x][i]);
////    printf("\n");
////    for(int i=0;i<sz;i++)printf("%d ",cal[i]);
////    sort(cal,cal+sz);
//    for(int i=0;;i++){
//        if(!len[i]){
//            sg[x]=i;
//            break;
//        }
//    }
////    printf("sg[%d]=%d\n",x,sg[x]);
//    return sg[x];
//}
int dfs(int x,int tt){
    if(x==-1)return 0;
    if(x==0)return 1;
//    for(int j=0;j<tt;j++)printf(" ");
//    printf("sg[%d]=%d\n",x,sg[x]);
    if(sg[x]>-1)return sg[x];
    int sz=ee[x].size();
//    for(int j=0;j<tt;j++)printf(" ");
//    printf("x=%d sz=%d\n",x,sz);
    if(ve[x].id==0){
        sg[x]=0;
        for(int i=0;i<sz;i++){
//            for(int j=0;j<tt;j++)printf(" ");
//            printf("i=%d a=%d sz=%d\n",i,ee[x][i],sz);
            if(dfs(ee[x][i],tt+1)==1){
                sg[x]=1;
            }
//            for(int j=0;j<tt;j++)printf(" ");
//            printf("i=%d a=%d sz=%d\n",i,ee[x][i],sz);
        }
//        for(int j=0;j<tt;j++)printf(" ");
//        printf("i=-- a=-- sz=%d\n",sz);
    }else{
        sg[x]=1;
        for(int i=0;i<sz;i++){
//            for(int j=0;j<tt;j++)printf(" ");
//            printf("i=%d a=%d sz=%d\n",i,ee[x][i],sz);
            if(dfs(ee[x][i],tt+1)==0){
                sg[x]=0;
            }
//            for(int j=0;j<tt;j++)printf(" ");
//            printf("i=%d a=%d sz=%d\n",i,ee[x][i],sz);
        }
    }
//    for(int j=0;j<tt;j++)printf(" ");
//    printf("sg[%d]=%d\n",x,sg[x]);
    return sg[x];
}
int main(){
    memset(sg,-1,sizeof(sg));
    node ss;
    memset(ss.x,0,sizeof(ss.x));
    int in;
    scanf("%d",&ss.a[0]);
    for(int i=0;i<ss.a[0];i++){
        scanf("%d",&in);
        ss.x[0][in]++;
    }
    scanf("%d",&ss.a[1]);
    for(int i=0;i<ss.a[1];i++){
        scanf("%d",&in);
        ss.x[1][in]++;
    }
    ss.pre.type=-1;
    ss.id=0;
    printf("start\n");
//    ss.out();

    ma[ss]=1;
    ve.push_back(ss);
    ve.push_back(ss);
    qu.push(1);
    while(!qu.empty()){
        int idd=qu.front();
        qu.pop();
        node now=ve[idd];

//        printf("idd=%d\n",idd);
//        now.out();

        int cc=0;
        if(now.pre.type<=0 || now.pre.type==1){
//            printf("cal:type1\n");
//            now.out();
            if(now.pre.type<=0)now.pre.a=2;
            for(int i=now.pre.a+1;i<18;i++){
                if(!now.x[now.id][i])continue;
                node add=now;
                add.x[now.id][i]--;
                add.a[now.id]--;
                add.pre.type=1;
                add.pre.a=i;
                add.id^=1;
                cc++;
                if(check(add)){
                    if(now.id==0){
                        edge[idd].push_back(add.pre);
                        ee[idd].push_back(0);
                    }else{
                        edge[idd].push_back(add.pre);
                        ee[idd].push_back(-1);
                    }
                    continue;
                }
                int pos=ma[add];
                if(!pos){
                    ma[add]=++cnt;
                    ve.push_back(add);
                    qu.push(cnt);
                    pos=cnt;
                }
                edge[idd].push_back(add.pre);
                ee[idd].push_back(pos);
            }
        }
        if(now.pre.type<=0 || now.pre.type==2){
//            printf("cal:type2\n");
//            now.out();
            if(now.pre.type<=0)now.pre.a=2;
            for(int i=now.pre.a+1;i<16;i++){
                if(now.x[now.id][i]<2)continue;
                node add=now;
                add.x[now.id][i]-=2;
                add.a[now.id]-=2;
                add.pre.type=2;
                add.pre.a=i;
                add.id^=1;
                cc++;
                if(check(add)){
                    if(now.id==0){
                        edge[idd].push_back(add.pre);
                        ee[idd].push_back(0);
                    }else{
                        edge[idd].push_back(add.pre);
                        ee[idd].push_back(-1);
                    }
                    continue;
                }
                int pos=ma[add];
                if(!pos){
                    ma[add]=++cnt;
                    ve.push_back(add);
                    qu.push(cnt);
                    pos=cnt;
                }
                edge[idd].push_back(add.pre);
                ee[idd].push_back(pos);
            }
        }
        if(now.pre.type<=0 || now.pre.type==3){
//            printf("cal:type3\n");
//            now.out();
            if(now.pre.type<=0)now.pre.a=2;
            for(int i=now.pre.a+1;i<16;i++){
                if(now.x[now.id][i]<3)continue;
                node add=now;
                add.x[now.id][i]-=3;
                add.a[now.id]-=3;
                add.pre.type=3;
                add.pre.a=i;
                add.id^=1;
                cc++;
                if(check(add)){
                    if(now.id==0){
                        edge[idd].push_back(add.pre);
                        ee[idd].push_back(0);
                    }else{
                        edge[idd].push_back(add.pre);
                        ee[idd].push_back(-1);
                    }
                    continue;
                }
                int pos=ma[add];
                if(!pos){
                    ma[add]=++cnt;
                    ve.push_back(add);
                    qu.push(cnt);
                    pos=cnt;
                }
                edge[idd].push_back(add.pre);
                ee[idd].push_back(pos);
            }
        }
        if(now.pre.type<=0 || now.pre.type==4){
//            printf("cal:type4\n");
//            now.out();
            if(now.pre.type<=0)now.pre.a=2;
            for(int i=now.pre.a+1;i<16;i++){
//                printf("i=%d x=%d\n",i,now.x[now.id][i]);
                if(now.x[now.id][i]<3)continue;
                for(int j=3;j<18;j++){
//                    printf("j=%d\n",j);
                    if(now.x[now.id][j]<1 || j==i)continue;
                    node add=now;
                    add.x[now.id][i]-=3;
                    add.x[now.id][j]--;
                    add.a[now.id]-=4;
                    add.pre.type=4;
                    add.pre.a=i;
                    add.pre.b=j;
                    add.id^=1;
                    cc++;
                    if(check(add)){
                        if(now.id==0){
                            edge[idd].push_back(add.pre);
                            ee[idd].push_back(0);
                        }else{
                            edge[idd].push_back(add.pre);
                            ee[idd].push_back(-1);
                        }
                        continue;
                    }
                    int pos=ma[add];
                    if(!pos){
                        ma[add]=++cnt;
                        ve.push_back(add);
                        qu.push(cnt);
                        pos=cnt;
                    }
                    edge[idd].push_back(add.pre);
                    ee[idd].push_back(pos);
                }
            }
        }
        if(now.pre.type<=0 || now.pre.type==5){
//            printf("cal:type5\n");
            if(now.pre.type<=0)now.pre.a=2;
            for(int i=now.pre.a+1;i<16;i++){
                if(now.x[now.id][i]<3)continue;
                for(int j=3;j<18;j++){
                    if(now.x[now.id][j]<2 || j==i)continue;
                    node add=now;
                    add.x[now.id][i]-=3;
                    add.x[now.id][j]-=2;
                    add.a[now.id]-=5;
                    add.pre.type=5;
                    add.pre.a=i;
                    add.pre.b=j;
                    add.id^=1;
                    cc++;
                    if(check(add)){
                        if(now.id==0){
                            edge[idd].push_back(add.pre);
                            ee[idd].push_back(0);
                        }else{
                            edge[idd].push_back(add.pre);
                            ee[idd].push_back(-1);
                        }
                        continue;
                    }
                    int pos=ma[add];
                    if(!pos){
                        ma[add]=++cnt;
                        ve.push_back(add);
                        qu.push(cnt);
                        pos=cnt;
                    }
                    edge[idd].push_back(add.pre);
                    ee[idd].push_back(pos);
                }
            }
        }
        if(now.pre.type<=0 || now.pre.type==6){
            if(now.pre.type<=0){
                for(int i=3;i<11;i++){
                    for(int j=5;i+j-1<15;j++){
                        bool pd=true;
                        for(int k=i;k<i+j;k++)if(now.x[now.id][k]<1){pd=false;break;}
                        if(pd){
                            node add=now;
                            for(int k=i;k<i+j;k++)add.x[now.id][k]--;
                            add.a[now.id]-=j;
                            add.pre.type=6;
                            add.pre.a=i;
                            add.pre.b=j;
                            add.id^=1;
                            if(check(add)){
                                if(now.id==0){
                                    edge[idd].push_back(add.pre);
                                    ee[idd].push_back(0);
                                }else{
                                    edge[idd].push_back(add.pre);
                                    ee[idd].push_back(-1);
                                }
                                continue;
                            }
                            int pos=ma[add];
                            if(!pos){
                                ma[add]=++cnt;
                                ve.push_back(add);
                                qu.push(cnt);
                                pos=cnt;
                            }
                            edge[idd].push_back(add.pre);
                            ee[idd].push_back(pos);
                        }
                    }
                }
            }else{
                for(int i=now.pre.a+1;i<11;i++){
                    int j=now.pre.b;
                    if(i+j-1>=15)break;
                    bool pd=true;
                    for(int k=i;k<i+j;k++)if(now.x[now.id][k]<1){pd=false;break;}
                    if(pd){
                        node add=now;
                        for(int k=i;k<i+j;k++)add.x[now.id][k]--;
                        add.a[now.id]-=j;
                        add.pre.type=6;
                        add.pre.a=i;
                        add.pre.b=j;
                        add.id^=1;
                        if(check(add)){
                            if(now.id==0){
                                edge[idd].push_back(add.pre);
                                ee[idd].push_back(0);
                            }else{
                                edge[idd].push_back(add.pre);
                                ee[idd].push_back(-1);
                            }
                            continue;
                        }
                        int pos=ma[add];
                        if(!pos){
                            ma[add]=++cnt;
                            ve.push_back(add);
                            qu.push(cnt);
                            pos=cnt;
                        }
                        edge[idd].push_back(add.pre);
                        ee[idd].push_back(pos);
                    }
                }
            }
        }
        if(now.x[now.id][16]&&now.x[now.id][17]){
            node add=now;
            add.pre.type=7;
            add.id^=1;
            add.x[now.id][16]--;
            add.x[now.id][17]--;
            add.a[now.id]-=2;
            if(check(add)){
                if(now.id==0){
                    edge[idd].push_back(add.pre);
                    ee[idd].push_back(0);
                }else{
                    edge[idd].push_back(add.pre);
                    ee[idd].push_back(-1);
                }
                continue;
            }
            int pos=ma[add];
            if(!pos){
                ma[add]=++cnt;
                ve.push_back(add);
                qu.push(cnt);
                pos=cnt;
            }
            edge[idd].push_back(add.pre);
            ee[idd].push_back(pos);
        }
        if(now.pre.type>0)
        {
            node add=now;
            add.pre.type=0;
            add.id^=1;
            int pos=ma[add];
            if(!pos){
                ma[add]=++cnt;
                ve.push_back(add);
                qu.push(cnt);
                pos=cnt;
            }
            edge[idd].push_back(add.pre);
            ee[idd].push_back(pos);
        }
    }
    printf("cnt=%d\n",cnt);
    dfs(1,0);
    printf("%d\n",sg[1]);
//    for(int i=1;i<=cnt;i++){
//        printf("i=%d\n",i);
//        ve[i].out();
//    }
//    for(int i=1;i<=cnt;i++){
//        for(int j=0;j<ee[i].size();j++){
//            printf("%d %d\n",i,ee[i][j]);
//        }
//    }
//    sg[-1]=1;
//    sg[0]=0;
//    for(int i=1;i<15000;i++){
//        printf("%d ",sg[i]);
//    }
    while(1){
        int ff;
        scanf("%d",&ff);
        printf("sg=%d\n",sg[ff]);
        int sz=ee[ff].size();
        for(int i=0;i<sz;i++){
            printf("x=%d sg=%d type=%d %d %d\n",ee[ff][i],sg[ee[ff][i]],edge[ff][i].type,edge[ff][i].a,edge[ff][i].b);
        }
    }
    return 0;
}
/*
3
3 3 4
3
5 5 6
8
3 6 7 7 9 9 13 17
4
6 11 15 15
10
3 3 6 8 9 10 11 12 12 14
13
4 5 6 8 9 9 10 10 11 11 12 13 17
*/
