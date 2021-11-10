function graph_3d_vel(new_DATA);    
    tablename = inputname(1);
    figure();
    plot(new_DATA.Time,new_DATA.X_axis,'DisplayName','X axis');hold on;
    plot(new_DATA.Time,new_DATA.Y_axis,'DisplayName','Y axis');
    plot(new_DATA.Time,new_DATA.Z_axis,'DisplayName','Z axis');
    title(tablename); ylabel('Acceleration');
    yyaxis right; plot(new_DATA.Time,new_DATA.Velocity,'DisplayName','Velocity');ylabel('Velocity');ylim([0 30]);hold off;
end