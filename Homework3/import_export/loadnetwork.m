function network = loadnetwork(weights, thresholds,nInputs)

    tM = cell(size(weights));
    wM = cell(size(thresholds));
    nLayers = size(thresholds,2);
    
    nSize = [nInputs];
    
    for l = 1:nLayers
        tM{l} = csvread(thresholds(l));
        wM{l} = csvread(weights(l));
        nSize = [nSize size(tM{l},1)];
    end
 
   
       act  = @(x) tanh(x);

    
    network = Network(nSize,0,act);
    
    for l=1:nLayers
        network.layers(l).weightMatrix = wM{l};
        network.layers(l).thresholds = tM{l};
    end
end