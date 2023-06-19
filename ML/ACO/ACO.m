% ACO
% y=x1^2+x2^2+x3^3+x4^4

clc;
clear;

NGEN = 100;         % 迭代次数
pop_size = 15;      % 种群大小
var_num = 4;        % 变量个数
bound = [1, 30];    % 变量范围

pop_x = zeros(pop_size, var_num);
g_best = zeros(1, var_num);

best_fitness_history = [];
best_position_history = [];
temp = -1;

for i = 1:pop_size
    pop_x(i, :) = rand(1, var_num) * (bound(2) - bound(1)) + bound(1);
    fit = fit_target(pop_x(i, :));
    if fit > temp
        g_best = pop_x(i, :);
        temp = fit;
    end
end

best_fitness_history = [best_fitness_history, temp];
best_position_history = [best_position_history; g_best];

for gen = 1:NGEN
    t = gen * pop_size;
    for i = 1:pop_size
        ant_x = pop_x(i, :);
        candidate_x = zeros(1, var_num);
        
        for j = 1:var_num
            if rand < t / (NGEN * pop_size)
                disturbance = rand*1.9;
                candidate_x(j) = ant_x(j) + disturbance;
                candidate_x(j) = max(bound(1), min(candidate_x(j), bound(2)));
            else
                candidate_x(j) = rand * (bound(2)-bound(1)) + bound(1);
            end
        end
        
        fit_candidate = fit_target(candidate_x);
        if fit_candidate > temp
            g_best = candidate_x;
            temp = fit_candidate;
        end
    end
    pop_x(i, :) = candidate_x;
    best_fitness_history = [best_fitness_history, temp];
    best_position_history = [best_position_history; g_best];
%     data_str = sprintf('%.2f, ', g_best);
%     data_str = data_str(1:end-2);
%     fprintf('gen: %d, position: %s\n', gen, data_str);
end

best_solution = g_best;
best_fitness = temp;

plot(best_fitness_history);
xlabel('Generation');
ylabel('Best');
title('ACO');

%disp(best_solution);
%disp(best_fitness);


function y = fit_target(ind_var)
    x1 = ind_var(1);
    x2 = ind_var(2);
    x3 = ind_var(3);
    x4 = ind_var(4);
    y = x1^2 + x2^2 + x3^3 + x4^4;
end
