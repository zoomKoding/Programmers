## 문제

이중 우선순위 큐는 다음 연산을 할 수 있는 자료구조를 말합니다.

>* 명령어    수신 탑(높이)
>* I 숫자    큐에 주어진 숫자를 삽입합니다.
>* D 1    큐에서 최댓값을 삭제합니다.
>* D -1    큐에서 최솟값을 삭제합니다.

이중 우선순위 큐가 할 연산 operations가 매개변수로 주어질 때, 모든 연산을 처리한 후 큐가 비어있으면 [0,0] 비어있지 않으면 [최댓값, 최솟값]을 return 하도록 solution 함수를 구현해주세요.


**제한사항**

>* operations는 길이가 1 이상 1,000,000 이하인 문자열 배열입니다.
>* operations의 원소는 큐가 수행할 연산을 나타냅니다.
>* 원소는 “명령어 데이터” 형식으로 주어집니다.- 최댓값/최솟값을 삭제하는 연산에서 최댓값/최솟값이 둘 이상인 경우, 하나만 삭제합니다.
>* 빈 큐에 데이터를 삭제하라는 연산이 주어질 경우, 해당 연산은 무시합니다.

## 문제 이해

>* priority queue를 양방향으로 쓰는 문제이다.
>* pq를 두개 하면 될 것 같다!

## 방법은?

>* pq 두개를 이용하고 최대값을 찾을 때는 pq_M를 이용하고 최소값을 찾을 때는 pq_m을 이용해서 빼준다.
>* 근데 두개의 갯수가 다르므로 전체 갯수를 n으로 기록해두어 n이 0이 될 때마다 두 queue를 초기화 해준다.
>* 그리고 n이 0일 때는 빼내는 연산이 안되게 막아준다.

## 힙 활용 코드(점수: 100점)

    #include <string>
    #include <vector>
    #include <queue>

    using namespace std;

    vector<int> solution(vector<string> operations) {
        vector<int> answer;
        priority_queue<int, vector<int>, greater<int>> pq_m;
        priority_queue< int > pq_M;
        int n = 0;
        for(int i = 0; i < operations.size(); i++){
            if(n == 0){
                while(!pq_M.empty())pq_M.pop();
                while(!pq_m.empty())pq_m.pop();
            }
            int num = stoi(operations[i].substr(1,operations[i].length()));
            if(operations[i].at(0) == 'I'){
                pq_M.push(num);
                pq_m.push(num);
                n ++;
            }
            else if(operations[i].at(0) == 'D'){
                if(n == 0) continue;
                if(num == 1 && !pq_M.empty()) pq_M.pop();
                else if(num == -1 && !pq_m.empty()) pq_m.pop();
                n --;
            }
        }
        if(n == 0) {
            answer.push_back(0);
            answer.push_back(0);
        }
        else{
            answer.push_back(pq_M.top());
            answer.push_back(pq_m.top());
        }
        return answer;
    }

## 결론

>* 생각보다 간단한 문제였다ㅎㅎ
>* 이제 heap도 끝나가는 구나~ 남은 한문제도 화이팅이다.
>* 과제는 언제하지....

