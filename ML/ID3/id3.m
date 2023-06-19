% ID3
% DNA dataset

clc;
clear;

% 读取训练集
rawData_train = load('dna.data');
[r, c] = size(rawData_train);
[X_train, y_train] = trans2ATCG(rawData_train);
[m, n] = size(X_train);
fprintf('size of train data: %d, %d \n', m, n);
feature = (1:n); % 存储特征（即研究DNA片段的1-60号位）

% 由ID3算法生成决策树
fprintf('Constructing decision tree ... \n');
treeRoot = decisionTree(X_train, y_train, feature);
fprintf('Construction completed! \n')

% 读取测试集
rawData_test = load('dna.test');
[X_test, y_test] = trans2ATCG(rawData_test);
[m, n] = size(X_test);
fprintf('size of test data: %d, %d \n', m, n);
pre = zeros(m, 1); % 存储预测值

for i = 1:m
    cNode = treeRoot;
    while(~isempty(cNode.children))
        cF = cNode.feature;
        if(X_test(i, cF) == 'A')
            cNode = cNode.children(1);
        elseif(X_test(i, cF) == 'T')
            cNode = cNode.children(2);
        elseif(X_test(i, cF) == 'C')
            cNode = cNode.children(3);
        else % 'G'
            cNode = cNode.children(4);
        end
    end
    pre(i, 1) = cNode.value;
end

% 检测准确率
accCount = 0;
for i= 1:m
    if(pre(i) == y_test(i))
        accCount = accCount+1;
    end
end
acc = accCount/m;
fprintf('accuracy: %f \n', acc);

% 将编码还原为ATCG，制作标签
function [X, y] = trans2ATCG(raw)
    [r, c] = size(raw);
    X = char(zeros(r, (c-1)/3));
    y = zeros(r, 1);
    for i = 1:r
        for j = 1:3:c-1
            tmp = [raw(i,j), raw(i,j+1), raw(i,j+2)];
            if(isequal(tmp, [1, 0, 0]))
                X(i, (j+2)/3) = "A";
            elseif(isequal(tmp, [0, 0, 0]))
                X(i, (j+2)/3) = "T";
            elseif(isequal(tmp, [0, 1, 0]))
                X(i, (j+2)/3) = "C";
            else
                X(i, (j+2)/3) = "G";
            end
        y(i) = raw(i, c);
        end
    end
end


% 生成决策树
function [node] = decisionTree(X, y, feature)
    [m, n] = size(X);
    EntropyList = [];
    node = struct('feature', 'null', 'value', 'null', 'children', []);
    % 如果当前窗口下的数据为同一类，则为叶结点
    if(length(unique(y)) == 1)
        node.feature = feature(1);
        node.value = y(1);
        return;
    end
    % 如果当前窗口没有数据
    if(isempty(X))
        node.value = randperm(3,1);
        return;
    end

    % 获取当前窗口中各特征的熵，并找到最小熵
    for i = 1:n
        EntropyList = [EntropyList, Entropy(X(:, i), y)]; %#ok<AGROW> 
    end
    [minE, k] = min(EntropyList); %#ok<ASGLU> 
    % 选择具有最小熵的特征作为当前结点
    node.feature = feature(k);
    X_A = [];
    X_T = [];
    X_C = [];
    X_G = [];
    y_A = [];
    y_T = [];
    y_C = [];
    y_G = [];
    % 特征列表中移除当前选中的特征
    feature(k) = [];
    for i = 1:m
        if(X(i, k) == 'A')
            X_A = [X_A; X(i, :)];
            y_A = [y_A; y(i)];
        elseif(X(i, k) == 'T')
            X_T = [X_T; X(i, :)];
            y_T = [y_T; y(i)];
        elseif(X(i, k) == 'C')
            X_C = [X_C; X(i, :)];
            y_C = [y_C; y(i)];
        else % 'G'
            X_G = [X_G; X(i, :)];
            y_G = [y_G; y(i)];
        end
    end
    if(~isempty(X_A))
        X_A(:, k) = [];
    end
    if(~isempty(X_T))
        X_T(:, k) = [];
    end
    if(~isempty(X_C))
        X_C(:, k) = [];
    end
    if(~isempty(X_G))
        X_G(:, k) = [];
    end
    % 递归生成子结点
    node_A = decisionTree(X_A, y_A, feature);
    node_T = decisionTree(X_T, y_T, feature);
    node_C = decisionTree(X_C, y_C, feature);
    node_G = decisionTree(X_G, y_G, feature);
    node.children = [node.children; node_A; node_T; node_C; node_G];
    return;
end

% 计算三个数的信息量
function [I] = Info(a, b, c)
    total = a+b+c;
    if((a==0&&b==0)||(a==0&&c==0)||(b==0&&c==0))
        I = 0;
        return;
    end
    if(a == 0)
        I = (-1) * (b/total*log2(b/total) + c/total*log2(c/total));
        return;
    end
    if(b == 0)
        I = (-1) * (a/total*log2(a/total) + c/total*log2(c/total));
        return;
    end
    if(c == 0)
        I = (-1) * (a/total*log2(a/total) + b/total*log2(b/total));
        return;
    end
    I = (-1) * (a/total*log2(a/total) + b/total*log2(b/total) + c/total*log2(c/total));
end

% 计算属性的熵
% 将DNA序列的每一个位置看作一个属性
function [E] = Entropy(data, label)
    E = 0;
    total = length(data);
    count = zeros(4, 4);
    ty = ['A', 'T', 'C', 'G'];
    % 各属性值数量
    % count第一行为当前位置ATCG各自的数量
    % count二三四行为各碱基对应的三种类别的数量
    for i = 1:4
        for j =1:total
            if(data(j) == ty(i))
                count(1, i) = count(1, i) + 1;
                if(label(j) == 1)
                    count(2, i) = count(2, i) + 1;
                elseif(label(j) == 2)
                    count(3, i) = count(3, i) + 1;
                else
                    count(4, i) = count(4, i) + 1;
                end
            end
        end
    end
    %disp(count)
    for  i = 1:4
        if(count(1, i) ~= 0)
            E = E + count(1,i)/total * Info(count(2,i), count(3,i), count(4,i));
        end
    end
end
