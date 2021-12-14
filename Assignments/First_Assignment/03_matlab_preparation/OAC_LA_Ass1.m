% --------------------------------------------------------------------------- %
% Optimization and Control, Laboratory
%
% Assignment 1: Inverted Pendulum
%
% Michael Kolm, 11708811
% Lukas Totschnig, ???
%
% Version 1
% --------------------------------------------------------------------------- %
%
% https://yalmip.github.io/allcommands ... command documentation of YALMIP
% --------------------------------------------------------------------------- %

% tidy up Matlab
clear all; close all; clc;
format shorteng
format compact


% variables
g = 9.81; % m/s^2
% g = 9.80620; % at the 45th parallel

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Task 1                                                                    %%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% --------------------------------------------------------------------------- %
%% Task 1b.)
% Yalmip optimization
load('measurements_1.mat');

phi = measurements_1.signals.values(:,1);
omega = measurements_1.signals.values(:,2);
domega = measurements_1.signals.values(:,3);
t_measurements_1 = measurements_1.time(:);

% use this vector to show the difference between the different optimization 
% methods - random noise is added to the measurement value domega 
%domega = measurements_1.signals.values(:,3) + 10*randn(size(measurements_1.signals.values(:,1)));

l_L1 = Task1_Funcs.perfrom_optimization(phi, domega, g, 'L1');
l_L2 = Task1_Funcs.perfrom_optimization(phi, domega, g, 'L2');
l_Linfty = Task1_Funcs.perfrom_optimization(phi, domega, g, 'Linfty');

% --------------------------------------------------------------------------- %
%% Task 1c.)
% Simulink Simulation to compare the outcome of the optimization to the 
% measured results used for the optimization.

% initial conditions of phi and omega
phi_0 = phi(1);
omega_0 = omega(1);

% evaluate the simulink model for the different optimization results
l = [l_L1; l_L2; l_Linfty];
sim('OAC_LA_Ass1_Task1_simu.slx', t_measurements_1(end));

Task1_Funcs.compare_phi(t_measurements_1, phi, phi_simu);
suptitle('Optimization Results Compared to Measurement Results Used for the Optimization');

% --------------------------------------------------------------------------- %
%% Task 1d.)
% compare the optimization result to a measurement result not used for the 
% optimization by re-running the simulink model with new initial conditions

load('measurements_2.mat');

phi = measurements_2.signals.values(:,1);
omega = measurements_2.signals.values(:,2);
domega = measurements_2.signals.values(:,3);
t_measurements_2 = measurements_2.time(:);

% initial conditions of phi and omega
phi_0 = phi(1);
omega_0 = omega(1);

sim('OAC_LA_Ass1_Task1_simu.slx', t_measurements_2(end));

Task1_Funcs.compare_phi(t_measurements_2, phi, phi_simu);
suptitle('Optimization Results Compared to Measurement Results "measurements\_2" ');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
l = l_L1; % best optimisation result


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Task 2                                                                    %%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% --------------------------------------------------------------------------- %
%% Task 2b.)

% Yalmip optimization
load('measurements_3.mat');

i_A = measurements_3.signals.values(:,1);
x_W = measurements_3.signals.values(:,2);
phi = measurements_3.signals.values(:,3);
v_W = measurements_3.signals.values(:,4);
omega = measurements_3.signals.values(:,5);
domega = measurements_3.signals.values(:,6);
t_measurements_3 = measurements_3.time(:,1);

p_L1 = Task2_Funcs.perfrom_optimization_large_pendulum(i_A, phi, v_W, omega, domega, l, g, 'L1');
p_L2 = Task2_Funcs.perfrom_optimization_large_pendulum(i_A, phi, v_W, omega, domega, l, g, 'L2');
p_Linfty = Task2_Funcs.perfrom_optimization_large_pendulum(i_A, phi, v_W, omega, domega, l, g, 'Linfty');

% --------------------------------------------------------------------------- %
%% Task 2c.)
params_L1 = Task2_Funcs.solve_LGS_large_pendulum(p_L1, domega(1), l, g, phi(1), omega(1), i_A(1), v_W(1))
params_L2 = Task2_Funcs.solve_LGS_large_pendulum(p_L2, domega(1), l, g, phi(1), omega(1), i_A(1), v_W(1))
params_Linfty = Task2_Funcs.solve_LGS_large_pendulum(p_Linfty, domega(1), l, g, phi(1), omega(1), i_A(1), v_W(1))

% --------------------------------------------------------------------------- %
%% Task 2e.)

% initial values
x0 = [x_W(1); phi(1); v_W(1); omega(1)];

sim('OAC_LA_Ass1_Task2_simu.slx',t_measurements_3(end));

Task2_Funcs.compare_phi(t_measurements_3, phi, phi_simu);
suptitle('Optimization Results Compared to Measurement Results Used for the Optimization');

Task2_Funcs.compare_x_w(t_measurements_3, x_W, x_W_simu);
suptitle('Optimization Results Compared to Measurement Results Used for the Optimization');

% --------------------------------------------------------------------------- %
%% Task 2.f.)
load('measurements_4.mat');

i_A = measurements_4.signals.values(:,1);
x_W = measurements_4.signals.values(:,2);
phi = measurements_4.signals.values(:,3);
v_W = measurements_4.signals.values(:,4);
omega = measurements_4.signals.values(:,5);
domega = measurements_4.signals.values(:,6);
t_measurements_3 = measurements_4.time(:,1);

% initial values
x0 = [x_W(1); phi(1); v_W(1); omega(1)];

sim('OAC_LA_Ass1_Task2_simu.slx',t_measurements_3(end));

Task2_Funcs.compare_phi(t_measurements_3, phi, phi_simu);
suptitle('Optimization Results Compared to Measurement Results "measurements\_4" ');

Task2_Funcs.compare_x_w(t_measurements_3, x_W, x_W_simu);
suptitle('Optimization Results Compared to Measurement Results "measurements\_4" ');

% best optimisation result
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
ms = params_L1(1); 
mw = params_L1(2);
V = params_L1(3);
k1 = params_L1(4);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Task 3                                                                    %%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% --------------------------------------------------------------------------- %
all_params = [l, ms, mw, V, k1];

%% Linearization around the upper equilibrium point

%eq_points = Task3_Funcs.get_equilibrium_points(all_params,g);
%x_eq_upper = eq_points(1,1:4)';
%iA_eq_upper = eq_points(1,5);
x_eq = zeros(4,1);
iA_eq = 0;

% IC for the linmod simulation
x0 = [0; deg2rad(10); 0; 0]; % IC of the linearization simulink model

[A,B,C,D] = linmod('OAC_LA_Ass1_Task3_linearization', x_eq, iA_eq);

%% Design of the LQR controller 

% weightings
Q = zeros(4,4);
Q(1,1) = 1000;
Q(2,2) = 1;

R = 1; % limitation of the control action

kT = lqr(A,B,Q,R)

%% Visualization of the movement
x0 = [0, deg2rad(45), 0, 0]';

sim('OAC_LA_Ass1_Task3_full_model_lqr_controller.slx',2);

Task3_Funcs.visualisation(l,lqr_simdata);


