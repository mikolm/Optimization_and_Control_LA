function delta_u_hat = MPC_function(input)
    
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
    u_eq = evalin('base','u_eq');
    x_eq = evalin('base','x_eq');
    x_upper_limit = evalin('base','x_upper_limit');
    x_lower_limit = evalin('base','x_lower_limit');
    u_upper_limit = evalin('base','u_upper_limit');
    u_lower_limit = evalin('base','u_lower_limit');
    roh = evalin('base','roh');
    
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

    %calculate L and M Matrizes for constraints
    L = repmat(eye(m),Nc,1);
    M_row = [eye(m),zeros(m,(m*Nc)-m)];
    M = toeplitz(L(:,1), M_row(1,:));
   
    % actuatiting variable
    
    u_min = -u_eq(1) + u_lower_limit;
    u_max = u_min + u_upper_limit - u_lower_limit;
    actuating_constraint = [L * (last_uk - u_min); L*(u_max - last_uk)]; 
        
    %state variable
    
    x_min = -x_eq + h + x_lower_limit;
    xmin_vec = repmat(x_min,Np,1);
    x_max = x_min + x_upper_limit - x_lower_limit;
    xmax_vec = repmat(x_max,Np,1);
    
    state_variable_constraint = [gkx_hat - xmin_vec; xmax_vec - gkx_hat];
    
    W = [-M; M; -Hx; Hx];
    w_hat = [actuating_constraint; state_variable_constraint];
    v_hat = [ones(2*size(M,1),1);ones(2*size(Hx,1),1)];
    constraints = [W*delta_u_hat <= w_hat + v_hat * epsilon, epsilon >=0];
    %%

    ek_hat = gk_hat -rk;
    
    % Objective Function
    J = delta_u_hat' * (H'*Q*H+R) * delta_u_hat + 2*delta_u_hat'* H' * Q * ek_hat + roh * epsilon;
            
    diagnostics = optimize(constraints,J,options);
    if diagnostics.problem > 0
        error('Error during optimization')
    end

    delta_u_hat_vec = value(delta_u_hat);
    delta_u_hat = delta_u_hat_vec(1);

end