act = @(x) tanh(x);

T = csvread("training_set.csv");
V = csvread("validation_set.csv");

n = Network([2 20 10 1],0.008,act);


for t = 1:10000
    mu = randi([1 10000]);
    n.train([T(mu,1) T(mu,2)].', T(mu,3));
end


count = 0;
for v = 1:5000
    guess = n.predict([V(v,1) V(v,2)].');
    if (guess == V(v,3))
        count = count +1;
    end
   
end

imagineX = linspace(-1,1,100);
imagineY= linspace(-1,1,100);
guesses = zeros(10000);

c = 1;
for i  = imagineX
    for j = imagineY
        
        guess = n.predict([i j].');
        if (guess == 1)
            guesses(c) = 10;
            
        else
            guesses(c) = 1;
          
        end
        
        c=  c+1;
    end
end

scatter([imagineX imagineY],[imagineX imagineY], guesses);

disp(count)