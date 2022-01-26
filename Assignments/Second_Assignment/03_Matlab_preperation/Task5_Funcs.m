classdef Task5_Funcs
    methods(Static)
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        function [Fx,Gx,Hx] = Fx_Gx_Hx_Matrix_calculation(Ad,Bd,Nc,Np,m,n)
            
            % Matrix initzialisation
            Fx = [];
            Gx = [];

            for index = 1:Np
                Fx_loop = Ad^(index);
                Fx = [Fx;Fx_loop];
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

                Gx_loop = A_itter*Bd;
                Gx = [Gx; Gx_loop];
            end
            
            % Calculate Töplitz Marix
            toplitzcolumn = Gx;
            Hx = [];
            Hx(:,1) = Gx;
            for counter = 2:m*Nc
                
                vektorneu = [zeros(size(Bd)); toplitzcolumn];
                toplitzcolumn = vektorneu(1:(length(vektorneu)-size(Bd(:,1))));
                Hx(:,counter) = toplitzcolumn;
                
            end
        end 
    end
end



