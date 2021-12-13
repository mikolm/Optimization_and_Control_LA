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
%% Task 3.) 

% variables
g = 9.81; % m/s^2

% optimization results from task1 and task 2
l = 0.3; % m
ms = 0.5;
mw = 0.4;
V = 2;
k1 = 19;
params = [ms, mw, V, k1];

%% Linearization around the upper equilibrium point
% done with matlab 
%{
syms F_eq phi_eq v_W_eq omega_eq

eq_system = [v_W_eq == 0, ...
             omega_eq == 0, ...
             1/( mw + ms*(1-(cos(phi_eq))^2) ) * ( F_eq + ms*l*omega_eq^2*sin(phi_eq) - ms*g*sin(phi_eq)*cos(phi_eq) ) == 0, ...
             1/( l * ( 1 - ms/(mw+ms)*(cos(phi_eq))^2 ) ) * ( g*sin(phi_eq) - cos(phi_eq)/(ms+mw)*F_eq - ms/(mw+ms)*l*omega_eq^2*sin(phi_eq)*cos(phi_eq) ) == 0];
    
S = solve(eq_system, [F_eq, phi_eq, v_W_eq, omega_eq]);

eq_points = [double(S.F_eq), double(S.phi_eq), double(S.v_W_eq), double(S.omega_eq)]

%}

% IC for the linmod simulation
x0 = [0; 0; 0; 0];

x_eq = zeros(4,1);
F_eq = 0;

[A,B,C,D] = linmod('OAC_LA_Ass1_Task3_linearization', x_eq, F_eq);

%% Design of the LQR controller 

% weightings
Q(1,1) = 100;
Q(2,2) = 1;
Q(3,3) = 1e-3;
Q(4,4) = 1e-3;

R = 1; % limitation of the control action

kT = lqr(A,B,Q,R);

%% Visualization of the movement
x0_lin = [0, deg2rad(60), 0, 0]';

sim('OAC_LA_Ass1_Task3_linearized_model.slx',3);

visualisation(l,lin_simdata);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% function section                                                          %%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function visualisation(l, lin_simdata)
    
    % variables
    counter = 1;
    speedup = 20;
    n_iter = length(lin_simdata.time(:));
    linewidth = 3;
    
    % assign meaningful names
    bottom_pos_x = lin_simdata.signals.values(:,1);   
    top_pos_x = bottom_pos_x + l*sin(lin_simdata.signals.values(:,2));
    top_pos_y = l*cos(lin_simdata.signals.values(:,2));
    
    % plot animation
    figure(1)
    %set(gcf, 'Units', 'Normalized', 'Position', [0.2, 0.2, 0.6, 0.6]);
    while counter < n_iter
        plot([bottom_pos_x(counter), top_pos_x(counter)], ...
             [0, top_pos_y(counter)], '-', 'linewidth', linewidth, ...
              'color', [0.8,0,0]);  
        grid on; box on; hold on;
        plot(bottom_pos_x(counter), 0, 'x', 'linewidth', linewidth, ...
             'color', [0.8,0,0]);
        plot(top_pos_x(counter), top_pos_y(counter), 'o', ...
            'linewidth', linewidth, 'color', [0.8,0,0]);
        % figure cosmetics 
        title('Pendulum Movement', 'Linewidth', 16);
        axis equal
        xlim([-1,1]); ylim([-1,1]);
        xticks(-1:0.2:1);
        yticks(-1:0.2:1);
        txt = ['t = ', num2str(lin_simdata.time(counter,1)), 's'];
        text(0.3, 0.75, txt, 'Fontsize', 14);
        
        if counter == 1
            pause(1);
            clf;
        elseif counter >= n_iter-speedup
            break
        else
            pause(1e-6);
            clf
        end
        counter = counter + speedup;
    end
end    



