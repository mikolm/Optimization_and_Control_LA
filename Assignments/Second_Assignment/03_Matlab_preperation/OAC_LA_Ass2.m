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


% Sampling Time
Ts = 0.5;
% Simulation Time
T_sim = 80;
% Reference
y_eq = 15;
% Tank limits
x_lower_limit = [0; 0];
x_upper_limit = [20; 20];
% Control action limit
u_lower_limit = 0;
u_upper_limit = 5;
% prediction horizon control horizon
Np = 15;
Nc = 10;
% soft constraints parameter
roh = 1000;

%%% =================================================================== %%%
%% Task 1                                                                %%
%%% =================================================================== %%%

% calculation of the equilibrium points
x2_eq = y_eq+h(2);% in cm

% matlab results of the equilibrium point
[u_eq,x_eq] = Task1_Funcs.equilibrium(alpha, beta, gamma, k, x2_eq);

x0=[0;0];
[A,B,C,D] = linmod('task1_nonlin_model_simu', x_eq, u_eq(1));

C = [0,1];
D = 0;


%%% =================================================================== %%%
%% Task 2                                                                %%   
%%% =================================================================== %%%

%initial conditions
x0 = x_eq;

% nonlinear and linear simulation to verify the linearized model 
% and the calculated equilibrium point

sim('task2_nonlin_model_simu.slx', 5);
sim('task2_lin_model_simu.slx', 5);

%%% =================================================================== %%%
%% Task 3                                                                %%
%%% =================================================================== %%%

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
n = size(Ad,1);
m = size(Bd,2);
p = size(Cd,1);

% Function call to calculate Matrices F G and H
[F,G,H] = Task4_Funcs.F_G_H_Matrix_calculation(Ad,Bd,Cd,Nc,Np,m,n,p);


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
r2 = y_eq+h(2);
r = zeros(T_sim/Ts,Np*m);
r = repmat(r2,T_sim/Ts,Np);
timesteps = (0:Ts:T_sim-Ts)';
r = [timesteps, r];

x0_linear = -x_eq+h;
sim('task4_lin_nonlin_model_MPC_simu',T_sim);




%%% =================================================================== %%%
%% Task 5                                                                %%
%%% =================================================================== %%%

% Calculate Fx Gx and Hx for state constraint case
% same function but for Cd Matrix Identety Matrix

[Fx,Gx,Hx] = Task5_Funcs.Fx_Gx_Hx_Matrix_calculation(Ad,Bd,Nc,Np,m,n);
sim('task5_constraint_mpc',T_sim);


%%% =================================================================== %%%
%% Task 6                                                                %%
%%% =================================================================== %%%
Np = 40;
Nc = 35;
% Weight Matrices
Q = 10*eye(p*Np);
R = 1*eye(m*Nc);

[F,G,H] = Task4_Funcs.F_G_H_Matrix_calculation(Ad,Bd,Cd,Nc,Np,m,n,p);
[Fx,Gx,Hx] = Task5_Funcs.Fx_Gx_Hx_Matrix_calculation(Ad,Bd,Nc,Np,m,n);

% Calculate K Matrix for unconstraint MPC
K = [eye(m),zeros(m,m*(Nc-1))]*inv(H'*Q*H+R)*H'*Q;

% reference
r2 = y_eq+h(2);
r = zeros(T_sim/Ts,Np*m);
r = repmat(r2,T_sim/Ts,Np);
timesteps = (0:Ts:T_sim-Ts)';
r = [timesteps, r];


sim('task5_constraint_mpc',T_sim);
 

%%% =================================================================== %%%
%% Task 7                                                                %%
%%% =================================================================== %%%
T_sim = 80;
% Weight Matrices
Q = 1*eye(p*Np);
R = 1*eye(m*Nc);
roh = 50;
Nc = 80;
Np = 80;

% evaluate matrices
[F,G,H] = Task4_Funcs.F_G_H_Matrix_calculation(Ad,Bd,Cd,Nc,Np,m,n,p);
[Fx,Gx,Hx] = Task5_Funcs.Fx_Gx_Hx_Matrix_calculation(Ad,Bd,Nc,Np,m,n);

% reference
r2 = y_eq+h(2);
r = zeros(T_sim/Ts,Np*m);
r = repmat(r2,T_sim/Ts,Np);
timesteps = (0:Ts:T_sim-Ts)';
r = [timesteps, r];

sim('task7_soft_constraint_mpc',T_sim);

