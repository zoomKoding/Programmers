## 문제

프로그래머스 팀에서는 기능 개선 작업을 수행 중입니다. 각 기능은 진도가 100%일 때 서비스에 반영할 수 있습니다.

또, 각 기능의 개발속도는 모두 다르기 때문에 뒤에 있는 기능이 앞에 있는 기능보다 먼저 개발될 수 있고, 이때 뒤에 있는 기능은 앞에 있는 기능이 배포될 때 함께 배포됩니다.

먼저 배포되어야 하는 순서대로 작업의 진도가 적힌 정수 배열 progresses와 각 작업의 개발 속도가 적힌 정수 배열 speeds가 주어질 때 각 배포마다 몇 개의 기능이 배포되는지를 return 하도록 solution 함수를 완성하세요.
 
**제한사항**

>* 작업의 개수(progresses, speeds배열의 길이)는 100개 이하입니다.
>* 작업 진도는 100 미만의 자연수입니다.
>* 작업 속도는 100 이하의 자연수입니다.
>* 배포는 하루에 한 번만 할 수 있으며, 하루의 끝에 이루어진다고 가정합니다. 예를 들어 진도율이 95%인 작업의 개발 속도가 하루에 4%라면 배포는 2일 뒤에 이루어집니다.

## 문제 이해

>* 맨 앞에 원소부터 100퍼를 채운다.
>* 100퍼를 채울 때까지 날이 흐르고 다음원소를 봤는데 100퍼이면 출시 count ++
>* 다음 원소가 100퍼가 아니야 그러면 이전 단계를 반복해라
>* 모든 원소가 다 출시될 때까지 돌아봅시다

## 방법은?

>* Queue에 인덱스를 넣어야할 것 같다. 
>* 날짜라는 변수를 만들어주고 progresses[i] + 날짜 * speeds[i] 해서 확인
>* Queue가 다 빌 때까지 돌려라


## queue 활용 코드 (점수: 100점)

    #include <string>
    #include <vector>
    #include <queue>

    using namespace std;

    vector<int> solution(vector<int> progresses, vector<int> speeds) {
        vector<int> answer;
        int dates = 0;
        int count = 0;
        queue<int> q;
        for(int i = 0; i < progresses.size(); i++)q.push(i);
        while(!q.empty()){
            int i = q.front();
            q.pop();
            progresses[i] += dates * speeds[i];
            if(progresses[i]>=100) count++;
            else{
                if(i != 0)answer.push_back(count);
                dates += (100 - progresses[i])/ speeds[i];
                if((100 - progresses[i]) % speeds[i] != 0)  dates ++;
                count = 1;
            }
        }
        answer.push_back(count);
        return answer;
    }
    
근데 생각해보니까 처음부터 끝까지 훑을 것이기 때문에 queue를 안쓰고 for문으로 끝낼 수 있을 것 같다.

## 그냥 반복문으로 뚝딱 코드 (점수: 100점)
    
    #include <string>
    #include <vector>

    using namespace std;

    vector<int> solution(vector<int> progresses, vector<int> speeds) {
        vector<int> answer;
        int dates = 0;
        int count = 0;
        for(int i = 0; i < progresses.size(); i++){
            progresses[i] += dates * speeds[i];
            if(progresses[i]>=100) count++;
            else{
                if(i != 0)answer.push_back(count);
                dates += (100 - progresses[i])/ speeds[i];
                if((100 - progresses[i]) % speeds[i] != 0)  dates ++;
                count = 1;
            }
        }
        answer.push_back(count);
        return answer;
    }

## 느낀점

>* 생각한대로 되서 너무 좋았다 ㅎㅎ
>* queue를 써도 좋았겠지만 그냥 반복문으로도 충분할 수 있다는 것을 발견한 것도 기분 좋았던 코딩시간이었다ㅎㅎ
