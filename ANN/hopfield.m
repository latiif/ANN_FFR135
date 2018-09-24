A = zeros(4,4);

p1 = [1 -1 -1 1];

P = [p1];

% MEMORIZE PATTERN

[m,n] = size(P);
for k = 1:m
    p = P(k,:);
    for i = 1:4
        for j = 1:4
           if i==j 
               A(i,j) = 0;
               continue
           end 
           A(i,j) = p(i) * p(j);
        end
    end
end

question = [-1 -1 -1 -1];
output = zeros(1,4);


for i = 1:4
    if (dot(A(i,:),  question)>=0)
        output(i)=1;
    else
        output(i)=-1;
    end
end