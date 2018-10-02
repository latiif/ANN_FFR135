[xTrain, tTrain, xValid, tValid, xTest, tTest] = LoadMNIST(1);

mean = calculateMean(xTrain);

imshow(reshape(xTrain(:,9000) - mean, [28 28]));

