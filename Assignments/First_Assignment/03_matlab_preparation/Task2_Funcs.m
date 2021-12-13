classdef Task2_Funcs
    methods(Static)
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        function [phat] = perfrom_optimization_large_pendulum(i_A, phi, v_W, omega, domega, l, g, norm)

            yalmip('clear') % delete old yalmip variables

            A = [l*domega.*(cos(phi)).^2 - l*omega.^2.*sin(phi).*cos(phi), ...
                cos(phi).*i_A, cos(phi).*v_W];

            phat = sdpvar(3,1); % Declare optimization variables

            e = domega*l - g*sin(phi) -A*phat; % Error

            bounds = sdpvar(length(e),1);
            constraints = [-bounds <= e <= bounds];
            options = sdpsettings('verbose',0);

            % what optimization is performed
            if strcmp(norm,'L1')
                diagnostics = optimize(constraints,sum(bounds),options)    
            elseif strcmp(norm,'L2')
                diagnostics = optimize(constraints,sum(bounds'*bounds),options)       
            elseif strcmp(norm,'Linfty')
                diagnostics = optimize(constraints,max(bounds),options)        
            else
                error('ERROR: wrong setting for the cost function');
            end

            % error handling
            if diagnostics.problem > 0
                error('Error during optimization')
            end

            % calculate the unknown parameter based on the optimization variable
            phat = value(phat); % Convert results in double variables

        end


        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        function params = solve_LGS_large_pendulum(p, domega, l, g, phi, omega, i_A, v_W)

            syms mw V k1

            ms = 0.5; % kg

            eq_system = [ms/(mw+ms) == p(1), ...
                         -V/(mw+ms) == p(2), ...
                         k1/(mw+ms) == p(3)];

            S = solve(eq_system, [mw,V,k1]);

            params = [double(ms), double(S.mw), double(S.V), double(S.k1)];

        end


        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        function compare_phi(t_measurements, phi, phi_simu)

            % plot the results in a figure
            figure()
                set(gcf, 'Units', 'Normalized', 'Position', [0, 0, 0.8, 0.9]);
                %
                subplot(3,1,1)
                plot(t_measurements, phi, 'linewidth', 2);
                hold on; box on; grid on;
                plot(phi_simu.time(:), phi_simu.signals.values(:,1), '--', 'linewidth', 2);
                title('Result of the $L_1$ Optimization', 'Interpreter', 'Latex','Fontsize', 14);
                xlabel('t in s', 'Interpreter', 'Latex', 'Fontsize', 12); 
                ylabel('$\varphi$ in rad', 'Interpreter', 'Latex','Fontsize', 12);
                %ylim([0,2*pi]); yticks([0:pi/2:2*pi]);
                %yticklabels({'0','pi/2','pi', '3/2 pi', '2pi'});
                %
                subplot(3,1,2)
                plot(t_measurements, phi, 'linewidth', 2);
                hold on; box on; grid on;
                plot(phi_simu.time(:), phi_simu.signals.values(:,2), '--', 'linewidth', 2);
                title('Result of the $L_2$ Optimization', 'Interpreter', 'Latex','Fontsize', 14);
                xlabel('t in s', 'Interpreter', 'Latex', 'Fontsize', 12); 
                ylabel('$\varphi$ in rad', 'Interpreter', 'Latex','Fontsize', 12);
                %ylim([0,2*pi]); yticks([0:pi/2:2*pi]);
                %yticklabels({'0','pi/2','pi', '3/2 pi', '2pi'});
                %
                subplot(3,1,3)
                plot(t_measurements, phi, 'linewidth', 2);
                hold on; box on; grid on;
                plot(phi_simu.time(:), phi_simu.signals.values(:,3), '--', 'linewidth', 2);
                title('test', 'Fontsize', 16); 
                title('Result of the $L_\infty$ Optimization', 'Interpreter', 'Latex','Fontsize', 14);
                xlabel('t in s', 'Interpreter', 'Latex', 'Fontsize', 12); 
                ylabel('$\varphi$ in rad', 'Interpreter', 'Latex','Fontsize', 12);
                %ylim([0,2*pi]); yticks([0:pi/2:2*pi]);
                %yticklabels({'0','pi/2','pi', '3/2 pi', '2pi'});
        end


        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        function compare_x_w(t_measurements, x_W, x_W_simu)

            % plot the results in a figure
            figure()
                set(gcf, 'Units', 'Normalized', 'Position', [0, 0, 0.8, 0.9]);
                %
                subplot(3,1,1)
                plot(t_measurements, x_W, 'linewidth', 2);
                hold on; box on; grid on;
                plot(x_W_simu.time(:), x_W_simu.signals.values(:,1), '--', 'linewidth', 2);
                title('Result of the $L_1$ Optimization', 'Interpreter', 'Latex','Fontsize', 14);
                xlabel('t in s', 'Interpreter', 'Latex', 'Fontsize', 12); 
                ylabel('$x_W$ in m', 'Interpreter', 'Latex','Fontsize', 12);
                %
                subplot(3,1,2)
                plot(t_measurements, x_W, 'linewidth', 2);
                hold on; box on; grid on;
                plot(x_W_simu.time(:), x_W_simu.signals.values(:,2), '--', 'linewidth', 2);
                title('Result of the $L_2$ Optimization', 'Interpreter', 'Latex','Fontsize', 14);
                xlabel('t in s', 'Interpreter', 'Latex', 'Fontsize', 12); 
                ylabel('$x_W$ in m', 'Interpreter', 'Latex','Fontsize', 12);
                %
                subplot(3,1,3)
                plot(t_measurements, x_W, 'linewidth', 2);
                hold on; box on; grid on;
                plot(x_W_simu.time(:), x_W_simu.signals.values(:,3), '--', 'linewidth', 2);
                title('test', 'Fontsize', 16); 
                title('Result of the $L_\infty$ Optimization', 'Interpreter', 'Latex','Fontsize', 14);
                xlabel('t in s', 'Interpreter', 'Latex', 'Fontsize', 12); 
                ylabel('$x_W$ in m', 'Interpreter', 'Latex','Fontsize', 12);
        end
    end
end
