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
    
    correct = 0;
    datasetSize = size(trainingSet,2);
    for p = 1:datasetSize
        if (network.checkGuess(trainingSet(:,p),trainingSetTargets(:,p)))
            correct = correct +1;
        end
    end
    trainError = (datasetSize - correct)/(2*datasetSize);
    
    
    waitbar(1,f,"Calculating Validation Error");
    
    correct = 0;
    datasetSize = size(validationSet,2);
    for p = 1:datasetSize
        if (network.checkGuess(validationSet(:,p),validationSetTargets(:,p)))
            correct = correct +1;
        end
    end
    validationError = (datasetSize - correct)/(2*datasetSize);
    
    
    
    close(f)

   
end