load('¸½¼þ2  ¼òÒ×ÐÇ±í.mat');
file=fopen('star_data.txt','w');
for i=1:4908
    fprintf(file,'%.0f %.16f %.16f %.16f\n',star_data(i,1),star_data(i,2),star_data(i,3),star_data(i,4));
end
fclose(file);