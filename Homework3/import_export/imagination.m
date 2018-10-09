dir()
w = ["wt/w1.csv" "wt/w2.csv" "wt/w3.csv"];
t = ["wt/t1.csv" "wt/t2.csv" "wt/t3.csv"];

n = loadnetwork(w,t,2);


SIZE = 2000;
x = linspace(-1,1,SIZE);
y = linspace(-1,1,SIZE);
res = zeros(SIZE,SIZE);

c = 1;
r = 1;
for i=x
    for j=y
        g = n.predict([i;j]);
        %if (g>0) 
         %   g = 1;
        %else
        %    g = 0;
        %end
        res(r,c) = 1/(1+exp(-g));
        
        c=c+1;
    end
    
    r=r+1;
    c=1;
end

imshow(res);