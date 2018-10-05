
[xTrain, tTrain, xValid, tValid, xTest, tTest] = LoadMNIST(1);

mean = calculateMean(xTrain);
[bits, patterns ] = size(xTrain);
xTrain = xTrain - repmat(mean,[1 patterns]);
shuffleFactor = randperm(size(xTrain,2));
xTrain = xTrain(:,shuffleFactor);
tTrain = tTrain(:,shuffleFactor);


%%TODO remove mean from all datasets

sigmoid  = @(x) 1.0 ./ ( 1.0 + exp(-x));



network = Network([784 30 10],0.3,sigmoid);

f = waitbar(0,"Init");
batch = 1;
batchSize = 5;

for t  = 1:(50000/batchSize)-1
    waitbar(t/(50000/batchSize),f,"Training batch " + t);
    network.train(xTrain(:,batch:batch+batchSize),tTrain(:,batch:batch+batchSize),batchSize);
    batch = t * batchSize;
end
close(f)

correct = 0;
for p = 1:50000
    if (network.checkGuess(xTrain(:,p),tTrain(:,p)))
        correct = correct +1;
    end
end

disp(correct);