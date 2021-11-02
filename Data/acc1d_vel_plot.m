function acc1d_vel_plot(Field4_1D);
    tablename = inputname(1);
    figure;
    plot(Field4_1D.Time,Field4_1D.('1D_acc'),'DisplayName','1D Acc');
    title(tablename); ylabel('Acceleration');
    yyaxis right;  plot(Field4_1D.Time,Field4_1D.Velocity,'DisplayName','Velocity');ylabel('Velocity');ylim([0 25]);hold off;
end