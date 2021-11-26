function lengmat = selectbest(inputname)
    lengmat = [];
    for vel = 0.2:0.4:30
        filename = sprintf('%s1Dseg_%.1fkmh.csv',inputname,vel);
        if isfile(filename)
            rm = readmatrix(filename);
            lengmat = [lengmat length(rm)];
        else
            lengmat = [lengmat 0];
        end
    end
    figure;
    plot(lengmat)
end
