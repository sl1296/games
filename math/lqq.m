hm = [3,5,9];
a = 0;
b = 3;
for i=1:3
    N = (b-a)*hm(i);
    x = linspace(a,b,N+1);
    y = x;
    h = 1/hm(i);
    y(1) = 100;
    for j=2:N+1
        y(j) = y(j-1)+(-8*y(j-1)-40*(3*exp(-x(j-1)/8)-1))*h;
    end
    y
    subplot(2,2,i)
    plot(x,y);
    subplot(2,2,i)
    title(['m=1/',num2str(hm(i))])
end