## 2021년 2학기 컴퓨터공학과 캡스톤디자인1 VHiKHU팀
### 실내 VR 자전거를 위한 노면 질감 구현

김한엽 기계공학과  
나혜원 컴퓨터공학과  
윤동주 컴퓨터공학과  

----------------------
# 폴더

 ## Arduino Code
 ___아두이노 사용 시 사용한 코드___
 * _mega_switch_: 아두이노 Mega용 가속도 + 속력 측정 코드(데이터 수집 시 사용)
 * _uno_switch_: 아두이노 uno용 가속도 + 속력 측정 코드(데이터 수집 시 사용)
 * _velo_: 자전거 속력 측정 코드(진동 구현 시 사용)   


 ## Data
 ___수집한 데이터___
 * __Arduino Sample__: 아두이노를 사용하여 수집한 데이터
 * __Asphalt__: DAQ를 이용하여 수집한 데이터(아스팔트 바닥)
 * __Field__: DAQ를 이용하여 수집한 데이터(인조잔디 구장 바닥)
 * __Grid__: DAQ를 이용하여 수집한 데이터(격자무늬 바닥)
 * __Measure output__: 구현한 시스템에서 출력된 데이터
 * __Segmented__: 보간법을 위해 속력에 따라 구분된 데이터    
  

 ## Matlab Code
 ___매트랩 사용 시 사용한 코드___
 * __IRtoVel.m__: 수집한 IR센서 입력을 속력으로 변환
 * __acc1d.m__: x,y,z 3축의 가속도를 1d 가속도로 변환
 * __arduino2.mlx__: 아두이노와 연결하여 입력받는 속력에 따른 가속도 보간 및 출력
 * __asphaltcompare.mlx__: 아스팔트 바닥으로 설정하였을 때 출력된 데이터와 수집한 데이터 비교 
 * __dft321.m__: x,y,z 3축의 가속도를 1d 가속도로 변환 (https://github.com/haptics-nri/mfi16-figures/blob/master/dft321.m)
 * __fieldcompare.mlx__: 인조잔디 구장 바닥으로 설정하였을 때 출력된 데이터와 수집한 데이터 비교 
 * __graph_3d_vel.m__: 가속도와 속력데이터를 그래프로 시각화
 * __gridcompare.mlx__: 격자무늬 바닥으로 설정하였을 때 출력된 데이터와 수집한 데이터 비교 
 * __highpass_1D.m__: Highpass filter적용 후 x,y,z 3축의 가속도를 1d 가속도로 변환
 * __segment5.m__: 속력에 따른 데이터 분할
 * __selectbest.m__: 분할된 데이터들의 분포 시각화
 * __speedmat.m__: 분할된 가속도를 행렬으로 변화   
  

 ## Report
 ___논문 및 보고서___
