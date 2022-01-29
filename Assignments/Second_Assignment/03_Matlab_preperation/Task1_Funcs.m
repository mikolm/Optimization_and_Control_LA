classdef Task1_Funcs
    methods(Static)
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        function [u_eq,x_eq] = equilibrium(alpha,beta,gamma,k,x2_eq)

            syms u1_eq x1_eq

            eq_system = [ % first ODE
                          k(1)*sqrt(x1_eq) == alpha(1) + sqrt( beta(1)+gamma(1)*u1_eq ), ...
                          % second ODE
                          k(2)*sqrt(x2_eq) == alpha(1) + sqrt( beta(1)+gamma(1)*u1_eq )];

            S = solve(eq_system, [u1_eq, x1_eq]);
            x_eq = [double(S.x1_eq); x2_eq];
            u_eq = [double(S.u1_eq); 0];
        end
        
        
        function [A_ana, B_ana] = lin_matrices_ana(x_eq,u_eq,k,beta,gamma)
            
            A_ana = [-k(1)/2*x_eq(1)^(-0.5), 0;
                     k(1)/2*x_eq(1)^(-0.5), -k(2)/2*x_eq(2)^(-0.5)];
                 
            B_ana = [gamma(1)/2*(beta(1) + gamma(1)*u_eq(1))^(-0.5);
                                                                  0];     
        end
    end
end
