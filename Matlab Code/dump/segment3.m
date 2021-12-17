% 설정한 시간 단위로 분산계수 비교, 만족하면 다음 단위까지 묶어서 비교/만족안하면 +1
function NEW_DATA = segment3(INPUT)
    DATA = table2array(INPUT(:,6));
    rows1sec = 0.5 /0.0005;
    constVel = zeros(length(DATA),1);
    allowance = 0.02;
    count=0;
    i=1;
    while i <= length(DATA)-rows1sec
        CV = std(DATA(i:i+rows1sec))/mean(DATA(i:i+rows1sec));
        if CV < allowance && i+rows1sec*(count+2)<length(DATA)
            while CV < allowance && i+rows1sec*(count+2)<length(DATA)
                count=count+1;
                CV = std(DATA(i:i+rows1sec*(count+1)))/mean(DATA(i:i+rows1sec*(count+1)));
            end
            constVel(i:i+rows1sec*count)=mean(DATA(i:i+rows1sec*count));
            i = i+rows1sec*count;
            count = 0;
        else
            i = i+1;
            count = 0;
        end
    end
    NEW_DATA = addvars(INPUT,constVel);
    % NEW_DATA = [DATA constVel];
end