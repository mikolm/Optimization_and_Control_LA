clc;
Nc = 4;
m = 3;
dim = m * Nc

L=[];
for index = 1:Nc
    L_loop = eye(m);
    L = [L; L_loop];
end

M_row = [eye(m),zeros(m,m*(Nc-1))];

M = toeplitz(L(:,1), M_row(1,:));

%H = p*np x  m*Nc
E = eye(size(M))
W = [-M; M ; -E ; E; H; -H];

% actuatiting variable
u_min = [];
u_max = [];
actuating_constraint = [L * last_uk - u_min; u_max - L * last_uk];

%change of the actuatiting variable
delta_u_min = [];
delta_u_max =[];
actuating_change_constraint = [-delta_u_min;delta_u_max];

%controlled variable
y_hat_min = [];
y_hat_max = [];
controll_variable_constraint = [gk_hat - y_hat_min; y_hat_max - gk_hat];

w = [actuating_constraint;actuating_change_constraint;controll_variable_constraint];

%%
M = 5;

x = [1,2,3,4,5,6,7];
X_buf = buffer(x,M,M-1)
%%
rk=2;
last_rk_vec = [];
last_rk_vec = [last_rk_vec,rk]

%% 
vektoralt = [0 0 0 0 0]
wert = 1:1:7;
for index =  1:7
    vektorneu = [wert(index), vektoralt];
    vektoralt = vektorneu(1:(length(vektorneu)-1))
end

%%

buffer = [0 0 0 0 0]
wert = 1:1:7;
for index =  1:7
    vektorneu = [wert(index), buffer];
    buffer = vektorneu(1:(length(vektorneu)-1));
    buffer'
end

%%

A = [1 1; 2 2];
F = [];
Np =15;
for index = 1:Np
    Fx_loop = A^(index);
    Fx = [F;Fx_loop]
end
%%
F = [];
G = [];
H = zeros(p*Np,m*Nc);

Ad = [1 1; 2 2];
Cd = [1 4];


for index = 1:Np
    Fx_loop = Ad^(index);
    Fx = [Fx;Fx_loop]
end


%% 
a = [1;2];
anew = []
for counter = 1:15
    anew = [anew; a]
end

size(anew)


%%













