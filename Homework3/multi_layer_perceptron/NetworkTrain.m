function NetworkTrain(network,nEpochs,batchSize,trainingSet,trainingSetTargets,validationSet,validationSetTargets)
    

    figure('NumberTitle', 'off', 'Name', network.getDescription());

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

    for epoch = 1:nEpochs
        [tE,vE ] = EpochTrain(network,batchSize,trainingSet,trainingSetTargets,validationSet,validationSetTargets);


        addpoints(tEl,epoch,tE);
        hold on

        addpoints(vEl,epoch,vE);
        hold on

        [~,y] = getpoints(vEl);

        axis([1 nEpochs min(y)-0.05 max(y)+0.05])

        set(gca, 'YScale', 'log')
        drawnow

    end
end