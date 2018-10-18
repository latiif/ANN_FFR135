
[xTrain, tTrain, xValid, tValid, xTest, tTest] = LoadMNIST(1);

mean = calculateMean(xTrain);
[bits, patterns ] = size(xTrain);

xTrain = xTrain - repmat(mean,[1 patterns]);
xValid = xValid - repmat(mean,[1 size(xValid,2)]);
xTest = xTest - repmat(mean, [1 size(xTest,2)]);

shuffleFactor = randperm(size(xTrain,2));
xTrain = xTrain(:,shuffleFactor);
tTrain = tTrain(:,shuffleFactor);


%%TODO remove mean from all datasets

sigmoid  = @(x) 1.0 ./ ( 1.0 + exp(-x));


        
parpool(4)
parfor i = 0:3
    
    if i==0
        NetworkTrain(Network([784 10],0.3,sigmoid),30,10,xTrain,tTrain,xValid,tValid,xTest,tTest);
    end
    
    if i==1
        NetworkTrain(Network([784 30 10],0.3,sigmoid),30,10,xTrain,tTrain,xValid,tValid,xTest,tTest);
    end
    
    if i==2
        NetworkTrain(Network([784 100 10],0.3,sigmoid),30,10,xTrain,tTrain,xValid,tValid,xTest,tTest);
    end
    
    if i==3
        NetworkTrain(Network([784 100 100 10],0.3,sigmoid),30,10,xTrain,tTrain,xValid,tValid,xTest,tTest);
    end
end





