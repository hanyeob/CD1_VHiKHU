function vel2acc_pre(INPUT)
    INPUT{:,3} = 6/3.3 * (INPUT{:,3} - 3.3) + 3;
    INPUT{:,4} = 6/3.3 * (INPUT{:,4} - 3.3) + 3;
    INPUT{:,5} = 6/3.3 * (INPUT{:,5} - 3.3) + 3;

    % highpass
    DATA = table2array(INPUT);
    Ax = DATA(:,3);Ay = DATA(:,4);Az = DATA(:,5);
    Ax_filted = highpass(Ax, 7, 2000);Ay_filted = highpass(Ay, 7, 2000);Az_filted = highpass(Az, 7, 2000);
    DATA(:,3) = Ax_filted;DATA(:,4) = Ay_filted;DATA(:,5) = Az_filted;
 
    % 1D
    acc_1D = dft321(DATA(:,3:5));

    NEW_DATA = [DATA acc_1D];
    NEW_DATA = array2table(NEW_DATA,'VariableNames',{'Time','IRSensor','XAxis','YAxis','ZAxis','Velocity','1D_acc'});

    segment5_1d_only(NEW_DATA);
end
