% GA
% y = x**2 - 9*x + 15*sin(5*x) + 3*cos(4*x) + tan(2*x)

clc;
clear;

xSize = 30; % 种群大小
chromosomeLength = 20; % 染色体长度
mutationRate = 0.6; % 变异率
tournamentSize = 5; % 锦标赛选择的参与个体数量
elite = true; % 是否保留上一代最优个体

% Initialization
X = randi([0, 1], xSize, chromosomeLength);
Gen = 50;
val = getVal(X);
maxVal = zeros(Gen, 1);

% GA
for gen = 1:Gen
    fitness = val;
    
    % 保存最佳个体和最大函数值
    [maxFitness, maxIndex] = max(fitness);
    maxVal(gen) = maxFitness;
    bestChromosome = X(maxIndex, :);
    
    % 输出当前代数的最佳染色体表现型和最大函数值
    disp(['Gen: ', num2str(gen), ', Chromosome: ', num2str(bestChromosome), ', Val: ', num2str(maxFitness)]);
    
    newPopulation = selection(X, fitness, tournamentSize);
    newPopulation = crossover(newPopulation, chromosomeLength);
    newPopulation = mutation(newPopulation, mutationRate, chromosomeLength);

    % 保留上一代最优个体
    if elite
        newPopulation(1, :) = bestChromosome;
    end
    
    X = newPopulation;
    val = getVal(X);
end

% 绘制最大函数值的变化趋势
plot(maxVal);
xlabel('Generation');
ylabel('Max Value');

function val = decode(chromosome)
    x = bin2dec(num2str(chromosome)) / (2^length(chromosome)-1) * 9;
    val = 3*sin(5*x) + 9*cos(4*x) - 5*sin(2*x) + x;
end

function value = getVal(x)
    n = size(x, 1);
    value = zeros(n, 1);
    for i=1:n
        value(i) = decode(x(i, :));
    end
end

% selection
function xSelection = selection(x, fitness, tournamentSize)
    n = size(x, 1);
    xSelection = zeros(size(x));
    for i = 1:n
        tournament = randperm(n, tournamentSize);
        [~, maxIndex] = max(fitness(tournament));
        xSelection(i, :) = x(tournament(maxIndex), :);
    end
end

% cross
function xCross = crossover(x, chromosomeLength)
    n = size(x, 1);
    xCross = zeros(size(x));
    for i = 1:2:n
        parent1 = x(i, :);
        parent2 = x(i+1, :);
        crossoverPoint = randi(chromosomeLength - 1);
        xCross(i, :) = [parent1(1:crossoverPoint), parent2(crossoverPoint+1:end)];
        xCross(i+1, :) = [parent2(1:crossoverPoint), parent1(crossoverPoint+1:end)];
    end
end

% mutation
function xMutation = mutation(x, mutationRate, chromosomeLength)
    n = size(x, 1);
    xMutation = x;
    for i = 1:n
        for j = 1:chromosomeLength
            if rand < mutationRate
                xMutation(i, j) = ~xMutation(i, j);
            end
        end
    end
end
