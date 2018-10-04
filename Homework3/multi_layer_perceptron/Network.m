classdef Network < handle
    properties
        learningRate
        layers
        a_function
        nLayers
    end
    
    methods
        
        function obj = Network(sizes,eta,activation)
            
            obj.a_function = activation;
            obj.nLayers = length(sizes)-1;
            
            for l = 1:obj.nLayers
                t = Layer(sizes(l+1),sizes(l),activation,false);
                obj.layers = [obj.layers; t];
            end
            obj.layers(obj.nLayers).isOutput = true;
            
            obj.learningRate = eta;
        end
        
        function prediction =  predict(obj,pattern)
            
            for l = 1:obj.nLayers
                pattern = (obj.layers(l).fire(pattern));
            end
            
            prediction  = pattern;
        end
        
        function train(obj,patterns, desiredTargets, batchSize)
            % TODO fire, backpropagate, update weights
            
            batchErrors = cell(obj.nLayers,1);
            batchActivations = cell(obj.nLayers,1);
            
            for layer = 1:obj.nLayers
                batchErrors{layer} = zeros(obj.layers(layer).nNeurons,1);
                batchActivations{layer} = zeros(obj.layers(layer).nNeurons,1);
            end
            
            for pattern = 1:batchSize
                obj.predict(patterns(:,pattern));
                
                batchErrors{obj.nLayers,pattern} = obj.layers(obj.nLayers).backpropagate(desiredTargets(:,pattern));
                batchActivations{obj.nLayers,pattern} = batchActivations{obj.nLayers} + obj.layers(obj.nLayers).activations;

                for l = obj.nLayers-1:-1:1
                   batchErrors{l,pattern} = obj.layers(l).backpropagate(obj.layers(l+1));
                   batchActivations{l,pattern} =  obj.layers(l).activations;
                end
            end
            
            disp("complete")

            obj.layers(1).updateLayer(obj.learningRate,patterns,[batchErrors{1,:}]);

            for l = 2:obj.nLayers
                obj.layers(l).updateLayer(obj.learningRate,[batchActivations{l-1,:}],[batchErrors{l,:}]);
            end            
        end
        
    end
end