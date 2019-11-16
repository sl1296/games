function sum=aaa(ut)
sum=0;
for i=1:10000
    u=ut;
    a=exprnd(5,1000,1);
    b=chi2rnd(6,1000,1);
    for j=1:1000
        u=u+2*a(j)-b(j);
        if u<0
            sum=sum+1;
            break;
        end
    end
end