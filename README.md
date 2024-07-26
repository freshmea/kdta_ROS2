# kdta_ROS2

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