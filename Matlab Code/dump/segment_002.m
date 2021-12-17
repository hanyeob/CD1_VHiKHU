function segment_002(INPUT)
    NEW_DATA = INPUT;
    tablename = inputname(1);
    j=1; next=1; fileNum=1;
    while j < height(NEW_DATA) 
        currVel = NEW_DATA.Velocity(j);
        while currVel == NEW_DATA.Velocity(j+next) && j+next<height(NEW_DATA) 
            next=next+1;
        end
        index=next;
        while currVel-0.2 <= NEW_DATA.Velocity(j+next) && currVel+0.2 >= NEW_DATA.Velocity(j+next) && j+next<height(NEW_DATA) 
            next=next+1;
        end
            filename = sprintf('SEG1\\%sseg%d_%.2f.csv',tablename, fileNum, NEW_DATA.Velocity(j));
            writetable(NEW_DATA(j:j+next-1,:),filename);
            fileNum = fileNum+1;
        j=j+index;
        next = 1;
    end
end