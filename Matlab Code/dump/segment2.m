% 두 번 연속 분산계수를 만족하면 한번에 묶에서 분산계수 비교
function NEW_DATA = segment2(DATA)
    rows1sec = 1.5 /0.0005;
    seg_mean = zeros(length(DATA),1);
    count=0;
    i=1;
    while i <= length(DATA)-rows1sec
        CV = std(DATA(i:i+rows1sec))/mean(DATA(i:i+rows1sec));
        if CV < 0.025
            seg_mean(i:i+rows1sec)=mean(DATA(i:i+rows1sec));
            i = i+rows1sec;
            count=count+1;
            if count > 1
                CV2 = std(DATA(i-count*rows1sec:i))/mean(DATA(i-count*rows1sec:i));
                if CV2 < 0.025
                    seg_mean(i-count*rows1sec:i)=mean(DATA(i-count*rows1sec:i));
                end
            end
        else
            i = i+1;
            count = 0;
        end
    end
    NEW_DATA = [DATA seg_mean];
end