clc;
clear all;
close all;

%randomly generated data 
% use your acceleration data
data1  = randi([-10,10],1000,1);
data2  = randi([-10,10],1000,1);

% let, a cut-of frequency of 7 Hz 
% let, 1020 hz is collected acceleration frequency.
% high pass filter
data1 = bandpass(data1,[7 1020],1020); 
data2 = bandpass(data2,[7 1020],1020); 

%interpolation for velocity
%inverse weighted distance interpolation
velocity = 10;
PreviousVelocity = 7;
PostVelocity = 12;


distance1 = sqrt((velocity - PreviousVelocity).^2);
distance2 = sqrt((velocity - PostVelocity).^2);



inv_dis1 = 1/distance1;
inv_dis2 = 1/distance2;

weight1 = inv_dis1/(inv_dis1+inv_dis2);
weight2 = inv_dis2/(inv_dis1+inv_dis2);


for kkk = 1 : length(data1)
newData(kkk) = (data1(kkk)*weight1 + data2(kkk)*weight2);
end

figure, plot(data1);
figure, plot(data2);
figure, plot(newData);