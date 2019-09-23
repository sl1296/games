#include<bits/stdc++.h>
using namespace std;
#define N 4908
#define PN 12041778
const double PI=3.1415926535897932;
double f1,f2;
struct StarZB;
struct Position;
const double CH=PI/30.0;
const double PI2=PI*2;
const double ANG1=PI/15.0;
const double ANG2=PI/9.0;
double avg=0;
inline double argdis(double a,double b){
    double tmp=a-b,tmp1=tmp+PI2,tmp2=tmp-PI2;
    return min(fabs(tmp),min(fabs(tmp1),fabs(tmp2)));
}
struct StarMap{
    double ew,ns,l;
    StarZB toZB();
    Position toPosition();
    bool check(StarMap& p){
        if(fabs(p.ns-ns)>CH||argdis(p.ew,ew)>CH)return false;
        return true;
    }
    void printfx(){
        printf("StarMap:ew=%f %f ns=%f %f l=%f\n",ew,ew*180/PI,ns,ns*180/PI,l);
    }
};
StarMap mp[N];
double ang[N][N];
struct StarZB{
    double x,y,z;
    StarMap toMap(){
        StarMap ret;
        ret.ew=atan2(y,x);
        if(ret.ew<0)ret.ew+=PI2;
        ret.ns=asin(z/sqrt(x*x+y*y+z*z));
        return ret;
    }
    double multi(StarZB& a){
        return x*a.x+y*a.y+z*a.z;
    }
    void printfx(){
        printf("StarZB:x=%f y=%f z=%f\n",x,y,z);
    }
};
StarZB StarMap::toZB(){
    StarZB ret;
    double tmp=cos(ns);
    ret.x=cos(ew)*tmp;
    ret.y=sin(ew)*tmp;
    ret.z=sin(ns);
    return ret;
}
struct StarImg{
    double x,y;
    double dis() const{return sqrt(x*x+y*y);}
    bool operator < (const StarImg &p) const{
        return dis()<p.dis();
    }
    double pdis(StarImg& p){
        double tx=p.x-x,ty=p.y-y;
        return sqrt(tx*tx+ty*ty);
    }
    void printfx(){
        printf("StarImg:x=%f y=%f %f\n",x,y,dis());
    }
};
StarImg xt[10][50];
int cxt[10];
struct Position{
    double ew,ns,rot;
    void printfx(){
        printf("Position:ew=%f ns=%f rot=%f\n",ew,ns,rot);
    }
};
Position StarMap::toPosition(){
    Position ret;
    ret.ew=ew;
    ret.ns=ns;
    ret.rot=0;
    return ret;
}
struct PointPair{
    int a,b;
    double ang;
    PointPair(int a=0,int b=0,double ang=0):a(a),b(b),ang(ang){}
    bool operator < (const PointPair &p) const{
        return ang<p.ang;
    }
    void printfx(){
        printf("PointPair:a=%d b=%d ang=%f\n",a,b,ang);
    }
};
PointPair pp[PN],angsort[N][N];
inline void read_map(){
    FILE *fp=fopen("star_data.txt","r");
    for(int i=0;i<N;++i){
        fscanf(fp,"%*d%lf%lf%lf",&mp[i].ew,&mp[i].ns,&mp[i].l);
        avg+=pow(2.5,-mp[i].l);
        mp[i].ew=mp[i].ew*PI/180.0;
        mp[i].ns=mp[i].ns*PI/180.0;
    }
    avg/=N;
    fclose(fp);
}
inline void read_xt(){
    char fn[50]="xt0?.txt";
    for(int i=1;i<9;++i){
        fn[3]=i+48;
        FILE *fp=fopen(fn,"r");
        while(~fscanf(fp,"%*s%lf%lf",&xt[i][cxt[i]].x,&xt[i][cxt[i]].y)){
            double dec=i<7?256.5:512.5;
            xt[i][cxt[i]].x-=dec;
            xt[i][cxt[i]].y-=dec;
            ++cxt[i];
        }
        fclose(fp);
    }
}
inline void initf(){
    f1=256.0/tan(ANG1);
    f2=512.0/tan(ANG2);
}
inline StarImg mtoi(StarMap s,Position p,double f){
    double sinns=sin(p.ns),cosns=cos(p.ns);
    double sinrot=sin(p.rot),cosrot=cos(p.rot);
    double dec=s.ew-p.ew,sindec=sin(dec),cosdec=cos(dec);
    double sinv=sin(s.ns),cosv=cos(s.ns);
    double x=sinrot*cosns*sinv+cosv*(cosrot*sindec-sinns*cosdec*sinrot);
    double y=cosrot*cosns*sinv-cosv*(sinrot*sindec+sinns*cosdec*cosrot);
    double z=cosv*cosdec*cosns+sinns*sinv;
    StarImg ret;
    ret.x=f*x/z;
    ret.y=f*y/z;
    return ret;
}
inline StarMap itox(StarImg x,double f){
    StarZB r;
    r.z=f;
    r.x=x.x;
    r.y=x.y;
    return r.toMap();
}
inline StarZB xtom(StarMap s,Position p){
    double sinew=sin(p.ew),cosew=cos(p.ew);
    double sinns=sin(p.ns),cosns=cos(p.ns);
    double sinadd=sin(p.rot+s.ew),cosadd=cos(p.rot+s.ew);
    double sinv=sin(s.ns),cosv=cos(s.ns);
    StarZB ret;
    ret.x=(-sinns*sinadd*cosew-sinew*cosadd)*cosv+cosew*cosns*sinv;
    ret.y=(-sinns*sinadd*sinew+cosew*cosadd)*cosv+sinew*cosns*sinv;
    ret.z=cosv*sinadd*cosns+sinns*sinv;
    return ret;
}
inline double imgang(StarImg a,StarImg b){
    double ret=acos((a.x*b.x+a.y*b.y)/(a.dis()*b.dis()));
    if(a.x*b.y-a.y*b.x>0){
        ret=-ret;
    }
    return ret;
}
inline double oang(StarMap s1,StarMap s2){
    StarZB z1=s1.toZB(),z2=s2.toZB();
    return acos(z1.multi(z2));
}
inline void init1(){
    int cnt[N]={0},pn=0;
    for(int i=0;i<N;++i){
        for(int j=i+1;j<N;++j){
            ang[j][i]=ang[i][j]=oang(mp[i],mp[j]);
            pp[pn++]=PointPair(i,j,ang[i][j]);
            angsort[i][cnt[i]++]=PointPair(i,j,ang[i][j]);
            angsort[j][cnt[j]++]=PointPair(j,i,ang[i][j]);
        }
    }
    sort(pp,pp+PN);
    for(int i=0;i<N;++i){
        sort(angsort[i],angsort[i]+N-1);
    }
}
inline void save1(){
    FILE *fp=fopen("data.xx","wb");
    fwrite(ang,sizeof(ang),1,fp);
    fwrite(angsort,sizeof(angsort),1,fp);
    fwrite(pp,sizeof(pp),1,fp);
    fclose(fp);
}
inline void read1(){
    FILE *fp=fopen("data.xx","rb");
    fread(ang,sizeof(ang),1,fp);
    fread(angsort,sizeof(angsort),1,fp);
    fread(pp,sizeof(pp),1,fp);
    fclose(fp);
}
inline void makep1(StarMap& s1,StarMap& s2,StarMap& s3,double& a1,double& a2,double& a3,StarMap& ret){
    int mx,id,a,b,c;
    do{
        id=rand()%N;
        mx=upper_bound(angsort[id],angsort[id]+N-1,PointPair(0,0,CH))-angsort[id];
    }while(mx<4);
    do{
        a=rand()%(mx-1)+1;
        b=rand()%(mx-1)+1;
        c=rand()%(mx-1)+1;
    }while(a==b||a==c||b==c);
    s1=mp[angsort[id][a].b];
    s2=mp[angsort[id][b].b];
    s3=mp[angsort[id][c].b];
    ret=mp[id];
    Position p;
    p.ew=ret.ew;
    p.ns=ret.ns;
    p.rot=0.0;
    StarImg x1=mtoi(s1,p,f1);
    StarImg x2=mtoi(s2,p,f1);
    StarImg x3=mtoi(s3,p,f1);
    a1=x1.dis();
    a2=x2.dis();
    a3=x3.dis();
}
inline StarMap calp11(StarMap s1,StarMap s2,StarMap s3,double a1,double a2,double a3,double f){
    StarZB z1=s1.toZB(),z2=s2.toZB(),z3=s3.toZB(),zz;
    double c1=sqrt(a1*a1+f*f);
    double c2=sqrt(a2*a2+f*f);
    double c3=sqrt(a3*a3+f*f);
    zz.x=f*(c1*c2*z1.y*z2.z-c1*c2*z2.y*z1.z-c1*c3*z1.y*z3.z+c1*c3*z3.y*z1.z+c2*c3*z2.y*z3.z-c2*c3*z3.y*z2.z);
    zz.y=-f*(c1*c2*z1.x*z2.z-c1*c2*z2.x*z1.z-c1*c3*z1.x*z3.z+c1*c3*z3.x*z1.z+c2*c3*z2.x*z3.z-c2*c3*z3.x*z2.z);
    zz.z=f*(c1*c2*z1.x*z2.y-c1*c2*z2.x*z1.y-c1*c3*z1.x*z3.y+c1*c3*z3.x*z1.y+c2*c3*z2.x*z3.y-c2*c3*z3.x*z2.y);
    if(zz.x*z1.x+zz.y*z1.y+zz.z*z1.z<0)zz.x=-zz.x,zz.y=-zz.y,zz.z=-zz.z;
    return zz.toMap();
}
/*
inline StarMap calp12(StarMap s1,StarMap s2,StarMap s3,double a1,double a2,double a3){
    if(a2<a1){swap(a2,a1);swap(s2,s1);}
    if(a2<a3){swap(a2,a3);swap(s2,s3);}
    if(a1<a3){swap(a1,a3);swap(s1,s3);}
    double sin1ew=sin(s1.ew),cos1ew=cos(s1.ew),sin1ns=sin(s1.ns),cos1ns=cos(s1.ns);
    double sin2ew=sin(s2.ew),cos2ew=cos(s2.ew),sin2ns=sin(s2.ns),cos2ns=cos(s2.ns);
    double sin3ew=sin(s3.ew),cos3ew=cos(s3.ew),sin3ns=sin(s3.ns),cos3ns=cos(s3.ns);
    double x1=cos1ew*cos1ns,y1=sin1ew*cos1ns,z1=sin1ns;
    double x2=cos2ew*cos2ns,y2=sin2ew*cos2ns,z2=sin2ns;
    double x3=cos3ew*cos3ns,y3=sin3ew*cos3ns,z3=sin3ns;
    double q21=sqrt(a2*a2-a1*a1),q23=sqrt(a2*a2-a3*a3),q13=sqrt(a1*a1-a3*a3);
    double b=(y3*q23-y1*q21)/(x1*q21-x3*q23);
    double c=(z3*q23-z1*q21)/(x1*q21-x3*q23);
    double d=((y2+x2*b)*q23-(y1+x1*b)*q13)/((z1+x1*c)*q13-(z2+x2*c)*q23);
    StarMap ret;
    double bpcmd=b+c*d;
    ret.ew=atan(1/bpcmd);
    ret.ns=atan(d/sqrt(bpcmd*bpcmd+1));
    return ret;
}
*/
inline void test11(){
//    double mi=0;
    for(int i=0;i<10;++i){
        StarMap s1,s2,s3,ret;
        double a1,a2,a3;
        makep1(s1,s2,s3,a1,a2,a3,ret);
        StarMap ans=calp11(s1,s2,s3,a1,a2,a3,f1);
//        mi=max(mi,fabs(ret.ew-ans.ew));
//        mi=max(mi,fabs(ret.ns-ans.ns));
        printf("ret:%f %f\n",ret.ew,ret.ns);
        printf("ans:%f %f\n",ans.ew,ans.ns);
    }
//    printf("%.16f\n",mi);
    /*
    0.0000000000244161
    0.0000000000101150
    0.0000000000081682
    0.0000000000952647
    */
}
inline Position cal2_f1(StarImg* xt,int len,const double& f){
    double eps=1e-2;
    StarMap zb[50];
    sort(xt,xt+len);
    for(int i=0;i<len;++i)zb[i]=itox(xt[i],f);
    vector<vector<int> > ans,next;
    vector<int> tmp;
    double angx=oang(zb[0],zb[1]);
    int fid=lower_bound(pp,pp+PN,PointPair(0,0,angx))-pp;
    for(int i=fid;i<PN&&pp[i].ang-angx<eps;++i){
        tmp.clear();
        tmp.push_back(pp[i].a);
        tmp.push_back(pp[i].b);
        ans.push_back(tmp);
    }
    for(int i=fid-1;i>=0&&angx-pp[i].ang<eps;--i){
        tmp.clear();
        tmp.push_back(pp[i].a);
        tmp.push_back(pp[i].b);
        ans.push_back(tmp);
    }
    printf("size=%d\n",ans.size());
    double anga=oang(zb[0],zb[2]),angb=oang(zb[1],zb[2]);
    for(int i=0;i<ans.size();++i){
        int pa=ans[i][0],pb=ans[i][1];
        int fid=lower_bound(angsort[pa],angsort[pa]+N-1,PointPair(0,0,anga))-angsort[pa];
        for(int j=fid;j<N-1&&fabs(angsort[pa][j].ang-anga)<eps;++j){
            int add=angsort[pa][j].b;
            if(fabs(ang[add][pb]-angb)<eps){
                next.push_back(ans[i]);
                next.back().push_back(add);
            }
        }
        for(int j=fid-1;j>=0&&fabs(angsort[pa][j].ang-anga)<eps;--j){
            int add=angsort[pa][j].b;
            if(fabs(ang[add][pb]-angb)<eps){
                next.push_back(ans[i]);
                next.back().push_back(add);
            }
        }
    }
    printf("size=%d\n",next.size());
    ans=next;
    next.clear();
//    for(int i=0;i<ans.size();++i){
//        for(int j=0;j<3;++j){
//            printf("%d ",ans[i][j]);
//        }
//        printf("\n");
//    }
}
inline Position cal2_f2(StarImg* xt,int len,const double& f){
    double eps=1e-2;
    StarMap zb[50];
//    sort(xt,xt+len);
    for(int i=0;i<len;++i)zb[i]=itox(xt[i],f);
    vector<vector<int> > ans,next;
    vector<int> tmp;
    double angx=oang(zb[0],zb[1]);
    int fid=lower_bound(pp,pp+PN,PointPair(0,0,angx))-pp;
    for(int i=fid;i<PN&&pp[i].ang-angx<eps;++i){
        tmp.clear();
        tmp.push_back(pp[i].a);
        tmp.push_back(pp[i].b);
        ans.push_back(tmp);
    }
    for(int i=fid-1;i>=0&&angx-pp[i].ang<eps;--i){
        tmp.clear();
        tmp.push_back(pp[i].a);
        tmp.push_back(pp[i].b);
        ans.push_back(tmp);
    }
    printf("size=%d\n",ans.size());
    for(int z=2;z<len;++z){
        double angy[50];
        for(int i=0;i<z;++i)angy[i]=oang(zb[i],zb[z]);
        for(int i=0;i<ans.size();++i){
            int pa=ans[i][0];
            int fid=lower_bound(angsort[pa],angsort[pa]+N-1,PointPair(0,0,angy[0]))-angsort[pa];
            for(int j=fid;j<N-1&&fabs(angsort[pa][j].ang-angy[0])<eps;++j){
                int add=angsort[pa][j].b;
                bool check=true;
                for(int c=1;c<z;++c){
                    if(fabs(ang[add][ans[i][c]]-angy[c])>=eps){
                        check=false;
                        break;
                    }
                }
                if(check){
                    next.push_back(ans[i]);
                    next.back().push_back(add);
                }
            }
            for(int j=fid-1;j>=0&&fabs(angsort[pa][j].ang-angy[0])<eps;--j){
                int add=angsort[pa][j].b;
                int c=1;
                bool check=true;
                for(int c=1;c<z;++c){
                    if(fabs(ang[add][ans[i][c]]-angy[c])>=eps){
                        check=false;
                        break;
                    }
                }
                if(check){
                    next.push_back(ans[i]);
                    next.back().push_back(add);
                }
            }
        }
        printf("size=%d\n",next.size());
        ans=next;
        next.clear();
    }
    for(int i=0;i<ans.size();++i){
        for(int j=0;j<len;++j){
            printf("%d ",ans[i][j]);
        }
        printf("\n");
    }
}
inline Position cal2_f3(StarImg* xt,int len,const double& f){
    double eps=1e-3,eps2=1e-3;
    StarMap zb[50];
//    sort(xt,xt+len);
    for(int i=0;i<len;++i)zb[i]=itox(xt[i],f);
    vector<vector<int> > ret;
    for(int aa=0;aa<len;++aa)for(int bb=aa+1;bb<len;++bb)for(int cc=bb+1;cc<len;++cc){
        vector<vector<int> > ans,next;
        vector<int> tmp;
        double angx=oang(zb[aa],zb[bb]);
        int fid=lower_bound(pp,pp+PN,PointPair(0,0,angx))-pp;
        for(int i=fid;i<PN&&pp[i].ang-angx<eps;++i){
            tmp.clear();
            tmp.push_back(pp[i].a);
            tmp.push_back(pp[i].b);
            ans.push_back(tmp);
        }
        for(int i=fid-1;i>=0&&angx-pp[i].ang<eps;--i){
            tmp.clear();
            tmp.push_back(pp[i].a);
            tmp.push_back(pp[i].b);
            ans.push_back(tmp);
        }
        double anga=oang(zb[aa],zb[cc]),angb=oang(zb[bb],zb[cc]);
        for(int i=0;i<ans.size();++i){
            int pa=ans[i][0],pb=ans[i][1];
            int fid=lower_bound(angsort[pa],angsort[pa]+N-1,PointPair(0,0,anga))-angsort[pa];
            for(int j=fid;j<N-1&&fabs(angsort[pa][j].ang-anga)<eps;++j){
                int add=angsort[pa][j].b;
                if(fabs(ang[add][pb]-angb)<eps){
                    next.push_back(ans[i]);
                    next.back().push_back(add);
                    next.back().push_back(aa);
                    next.back().push_back(bb);
                    next.back().push_back(cc);
                }
            }
            for(int j=fid-1;j>=0&&fabs(angsort[pa][j].ang-anga)<eps;--j){
                int add=angsort[pa][j].b;
                if(fabs(ang[add][pb]-angb)<eps){
                    next.push_back(ans[i]);
                    next.back().push_back(add);
                    next.back().push_back(aa);
                    next.back().push_back(bb);
                    next.back().push_back(cc);
                }
            }
        }
        ans=next;
        next.clear();
//        printf("add=%d\n",ans.size());
        for(int i=0;i<ans.size();++i)ret.push_back(ans[i]);
        ans.clear();
    }
    printf("size=%d\n",ret.size());
    vector<double> val;
    val.resize(ret.size());
    int choose[50],chnow[50];
    double wc[50],wcnow[50];
    double eval2=1e100;
    int eval=-1,err=0;
    for(int i=0;i<ret.size();++i){
        if(i%1000==0)printf("i=%d\n",i);
        double enow2=0;
        int enow=0;
        int ta=ret[i][0],tb=ret[i][1],tc=ret[i][2];
        int aa=ret[i][3],bb=ret[i][4],cc=ret[i][5];
        Position ret=calp11(mp[ta],mp[tb],mp[tc],xt[aa].dis(),xt[bb].dis(),xt[cc].dis(),f).toPosition();
        StarImg p1=mtoi(mp[ta],ret,f);
        StarImg p2=mtoi(mp[tb],ret,f);
        StarImg p3=mtoi(mp[tc],ret,f);
        double rg1=imgang(p1,xt[aa]);
        double rg2=imgang(p2,xt[bb]);
        double rg3=imgang(p3,xt[cc]);
        if(argdis(rg1,rg2)>CH||argdis(rg1,rg3)>CH||argdis(rg2,rg3)>CH){
            ++err;
            continue;
        }
//        printf("%f %f %f\n",rg1,rg2,rg3);
//        printf("%f\n",ret.rot);
//        p1.printfx();
//        p2.printfx();
//        p3.printfx();
//        xt[aa].printfx();
//        xt[bb].printfx();
//        xt[cc].printfx();
        ret.rot=(rg1+rg2+rg3)/3;
        val[i]=0;
//        printf("%d %d %d\n",ta,tb,tc);
//        mp[ta].printfx();
//        mp[tb].printfx();
//        mp[tc].printfx();
        for(int j=0;j<len;++j){
            StarMap xx=itox(xt[j],f);
            xx=xtom(xx,ret).toMap();
//            xx.printfx();
            wcnow[j]=1e100;
            chnow[j]=-1;
            for(int k=0;k<N;++k){
                if(xx.check(mp[k])){
                    double now=oang(xx,mp[k]);
                    if(now<wcnow[j])wcnow[j]=now,chnow[j]=k;
                }
            }
            if(wcnow[j]<eps2)enow2=max(enow2,wcnow[j]);
            if(wcnow[j]<eps2)++enow;
        }
//        if(enow<eval){
        if(enow>eval||enow==eval&&enow2<eval2){
            eval=enow;
            eval2=enow2;
            for(int j=0;j<len;++j)choose[j]=chnow[j],wc[j]=wcnow[j];
        }
    }
    printf("err=%d\ncnt=%d val=%f\n",err,eval,eval2);
    for(int i=0;i<len;++i){
        printf("%d %f\n",choose[i],wc[i]);
    }
}
struct VAL{
    double pperr,sa,sb,dis[50],sfc;
    int fail;
    int id[50];
    Position ret;
    int cc;
    vector<StarImg> pic;
    vector<int> picid;
    vector<bool> picbj;
    bool operator < (const VAL &p) const{
        if(fail!=p.fail)return fail<p.fail;
        return sb<p.sb;
//        return sa*5+sb*3+fail<p.sa*5+p.sb*3+p.fail;
    }
};
vector<VAL> val;
inline bool cmpf4(int a,int b){
    return val[a]<val[b];
}
inline Position cal2_f4(StarImg* xt,int len,const double& f,const double& fang,const double& eps2,const double& djx,const double& bjp){
    double eps=0.001;
    StarMap zb[50];
//    sort(xt,xt+len);
    for(int i=0;i<len;++i)zb[i]=itox(xt[i],f);
    vector<vector<int> > ret;
    for(int aa=0;aa<len;++aa)for(int bb=aa+1;bb<len;++bb)for(int cc=bb+1;cc<len;++cc){
        vector<vector<int> > ans,next;
        vector<int> tmp;
        double angx=oang(zb[aa],zb[bb]);
        int fid=lower_bound(pp,pp+PN,PointPair(0,0,angx))-pp;
        for(int i=fid;i<PN&&pp[i].ang-angx<eps;++i){
            tmp.clear();
            tmp.push_back(pp[i].a);
            tmp.push_back(pp[i].b);
            ans.push_back(tmp);
        }
        for(int i=fid-1;i>=0&&angx-pp[i].ang<eps;--i){
            tmp.clear();
            tmp.push_back(pp[i].a);
            tmp.push_back(pp[i].b);
            ans.push_back(tmp);
        }
        double anga=oang(zb[aa],zb[cc]),angb=oang(zb[bb],zb[cc]);
        for(int i=0;i<ans.size();++i){
            int pa=ans[i][0],pb=ans[i][1];
            int fid=lower_bound(angsort[pa],angsort[pa]+N-1,PointPair(0,0,anga))-angsort[pa];
            for(int j=fid;j<N-1&&fabs(angsort[pa][j].ang-anga)<eps;++j){
                int add=angsort[pa][j].b;
                if(fabs(ang[add][pb]-angb)<eps){
                    next.push_back(ans[i]);
                    next.back().push_back(add);
                    next.back().push_back(aa);
                    next.back().push_back(bb);
                    next.back().push_back(cc);
                }
            }
            for(int j=fid-1;j>=0&&fabs(angsort[pa][j].ang-anga)<eps;--j){
                int add=angsort[pa][j].b;
                if(fabs(ang[add][pb]-angb)<eps){
                    next.push_back(ans[i]);
                    next.back().push_back(add);
                    next.back().push_back(aa);
                    next.back().push_back(bb);
                    next.back().push_back(cc);
                }
            }
        }
        ans=next;
        next.clear();
//        printf("add=%d\n",ans.size());
        for(int i=0;i<ans.size();++i)ret.push_back(ans[i]);
        ans.clear();
    }
    printf("size=%d\n",ret.size());
    return Position();
    int err=0;
    vector<StarImg> pic;
    vector<int> picid;
    vector<bool> picbj;
    val.resize(ret.size());
    vector<int> pxx;
    double tsavg=0;
    int tscnt=0;
    for(int i=0;i<ret.size();++i){
//        if(i%1000==0)printf("i=%d\n",i);
        int ta=ret[i][0],tb=ret[i][1],tc=ret[i][2];
        int aa=ret[i][3],bb=ret[i][4],cc=ret[i][5];
        Position ret=calp11(mp[ta],mp[tb],mp[tc],xt[aa].dis(),xt[bb].dis(),xt[cc].dis(),f).toPosition();
        StarImg p1=mtoi(mp[ta],ret,f);
        StarImg p2=mtoi(mp[tb],ret,f);
        StarImg p3=mtoi(mp[tc],ret,f);
        double rg1=imgang(p1,xt[aa]);
        double rg2=imgang(p2,xt[bb]);
        double rg3=imgang(p3,xt[cc]);
        if(argdis(rg1,rg2)>CH||argdis(rg1,rg3)>CH||argdis(rg2,rg3)>CH){
            ++err;
            continue;
        }
        pxx.push_back(i);
        ret.rot=(rg1+rg2+rg3)/3;
        int xlen=lower_bound(angsort[ta],angsort[ta]+N-1,PointPair(0,0,fang))-angsort[ta];
        pic.resize(xlen);
        picid.resize(xlen);
        picbj.resize(xlen);
        cc=0;
        for(int j=0;j<xlen;++j){
            picid[cc]=angsort[ta][j].b;
            pic[cc]=mtoi(mp[picid[cc]],ret,f);
            if(pic[cc].x>=-bjp&&pic[cc].x<=bjp&&pic[cc].y>=-bjp&&pic[cc].y<=bjp)picbj[cc]=false,++cc;
//            else printf("%f %f\n",pic[cc].x,pic[cc].y);
        }
        val[i].cc=cc;
        val[i].pic=pic;
        val[i].picid=picid;
        val[i].fail=0;
        val[i].pperr=1e100;
        val[i].sa=0;
        val[i].sb=0;
        val[i].ret=ret;
        for(int k=0;k<len;++k){
            double mx=1e100;
            int mid=-1;
            for(int j=0;j<cc;++j){
                if(picbj[j])continue;
                double td=pic[j].pdis(xt[k]);
                if(td<mx){
                    mx=td;
                    mid=j;
                }
            }
            tsavg+=mx;
            tscnt++;
            if(mx<eps2){
                picbj[mid]=true;
                val[i].id[k]=picid[mid];
                val[i].dis[k]=mx;
                val[i].sb+=pow(2.5,-mp[picid[mid]].l)*mx/djx;
            }else{
                val[i].pperr=min(val[i].pperr,mx);
                val[i].id[k]=-1;
                val[i].fail++;
                val[i].sb+=avg;
            }
        }
        val[i].picbj=picbj;
        val[i].sfc=0;
        for(int j=0;j<len;++j)val[i].sfc+=(val[i].dis[j]-val[i].sa/len)*(val[i].dis[j]-val[i].sa/len);
        for(int j=0;j<cc;++j){
            if(!picbj[j]&&pic[j].x>=-bjp+51.5&&pic[j].x<=bjp-51.5&&pic[j].y>=-bjp+51.5&&pic[j].y<=bjp-51.5){
                val[i].sb+=pow(2.5,-mp[picid[j]].l);
            }
        }
    }
    tsavg/=tscnt;
    printf("err=%d tsavg=%.16f\n",err,tsavg);
    sort(pxx.begin(),pxx.end(),cmpf4);
    for(int i=0;i<1;++i){
        printf("%f %f %f %d\n",val[pxx[i]].sb,val[pxx[i]].sa,val[pxx[i]].sfc,val[pxx[i]].fail);
        for(int j=0;j<len;++j){
            printf("%d %f %f\n",val[pxx[i]].id[j],val[pxx[i]].dis[j],mp[val[pxx[i]].id[j]].l);
        }
        printf("dir:%f %f %f\n",val[pxx[i]].ret.ew,val[pxx[i]].ret.ns,val[pxx[i]].ret.rot);
    }
    printf("plot3(0,0,0,'.b')\n");
    printf("hold on\n");
    printf("x=[-%.0f,%.0f;-%.0f,%.0f];\n",bjp-51.5,bjp-51.5,bjp-51.5,bjp-51.5);
    printf("y=[-%.0f,-%.0f;%.0f,%.0f];\n",bjp-51.5,bjp-51.5,bjp-51.5,bjp-51.5);
    printf("z=[%f,%f;%f,%f];\n",f,f,f,f);
    printf("surf(x,y,z)\n",f,f,f,f);
    printf("alpha(0.3)\n",f,f,f,f);
    for(int i=0;i<len;++i){
        printf("plot3(%f,%f,%f,'.b')\n",xt[i].x,xt[i].y,f);
        printf("hold on\n");
        if(val[pxx[0]].id[i]!=-1){
            int ffid=-1;
            for(int j=0;j<val[pxx[0]].cc;++j){
                if(val[pxx[0]].picid[j]==val[pxx[0]].id[i]){
                    ffid=j;
                    break;
                }
            }
            printf("x=linspace(%f,%f,10000);\n",xt[i].x,val[pxx[0]].pic[ffid].x);
            printf("y=linspace(%f,%f,10000);\n",xt[i].y,val[pxx[0]].pic[ffid].y);
            printf("z=linspace(%f,%f,10000);\n",f,f);
            printf("plot3(x,y,z,'b')\n");
            printf("hold on\n");
        }
    }
    for(int i=0;i<val[pxx[0]].cc;++i){
        printf("plot3(%f,%f,%f,'.r','markersize',%f)\n",val[pxx[0]].pic[i].x,val[pxx[0]].pic[i].y,f,13-mp[val[pxx[0]].picid[i]].l);
        printf("hold on\n");
        StarZB tmp;
        tmp.x=val[pxx[0]].pic[i].x;
        tmp.y=val[pxx[0]].pic[i].y;
        tmp.z=f;
        tmp=tmp.toMap().toZB();
        printf("plot3(%f,%f,%f,'.r','markersize',%f)\n",tmp.x*f*3,tmp.y*f*3,tmp.z*f*3,17-mp[val[pxx[0]].picid[i]].l);
        printf("hold on\n");
        if(val[pxx[0]].picbj[i]){
            printf("x=linspace(0,%f,10000);\n",tmp.x*f*3);
            printf("y=linspace(0,%f,10000);\n",tmp.y*f*3);
            printf("z=linspace(0,%f,10000);\n",tmp.z*f*3);
            printf("plot3(x,y,z,'b')\n");
            printf("hold on\n");
        }
    }
    getchar();
}
inline void test2(){
    for(int id=1;id<9;++id){
        printf("id=%d\n",id);
//        cal2_f1(xt[id],cxt[id],id<7?f1:f2);
//        cal2_f2(xt[id],cxt[id],id<7?f1:f2);
//        cal2_f3(xt[id],cxt[id],id<7?f1:f2);
        cal2_f4(xt[id],cxt[id],id<7?f1:f2,id<7?ANG1:ANG2,id<7?50:50,id<7?512*sqrt(2):1024*sqrt(2),id<7?307.5:563.5);
    }
}
int main(){
    read_map();
    read_xt();
    initf();
    init1();
//    save1();
//    read1();
//    test11();
    test2();
    return 0;
}
