//���ݿ��е���������
#define N 4908
//�����Ǽн�����
#define PN 12041778
//����PI�ĳ�������
const double PI=3.1415926535897932;
const double CH=PI/30.0;
const double PI2=PI*2;
const double ANG1=PI/15.0;
const double ANG2=PI/9.0;
//�洢xingtu1-6�Ľ���Ϊf1����ͼ7-8�Ľ���Ϊf2
const double f1=256.0/tan(ANG1);
const double f2=512.0/tan(ANG2);
//�洢���������ݿ��ƽ������
double avg=0,xsum=0;
//���������Ƕȵļн�
inline double argdis(double a,double b){
    double tmp=a-b,tmp1=tmp+PI2,tmp2=tmp-PI2;
    return min(fabs(tmp),min(fabs(tmp1),fabs(tmp2)));
}
struct StarZB;
struct Position;
//�����Ƿ�����������Ϣ��ʹ����������ϵ��������������ϵ
struct StarMap{
    //ew��nsΪ����Ƕȣ�lΪ�ǵ�
    double ew,ns,l;
    //ת������ά������������
    StarZB toZB();
    //ת��Ϊ���������Ƕ���Ϣ
    Position toPosition();
    //�������ŵ����Ǽн��Ƿ��㹻С
    bool check(StarMap& p){
        if(fabs(p.ns-ns)>CH||argdis(p.ew,ew)>CH)return false;
        return true;
    }
    //���ڵ��Ե����
    void printfx(){
        printf("StarMap:ew=%f %f ns=%f %f l=%f\n",ew,ew*180/PI,ns,ns*180/PI,l);
    }
};
//��ά����
struct StarZB{
    double x,y,z;
    //ת��Ϊ������Ϣ
    StarMap toMap(){
        StarMap ret;
        ret.ew=atan2(y,x);
        if(ret.ew<0)ret.ew+=PI2;
        ret.ns=asin(z/sqrt(x*x+y*y+z*z));
        return ret;
    }
    //�������
    double multi(StarZB& a){
        return x*a.x+y*a.y+z*a.z;
    }
    //���ڵ��Ե����
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
//����������ͼ������ϵ����
struct StarImg{
    double x,y;
    //��ԭ��ľ���
    double dis() const{return sqrt(x*x+y*y);}
    //�����Ե�ԭ��ľ����С��ϵ����
    bool operator < (const StarImg &p) const{
        return dis()<p.dis();
    }
    //����һ����ľ���
    double pdis(StarImg& p){
        double tx=p.x-x,ty=p.y-y;
        return sqrt(tx*tx+ty*ty);
    }
    //���ڵ��Ե����
    void printfx(){
        printf("StarImg:x=%f y=%f %f\n",x,y,dis());
    }
};
//���������Ƕ���Ϣ
struct Position{
    //ew��ns�ǹ��᷽��rot�ǹ�ת��
    double ew,ns,rot;
    //���ڵ��Ե����
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
//�����Ǽн���Ϣ
struct PointPair{
    //���������ǵı��
    int a,b;
    //�нǽǶ�
    double ang;
    PointPair(int a=0,int b=0,double ang=0):a(a),b(b),ang(ang){}
    //���ڰ��Ƕȴ�С����
    bool operator < (const PointPair &p) const{
        return ang<p.ang;
    }
    //���ڵ��Ե����
    void printfx(){
        printf("PointPair:a=%d b=%d ang=%f\n",a,b,ang);
    }
};
