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


test = perfrom_optimization(i_A, phi, v_W, omega, domega, l, g, 'Linfty');







%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% function section                                                          %%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [phat] = perfrom_optimization(i_A, phi, v_W, omega, domega, l, g, norm)

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
    
    %{
    l = g/phat; % Compute results

    disp(['Length l yielded by the ', norm, ' optimization: l= ', num2str(l), 'm']);
    %}
end


