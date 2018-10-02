function mean  = calculateMean(dataset)
[nInputs, nPatterns] = size(dataset);
mean = zeros(nInputs,1);

for v = 1:nPatterns
    mean = mean + dataset(:,v);
end

mean = mean * (1/nPatterns);

end