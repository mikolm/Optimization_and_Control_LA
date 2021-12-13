classdef Task3_Funcs
    methods(Static)
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        function visualisation(l, lin_simdata)

            % variables
            counter = 1;
            speedup = 20;
            n_iter = length(lin_simdata.time(:));
            linewidth = 3;

            % assign meaningful names
            bottom_pos_x = lin_simdata.signals.values(:,1);   
            top_pos_x = bottom_pos_x + l*sin(lin_simdata.signals.values(:,2));
            top_pos_y = l*cos(lin_simdata.signals.values(:,2));

            % plot animation
            figure(1)
            %set(gcf, 'Units', 'Normalized', 'Position', [0.2, 0.2, 0.6, 0.6]);
            while counter < n_iter
                plot([bottom_pos_x(counter), top_pos_x(counter)], ...
                     [0, top_pos_y(counter)], '-', 'linewidth', linewidth, ...
                      'color', [0.8,0,0]);  
                grid on; box on; hold on;
                plot(bottom_pos_x(counter), 0, 'x', 'linewidth', linewidth, ...
                     'color', [0.8,0,0]);
                plot(top_pos_x(counter), top_pos_y(counter), 'o', ...
                    'linewidth', linewidth, 'color', [0.8,0,0]);
                % figure cosmetics 
                title('Pendulum Movement', 'Linewidth', 16);
                axis equal
                xlim([-1,1]); ylim([-1,1]);
                xticks(-1:0.2:1);
                yticks(-1:0.2:1);
                txt = ['t = ', num2str(lin_simdata.time(counter,1)), 's'];
                text(0.3, 0.75, txt, 'Fontsize', 14);

                if counter == 1
                    pause(1);
                    clf;
                elseif counter >= n_iter-speedup
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



