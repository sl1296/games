//存储导航星数据库
StarMap mp[N];
//ang[i][j]表示数据库中第i个导航星与第j个导航星的夹角
double ang[N][N];
//存储xingtu1-8的坐标数据
StarImg xt[10][50];
//存储xingtu1-8的坐标数量
int cxt[10];
//pp存储排序后的数据库中全部夹角，angsort[i]存储排序后的与第i个导航星形成的夹角
PointPair pp[PN],angsort[N][N];
//输入通过matlab转换后的star_data.txt数据库信息
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
//输入通过从xls中复制粘贴后得到的xt0?.txt的星图信息
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
//已知导航星方向信息s，星敏感器方向信息p，星敏感器焦距f，计算导航星在星敏感器图像坐标系中的点坐标
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
//星敏感器图像坐标系转星敏感器坐标系的三维坐标
inline StarMap itox(StarImg x,double f){
    StarZB r;
    r.z=f;
    r.x=x.x;
    r.y=x.y;
    return r.toMap();
}
//已知星敏感器坐标系坐标s，星敏感器方向p，计算导航星在惯性坐标系中的三维坐标
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
//计算图像坐标系中的两点间旋转角
inline double imgang(StarImg a,StarImg b){
    double ret=acos((a.x*b.x+a.y*b.y)/(a.dis()*b.dis()));
    //判定旋转方向
    if(a.x*b.y-a.y*b.x>0){
        ret=-ret;
    }
    return ret;
}
//计算两导航星方向的夹角
inline double oang(StarMap s1,StarMap s2){
    StarZB z1=s1.toZB(),z2=s2.toZB();
    return acos(z1.multi(z2));
}
//根据导航星数据库计算夹角信息与夹角排序信息
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
