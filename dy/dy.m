a=linspace(0,2*pi,14)
x=cos(a);
y=sin(a);
for i=1:14
    plot(x(i),y(i),'o')
    hold on
    x(13+i)=x(i);
    y(13+i)=y(i);
end
x
y
for i=1:14
    for j=i:14
        if j-i==1 || j-i==5 || i+13-j==1 || i+13-j==5
            plot([x(i),x(j)],[y(i),y(j)],'r')
        else
            plot([x(i),x(j)],[y(i),y(j)],'b')
        end
    end
end
axis equal