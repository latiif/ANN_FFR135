classdef Layer < handle
    properties
        nNeurons
        weightMatrix
        thresholds
        fields;
        activations;
        errors;
        a_function;
        isOutput = false;
    end
    
    methods
        function obj = Layer(numberOfNeurons,nInputs,activation_function, isOutputLayer)
            obj.nNeurons = numberOfNeurons;
            obj.weightMatrix = normrnd(0,1/(sqrt(nInputs)),[obj.nNeurons,nInputs]);
            obj.thresholds = zeros(obj.nNeurons,1);
            
            obj.fields= zeros(obj.nNeurons,1);
            obj.activations = zeros(obj.nNeurons,1);
            obj.errors = zeros(obj.nNeurons,1);
            
            obj.a_function = activation_function;
            obj.isOutput = isOutputLayer;
        end
        
        function out = fire(obj,input)
            obj.fields = ( obj.weightMatrix * input ) - obj.thresholds;
            
            obj.activations = obj.a_function(obj.fields);
            
            if obj.isOutput
                out = arrayfun(@(x) sgn(x),obj.activations);
            else
                out = obj.activations;
            end
        end
        
        
        function errors_vector = backpropagate(obj,target)
            
            
            dff = @(x) obj.a_function(x).*(1- obj.a_function(x));
            
            obj.errors = zeros(obj.nNeurons,1);
            
            
            if (obj.isOutput)
                
                obj.errors = (dff(obj.fields)) - (target - (obj.activations));
                
                errors_vector = obj.errors;
            else
                for j = 1:obj.nNeurons
                    sum = 0.0;
                    for i = 1:target.nNeurons
                        sum = sum + target.errors(i)*target.weightMatrix(i,j)*dff(obj.fields(j));
                    end
                    
                    obj.errors(j) = sum;
                end
                
                errors_vector = obj.errors;
            end
            
            
        end
        
        
        
        function updateLayer(obj, rate, inputs,errors)
            [M,N] = size(obj.weightMatrix);
            mb = size(errors,2);
            
            for m = 1:M
                for n = 1:N
                    sumW = 0;
                    for u = 1:mb
                        sumW = sumW + errors(m,u)*inputs(n,u);
                    end
                    
                    obj.weightMatrix(m,n)= obj.weightMatrix(m,n) + rate*sumW;
                end
                
                sumT = 0;
                for u = 1:mb
                    sumT = sumT + errors(m,u);
                end
                obj.thresholds(m) = obj.thresholds(m) - rate*sumT;
            end
            
        end
        
    end
end