
[xTrain, tTrain, xValid, tValid, xTest, tTest] = LoadMNIST(1);

mean = calculateMean(xTrain);
[bits, patterns ] = size(xTrain);
xTrain = xTrain - repmat(mean,[1 patterns]);
xTrain = xTrain(:,randperm(size(xTrain,2)));

%%TODO remove mean from all datasets

sigmoid  = @(x) 1.0 ./ ( 1.0 + exp(-x));

network.predict(xTrain(:,55))

network = Network([784 30 10],0.3,sigmoid);


network.train(xTrain(:,51:60),tTrain(:,51:60),10);

network.predict(xTrain(:,55))
imshow(reshape(xTrain(:,55), [28 28]));