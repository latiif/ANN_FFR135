
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



network = Network([784 100 100 10],0.3,sigmoid);

tEl = animatedline;
vEl = animatedline;



tEl.Color = "green";
vEl.Color = "blue";

axis([1 30 0 0.3])

for epoch = 1:30
    [tE,vE ] = EpochTrain(network,10,xTrain,tTrain,xValid,tValid);

    
    addpoints(tEl,epoch,tE);
    hold on

    addpoints(vEl,epoch,vE);
    hold on
    
    drawnow
    
end

