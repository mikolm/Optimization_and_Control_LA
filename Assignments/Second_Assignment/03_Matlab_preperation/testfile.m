% --------------------------------------------------------------------------- %
% Optimization and Control, Laboratory
%
% Assignment 1: Model Predictive Control of a "Two Tank System"
%
% Michael Kolm, 11708811
% Lukas Totschnig, ???
%
% Version 1
% --------------------------------------------------------------------------- %
%
% --------------------------------------------------------------------------- %

% load David's matrixn
load('matrixen_david.mat');

% tidy up Matlab
clear all; close all; clc;
format shorteng
format compact

% variables and parameters
k1 = 0.391;         % in sqrt(cm)/s
k2 = 0.386;         % in sqrt(cm)/s
h01 = 10.17;        % in cm
h02 = 10.53;        % in cm
alpha1 = 0.055;     % in cm/s
alpha2 = 0.059;     % in cm/s
beta1 = -3.077;     % in cm^2/s^2
beta2 = -3.246;     % in cm^2/s^2
gamma1 = 3.551;     % in cm^2/(s^2*V)
gamma2 = 3.610;     % in cm^2/(s^2*V)

k = [k1; k2];
h = [h01; h02];
alpha = [alpha1; alpha2];
beta = [beta1; beta2];
gamma = [gamma1; gamma2];

%%% ======================================================================= %%%
%% Task 1                                                                    %%
%%% ======================================================================= %%%
% calculation of the equilibrium points
ye = 15; % in cm
x2e = ye+h(2); 

% analytical results of the equilibrium point
% u1e = 1/gamma(1)*( (k(2)*sqrt(x2e)-alpha(1))^2 - beta(1) );
% x1e = 1/k(1)^2 * (alpha(1) + sqrt(beta(1)+gamma(1)*u1e) )^2;
% xe_ana = [x1e; x2e]
% ue_ana = [u1e; 0]

% matlab results of the equilibrium point
syms u1e x1e

eq_system = [ % first ODE
              k(1)*sqrt(x1e) == alpha(1) + sqrt( beta(1)+gamma(1)*u1e ), ...
              % second ODE
              k(2)*sqrt(x2e) == alpha(1) + sqrt( beta(1)+gamma(1)*u1e )];

S = solve(eq_system, [u1e, x1e]);
xe = [double(S.x1e); x2e]
ue = [double(S.u1e); 0]

if (beta(1)+gamma(1)*ue(1)) <= 0
    error('Task1: negative squareroot! - we are in the wrong section of the pumps input-output curve.');
end 

% calculate matrices
% analytical results
A = [-k(1)/2 * xe(1)^(-0.5),   0;
     k(1)/2 * xe(1)^(-0.5),    -k(2)/2 * xe(2)^(-0.5)];
 
b1 = [gamma(1)/2 * ( beta(1)+gamma(1)*ue(1) )^(-0.5);
                                                  0];                                           
                                           
cT = [0, 1];
d = 0;

cT_simu = eye(2);

% only pump 1 is included in this model
lin_sys = ss(A, b1, cT, d);


%%% ======================================================================= %%%
%% Task 2                                                                    %%
%%% ======================================================================= %%%

% initial conditions
x0 = [xe(1); xe(2)];
% nonlinear and linear simulation to verify the linearized model and the calculated equilibrium point
sim('task2_nonlin_model_simu.slx', 5);
sim('task2_lin_model_simu.slx', 5);

%%% ======================================================================= %%%
%% Task 3                                                                    %%
%%% ======================================================================= %%%
Ts = 0.5; % in s

% discretize the linearized model
lin_sys_dis = c2d(lin_sys, Ts);

Ad = lin_sys_dis.A;
Bd = lin_sys_dis.B;
CTd = lin_sys_dis.C;
Dd = lin_sys_dis.D;

%%% ======================================================================= %%%
%% Task 4                                                                    %%
%%% ======================================================================= %%%
Np = 10;
Nc = 5;

n = size(Ad,1)
m = size(Bd,2)
p = size(CTd,1)




%%% ======================================================================= %%%
%% Task 5                                                                    %%
%%% ======================================================================= %%%


%%% ======================================================================= %%%
%% Task 6                                                                    %%
%%% ======================================================================= %%%


%%% ======================================================================= %%%
%% Task 7                                                                    %%
%%% ======================================================================= %%%
