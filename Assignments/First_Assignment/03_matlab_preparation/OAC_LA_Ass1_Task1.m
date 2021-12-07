% --------------------------------------------------------------------------- %
% Optimization and Control, Laboratory
%
% Assignment 1: Inverted Pendulum
%
% Task 1 - Parameter Identification 
%
% Michael Kolm, 11708811
% Lukas Totschnig, ???
%
% Version 1
% --------------------------------------------------------------------------- %
%
% https://yalmip.github.io/allcommands ... command documentation of YALMIP
% --------------------------------------------------------------------------- %


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% main section                                                              %%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% tidy up Matlab
clear all; close all; clc;

% --------------------------------------------------------------------------- %
%% Task 1b.)
% Yalmip optimization
load('measurements_1.mat');

phi = measurements_1.signals.values(:,1);
omega = measurements_1.signals.values(:,2);
domega = measurements_1.signals.values(:,3);
t_measurements_1 = measurements_1.time(:);

% L1 optimization with yalmip
yalmip('clear') % delete old yalmip variables

p1_hat_L1 = sdpvar(1,1); % define YALMPIs symbolic decision  variable
A = p1_hat_L1 * sin(phi); % how the opt. var. acts on the measured qunatity

e = phi-A*p1_hat_L1; % Error

bounds = sdpvar(length(e),1); % define YALMPIs symbolic decision  variable
constraints = [-bounds <= e <= bounds];
options = sdpsettings('verbose',0); % communicate options to YALMIP and solvers

diagnostics_L1 = optimize(constraints,sum(bounds),options); % solve optimization problems

if diagnostics_L1.problem > 0
error('Error during optimization')
end
p1_hat_L1 = value(p1_hat_L1); % Get the numerical value of the decision varible
l_L1 = g/p1_hat_L1;
disp(['L1 optimization result: l = ', num2str(l_L1), 'm']);
%y_L1 = A*p1_hat_L1; % Compute results



%l_L1 = 0.32;
%l_L2 = 0.31;
%l_Linfty = 0.3;

%{
% --------------------------------------------------------------------------- %
%% Task 1c.)
% Simulink Simulation

% initial conditions of phi and omega
phi_0 = phi(1);
omega_0 = omega(1);

% known values
g = 9.81; % m/s^2
% g = 9.80620; % at the 45th parallel

% evaluate the simulink model for different optimization results
l = l_L1;
sim('OAC_LA_Ass1_Task1_simu.slx', t_measurements_1);
phi_simu_L1 = phi_simu;

l = l_L2;
sim('OAC_LA_Ass1_Task1_simu.slx', t_measurements_1);
phi_simu_L2 = phi_simu;

l = l_Linfty;
sim('OAC_LA_Ass1_Task1_simu.slx', t_measurements_1);
phi_simu_Linfty = phi_simu;

% plot the results in a figure
figure()
    set(gcf, 'Units', 'Normalized', 'Position', [0, 0, 0.8, 0.9]);
    %
    subplot(3,1,1)
    plot(t_measurements_1, phi, 'linewidth', 2);
    hold on; box on; grid on;
    plot(phi_simu_L1.time(:), phi_simu_L1.signals.values(:), '--', 'linewidth', 2);
    title('Result of the $L_1$ Optimization', 'Interpreter', 'Latex','Fontsize', 14);
    xlabel('t in s', 'Interpreter', 'Latex', 'Fontsize', 12); 
    ylabel('$\varphi$ in rad', 'Interpreter', 'Latex','Fontsize', 12);
    ylim([0,2*pi]); yticks([0:pi/2:2*pi]);
    yticklabels({'0','pi/2','pi', '3/2 pi', '2pi'});
    %
    subplot(3,1,2)
    plot(t_measurements_1, phi, 'linewidth', 2);
    hold on; box on; grid on;
    plot(phi_simu_L2.time(:), phi_simu_L2.signals.values(:), '--', 'linewidth', 2);
    title('Result of the $L_2$ Optimization', 'Interpreter', 'Latex','Fontsize', 14);
    xlabel('t in s', 'Interpreter', 'Latex', 'Fontsize', 12); 
    ylabel('$\varphi$ in rad', 'Interpreter', 'Latex','Fontsize', 12);
    ylim([0,2*pi]); yticks([0:pi/2:2*pi]);
    yticklabels({'0','pi/2','pi', '3/2 pi', '2pi'});
    %
    subplot(3,1,3)
    plot(t_measurements_1, phi, 'linewidth', 2);
    hold on; box on; grid on;
    plot(phi_simu_Linfty.time(:), phi_simu_Linfty.signals.values(:), '--', 'linewidth', 2);
    title('test', 'Fontsize', 16); 
    title('Result of the $L_\infty$ Optimization', 'Interpreter', 'Latex','Fontsize', 14);
    xlabel('t in s', 'Interpreter', 'Latex', 'Fontsize', 12); 
    ylabel('$\varphi$ in rad', 'Interpreter', 'Latex','Fontsize', 12);
    ylim([0,2*pi]); yticks([0:pi/2:2*pi]);
    yticklabels({'0','pi/2','pi', '3/2 pi', '2pi'});
    %
    suptitle('Optimization Results Compared to Measurement Results');
%}




%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% function section                                                          %%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%





