% --------------------------------------------------------------------------- %
% MPC_init.m
% OAC Lab
% Inlab-file to calculate all variables needed for the MPC.slx file
% Michael Kolm
% 29.01.2022    
% --------------------------------------------------------------------------- %

% Tidy up Matlab
clear all
close all
clc

% Declaration of the Variables
% Reference
y_eq = 15;
% Tank limits
x_lower_limit = [0; 0];
x_upper_limit = [20; 20];
% Control action limit
u_lower_limit = 0;
u_upper_limit = 10;
% prediction horizon control horizon
Np = 40;
Nc = 20;
% soft constraints parameter
roh = 1000;

% load Data of the real model and convert it to the format used in our
% preperations
load('Model1_Pumps_120122.mat');
load('Model1_Tanks_120122.mat');

alpha = [alpha1; alpha2];
beta = [beta1; beta2];
gamma = [gamma1; gamma2];
h = [h01; h02];
k = [k1; k2];

% Sampling / Discretization time
Td = 0.5;
Ts = Td;


%%% =================================================================== %%%
%% Task 1                                                                %%
%%% =================================================================== %%%
% calculation of the equilibrium points

x2_eq = y_eq+h(2);% in cm
% matlab results of the equilibrium point
[u_eq,x_eq] = Task1_Funcs.equilibrium(alpha, beta, gamma, k, x2_eq);
% Analytical linearization
[A, B] = Task1_Funcs.lin_matrices_ana(x_eq,u_eq,k,beta,gamma);
C = [0,1];
D = 0;


%%% =================================================================== %%%
%% Task 3                                                                %%
%%% =================================================================== %%%
% Discretization of the linearized system

lin_sys = ss(A, B, C, 0);

lin_dsys = c2d(lin_sys, Ts);

% extract Matrizes 
Ad = lin_dsys.A;
Bd = lin_dsys.B;
Cd = lin_dsys.C;
Dd = lin_dsys.D;


%%% =================================================================== %%%
%% Task 5                                                                %%
%%% =================================================================== %%%
% Calculate the matrices for the constrained MP-controller

n = size(Ad,1);
m = size(Bd,2);
p = size(Cd,1);

% Weight Matrices
Q = 1*eye(p*Np);
R = 1*eye(m*Nc);

%calculate L and M Matrizes for constraints
L = repmat(eye(m),Nc,1);
M_row = [eye(m),zeros(m,(m*Nc)-m)];
M = toeplitz(L(:,1), M_row(1,:));

[F,G,H] = Task4_Funcs.F_G_H_Matrix_calculation(Ad,Bd,Cd,Nc,Np,m,n,p);
[Fx,Gx,Hx] = Task5_Funcs.Fx_Gx_Hx_Matrix_calculation(Ad,Bd,Nc,Np,m,n);
