# kdta_ROS2

-torch37
  -[클릭](https://colab.research.google.com/drive/1XQxHCNBZc1StMnk0vIEh3t4nQPaDDeds?usp=sharing)

-torch35
  -[클릭](https://colab.research.google.com/drive/1WFpTshg63vb5ySpGzCNAg8vpMFwgLzgC?usp=sharing)

-torch34
  -[클릭](https://colab.research.google.com/drive/1t2YN3NEeA23EVZtgwTT8sSmwyYzmAzSM?usp=sharing)

-torch32 nlk
  -[클릭](https://colab.research.google.com/drive/1nupH8KpTvB1L7cV9ZIInTztSfIsD7pjQ?usp=sharing)

-torch27 lstm
  -[클릭](https://colab.research.google.com/drive/1skFKCyaJX_F-AU9qT5St06Cc2abJl5eA?usp=sharing)


-torch26 lstm
  -[클릭](https://colab.research.google.com/drive/143rdxGKYvL3KhyWqcLLxDqX-p5QYTwse?usp=sharing)

-torch25 rnn
  -[클릭](https://colab.research.google.com/drive/1SAI79ItITXIDxlVjh3i2L0hXgtGHAbLG?usp=sharing)


-torch24 rnn
  -[클릭](https://colab.research.google.com/drive/1fbpqwOjUxeV2rxdOmNzfxZ-eAOCrVp3D?usp=sharing)


-torch1 link
  -[클릭](https://colab.research.google.com/drive/1JwZTcZYcRM1YkiftpaqEGrVtyAmtCvAw?usp=sharing)


-perceptron link
  -[클릭](https://colab.research.google.com/drive/1ucZHqf3DCLwq7E3MeTZWn7KeCzCjqFWw?usp=sharing)

-lightening ai link
  - [클릭](https://7860-01j6zv6kf7tgcmjmefs5a6fc4k.cloudspaces.litng.ai/)
- gpt2 학습
  - [클릭](https://colab.research.google.com/drive/1JBkrXNvk4lTVBUxiWxOB_Jf8lTw0BEai?usp=sharing)
- mixtral lightening.ai 
- [클릭](https://8501-01j6zcdh989h9c809c2skjmtae.cloudspaces.litng.ai)


- Environment :
  - windows11 : wmware workstation 16 player
  - ubuntu 22.04:
  - ROS2 : humble
  - Book : ROS2로 배우는 로봇 프로그래밍

- 공유 슬라이드
[링크](https://docs.google.com/presentation/d/1453nx14DVMk0nBLW7jpt0g6x7a7z2wuNaJKmcVQi4rw/edit?usp=sharing)

- ubuntu 설치 후 OpenCV 설치

```bash
sudo apt update 
sudo apt upgrade
sudo apt install libopencv-dev python3-opencv
sudo apt install build-essential cmake git pkg-config
'''

- OpenCV 설치 후 추가 작업
  - 각 패키지에 대한 추가 설명
  - libjpeg-dev, libtiff5-dev, libpng-dev: 이미지 파일 포맷을 읽고 쓰기 위한 라이브러리
  - libavcodec-dev, libavformat-dev, libswscale-dev, libv4l-dev: 비디오 파일 포맷을 읽고 쓰기 위한 라이브러리
  - libxvidcore-dev, libx264-dev: 비디오 코덱 라이브러리
  - libgtk-3-dev: GUI 툴킷 라이브러리
  - libatlas-base-dev, gfortran: 선형대수 라이브러리
  - python3-dev: 파이썬 개발 헤더 파일
  - python3-pip: 파이썬 패키지 설치 도구
  - numpy: 수치 계산 라이브러리
  - libopencv-dev: OpenCV 라이브러리
  - python3-opencv: OpenCV 파이썬 바인딩 라이브러리
  - build-essential: 빌드 도구
  - cmake: 빌드 자동화 도구
  - git: 소스 코드 버전 관리 도구
  - pkg-config: 라이브러리 정보 검색 도구

```bash
sudo apt-get install libjpeg-dev libtiff5-dev libpng-dev
sudo apt-get install libavcodec-dev libavformat-dev libswscale-dev libv4l-dev
sudo apt-get install libxvidcore-dev libx264-dev
sudo apt-get install libgtk-3-dev
sudo apt-get install libatlas-base-dev gfortran
sudo apt-get install python3-dev
sudo apt-get install python3-pip
pip3 install numpy
```

---

## 2024-07-23

---

- 1 차시
  - vmware 설치
  - ubuntu 22.04 설치
  - terminator 설치
  - git 설치
- 2 차시
  - vscode 설치
  - github 연동
- 3 차시
  - 주요 클래스 Point, Size, Rect, Scalar

---

## 2024-07-24

---

- 주요 클래스 마무리
  - Mat 클래스
- ch04
  - 비디오 캡쳐
  - 비디오 파일 저장
  - line, rectangle, circle, ellipse, polylines, fillPoly, putText 함수
  - 키보드 이벤트 처리

---

## 2024-07-25

---

- 1 차시
  - 복습
  - mouse callback 함수 작성
- 2 차시
  - 트랙바 설정
  - 트랙바 콜백 함수 작성
- 3 차시
  - 파일스토리지 사용법
  - 마스크 연산
- 4 차시
  - 종합 과제 - 마우스 따라 다니는 사각형
- 5 차시

---

## 2024-07-26

---

- 1차시
  - 복습
  - affine transformation
- 2차시
  - warpaffine
  - affineRotation - 트랙바 연결 예제 작성
- 3차시
  - 투시변환
    - 카드 예제에서 거리 및 각도 측정 코드 추가
  - 엣지 검출
  - 캐니 엣지 검출
- 4차시
  - 허프변환

---

## 2024-07-30

---

- ROS2 시작
- ROS2 개념
  - 노드
  - 토픽
  - 메시지
  - 런처
  - 노드 통신
  - 노드 실행
- ROS2 설치
  - ROS2 humble 설치
  - ros2 humble documentation debian installation
  - 환경 설정 파일
    - .bashrc
      - source /opt/ros/humble/setup.bash
      - source ~/xxx_ws/install/local_setup.bash
      - 여러가지 alias 설정
      - export ROS_DOMAIN_ID 설정
- 패키지 작성
  - kdta_ws
    - simple_pkg_cpp
      - xml 수정
      - CMakeLists.txt 수정
      - 노드 추가
        - helloword.cpp : 기본 main 코드
        - helloOpenCV.cpp : OpenCV 사용 코드(외부 라이브러리 적용)
        - hellow_publisher : Node 및 spin timer 적용
        - hellow_publisher_class : Node 상속 클래스 적용

---

## 2024-07-31

---

- 복습
- 패키지 작성 (이어서)
  - kdta_ws
    - simple_pkg_cpp 패키지
      - 노드 추가
        - hellow_publisher_class2 : 분할컴파일 (해더, 메인, CPP)
        - hellow_subscriber : subscriber 노드
        - time_publisher_class : timer 노드
        - time_subscriber : timer subscriber 노드
    - move_t_sim 패키지
      - 노드 추가
        - moveTurtleSim.cpp : 터틀심 이동 노드( turtle1, turtle2 동시 이동)
- 최종 실습(Topic)
  - 5개 노드 3개 Topic 사용
    - 노드 : mpub, msub, msub2, tpub, mtsub
    - Topic :
      - /message1: String ( mpub -> msub, mtsub)
      - /message2: String ( mpub -> msub2)
      - /time: Header ( tpub -> mtsub)

---

## 2024-08-01

---

- 복습
- 터틀봇3 네트워크 설정
  - 공유기 설치
    - ssid: turtlebot3
    - password: turtlebot3
  - 가상환경 bridge 설정
    - 네트워크 브릿지 클리 후 네트워크 카드 하나만 사용
- 터틀봇3 개요
  - 터틀봇3 소개
  - 터틀봇3 구성
  - 터틀봇3 시스템 구성
- 터틀봇3 ssh 연결
  - 터미널에서 연결
    - `ssh ubuntu@192.169.14.XX`
      - userid: ubuntu
      - password: aa
    - vscode remote ssh 연결
      - vscode remote ssh 설정
- 터틀봇3 브링업
  - 터틀봇3 브링업
    - ROS_DOMAIN_ID 확인
    - `export TURTLEBOT3_MODEL=burger`
    - 브링업 런치 실행 `ros2 launch turtlebot3_bringup robot.launch.py`
- 텔레옵키 노드 실행(노트북)
  - 텔레옵키 노드 실행
    - `ros2 run turtlebot3_teleop teleop_keyboard`
- gazebo
  - gazebo 설치
    - `sudo apt install ros-humble-gazebo-*`
  - turtlebot3 simulation 설치(깃 클론)
    - `cd ~/kdta_ws/src`
    - `git clone -b humble-devel https://github.com/ROBOTIS-GIT/turtlebot3_simulations.git`
    - `cd ~/turtlebot3_ws && colcon build --symlink-install`
  - turtlebot3 simulation 실행
    - `ros2 launch turtlebot3_gazebo turtlebot3_world.launch.py`
- 터틀봇3에서 빌드 후 실행
  - move_t_sim 이동
    - vscode 로컬과 원격을 동시 실행 후 이동
    - 빌드 후 실행(터틀봇3)
      - `cd ~/robot_ws`
      - `colcon build --symlink-install`
      - `ros2 run move_t_sim moveTurtleBot`
- 터틀심 사각형 움직임 구현
  - moveTurtleSim2.cpp 작성
  - 빌드 후 실행(터틀봇3)
    - `ros2 run move_t_sim moveTurtleSim2`


---

## 2024-08-02

---

- 복습
- 터틀심 사각형 움직임 구현 -> 터틀봇 용 코드로 변경
  - moveTurtleBot2.cpp 작성
  - 세부 알고리즘 변경
- 사용자 인터페이스 작성
  - srv/AddTwoInt.srv 파일 작성
- Service 노드 추가
  - Service server 노드
  - Service client 노드1
    - spin_until_done 사용
  - Service client 노드2
    - spin 사용 후 callback 사용
- 파라미터 
  - 파라미터 기초
    - ros2 param get /node_name param_name
    - ros2 param set /node_name param_name param_value
    - ros2 param list /node_name
    - ros2 param dump /node_name
    - ros2 param load /node_name
- Launch 파일 작성
  - topic_final 에 추가

---

## 2024-08-05

---

- 복습
- 파라미터 코드 적용
  - param_events topic 활용.
  - 파라미터 변경시 이벤트 발생
  - set_parameters_callback 함수 사용 <- 적용 안됨
- action 코드 작성
  - interface_example 에서 fibonacci action 추가
  - simple_pkg_cpp 에서 action server, client 추가
- 토픽, 서비스, 액션 통합 예제 작성
  - arithmetic 패키지 작성
  - interface_example 에 토픽, 서비스 액션 추가
    - ArithmeticArgument.msg
    - ArithmeticOperator.srv
    - ArithmeticChecker.action
  - 토픽 노드 작성
    - argument.cpp

*** interface_example include 과정에서 문제 발견 -> 수정 완료.

이진우 : HP 010-8824-4455

---

## 2024-08-06

---

- 복습
- 남은 5일 일정 설명
  - 라즈베리파이3 CSI 카메라 설정
  - GPIO 이용한 추가 장치 설정
  - 아두이노를 이용한 추가 장치 설정
  - SLAM : cartographer 설치 및 설정
  - NAV2 : nav2 라이브러리 설치 및 설정
- Arithmetic 패키지 작성
  - 분할 컴파일
    - argument.cpp -> argument.cpp, argument.hpp
    - 폴더 나누기
  - 서비스 노드 작성
    - operator.cpp, operator.hpp
  - `실습` argument.cpp 기능 추가하기
    - 램덤하게 operator 발행 하기
    - 파라미터 설정해서 램덤 혹은 스테틱 설정하기
    - 파라미터를 yaml 로 저장해서 launch 파일로 불러오기
  - 액션 노드 작성
- action server 작성
  - 실습 argument.cpp 기능 추가하기
    램덤하게 operator 발행 하기
    파라미터 설정해서 램덤 혹은 스테틱 설정하기
    파라미터를 yaml 로 저장해서 launch 파일로 불러오기

---

## 2024-08-07

---

- 복습
- 카메라
  - 카메라 이론
  - 카메라 설정
    - 터틀봇3 카메라 설정
    - 가제보 카메라 설정
- 터틀봇3 카메라 노드 작성
  - canny_camera.cpp 작성
  - 빌드 후 실행(터틀봇3)

---

## 2024-08-08

---

- 복습
- 터틀봇3
  - 메인노드에 센서와 엑츄에이터 연결 프로그래밍
  - restrain 코드 추가
- 터틀봇3 30cm 유지하기 코드 작성
  - stay_thirty.cpp 작성
  - 빌드 후 실행(터틀봇3)
  - `ros2 run move_t_sim stay_thirty`
- 터틀봇3 벽 따라 움직이기 코드 작성
  - follow_wall.cpp 작성
  - 빌드 후 실행(터틀봇3)
  - `ros2 run move_t_sim follow_wall`

---

## 2024-08-09

---

- 복습
- 팀 프로젝트 진행
  - 팀 github 생성
  - 팀 구글 슬라이드 생성
  - 팀 주제 및 일정 회의
- SLAM
  - 슬램 패키지 설치
  - 지도 생성
  - 지도 파일 생성
- NAV2
  - 네비게이션 패키지 설치
  - 가제보 네비게이션 실행
  - 터틀봇3 기체 네비게이션 실행

---

## 2024-08-12

---

- 복습
- 네비게이션 action_client 작성
  - 4개의 목적지로 이동
