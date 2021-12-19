# 2021년 2학기 컴퓨터공학과 캡스톤디자인1 VHiKHU팀
***
## ◽ 주제
실내 VR 자전거를 위한 노면 질감 구현
### ◽ 지도교수
전석희 교수님
## ◽ 팀명
VHiKHU [바이쿠] - *Bike*와 발음 유사, **V**R × **H**aptics **i**n **KHU**>)
## ◽ 팀원
김한엽 기계공학과 <br>
나혜원 컴퓨터공학과 <br>
윤동주 컴퓨터공학과 <br>

# 요약
> 효과적인 VR 자전거 체험을 위한 노면 질감 데이터를 분석 및 구현 <br>
> 사용자에게 자전거가 달리는 노면의 질감을 사실적으로 전달함으로써 보다 현실과 유사한 VR 경험 제공

***

# ◽ 폴더 구성

 ## 📁Arduino Code
 ___아두이노 사용 시 사용한 코드___
 * _mega_switch_: 아두이노 Mega용 가속도 + 속력 측정 코드(데이터 수집 시 사용)
 * _uno_switch_: 아두이노 Uno용 가속도 + 속력 측정 코드(데이터 수집 시 사용)
 * _velo_: 자전거 속력 측정 코드(진동 구현 시 사용)   


 ## 📁Data
 ___수집한 가속도, 속력 데이터___
 * __Arduino Sample__: 아두이노를 사용하여 수집한 데이터
 * __Asphalt__: DAQ를 이용하여 수집한 데이터(아스팔트 바닥)
 * __Field__: DAQ를 이용하여 수집한 데이터(인조잔디 구장 바닥)
 * __Grid__: DAQ를 이용하여 수집한 데이터(격자무늬 돌 바닥)
 * __Measure output__: 구현한 시스템에서 출력된 데이터
 * __Segmented__: 보간법을 위해 속력에 따라 구분된 데이터    
  

 ## 📁Matlab Code
 ___매트랩 환경에서 DAQ 사용 시 사용한 코드___
 * __IRtoVel.m__: 수집한 IR센서 입력을 속력으로 변환
 * __acc1d.m__: x, y, z 3축의 가속도를 1D 가속도로 변환
 * __arduino2.mlx__: 아두이노와 연결하여 입력받는 속력에 따른 가속도 보간 및 출력
 * __asphaltcompare.mlx__: 아스팔트 바닥으로 설정하였을 때 출력된 데이터와 수집한 데이터 비교 
 * __dft321.m__: x, y, z 3축의 가속도를 1D 가속도로 변환 (https://github.com/haptics-nri/mfi16-figures/blob/master/dft321.m)
 * __fieldcompare.mlx__: 인조잔디 구장 바닥으로 설정하였을 때 출력된 데이터와 수집한 데이터 비교 
 * __graph_3d_vel.m__: 가속도와 속력 데이터를 그래프로 시각화
 * __gridcompare.mlx__: 격자무늬 바닥으로 설정하였을 때 출력된 데이터와 수집한 데이터 비교 
 * __highpass_1D.m__: Highpass filter 적용 후 x, y, z 3축의 가속도를 1D 가속도로 변환
 * __segment5.m__: 속력에 따른 데이터 분할
 * __selectbest.m__: 분할된 데이터들의 분포 시각화
 * __speedmat.m__: 분할된 가속도를 행렬로 변화
  

 ## 📁Report
 ___한국정보과학회논문, 최종보고서, 영상___

***

# ◽ 진행 과정

## 1. Data Collection
### ▫ 진행 방식
교내 3곳의 장소를 선정하여 DAQ, 가속도계, 속도계가 부착된 자전거를 타며 속력 및  가속도 데이터를 수집했다. <br><br>
![4 DataCollection_ThreeTextures](https://user-images.githubusercontent.com/47781507/146654571-ba5418e7-d8ef-4721-b122-3a95592632bf.jpg)
> 데이터 수집 장소 표면 (왼쪽부터 아스팔트, 인조잔디, 돌 타일) <br>

![1 DataCollection_Riding](https://user-images.githubusercontent.com/47781507/146654481-0f155cf9-286d-48e3-bf12-8d565d0cf26f.jpg)
> 자전거에 센서를 부착하고 데이터를 수집하는 모습

### ▫ 데이터 수집 시스템
![2 DAQsystem](https://user-images.githubusercontent.com/47781507/146654545-1b173ba5-ea4f-40d3-a873-3304d35dbc13.jpg)
> DAQ를 이용한 데이터 수집 시스템 개략도 <br>

## 2. Data Preprocessing
### ▫ 진행 방식
수집한 데이터는 7Hz 이상의 High-pass filter로 중력의 영향과 노면의 미세한 돌출부와 홈으로 인한 노이즈를 제거하였다. <br>
이후 진동구현을 위해 x, y, z축의 가속도 데이터의 기준을 모두 0으로 설정하였다. <Br>
각 축의 가속도 데이터를 푸리에 변환한 후 각 축의 진동수 크기를 벡터로 묶어 L2 Norm을 이용해 벡터의 크기를 구하고 벡터의 위상각을 구하였다. <br>
이 두 값을 이용해 푸리에 역변환을 수행하여 1차원 데이터로 변환하였다. <br><br>
![3 DAQgraph](https://user-images.githubusercontent.com/47781507/146654617-28d1af78-bb74-4d65-9e5d-38b7d161b585.jpg)
> DAQ 시스템을 이용하여 수집한 속력과 가속도 데이터 (전처리 전) <br>

![5 DAQgraph_1D](https://user-images.githubusercontent.com/47781507/146654643-7c16aab6-92cf-4294-9474-c87ad86f8080.jpg)
> 1차원 데이터화된 가속도와 속력 (전처리 후)

## 3. Data Segmentaion
### ▫ 진행 방식
수집된 데이터는 노이즈 및 후반부의 급격한 감속구간을 제거한 뒤 오차범위를 ±0.2km/h로 설정하고 오차범위 내의 속력과 그에 따른 가속도 값을 분류하여 저장하였다. <br>
아래 그림은 예시로 이해를 돕기 위해 범위를 크게 설정한 모습이다. <br><br>
![6 DataSegmentation Interpolation_Example](https://user-images.githubusercontent.com/47781507/146670931-dc68a4a0-0c32-4e57-b203-fd67ff479aea.jpg)
> 데이터 분할 및 보간 예시

## 4. Data Modeling
### ▫ 진행 방식
사용자가 VR 자전거를 체험하며 점진적으로 변하는 속력에 따른 진동 데이터를 실시간으로 느낄 수 있도록 입력 데이터에 따라 실시간으로 가속도를 보간해서 출력한다. <br>
아스팔트, 인조잔디, 타일 표면 각각의 데이터셋 중 최대 대표 속력이 20km/h를 넘기고 속력별 가속도가 많은 최적의 데이터셋을 선정하여 데이터 보간을 진행하였다. <br>
나누어진 가속도 값들을 속도와 시간을 기준으로 하는 행렬로 저장한뒤 Matlab 내장함수인 interpol2를 사용해 시간 도메인 보간을 진행했다. <br>
동일한 시간이 반복해서 출력되는 것을 방지하고자 매 출력시 임의의 랜덤 offset을 설정하여 같은 속력이라도 출력 데이터가 반복되지 않게 하였다. <br>

## 5. Data Rendering
### ▫ 진행 방식
핸들부에는 액츄에이터(Vibro Transducer Vp6)가 부착되어있고 앞주머니에는 아두이노와 앰플리파이어(XY-502)가 들어있다. <br> 
페달을 굴리면 뒷바퀴가 돌아가고 IR센서가 마킹을 읽고 신호를 보내 아두이노에서 속력으로 변환한다. <br>
아두이노는 노트북의 Matlab으로 계산된 속력을 보내고 Matlab은 입력속력에 따라 보간을 수행한다. <br>
보간으로 구해진 데이터를 앰플리파이어로 전송하고 액츄에이터를 통해 진동으로 출력되는 시스템이다. <br>

### ▫ 진동 구현 시스템 구조
![8 SystemStructure](https://user-images.githubusercontent.com/47781507/146654729-df7b4b19-7faf-404c-afdf-78e3b4daf6b7.jpg)
> 진동 구현 시스템 개략도

***

# ◽ 시스템 구현 결과
### ▫ 진동 구현 시스템
![7 BicycleSystem](https://user-images.githubusercontent.com/47781507/146654701-313c7476-89e6-4319-9cf2-0893e46dfc29.jpg)
> 실제 자전거에 구현한 시스템

### ▫ 결과 분석
![9 ResultGraph](https://user-images.githubusercontent.com/47781507/146654758-01535422-f25c-427f-a188-b3118d1dd43e.jpg)
> 각 노면별 동일 속력에서의 가속도 비교 (상: 수집한 데이터, 하: 구현된 데이터)

저주파의 크기가 크고 고주파로 갈수록 작아지는 양상이 공통적으로 나타났다. <br>
인조잔디구장(Field)의 경우 600Hz 부근의 출력이 유사하게 나타났다. <br>
진동의 크기의 경우 앰플리파이어의 볼륨, 컴퓨터의 볼륨에 따라 변화하였기 때문에 직접 볼륨에 따른 크기를 체험해가며 설정했다. <br>
조원 간의 자체 평가 결과 아스팔트, 인조잔디구장, 격자무늬바닥 순서로 현실의 표면과 유사한 것으로 나타났다.