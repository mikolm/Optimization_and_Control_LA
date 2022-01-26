classdef Task4_Funcs
    methods(Static)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        function [F,G,H] = F_G_H_Matrix_calculation(Ad,Bd,Cd,Nc,Np,m,n)

            % Matrix inizialization
            F = [];
            G = [];
            

            for index = 1:Np
                F_loop = Cd*Ad^(index);
                F = [F;F_loop];
            end

            for index = 1:Np
                A_itter = eye(n);

                for counter = 0: (index-1)

                    if counter == 0
                        A_itter = A_itter;
                    else
                        A_itter = A_itter + Ad^counter;
                    end

                end

                G_loop = Cd*A_itter*Bd;
                G = [G; G_loop];
            end

            H_row = zeros(1,m*Nc);
            H_row(1) = G(1);

            H = toeplitz(G,H_row); %works only if C*B is a scalar
        
        end
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        
        function balab()
            
        end
    end
end
