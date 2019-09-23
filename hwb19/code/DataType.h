//数据库中导航星数量
#define N 4908
//导航星夹角数量
#define PN 12041778
//关于PI的常量定义
const double PI=3.1415926535897932;
const double CH=PI/30.0;
const double PI2=PI*2;
const double ANG1=PI/15.0;
const double ANG2=PI/9.0;
//存储xingtu1-6的焦距为f1，星图7-8的焦距为f2
const double f1=256.0/tan(ANG1);
const double f2=512.0/tan(ANG2);
//存储导航星数据库的平均亮度
double avg=0,xsum=0;
//计算两个角度的夹角
inline double argdis(double a,double b){
    double tmp=a-b,tmp1=tmp+PI2,tmp2=tmp-PI2;
    return min(fabs(tmp),min(fabs(tmp1),fabs(tmp2)));
}
struct StarZB;
struct Position;
//导航星方向与亮度信息，使用天球坐标系或星敏感器坐标系
struct StarMap{
    //ew和ns为方向角度，l为星等
    double ew,ns,l;
    //转换到三维方向向量坐标
    StarZB toZB();
    //转换为星敏感器角度信息
    Position toPosition();
    //检验两颗导航星夹角是否足够小
    bool check(StarMap& p){
        if(fabs(p.ns-ns)>CH||argdis(p.ew,ew)>CH)return false;
        return true;
    }
    //用于调试的输出
    void printfx(){
        printf("StarMap:ew=%f %f ns=%f %f l=%f\n",ew,ew*180/PI,ns,ns*180/PI,l);
    }
};
//三维坐标
struct StarZB{
    double x,y,z;
    //转换为方向信息
    StarMap toMap(){
        StarMap ret;
        ret.ew=atan2(y,x);
        if(ret.ew<0)ret.ew+=PI2;
        ret.ns=asin(z/sqrt(x*x+y*y+z*z));
        return ret;
    }
    //向量点乘
    double multi(StarZB& a){
        return x*a.x+y*a.y+z*a.z;
    }
    //用于调试的输出
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
//星敏感器的图像坐标系坐标
struct StarImg{
    double x,y;
    //到原点的距离
    double dis() const{return sqrt(x*x+y*y);}
    //用于以到原点的距离大小关系排序
    bool operator < (const StarImg &p) const{
        return dis()<p.dis();
    }
    //与另一个点的距离
    double pdis(StarImg& p){
        double tx=p.x-x,ty=p.y-y;
        return sqrt(tx*tx+ty*ty);
    }
    //用于调试的输出
    void printfx(){
        printf("StarImg:x=%f y=%f %f\n",x,y,dis());
    }
};
//星敏感器角度信息
struct Position{
    //ew和ns是光轴方向，rot是滚转角
    double ew,ns,rot;
    //用于调试的输出
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
//导航星夹角信息
struct PointPair{
    //两个导航星的编号
    int a,b;
    //夹角角度
    double ang;
    PointPair(int a=0,int b=0,double ang=0):a(a),b(b),ang(ang){}
    //用于按角度大小排序
    bool operator < (const PointPair &p) const{
        return ang<p.ang;
    }
    //用于调试的输出
    void printfx(){
        printf("PointPair:a=%d b=%d ang=%f\n",a,b,ang);
    }
};
