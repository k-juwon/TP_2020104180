#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <numeric>
#include <iomanip>

using namespace std;

// 1. 이치방쿠지 한 세트 구성 (총 80개 기준)
struct PrizePool {
    int total_tickets = 80;
    vector<int> counts = { 2, 3, 5, 10, 20, 40 }; // A상: 2개, B상: 3개, C상: 5개, D상: 10개, E상: 20개, F상: 40개
    int price_per_ticket = 8000;                // 1회 비용은 8000원으로 설정
};

// 2. 이치방쿠지 판을 메모리에 생성
int simulate_one_round(mt19937& gen, const PrizePool& pool) {
    vector<int> tickets; // 당첨종이를 담을 vector형태의 tickets 생성
    for (size_t i = 0; i < pool.counts.size(); ++i) {  // 1번 반복문: 상(A상, B상, C상 등등)의 종류별로 확인
        for (int c = 0; c < pool.counts[i]; ++c) {     // 2번 반복문: 해당 상(A상, B상, C상 등등)의 개수만큼 반복
            tickets.push_back(i);                      // tickets(vector)에 티켓 번호 넣기
        }
    }

    // 3. A상이 당첨될 때까지 비복원 추출 실행
    int attempts = 0;                                                 // 뽑기 시행 횟수 초기화
    while (!tickets.empty()) {                                        // tickets에 남아있는 게 있을동안만 반복
        uniform_int_distribution<size_t> dist(0, tickets.size() - 1); // uniform_int_distribution을 사용하여 현재 남은 tickets의 전체 범위중 무작위로 하나의 index 선택
        size_t index = dist(gen);
        attempts++; // 뽑기를 1회 진행했으므로 attempts가 1씩 증

        if (tickets[index] == 0) { break; } // A상을 뽑으면 종료

        tickets.erase(tickets.begin() + index); // 비복원 추출 처리
        // A상이 아닌 다른 상품을 뽑으면, 현실의 이치방쿠지처럼 다시 넣지 않고 삭제(비복원 추출)
        // tickets.erase를 통해 tickets에서 방금 뽑은 위치의 데이터를 삭제
    }
    return attempts;                            // 반복문이 끝나면(A상을 뽑았다면), attempts(A상이 나올 때까지 시행한 횟수)를 반환
}

int main() {
    // 4. Simulation 준비 및 난수 생성기 설정
    int total_simulations = 100000; // total_simulations == 시행 횟수 100,000회
    PrizePool pool;                 // pool == 이치방쿠지 상자 객체

    random_device rd;               // rd == 난수 생성 객
    mt19937 gen(rd());

    long long total_attempts = 0;               // total_attempts == 100000번 동안 시도한 횟수 총합
    vector<int> attempt_history;                // attempt_history == 각 판마다 몇 번 만에 뽑았는지 기록할 vector
    attempt_history.reserve(total_simulations); // reserve == 100000개 공간을 미리 예약하여 메모리 성능 최적화

    // 5. 100000번 이치방쿠지 실행
    for (int i = 0; i < total_simulations; ++i) {
        int att = simulate_one_round(gen, pool);  // 100000번 동안 simulate_one_round 함수 호출
        total_attempts += att;                    // A상이 나올 때까지 몇 번 걸렸는지 att에 저장, 이를 total_attempts에 합산
        attempt_history.push_back(att);           // 파일 출력을 위해 attempt_history에 att 저장
    }

    double average_attempts = static_cast<double>(total_attempts) / total_simulations; // A상을 뽑는데 걸렸던 평균 시도 횟수 계산
    double average_cost = average_attempts * pool.price_per_ticket;                    // A상을 뽑는데 필요했던 평균 기대 비용 계산

    // 6. 100000번 이치방쿠지 실행 결과 출력(평균 시도 횟수, 평균 기대 비용)
    cout << "===== Result (N = 100,000) =====" << endl;
    cout << "average attempts for A PRIZE: " << average_attempts << " time(s)" << endl;
    cout << "average cost for A PRIZE: " << average_cost << " won" << endl;

    // 7. 개별 결과 텍스트 파일로 출력
    ofstream outFile("individual_result.txt");

    for (int i = 0; i < total_simulations; i++) {
        outFile << (i + 1) << " " << attempt_history[i] << " " << (attempt_history[i] * pool.price_per_ticket) << endl;
    }
    outFile.close();
    cout << "\n'individual_result' is saved successfully." << endl;

    // 8. 1000개 단위 구간 평균 데이터 저장
    ofstream avgFile("avg_result.txt");

    int interval = 1000;
    long long interval_sum = 0;
    for (int i = 0; i < total_simulations; ++i) {
        interval_sum += attempt_history[i];
        
        if ((i + 1) % interval == 0) {
            double interval_avg_att = static_cast<double>(interval_sum) / interval;
            double interval_avg_cost = interval_avg_att * pool.price_per_ticket;
            avgFile << (i + 1) << " " << interval_avg_att << " " << interval_avg_cost << "\n";
            interval_sum = 0; // 다음 반복을 실행하기 전에 interval_sum 초기화
            }
        }
    avgFile.close();
    
    cout << "\n'avg_result' is saved successfully." << endl;
    return 0;
}
