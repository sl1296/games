n=100;
f=21;
h=pi/12/f;
A='3';
B='3';
X1='sin(2*T)';
X2='2*cos(3*T)';
X1A='X1/(1+X1^2)';
X2A='X2/(1+X2^2)';
F1=['cos(',A,'*T)-',A,'*sin(',A,'*T)'];
F2=['sin(',B,'*T)-',B,'*cos(',B,'*T)'];
J1='exp(S-T)*(7*X1+3*X2)';
J2='exp(S-T)*(3*X1-X2)';
R1=1/96*(subs(X1A,{'T'},{'T-pi/12'})+sqrt(5)*subs(X2A,{'T'},{'T-pi/12'}))+[F1,'-X1'];
R2=1/96*(sqrt(5)*subs(X1A,{'T'},{'T-pi/12'})-3*subs(X2A,{'T'},{'T-pi/12'}))+[F2,'-X2'];
t=linspace(-pi/12,0,f);
x1=vpa(subs(X1,t));
x2=vpa(subs(X2,t));
j1=vpa(subs(subs(J1,{'X1'},{X1}),{'S','T'},{t,0}));
j2=vpa(subs(subs(J2,{'X2'},{X2}),{'S','T'},{t,0}));
t(f+1)=h;
y0a=-1/4/pi*(sum(j1)-(j1(1)+j1(f))/2)*h;
y0b=-1/4/pi*(sum(j2)-(j2(1)+j2(f))/2)*h;
f0a=vpa(subs(subs(R1,{'X1','X2'},{X1,X2}),{'T'},{0}));
f0b=vpa(subs(subs(R2,{'X1','X2'},{X1,X2}),{'T'},{0}));
prea=sum(j1(2:f))-j1(2)/2;
preb=sum(j2(2:f))-j2(2)/2;
L='-1/4/pi*H*(PRE+JF/2)';
Z='-Y1+Y0+H*(F0+F1)/2';
VA=subs(subs(Z,{'F0','Y0','F1','Y1'},{f0a,y0a,R1,subs(L,{'PRE','JF'},{prea,subs(J1,{'S'},{t(f+1)})})}),{'H','T'},{h,t(f+1)})
VB=subs(subs(Z,{'F0','Y0','F1','Y1'},{f0b,y0b,R2,subs(L,{'PRE','JF'},{prea,subs(J2,{'S'},{t(f+1)})})}),{'H','T'},{h,t(f+1)})
[ra,rb]=solve(VA,VB)
if length(ra)==1
    x1(f+1)=vpa(ra)
else
    x1(f+1)=vpa(ra(1))
end
if length(rb)==1
    x2(f+1)=vpa(rb)
else
    x2(f+1)=vpa(rb(1))
end
G=[L,'-4/3*Y1+1/3*Y0-2/3*H*F'];
for i=f+2:50
    i
    t(i)=t(i-1)+h;
    y0a=-1/4/pi*(sum(j1(i-f-1:i-2))-(j1(i-f-1)+j1(i-2))/2)*h;
    y0b=-1/4/pi*(sum(j2(i-f-1:i-2))-(j2(i-f-1)+j2(i-2))/2)*h;
    y1a=-1/4/pi*(sum(j1(i-f:i-1))-(j1(i-f)+j1(i-1))/2)*h;
    y1b=-1/4/pi*(sum(j2(i-f:i-1))-(j2(i-f)+j2(i-1))/2)*h;
    prea=sum(j1(i-f+1:i-1))-j1(i-f+1)/2;
    preb=sum(j2(i-f+1:i-1))-j2(i-f+1)/2;
    VA=subs(subs(G,{'Y0','Y1','H','F','PRE','JF'},{y0a,y1a,h,R1,prea,subs(J1,{'S'},{t(i)})}),{'T'},{t(i)})
    VB=subs(subs(G,{'Y0','Y1','H','F','PRE','JF'},{y0b,y1b,h,R2,preb,subs(J2,{'S'},{t(i)})}),{'T'},{t(i)})
    [ra,rb]=solve(VA,VB);
    if length(ra)==1
        x1(i)=vpa(ra)
    else
        x1(i)=vpa(ra(1))
    end
    if length(rb)==1
        x2(i)=vpa(rb)
    else
        x2(i)=vpa(rb(1))
    end
    j1(i)=vpa(subs(J1,{'S','T','X1','X2'},{t(i),t(i),x1(i),x2(i)}));
    j2(i)=vpa(subs(J2,{'S','T','X1','X2'},{t(i),t(i),x1(i),x2(i)}));
end
