a=inline('-1/t^2-y/t-y^2','t','y')
[x,y]=odeEuler(a,1,2,0.01,-1)
disp([x,y])
plot(x,y)
hold on