% 1씩 커지면서 설정한 행을 표본으로 분산계수값 비교
function NEW_DATA = segment(DATA)
    rows1sec = 3 /0.0005;
    seg_mean = zeros(length(DATA),1);
    for c = 1:length(DATA)-rows1sec
        CV = std(DATA(c:c+rows1sec))/mean(DATA(c:c+rows1sec));
        if CV < 0.015
            seg_mean(c:c+rows1sec)=mean(DATA(c:c+rows1sec));
        end
    end
    NEW_DATA = [DATA seg_mean];
end