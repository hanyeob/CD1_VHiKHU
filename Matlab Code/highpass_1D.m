%INPUT type: table, Columns:'Time','IRSensor','XAxis','YAxis','ZAxis','Velocity','1D_acc'
function NEW_DATA = highpass_1D(INPUT) 
    DATA = table2array(INPUT);
    Ax = DATA(:,3);Ay = DATA(:,4);Az = DATA(:,5);
    Ax_filted = highpass(Ax, 7, 2000);Ay_filted = highpass(Ay, 7, 2000);Az_filted = highpass(Az, 7, 2000);
    DATA(:,3) = Ax_filted;DATA(:,4) = Ay_filted;DATA(:,5) = Az_filted;
 
    acc_1D = dft321(DATA(:,3:5));

    NEW_DATA = [DATA acc_1D];
    NEW_DATA = array2table(NEW_DATA,'VariableNames',{'Time','IRSensor','XAxis','YAxis','ZAxis','Velocity','1D_acc'});
%     NEW_DATA(:,'1D_acc') = [];
%     NEW_DATA = addvars(NEW_DATA,acc_1D);

    tablename = inputname(1);
    filename = strcat(tablename,"_1D.csv");
    writetable(NEW_DATA,filename);
end