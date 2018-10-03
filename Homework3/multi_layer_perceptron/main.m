
[xTrain, tTrain, xValid, tValid, xTest, tTest] = LoadMNIST(1);


sigmoid  = @(x) 1/(1+exp(-x));


network = Network([784 30 10],0.3,sigmoid);


network.train(xTrain(:,50:100),tTrain(:,50:100),50);