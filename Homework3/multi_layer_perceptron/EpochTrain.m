function [trainError, validationError] = EpochTrain(network,batchSize,trainingSet,trainingSetTargets,validationSet,validationSetTargets)
    f = waitbar(0,"Init");
    batch = 1;
   
    datasetSize = size(trainingSet,2);

    for t  = 1:(datasetSize/batchSize)-1
        waitbar(t/(datasetSize/batchSize),f,"Training batch " + t);
        network.train(trainingSet(:,batch:batch+batchSize),trainingSetTargets(:,batch:batch+batchSize),batchSize);
        batch = t * batchSize;
    end
    
    waitbar(1,f,"Calculating Train Error");
    
    counter = 0;
    datasetSize = size(trainingSet,2);
    for p = 1:datasetSize
        %%counter = counter + abs( find(network.checkGuess(trainingSet(:,p))==1,1) - find(trainingSetTargets(:,p))==1);
        counter = counter + sum(abs(network.checkGuess(trainingSet(:,p))-trainingSetTargets(:,p)));
    end
    trainError = counter/(2*datasetSize);
    
    
    if (~ isequal(validationSet,[]))
        waitbar(1,f,"Calculating Validation Error");

        counter = 0;
        datasetSize = size(validationSet,2);
        for p = 1:datasetSize
           % counter = counter + abs(find(network.checkGuess(validationSet(:,p))==1,1) - find(validationSetTargets(:,p))==1);
           counter = counter + sum(abs(network.checkGuess(validationSet(:,p))-validationSetTargets(:,p)));
        end
        validationError = (counter)/(2*datasetSize);
    end
    
    
    close(f)

   
end