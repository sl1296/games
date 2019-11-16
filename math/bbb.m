function sum=bbb(ut,up,tx)
sum=0;
for i=1:10000
    u=ut;
    t=0;
    while 1
        a=exprnd(5);
        b=chi2rnd(6);
        u=u+2*a;
        t=t+a;
        if u>up
            u=up;
        end
        u=u-b;
        if t>tx
            break;
        end
        if u<0
            sum=sum+1;
            break;
        end
    end
end