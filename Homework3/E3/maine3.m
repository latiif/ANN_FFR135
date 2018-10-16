[xTrain, tTrain, xValid, tValid, xTest, tTest] = LoadMNIST(3);

n1 = [ ...
    imageInputLayer([28 28 1])
    fullyConnectedLayer(100)
    reluLayer
    fullyConnectedLayer(100)
    reluLayer
    fullyConnectedLayer(10)
    softmaxLayer
    classificationLayer
];

options = trainingOptions('sgdm', ...
    'Momentum',0.9,...
    'InitialLearnRate',0.01, ...
    'MaxEpochs',200, ...
    'Shuffle','every-epoch', ...
    'ValidationData',{xValid,tValid}, ...
    'ValidationFrequency',30, ...
    'ValidationPatience',5,...
    'Verbose',false, ...
    'MiniBatchSize',8192, ...
    'Plots','training-progress');

net = trainNetwork(xTrain,tTrain,n1,options);


disp("Train Classification Error")
sum((abs(grp2idx(net.classify(xTrain))-grp2idx(tTrain))))/(size(tTrain,1)*2)

disp("Validation Classification Error")
sum((abs(grp2idx(net.classify(xValid))-grp2idx(tValid))))/(size(tValid,1)*2)

disp("Test Classification Error")
sum((abs(grp2idx(net.classify(xTest))-grp2idx(tTest))))/(size(tTest,1)*2)


