% ----------------------------------------------------------------------- %
% Optimization and Control, Laboratory
%
% Assignment 1: Model Predictive Control of a "Two Tank System"
%
% Michael Kolm, 11708811
% Lukas Totschnig, 11701449
%
% Version 1
% ----------------------------------------------------------------------- %
%
% ----------------------------------------------------------------------- %

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

alpha = [alpha1; alpha2];
beta = [beta1; beta2];
gamma = [gamma1; gamma2];
h = [h01; h02];
k = [k1; k2];
x0 = [0,0];

%%% =================================================================== %%%
%% Task 1                                                                %%
%%% =================================================================== %%%

% calculation of the equilibrium points
y_eq = 15;
x2_eq = y_eq+h(2);% in cm

% matlab results of the equilibrium point
[u_eq,x_eq] = Task1_Funcs.equilibrium(alpha, beta, gamma, k, x2_eq);


[A,B,C,D] = linmod('task1_nonlin_model_simu', x_eq, u_eq(1));

C = [0,1];
D = 0;


%%% =================================================================== %%%
%% Task 2                                                                %%   
%%% =================================================================== %%%

%initial conditions
x0 = [x_eq(1); x_eq(2)];

% nonlinear and linear simulation to verify the linearized model 
% and the calculated equilibrium point

sim('task2_nonlin_model_simu.slx', 5);
sim('task2_lin_model_simu.slx', 5);

%%% =================================================================== %%%
%% Task 3                                                                %%
%%% =================================================================== %%%

Ts = 0.5; % in s
lin_sys = ss(A, B, C, 0);

% discretize the linearized model
lin_dsys = c2d(lin_sys, Ts);

% extract Matrizes 
Ad = lin_dsys.A;
Bd = lin_dsys.B;
Cd = lin_dsys.C;
Dd = lin_dsys.D;

%%% =================================================================== %%%
%% Task 4                                                                %%
%%% =================================================================== %%%
Np = 15;
Nc = 10;
n = size(Ad,1);
m = size(Bd,2);
p = size(Cd,1);

% Function call to calculate Matrices F G and H
[F,G,H] = Task4_Funcs.F_G_H_Matrix_calculation(Ad, Bd, Cd, Nc, Np, m, n);

% Weight Matrices
Q = 1*eye(p*Np);
R = 1*eye(m*Nc);

% Check definitnes of the matrix
if eig(H'*Q*H+R)<=0
    error("definitness Problem: Task4.");
end

% Calculate K Matrix for unconstraint MPC
K = [eye(m),zeros(m,m*(Nc-1))]*inv(H'*Q*H+R)*H'*Q;


% reference
Simtime = 100;
data = (15+h(2))*ones(100/Ts,Np*p);
sampleRate = 1/Ts;   %Hz

% prior to 2018b
timeSamples = seconds(0 : 1/sampleRate : (size(data)-1)/sampleRate);
r = timetable(timeSamples', data);


%%% =================================================================== %%%
%% Task 5                                                                %%
%%% =================================================================== %%%

% Calculate Fx Gx and Hx for state constraint case
[Fx,Gx,Hx] = Task5_Funcs.Fx_Gx_Hx_Matrix_calculation(Ad,Bd,Nc,Np,m,n);



%%% =================================================================== %%%
%% Task 6                                                                %%
%%% =================================================================== %%%


%%% =================================================================== %%%
%% Task 7                                                                %%
%%% =================================================================== %%%
