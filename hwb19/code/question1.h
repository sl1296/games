//生成问题1(1)(2)的数据用于正确性检验
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
//根据问题1(1)的条件计算星敏感器方向，其中s1,s2,s3为三个导航星方向，a1,a2,a3,f为已知条件
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
//根据问题1(2)的条件计算星敏感器方向，其中s1,s2,s3为三个导航星方向，a1,a2,a3为已知条件
inline StarMap calp12(StarMap s1,StarMap s2,StarMap s3,double a1,double a2,double a3){
    if(a2<a1){swap(a2,a1);swap(s2,s1);}
    if(a2<a3){swap(a2,a3);swap(s2,s3);}
    if(a1<a3){swap(a1,a3);swap(s1,s3);}
    StarMap ret;
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
    double e=xsum;ret=calp11(s1,s2,s3,a1,a2,a3,f1);
    double bpcmd=b+c*d;
    ret.ew+=atan(1/bpcmd)*xsum;
    ret.ns+=atan(d/sqrt(bpcmd*bpcmd+1))*xsum;
    return ret;
}
