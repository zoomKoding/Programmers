## 문제

하드디스크는 한 번에 하나의 작업만 수행할 수 있습니다. 디스크 컨트롤러를 구현하는 방법은 여러 가지가 있습니다. 가장 일반적인 방법은 요청이 들어온 순서대로 처리하는 것입니다.

예를들어

- 0ms 시점에 3ms가 소요되는 A작업 요청
- 1ms 시점에 9ms가 소요되는 B작업 요청
- 2ms 시점에 6ms가 소요되는 C작업 요청

와 같은 요청이 들어왔습니다. 이를 그림으로 표현하면 아래와 같습니다.

![사진](https://raw.githubusercontent.com/zoomKoding/zoomKoding.github.io/source/assets/_posts/heap-1.png)

한 번에 하나의 요청만을 수행할 수 있기 때문에 각각의 작업을 요청받은 순서대로 처리하면 다음과 같이 처리 됩니다.

![사진](https://raw.githubusercontent.com/zoomKoding/zoomKoding.github.io/source/assets/_posts/heap-2.png)

- A: 3ms 시점에 작업 완료 (요청에서 종료까지 : 3ms)
- B: 1ms부터 대기하다가, 3ms 시점에 작업을 시작해서 12ms 시점에 작업 완료(요청에서 종료까지 : 11ms)
- C: 2ms부터 대기하다가, 12ms 시점에 작업을 시작해서 18ms 시점에 작업 완료(요청에서 종료까지 : 16ms)
이 때 각 작업의 요청부터 종료까지 걸린 시간의 평균은 10ms(= (3 + 11 + 16) / 3)가 됩니다.

하지만 A → C → B 순서대로 처리하면

![사진](https://raw.githubusercontent.com/zoomKoding/zoomKoding.github.io/source/assets/_posts/heap-3.png)

- A: 3ms 시점에 작업 완료(요청에서 종료까지 : 3ms)
- C: 2ms부터 대기하다가, 3ms 시점에 작업을 시작해서 9ms 시점에 작업 완료(요청에서 종료까지 : 7ms)
- B: 1ms부터 대기하다가, 9ms 시점에 작업을 시작해서 18ms 시점에 작업 완료(요청에서 종료까지 : 17ms)

이렇게 A → C → B의 순서로 처리하면 각 작업의 요청부터 종료까지 걸린 시간의 평균은 9ms(= (3 + 7 + 17) / 3)가 됩니다.

각 작업에 대해 [작업이 요청되는 시점, 작업의 소요시간]을 담은 2차원 배열 jobs가 매개변수로 주어질 때, 작업의 요청부터 종료까지 걸린 시간의 평균을 가장 줄이는 방법으로 처리하면 평균이 얼마가 되는지 return 하도록 solution 함수를 작성해주세요. (단, 소수점 이하의 수는 버립니다)

**제한 사항**
>* jobs의 길이는 1 이상 500 이하입니다.
>* jobs의 각 행은 하나의 작업에 대한 [작업이 요청되는 시점, 작업의 소요시간] 입니다.
>* 각 작업에 대해 작업이 요청되는 시간은 0 이상 1,000 이하입니다.
>* 각 작업에 대해 작업의 소요시간은 1 이상 1,000 이하입니다.
>* 하드디스크가 작업을 수행하고 있지 않을 때에는 먼저 요청이 들어온 작업부터 처리합니다.

## 문제 이해

>* 가장 효율적인 방법은 아마도 각 시간 때에 가장 일이 가장 짧은 친구들을 먼저 끝내서 기다리는 요청을 최소화 하는 것이다.
>* 일단 일이 진행될 때 마다 시간이 증가되어야 할 것 같고 총 그 작업이 기다리고 작업된 시간은 기록되어야 할 것 같다.
>* 시간이 증가함에 따라 기다리고 있는 친구들은 매번 확인 되어야 한다.

## 방법은?

>* pq 두개를 이용했다. 하나는 들어가기 전에 요청이 들어오는 시간이 빠른 순으로 나열되어 있고 하나는 ready queue로 일의 길이가 짧은 순으로 나열되어있다.
>* 매번 ready queue를 업데이트 하고 그중 하나를 고르고 마무리한 뒤에 시간을 업데이트 해주기를 반복한다.
>* 만약에 ready queue에 아무것도 없는 순간이 있다면 그 때는 가장 근접한 요청 원소로 시간을 바꾼 후 continue한다.

## 힙 활용 코드(점수: 100점)

    #include <string>
    #include <vector>
    #include <queue>
    #include <algorithm>

    using namespace std;

    struct compare1 {
        bool operator()(vector<int> a, vector<int> b) return a[0] > b[0];    
    };

    struct compare2 {
        bool operator()(vector<int> a, vector<int> b) return a[1] > b[1];    
    };

    int solution(vector<vector<int>> jobs) {
        int answer = 0;
        int time = 0;
        int finished = 0;

        priority_queue<vector<int>, vector<vector<int>>, compare2> pq_time;
        priority_queue<vector<int>, vector<vector<int>>, compare1> pq_start;
        for(int i = 0; i < jobs.size(); i++) pq_start.push(jobs[i]);
        
        while(finished != jobs.size()){
            while(!pq_start.empty()){
                vector<int> cand = pq_start.top();
                if(cand[0] > time) break;
                pq_start.pop();
                pq_time.push(cand);
            }
            if(pq_time.empty()){
                time = pq_start.top()[0];
                continue;
            }
            vector<int> temp = pq_time.top();
            pq_time.pop();
            time += temp[1];
            answer += time - temp[0];
            finished ++;
        }
        return answer/jobs.size();
    }

## 결론

>* 힙도 이제 끝나버렸다...
>* 오늘은 그래도 힙에서 compare 함수를 짜는 것도 연습해보고 아주 값진 경험을 할 수 있는 시간이었다.
>* 생각보다 문제가 슝슝 끝나버리는 것이 눈에 보여서 너무 기분이 좋다 ㅎㅎ
>* 대회 때 힙을 꼭 써보고 싶슴다..ㅎㅎ

