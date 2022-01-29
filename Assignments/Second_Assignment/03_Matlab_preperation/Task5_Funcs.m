classdef Task5_Funcs
    methods(Static)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        function [F,G,H] = Fx_Gx_Hx_Matrix_calculation(Ad,Bd,Nc,Np,m,n)

            % Matrix inizialization
            F = [];
            G = [];
            
            for index = 1:Np
                F_loop = Ad^(index);
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

                G_loop = A_itter*Bd;
                G = [G; G_loop];
            end

           
            % Calculate "Töplitz" Marix           
            H = zeros(n*Np,m*Nc);
            H(:,1:m) = G;
            
            for counter = m+1:m:m*(Nc-1)+1
                H_shift = H(:,counter-m:counter-1);
                H_shift = [zeros(size(Bd)); H_shift];
                H_shift = H_shift(1:n*Np,:);
                
                H(:,counter:counter+m-1) = H_shift;
            end

            

        
        end
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        
        function balab()
            
        end
    end
end
