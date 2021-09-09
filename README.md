# 태양광자율주행자동차
이 프로젝트는 2020 서운고 태양광자율주행자동차부의 프로젝트입니다. 

##소개

**태양광을 동력으로하는 자율주행 자동차를 제작**
* Level3 자율주행 자동차 제작
* 태양 전지로 리튬 전지 충전 후 리튬 전지를 동력으로 자동차 동작
* 자동으로 충전소를 찾는 알고리즘 설계
* 안드로이드 어플리케이션으로 자동차를 조종하며 초음파 센서로 장애물 회피

##자율주행 자동차 제작

###회로설계

![image](https://user-images.githubusercontent.com/65582244/132711887-71b3f8eb-a736-4754-8e31-7f4905a0a6e3.png)
- 3.7V, 2600mAh인 18650 리튬 이온 전지 2개를 이용하여 7.4V의 전원을 공급해준다.
- 하비 기어모터를 좌우에 각각 2개씩 연결한다.
- HC-06 블루투스 모듈을 이용해 블루투스 통신을 하도록 한다.
- 초음파 센서를 이용해 거리 측정을 한다.
- 초록 LED와 능동 부저를 통해 시동 on/off, 충전 대기 등의 상태를 알린다.
- CdS로 충전소의 레이저 신호를 수신한다.
- 홀 센서(hall censor)로 충전소에서 정확한 위치에서 충전할 수 있도록 한다.
- 18650 리튬 이온 전지에 30Ω저항으로 부하를 걸어서 실제 전기에너지를 내는 힘을 체크하여 배터리 잔량을 측정한다.

