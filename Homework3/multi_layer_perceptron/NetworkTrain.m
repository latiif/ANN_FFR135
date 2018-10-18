function NetworkTrain(network,nEpochs,batchSize,trainingSet,trainingSetTargets,validationSet,validationSetTargets,testSet,testSetTargets)
    

    bestResult = [0 ;%epoch
                   1;%trError
                   1;%valError
                   1;%tstError
                 ];

    curr = figure('NumberTitle', 'off', 'Name', network.getDescription());

    title("Classificaiton Error as a function of epoch")
    
    tEl = animatedline;
    vEl = animatedline;

    tEl.Color = "green";
    tEl.DisplayName = "Training Error Classifciation";
    vEl.Color = "blue";
    vEl.DisplayName = "Validation Error Classification";
    legend("Training Error","Validation Error");
    xlabel("Epoch")
    ylabel("Classificaiton Error");

    bestText = text(0,0,"No info present");
    for epoch = 1:nEpochs
        [tE,vE ] = EpochTrain(network,batchSize,trainingSet,trainingSetTargets,validationSet,validationSetTargets);

        
        if vE<bestResult(3)
            counter = 0;
             datasetSize = size(testSet,2);
             for p = 1:datasetSize
                counter = counter + sum(abs(network.checkGuess(testSet(:,p))-testSetTargets(:,p)));
             end
        testE = (counter)/(2*datasetSize);
            
        bestResult = [epoch;tE;vE;testE];
        delete(bestText);
        bestText = text(epoch,testE,["\leftarrow epoch";"train ";"valid ";"test "]+num2str(bestResult));
        end

        addpoints(tEl,epoch,tE);
        hold on

        addpoints(vEl,epoch,vE);
        hold on

        [~,y] = getpoints(vEl);

        axis([1 nEpochs min(y)-0.05 max(y)+0.05])

        set(gca, 'YScale', 'log')
        drawnow
        saveas(curr,curr.Name+".png")

    end
end