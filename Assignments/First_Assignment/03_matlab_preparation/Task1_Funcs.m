classdef Task1_Funcs
    methods(Static)
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        function [l] = perfrom_optimization(phi, domega, g, norm)

            yalmip('clear') % delete old yalmip variables

            A = sin(phi);

            phat = sdpvar(1,1); % Declare optimization variables

            e = domega-A*phat; % Error

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
            l = g/phat; % Compute results

            disp(['Length l yielded by the ', norm, ' optimization: l= ', num2str(l), 'm']);
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
    end
end
