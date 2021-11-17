function segment5(INPUT)
    NEW_DATA = INPUT;

    tablename = inputname(1);
    j=1; next=1; fileNum=1;
    while j < height(NEW_DATA) 
        while NEW_DATA.Velocity(j) == NEW_DATA.Velocity(j+next) && j+next<height(NEW_DATA) 
            next=next+1;
        end
        filename = sprintf('F1\\%sseg%d_%.2f.csv',tablename, fileNum, NEW_DATA.Velocity(j));
        writetable(NEW_DATA(j:j+next-1,:),filename);
        fileNum = fileNum+1;
        j = j+next;
        next = 1;
    end
end