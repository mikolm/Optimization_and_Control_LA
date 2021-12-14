classdef Task3_Funcs
    methods(Static)
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        function visualisation(l, lin_simdata)

            % variables
            counter = 1;
            speedup = 20;
            n_iter = length(lin_simdata.time(:));
            linewidth = 2.5;
            rgb_color = [0.75, 0.37, 1];

            % assign meaningful names
            bottom_pos_x = lin_simdata.signals.values(:,1);   
            top_pos_x = bottom_pos_x + l*sin(lin_simdata.signals.values(:,2));
            top_pos_y = l*cos(lin_simdata.signals.values(:,2));

            % plot animation
            figure()
            set(gcf, 'Units', 'Normalized', 'Position', [0.2, 0.2, 0.6, 0.6]);
            while counter <= n_iter  
                
                if counter >= n_iter-speedup
                    counter = n_iter;
                end
                
                plot([bottom_pos_x(counter), top_pos_x(counter)], ...
                     [0, top_pos_y(counter)], '-', 'linewidth', linewidth, ...
                      'color', rgb_color);  
                grid on; box on; hold on;
                %plot(bottom_pos_x(counter), 0, 'x', 'linewidth', linewidth, ...
                 %    'color', rgb_color);
                plot(top_pos_x(counter), top_pos_y(counter), 'o', ...
                    'linewidth', 2.5*linewidth, 'color', rgb_color);
                % figure cosmetics 
                title('Pendulum Movement', 'Interpreter', 'Latex', 'Fontsize', 18);
                axis equal
                xlim([-1,1]); ylim([-0.4,0.4]);
                xticks(-1:0.2:1); yticks(-1:0.2:1);
                xlabel('$x_W$ in m', 'Interpreter', 'Latex', 'Fontsize', 14);
                txt = ['t = ', num2str(lin_simdata.time(counter,1)), 's'];
                text(0.4, -0.2, txt, 'Fontsize', 14);

                if counter == 1
                    pause(1);
                    clf;
                elseif counter == n_iter
                    break
                else
                    pause(1e-6);
                    clf
                end
                counter = counter + speedup;
            end
        end 
    end
end



