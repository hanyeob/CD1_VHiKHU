function acc1d(INPUT)
    tablename = inputname(1);
    filename = strcat(tablename,"_1D.csv");
    mat = table2array(INPUT);
    acc_1D = dft321(mat(:,3:5));
    acc_1D = table(acc_1D);
    INPUT_1D = [INPUT acc_1D];
    writetable(INPUT_1D,filename);
    figure;
    plot(INPUT_1D.Time,INPUT_1D.('acc_1D'),'DisplayName','1D Acc');
    title(tablename); ylabel('Acceleration');
    yyaxis right;  plot(INPUT_1D.Time,INPUT_1D.Velocity,'DisplayName','Velocity');ylabel('Velocity');ylim([0 25]);hold off;
end