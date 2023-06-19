% BP
% pima

clc;
clear;

% 读取数据集
data_train = load('pima.data');
X = data_train(:, 1:8);
X = mapminmax(X, 0, 1);
Y = data_train(:, 9);

X_train = X(1:500, :);
y_train = Y(1:500, :);
X_test = X(501:768, :);
y_test = Y(501:768, :);


disp(size(X_train));
disp(size(X_test));

BP(X_train, y_train, 15, 0.01, X_test, y_test);

function [v, r, w, h, y_pre] = BP(X, Y, hN, L, X_test, Y_test)
    % 输入层神经元数量
    xN = 8;
    % 输出层神经元数量
    yN = 1;
    % 输入层到隐层权值
    v = rand(xN, hN);
    % 隐层阈值
    r = rand(1, hN);
    % 隐层到输出层权值
    w = rand(hN, yN);
    % 输出层阈值
    h = rand(1, yN);
    % 学习率
    lr = 0.0001;
    % 初始损失
    loss = 1;
    iter = 0;

    while iter<8000000%loss > L
        index = round(rand(1,1)*length(Y));
        if index == 0
            index = length(Y);
        end
        
        x = X(index, :);
        y = Y(index);
	    A = x*v;
	    b = sigmoid(A-r);
	    B = b*w;
	    y_pre = sigmoid(B-h);
	    loss = 0.5 * power(y-y_pre, 2);
	    fprintf('iter: %d, loss: %f, y:%d, y_pre:%f\n', iter, loss, y, y_pre);
	    % 计算梯度
	    grad = y_pre.*(1-y_pre).*(y-y_pre);
	    e = b.*(1-b).*(w*grad)\';
	    % 更新输入层到隐层的权值和隐层阈值
	    for i=1:xN
		    for j=1:h
			    v(i,j) = v(i,j) + lr*x(i)*e(j);
		    end
	    end
	    r = r - lr*e;
	    % 更新隐层到输出层的权值和输出层阈值
	    for i=1:h
		    for j=1:yN
			    w(i,j) = w(i,j) + lr*b(i)*grad(j);
		    end
	    end
	    h = h - lr*grad;
        
        iter = iter+1;
    end

    function y = sigmoid(x)
	    y = 1./(1+exp(-x));
    end
    %test
    test_iter = 1;
    correct = 0;
    while test_iter<=length(Y_test)
        xt = X_test(test_iter, :);
        yt = Y_test(test_iter);
        A = xt*v;
	    b = sigmoid(A-r);
	    B = b*w;
	    yt_pre = sigmoid(B-h);
        if yt_pre>0.5 && yt==1 || yt_pre<0.5 && yt==0
            correct = correct+1;
        end
        test_iter = test_iter+1;
    end
    fprintf('accuracy: %f', correct/test_iter);
    
end
