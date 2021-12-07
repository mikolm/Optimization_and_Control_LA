clear all;
close all;
clc;

%% Load and plot recorded data
load('measurements.mat');

% dx1/dt = x2, dx2/dt = 1/a * (b*cos(x1) + c*u)
t = measurements.time;
u = measurements.signals.values(:,1);
x1 = measurements.signals.values(:,2);
x2 = measurements.signals.values(:,3);

figure() 
subplot(2,2,1)
plot(t, u, '-b', 'LineWidth', 1.5)
xlabel('t in s'), ylabel('u'), grid on;
subplot(2,2,3)
plot(t, x1, '-b', 'LineWidth', 1.5)
xlabel('t in s'), ylabel('x_1'), grid on;
subplot(2,2,2)
plot(t, x2, '-b', 'LineWidth', 1.5)
xlabel('t in s'), ylabel('x_2'), grid on;


%% Approximate dx2/dt
Ts = t(2) - t(1); % sampling time
dx2 = diff(x2) / Ts; % difference quotient

t = t(1:end-1);
u = u(1:end-1);
x1 = x1(1:end-1);
x2 = x2(1:end-1);

figure()
subplot(2,2,1)
plot(t, u, '-b', 'LineWidth', 1.5)
xlabel('t in s'), ylabel('u'), grid on;
subplot(2,2,3)
plot(t, x1, '-b', 'LineWidth', 1.5)
xlabel('t in s'), ylabel('x_1'), grid on;
subplot(2,2,2)
plot(t, x2, '-b', 'LineWidth', 1.5)
xlabel('t in s'), ylabel('x_2'), grid on;
subplot(2,2,4)
plot(t, dx2, '-b', 'LineWidth', 1.5)
xlabel('t in s'), ylabel('dx_2/dt'), grid on;

pause

%% identification (L2 - optimization)
p = sdpvar(2,1); % p1 = b/a, p2 = c/a
constraints = [p(1) >= 0, p(2) >= 0];

e = dx2 - p(1)*cos(x1) - p(2)*u;

options = sdpsettings('verbose', 0);
diagnostics_L2 = optimize(constraints, e'*e, options);
if diagnostics_L2.problem > 0
    error('Error during L2-Optimization')
end
p_hat = value(p);
a = 4;
b = p_hat(1)*a;
c = p_hat(2)*a;

Table_parameters = table([2;a],[3;b],[1;c], 'VariableNames', {'a','b','c'}, 'RowNames', {'true', 'identified'});
disp(Table_parameters);

pause

%% Run simulation and compare results
Tsim = t(end);
x0 = [x1(1); x2(1)];

sim('model_example');

figure()
subplot(1,2,1), hold on;
plot(t, x1, '-b', 'LineWidth', 1.5)
plot(x_sim.time, x_sim.signals.values(:,1), ':r', 'LineWidth', 1.5)
xlabel('t in s'), ylabel('x_1'), grid on;
legend('recorded', 'simulation');
subplot(1,2,2), hold on;
plot(t, x2, '-b', 'LineWidth', 1.5)
plot(x_sim.time, x_sim.signals.values(:,2), ':r', 'LineWidth', 1.5)
xlabel('t in s'), ylabel('x_2'), grid on;
legend('recorded', 'simulation');




 







