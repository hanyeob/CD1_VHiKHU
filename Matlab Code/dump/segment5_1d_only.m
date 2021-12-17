%%INPUT 데이터는 노이즈(속도 이상한 값)와 측정 끝부분 급격한 감속구간 이후를 제외했습니다.

function result = segment5_1d_only(INPUT)
    NEW_DATA = INPUT;
    threshold = 0.2;
    maxvel = 25;
    routine = 0.5; SampleRate=2000;
    filecheck = zeros(1, fix(maxvel/(threshold*2))+1);
    tablename = inputname(1);
    j=1; next=1; fileNum=1;

    NEW_DATA.Velocity(isinf(NEW_DATA.Velocity)|isnan(NEW_DATA.Velocity)) = 0;
    while j < height(NEW_DATA)

%         while (NEW_DATA.Velocity(j)+threshold) >= NEW_DATA.Velocity(j+next) ...
%                && NEW_DATA.Velocity(j+next) >= (NEW_DATA.Velocity(j)-threshold) ...
%                && j+next<height(NEW_DATA) 
%           next=next+1;    
%         end

        while NEW_DATA.Velocity(j) == NEW_DATA.Velocity(j+next)...
              && j+next<height(NEW_DATA) 
            next=next+1;
        end


        constvel = fix(NEW_DATA.Velocity(j)/(threshold*2))*(threshold*2)+threshold; % 대표 속도
        index = fix(NEW_DATA.Velocity(j)/(threshold*2))+1;
        filename = sprintf('%sseg_%.1f.csv',tablename, constvel);

        if filecheck(index) == 0
            writetable(NEW_DATA(j:j+next-1,7),filename);
            filecheck(index) = 1;
        else
            writetable(NEW_DATA(j:j+next-1,7),filename,'WriteMode','Append','WriteVariableNames',false);
        end

        fileNum = fileNum + 1;
        j = j+next;
        next = 1;

    end

    length_of_mat = SampleRate*routine;
    result = zeros(length_of_mat, fix(maxvel/(threshold*2))+1);
    vel = 0.2;
    for i = 1:fix(maxvel/(threshold*2))+1
        fname = sprintf('%sseg_%.1f.csv',tablename,vel);
        if exist(fname)
            mat = readmatrix(fname);
            if length(mat) < length_of_mat
                result(1:length(mat),i) = mat;
            else
                result(:,i) = mat(1:length_of_mat);
            end
        end
        vel = vel+0.4;
    end
end