% --------------------------------------------------------------------------- %
% Optimization and Control, Laboratory
%
% Assignment 1: Inverted Pendulum
%
% Task 2 - Parameter Identification 
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
%% Task 2b.)

% variables
g = 9.81; % m/s^2
l = 0.3; % m
% g = 9.80620; % at the 45th parallel

% Yalmip optimization
load('measurements_3.mat');

i_A = measurements_3.signals.values(:,1);
x_W = measurements_3.signals.values(:,2);
phi = measurements_3.signals.values(:,3);
v_W = measurements_3.signals.values(:,4);
omega = measurements_3.signals.values(:,5);
domega = measurements_3.signals.values(:,6);
t_measurements_3 = measurements_3.time(:,1);

p_L1 = perfrom_optimization_large_pendulum(i_A, phi, v_W, omega, domega, l, g, 'L1');
p_L2 = perfrom_optimization_large_pendulum(i_A, phi, v_W, omega, domega, l, g, 'L2');
p_Linfty = perfrom_optimization_large_pendulum(i_A, phi, v_W, omega, domega, l, g, 'Linfty');


%% Task 2c.)
params_L1 = solve_LGS_large_pendulum(p_L1, domega(1), l, g, phi(1), omega(1), i_A(1), v_W(1))
params_L2 = solve_LGS_large_pendulum(p_L2, domega(1), l, g, phi(1), omega(1), i_A(1), v_W(1))
params_Linfty = solve_LGS_large_pendulum(p_Linfty, domega(1), l, g, phi(1), omega(1), i_A(1), v_W(1))


%% Task 2e.)

% initial values
x0 = [x_W(1); phi(1); v_W(1); omega(1)];

sim('OAC_LA_Ass1_Task2_simu.slx',t_measurements_3(end));

compare_phi(t_measurements_3, phi, phi_simu);
suptitle('Optimization Results Compared to Measurement Results Used for the Optimization');

compare_x_w(t_measurements_3, x_W, x_W_simu);
suptitle('Optimization Results Compared to Measurement Results Used for the Optimization');


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

compare_phi(t_measurements_3, phi, phi_simu);
suptitle('Optimization Results Compared to Measurement Results "measurements\_4" ');

compare_x_w(t_measurements_3, x_W, x_W_simu);
suptitle('Optimization Results Compared to Measurement Results "measurements\_4" ');


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% function section                                                          %%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [phat] = perfrom_optimization_large_pendulum(i_A, phi, v_W, omega, domega, l, g, norm)

    yalmip('clear') % delete old yalmip variables

    A = [l*domega.*(cos(phi)).^2 - l*omega.^2.*sin(phi).*cos(phi), ...
        cos(phi).*i_A, cos(phi).*v_W];
    
    phat = sdpvar(3,1); % Declare optimization variables

    e = domega*l - g*sin(phi) -A*phat; % Error
    
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

end


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function params = solve_LGS_large_pendulum(p, domega, l, g, phi, omega, i_A, v_W)
    
    syms mw V k1
    
    ms = 0.5; % kg
             
    eq_system = [ms/(mw+ms) == p(1), ...
                 -V/(mw+ms) == p(2), ...
                 k1/(mw+ms) == p(3)];
    
    S = solve(eq_system, [mw,V,k1]);
    
    params = [double(ms), double(S.mw), double(S.V), double(S.k1)];

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


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function compare_x_w(t_measurements, x_W, x_W_simu)
    
    % plot the results in a figure
    figure()
        set(gcf, 'Units', 'Normalized', 'Position', [0, 0, 0.8, 0.9]);
        %
        subplot(3,1,1)
        plot(t_measurements, x_W, 'linewidth', 2);
        hold on; box on; grid on;
        plot(x_W_simu.time(:), x_W_simu.signals.values(:,1), '--', 'linewidth', 2);
        title('Result of the $L_1$ Optimization', 'Interpreter', 'Latex','Fontsize', 14);
        xlabel('t in s', 'Interpreter', 'Latex', 'Fontsize', 12); 
        ylabel('$x_W$ in m', 'Interpreter', 'Latex','Fontsize', 12);
        %
        subplot(3,1,2)
        plot(t_measurements, x_W, 'linewidth', 2);
        hold on; box on; grid on;
        plot(x_W_simu.time(:), x_W_simu.signals.values(:,2), '--', 'linewidth', 2);
        title('Result of the $L_2$ Optimization', 'Interpreter', 'Latex','Fontsize', 14);
        xlabel('t in s', 'Interpreter', 'Latex', 'Fontsize', 12); 
        ylabel('$x_W$ in m', 'Interpreter', 'Latex','Fontsize', 12);
        %
        subplot(3,1,3)
        plot(t_measurements, x_W, 'linewidth', 2);
        hold on; box on; grid on;
        plot(x_W_simu.time(:), x_W_simu.signals.values(:,3), '--', 'linewidth', 2);
        title('test', 'Fontsize', 16); 
        title('Result of the $L_\infty$ Optimization', 'Interpreter', 'Latex','Fontsize', 14);
        xlabel('t in s', 'Interpreter', 'Latex', 'Fontsize', 12); 
        ylabel('$x_W$ in m', 'Interpreter', 'Latex','Fontsize', 12);
end
