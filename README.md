# kdta_ROS2

- 공유 슬라이드
[링크](https://docs.google.com/presentation/d/1453nx14DVMk0nBLW7jpt0g6x7a7z2wuNaJKmcVQi4rw/edit?usp=sharing)

- ubuntu 설치 후 OpenCV 설치

```bash
sudo apt update 
sudo apt upgrade
sudo apt install libopencv-dev python3-opencv
'''

- OpenCV 설치 후 추가 작업
```bash
sudo apt-get install build-essential cmake git pkg-config
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