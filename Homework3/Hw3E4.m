[xTrain, tTrain, xValid, tValid, xTest, tTest] = LoadMNIST(3);


layers = [
    imageInputLayer([28 28 1])
    convolution2dLayer(5,20,'Padding',1,'Stride',1)
    reluLayer
    maxPooling2dLayer(2,'Stride',2,'Padding',0)
    fullyConnectedLayer(100)
    reluLayer
    fullyConnectedLayer(10)
    softmaxLayer
    classificationLayer];

options = trainingOptions('sgdm',...
    'Momentum',0.9,...
    'MaxEpochs',60, ...
    'MiniBatchSize',8192, ...
    'InitialLearnRate',0.001, ...
    'ValidationPatience',5,...
    'ValidationFrequency',30, ...
    'Shuffle','every-epoch', ...
    'ValidationData',{xValid,tValid}, ...
     'Plots','training-progress');
 
 net = trainNetwork(xTrain,tTrain,layers,options);


disp("Train Classification Error")
sum((abs(grp2idx(net.classify(xTrain))-grp2idx(tTrain))))/(size(tTrain,1)*2)

disp("Validation Classification Error")
sum((abs(grp2idx(net.classify(xValid))-grp2idx(tValid))))/(size(tValid,1)*2)

disp("Test Classification Error")
sum((abs(grp2idx(net.classify(xTest))-grp2idx(tTest))))/(size(tTest,1)*2)
