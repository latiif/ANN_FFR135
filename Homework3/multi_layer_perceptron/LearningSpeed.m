function LearningSpeed(network,nEpochs,batchSize,trainingSet,trainingSetTargets)

curr = figure('NumberTitle', 'off', 'Name', "Vanishing-Gradient Problem");

subplot(1,2,1)
title("Energy as a function of epoch")

H_E = animatedline;


H_E.Color = "green";
legend("Energy Function");

xlabel("Epoch")
ylabel("Energy Function");

xlim([0 nEpochs])

%FOR EPOCH 0

H =  network.getEnergyFunction(trainingSet,trainingSetTargets);
addpoints(H_E,0,H);
hold on

drawnow

subplot(1,2,2)
title("Learning Speed as a function of epoch")
xlabel("Epoch")
ylabel("Learning Speed of layers")

xlim([0 nEpochs])
U = zeros(network.nLayers,nEpochs+1);

for l = 1:network.nLayers
    U_l = (network.layers(l).thresholds).^(-1) * H;
    U_l = norm(U_l);
    U(l,1) = U_l;
end


for epoch = 1:nEpochs
    EpochTrain(network,batchSize,trainingSet,trainingSetTargets,[],[]);
    
    H = network.getEnergyFunction(trainingSet,trainingSetTargets);
    
    subplot(1,2,1);
    addpoints(H_E,epoch,H);
    hold on
    
    drawnow
    saveas(curr,curr.Name+".png")
    
    
    subplot(1,2,2);
    
    hold off
    
    for l = 1:network.nLayers
        U_l = (network.layers(l).thresholds).^(-1) * H;
        U_l = norm(U_l);
        U(l,epoch) = U_l;
        plot(0:epoch,U(l,1:epoch+1),"DisplayName","Layer "+num2str(l));
        hold on
    end
    title("Learning Speed as a function of epoch")
    xlabel("Epoch")
    ylabel("Learning Speed of layers")
    set(gca, 'YScale', 'log')
    xlim([0 nEpochs])
    legend
    
    
end
end