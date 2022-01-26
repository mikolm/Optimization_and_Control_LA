function delta_u_hat = MPC_softcon_function(input)
    
    % get Data from Workspace
    H = evalin('base','H');
    Hx = evalin('base','Hx');
    Q = evalin('base','Q');
    R = evalin('base','R');
    p = evalin('base','p');
    Np = evalin('base','Np');
    m = evalin('base','m ');
    Nc = evalin('base','Nc');
    h = evalin('base','h');
    
    % decompose Input vector 
    rk = input(1:Np*p);
    gkx_hat = input((Np*p)+1:3*Np*p);
    gk_hat= input((3*Np*p)+1:4*Np*p);
    last_uk= input((4*Np*m)+1:end);
        
    
    % prepare yalmip
    yalmip('clear') % delete old yalmip variables
    options = sdpsettings('verbose',0,'solver','qpoases','cachesolvers',1);
    delta_u_hat = sdpvar(m*Nc,1);
    epsilon = sdpvar(1);

%% Constraints

    % calculate L and M Matrizes for constraints
    L=[];
    for index = 1:Nc
        L_loop = eye(m);
        L = [L; L_loop];
    end

    M_row = [eye(m),zeros(m,m*(Nc-1))];
    M = toeplitz(L(:,1), M_row(1,:));

    
    % actuatiting variable
    u_min = 0;
    u_max = 5;
    actuating_constraint = [L * last_uk - u_min; u_max - L * last_uk];

    % %change of the actuatiting variable
    % delta_u_min = [];
    % delta_u_max =[];
    % actuating_change_constraint = [-delta_u_min;delta_u_max];

    % %controlled variable
    % y_hat_min = [];
    % y_hat_max = [];
    % controll_variable_constraint = [gk_hat - y_hat_min; y_hat_max - gk_hat];

    %state variable
    x_min = h;
    xmin_vec = [];
    for counter = 1:Np
        
        xmin_vec = [xmin_vec; x_min];
    
    end
    
    disp(xmin_vec)

    x_max = h+ [20; 20];
    xmax_vec = [];
    for counter = 1:Np
        
        xmax_vec = [xmax_vec; x_max];
    
    end
    
    state_variable_constraint = [gkx_hat - xmin_vec; xmax_vec - gkx_hat];



    %w_hat = [actuating_constraint;actuating_change_constraint;controll_variable_constraint];
    %E = eye(size(M));
    %W = [-M; M ; -E ; E; H; -H];
    
    W = [-M; M; -Hx ; Hx];
    w_hat = [actuating_constraint;state_variable_constraint];
    
%%

    ek_hat = gk_hat -rk;
    
    v_hat = ones(size(w_hat));
    roh = 100;
    
    constraints = W*delta_u_hat <= w_hat+v_hat*epsilon;
    
    % Objective Function
    J = delta_u_hat' * (H'*Q*H+R) * delta_u_hat + 2*delta_u_hat'* H' * Q * ek_hat + roh*epsilon;
            
    diagnostics = optimize(constraints,J,options);
    if diagnostics.problem > 0
        error('Error during optimization')
    end

    delta_u_hat_vec = value(delta_u_hat);
    delta_u_hat = delta_u_hat_vec(1);

end