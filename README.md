## TP_2020104180
## Monte Carlo Simulation 기반 이치방쿠지 기대 비용 및 확률 수렴 분석기

## 1. 주제 및 연계 강의
1. 주제명: Monte Carlo Simulation 기반 이치방쿠지(확률형 뽑기) 기대 비용 산출 및 확률 수렴성 분석 프로그램
2. 연계 강의:
  (1) 5강 Random Processing: C++ 난수 생성 및 Monte Carlo Simulation을 통한 확률 모델링
  (2) 1강 / 12-14강: C++ 파일 입출력(`txt`) 및 Git 버전 관리 연계

## 2. 개발 환경
1. OS: Windows 11
2. Language: C++ (Visual Studio 2022)
3. Tools: Git & GitHub
4. Data Visualization: Microsoft Excel

## 3. 빌드 및 실행 방법

1. C++ source code를 compile하고 실행하여 txt 데이터 파일을 생성하는 방법
(1) `src/` 폴더 안의 소스코드(`main.cpp`)를 C++ 지원 컴파일러(Visual Studio 2022)에서 연다.
(2) 아래 명령어나 IDE 빌드 버튼을 통해 실행 파일을 생성하고 실행한다.
   ```bash
   g++ -std=c++17 src/main.cpp -o ichibankuji_sim
   ./ichibankuji_sim

## 4. 결과 요약 및 시각화
1. 데이터 처리: 생성된 ichibankuji_data.txt 파일을 엑셀(Excel)로 불러와서 분석 진행
2. 정량 검증:
  (1) N=10000회 이상 시뮬레이션 결과, A상 당첨 누적 비율이 이론적 확률(2.5%)에 안정적으로 수렴함을 확인
  (2) A상 1개 획득을 위한 평균 기대 비용 및 시행 회차별 비용 분포 분석 완료
  (3) 결과 파일: results/ 폴더 내 텍스트 데이터 및 엑셀 시각화 그래프 이미지 참고

## 5. AI 활용 내역
1. 사용 도구: Gemini / Claude 등 AI 어시스턴트
2. 활용 용도: C++ 난수 시드 설정 방식, 텍스트 파일 출력 코드 작성 보조
3. 검증 방법: 생성된 코드를 1강, 5강 강의자료와 대조하여 직접 디버깅

## 6. GitHub 저장소 URL: https://github.com/k-juwon/TP_2020104180

## 7. 참고 출처
1. 소프트웨어랩 강의자료 1강, 5강
2. C++ Reference (std::mt19937, std::ofstream)
3. Sheldon Ross, Introduction to Probability Models (12th ed.) - 무작위 추출 및 Monte Carlo Method
