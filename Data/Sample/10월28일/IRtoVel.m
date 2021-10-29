function new_DATA = IRtoVel(DATA)
    tablename = inputname(1);
    filename = strcat(tablename,".csv");
    rows = height(DATA);
    last_check = 0;
    count = 0;
    last_row = 1;

    LENGTH = 25; % 자전거 지름(circumference) / 8(n) [cm]
    delta = 0.5; % 측정 단위시간(sampling cylce time) [ms]
    Velocity = zeros(rows,1);

    for i = 2:rows
        if DATA.Dev1_ai0(i) < 2.25
            curr_check = 0;
        else 
            curr_check = 1;
        end

        if  curr_check ~= last_check || i == rows
            vel = LENGTH * 36 / (count*delta); % *36 for [cm/ms] to [km/h] 
            Velocity(last_row : i) = vel;
            last_row = i+1;
            last_check = curr_check;
            count = 0;
        else
            count = count + 1;
        end
    end

    new_DATA = addvars(DATA,Velocity);
    new_DATA = renamevars(new_DATA,["Dev1_ai0","Dev1_ai1","Dev1_ai2","Dev1_ai3"], ...
                 ["IR Sensor","X axis","Y axis","Z axis"]);

    writetimetable(new_DATA,filename);
end