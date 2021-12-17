function result = speedmat(name)
    threshold = 0.2;
    maxvel = 30;
    routine = 0.5; SampleRate=2000;
%     filecheck = zeros(1, fix(maxvel/(threshold*2))+1);
%     tablename = inputname(1);
%     disp(tablename);
%     j=1; next=1; fileNum=1;
%     
%     LENGTH = 25.125; % 자전거 지름(circumference) / 8(n) [cm]
%     delta = 0.5; % 측정 단위시간(sampling cylce time) [ms]
%     Velocity = zeros(rows,1);
    
%     length_of_mat = SampleRate*routine;
    length_of_mat = 3000;
    result = zeros(length_of_mat, fix(maxvel/(threshold*2))+1);
    vel = 0.2;
    for i = 1:fix(maxvel/(threshold*2))+1
        fname = sprintf('%sseg_%.1fkmh.csv',name,vel);
        if exist(fname)
            mat = readmatrix(fname);
            mat = mat(:,7);
            if length(mat) < length_of_mat
                result(1:length(mat),i) = mat;
            else
                result(:,i) = mat(1:length_of_mat);
            end
        end
        vel = vel+0.4;
    end
end