function [t,y]=odeEuler(diffeq,t0,tn,h,y0)
t=(t0:h:tn)';
n=length(t);
y=y0*ones(n,1);
for j=2:n
    y(j)=y(j-1)+h*feval(diffeq,t(j-1),y(j-1));
end