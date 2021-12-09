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
format long
format compact

% --------------------------------------------------------------------------- %
%% Task 1b.)

% variables
g = 9.81; % m/s^2
% g = 9.80620; % at the 45th parallel

% Yalmip optimization
load('measurements_1.mat');

phi = measurements_1.signals.values(:,1);
omega = measurements_1.signals.values(:,2);
domega = measurements_1.signals.values(:,3);
t_measurements_1 = measurements_1.time(:);

% use this vector to show the difference between the different optimization 
% methods - random noise is added to the measurement values 
%domega = measurements_1.signals.values(:,3) + 20*randn(size(measurements_1.signals.values(:,1)));

l_L1 = perfrom_optimization(phi, domega, g, 'L1');
l_L2 = perfrom_optimization(phi, domega, g, 'L2');
l_Linfty = perfrom_optimization(phi, domega, g, 'Linfty');

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

compare_phi(t_measurements_1, phi, phi_simu);
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

compare_phi(t_measurements_2, phi, phi_simu);
suptitle('Optimization Results Compared to Measurement Results "measurements\_2" ');





%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% function section                                                          %%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [l] = perfrom_optimization(phi, domega, g, norm)

    yalmip('clear') % delete old yalmip variables

    A = sin(phi);

    phat = sdpvar(1,1); % Declare optimization variables

    e = domega-A*phat; % Error
    
    bounds = sdpvar(length(e),1);
    constraints = [-bounds <= e <= bounds];
    options = sdpsettings('verbose',0);
    
    % what optimization is performed
    if strcmp(norm,'L1')
        diagnostics = optimize(constraints,sum(bounds),options)    
    elseif strcmp(norm,'L2')
        diagnostics = optimize(constraints,sum(bounds'*bounds),options)       
    elseif strcmp(norm,'Linfty')
        diagnostics = optimize(constraints,max(bounds),options)        
    else
        error('ERROR: wrong setting for the cost function');
    end
    
    % error handling
    if diagnostics.problem > 0
        error('Error during optimization')
    end
    
    % calculate the unknown parameter based on the optimization variable
    phat = value(phat); % Convert results in double variables
    l = g/phat; % Compute results

    disp(['Length l yielded by the ', norm, ' optimization: l= ', num2str(l), 'm']);

end


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function compare_phi(t_measurements, phi, phi_simu)
    
    % plot the results in a figure
    figure()
        set(gcf, 'Units', 'Normalized', 'Position', [0, 0, 0.8, 0.9]);
        %
        subplot(3,1,1)
        plot(t_measurements, phi, 'linewidth', 2);
        hold on; box on; grid on;
        plot(phi_simu.time(:), phi_simu.signals.values(:,1), '--', 'linewidth', 2);
        title('Result of the $L_1$ Optimization', 'Interpreter', 'Latex','Fontsize', 14);
        xlabel('t in s', 'Interpreter', 'Latex', 'Fontsize', 12); 
        ylabel('$\varphi$ in rad', 'Interpreter', 'Latex','Fontsize', 12);
        %ylim([0,2*pi]); yticks([0:pi/2:2*pi]);
        %yticklabels({'0','pi/2','pi', '3/2 pi', '2pi'});
        %
        subplot(3,1,2)
        plot(t_measurements, phi, 'linewidth', 2);
        hold on; box on; grid on;
        plot(phi_simu.time(:), phi_simu.signals.values(:,2), '--', 'linewidth', 2);
        title('Result of the $L_2$ Optimization', 'Interpreter', 'Latex','Fontsize', 14);
        xlabel('t in s', 'Interpreter', 'Latex', 'Fontsize', 12); 
        ylabel('$\varphi$ in rad', 'Interpreter', 'Latex','Fontsize', 12);
        %ylim([0,2*pi]); yticks([0:pi/2:2*pi]);
        %yticklabels({'0','pi/2','pi', '3/2 pi', '2pi'});
        %
        subplot(3,1,3)
        plot(t_measurements, phi, 'linewidth', 2);
        hold on; box on; grid on;
        plot(phi_simu.time(:), phi_simu.signals.values(:,3), '--', 'linewidth', 2);
        title('test', 'Fontsize', 16); 
        title('Result of the $L_\infty$ Optimization', 'Interpreter', 'Latex','Fontsize', 14);
        xlabel('t in s', 'Interpreter', 'Latex', 'Fontsize', 12); 
        ylabel('$\varphi$ in rad', 'Interpreter', 'Latex','Fontsize', 12);
        %ylim([0,2*pi]); yticks([0:pi/2:2*pi]);
        %yticklabels({'0','pi/2','pi', '3/2 pi', '2pi'});

end

