h=0.01;
F='-1/T^2-Y/T-Y^2'
G='2*Y-3*YA+YB'-'H'*subs(F,{'T','Y'},{'-1/2*TA+3/2*T','-1/2*YA+3/2*Y'})
n=100;
t=zeros(1,n);
y=t;
t(1)=1;
y(1)=-1;
t(2)=1+h;
v=subs(F,{'T','Y'},{t(1),y(1)});
ka=y(1)+v*h;
km=y(1)+v*h/2;
v2=subs(F,{'T','Y'},{t(1)+h/2,km});
kb=km+v2*h/2;
ta=(y(1)+ka)*h/2;
tb=(y(1)+km+km+kb)*h/4;
y(2)=y(1)+(4*tb-ta)/3;
for i=3:n
    t(i)=t(i-1)+h;
    dd=subs(G,{'YA','YB','H','T','TA'},{y(i-1),y(i-2),h,t(i),t(i-1)});
    tmp=vpa(solve(dd,'Y'),16);
    y(i)=tmp(2);
    i
end
plot(t,y)
hold on
