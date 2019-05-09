## 문제

숫자 야구 게임이란 2명이 서로가 생각한 숫자를 맞추는 게임입니다. 게임해보기

각자 서로 다른 1~9까지 3자리 임의의 숫자를 정한 뒤 서로에게 3자리의 숫자를 불러서 결과를 확인합니다. 그리고 그 결과를 토대로 상대가 정한 숫자를 예상한 뒤 맞힙니다.

* 숫자는 맞지만, 위치가 틀렸을 때는 볼
* 숫자와 위치가 모두 맞을 때는 스트라이크
* 숫자와 위치가 모두 틀렸을 때는 아웃

예를 들어, 아래의 경우가 있으면

- A : 123
- B : 1스트라이크 1볼.
- A : 356
- B : 1스트라이크 0볼.
- A : 327
- B : 2스트라이크 0볼.
- A : 489
- B : 0스트라이크 1볼.

이때 가능한 답은 324와 328 두 가지입니다.

질문한 세 자리의 수, 스트라이크의 수, 볼의 수를 담은 2차원 배열 baseball이 매개변수로 주어질 때, 가능한 답의 개수를 return 하도록 solution 함수를 작성해주세요.

**제한사항**
질문의 수는 1 이상 100 이하의 자연수입니다.
baseball의 각 행은 [세 자리의 수, 스트라이크의 수, 볼의 수] 를 담고 있습니다.

## 문제 이해

>* 일단 123 부터 987까지 다 훑어서 가능성 있는 애들을 찾아봅니다
>* 근데 찾은 애가 0을 가지고 있을 수도 있으니 그런 애들은 걸러주고요!
>* 반복된 숫자가 있는 친구가 있을테니 걔네들도 걸러주세요~

### 문뜩 코드(점수: 100점)

    #include <string>
    #include <vector>

    using namespace std;

    int solution(vector<vector<int>> baseball) {
        int answer = 0;
        for(int i = 123; i < 987; i++){
            bool good = true;
            for(int j = 0; j < baseball.size(); j++){
                int strike = 0;
                int ball = 0;
                string n1 = to_string(i);
                string n2 = to_string(baseball[j][0]);
                for(int k = 0; k < 3; k ++){
                    if(n1.at(k) == n2.at(k)) {
                        strike ++;
                        continue;
                    }
                    for(int l = 0; l < 3; l++){
                        if(n1.at(k) == n2.at(l)){
                            ball ++;
                            break;
                        }
                    }
                }
                if(strike == baseball[j][1] && ball == baseball[j][2]);
                else {
                    good = false;
                    break;
                }
            }
            if(good) {
                string s = to_string(i);
                for(int j = 0; j < s.length(); j++){
                    if(s.at(j) == '0'){
                        good = false;
                        break;
                    }
                    for(int k = 0; k < s.length(); k++){
                        if(j == k) continue;
                        if(s.at(j) == s.at(k)){
                            good =false;
                            break;
                        }
                    }
                }
                if(good)answer ++;
            }
        }
        return answer;
    }
    
## 느낀점

>* 브루트 폴스는 문뜩 드는 생각으로 끝낼 수 있었다아ㅏㅏㅋㅋ
>* 4중 for문이라니 너무 즐겁다 ㅋㅋㅋ 이렇게 완전탐색도 끝낸다 고생했다!
