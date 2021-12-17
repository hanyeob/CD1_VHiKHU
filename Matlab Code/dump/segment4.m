% 설정한 시간 단위로 분산계수 비교, 만족하면 다음 단위까지 묶어서 비교(다음단위를 이전단위와 같은 길이로 가중치부여)
function NEW_DATA = segment4(INPUT)
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
                extrarows = repmat(DATA(i+rows1sec*count+1:i+rows1sec*(count+1)),count,1);
                weighted = [DATA(i:i+rows1sec*count); extrarows];
                CV = std(weighted)/mean(weighted);
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

    tablename = inputname(1);
    leasttime = 3 / 0.0005;
    j=1; next=1; fileNum=1;
    while j < height(NEW_DATA) 
        while NEW_DATA.constVel(j) == NEW_DATA.constVel(j+next) && j+next<height(NEW_DATA) 
            next=next+1;
        end
        if next >= leasttime
            filename = sprintf('%sseg%d(%.2f).csv',tablename, fileNum, NEW_DATA.constVel(j));
            writetable(NEW_DATA(j:j+next,:),filename);
            fileNum = fileNum+1;
        end
        j = j+next;
        next = 1;
    end

end