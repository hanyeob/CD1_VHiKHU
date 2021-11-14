function NEW_DATA = treaterror(INPUT)
    DATA = table2array(INPUT(:,6));
    i=10;
    while i<200000
        if DATA(i) - DATA(i+1) >= 0.5
            j=1;
            while DATA(i+1) == DATA(i+j) && (i+j) < 200000
                j = j+1;
            end
            DATA(i+1:i+j-1) = (DATA(i)+DATA(i+j)+DATA(i+1))/3;
        end
        i = i+1;
    end
    while i<700000
        if DATA(i) - DATA(i+1) >= 0.7
            j=1;
            while DATA(i+1) == DATA(i+j) && (i+j) < 720000
                j = j+1;
            end
            DATA(i+1:i+j-1) = (DATA(i)+DATA(i+j)+DATA(i+1))/3;
        end
        i = i+1;
    end
    NEW_DATA=DATA;
end