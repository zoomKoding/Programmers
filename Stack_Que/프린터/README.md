## 문제

일반적인 프린터는 인쇄 요청이 들어온 순서대로 인쇄합니다. 그렇기 때문에 중요한 문서가 나중에 인쇄될 수 있습니다. 이런 문제를 보완하기 위해 중요도가 높은 문서를 먼저 인쇄하는 프린터를 개발했습니다. 이 새롭게 개발한 프린터는 아래와 같은 방식으로 인쇄 작업을 수행합니다.

 >* 인쇄 대기목록의 가장 앞에 있는 문서를 대기목록에서 꺼냅니다.
 >* 나머지 인쇄 대기목록에서 J보다 중요도가 높은 문서가 한개라도 존재하면 J를 대기목록의 가장 마지막에 넣습니다.
 >* 그렇지 않으면 J를 인쇄합니다.
 
 예를 들어, 4개의 문서(A, B, C, D)가 순서대로 인쇄 대기목록에 있고 중요도가 2 1 3 2 라면 C D A B 순으로 인쇄하게 됩니다.
 
**제한사항**

>* 현재 대기목록에는 1개 이상 100개 이하의 문서가 있습니다.
>* 인쇄 작업의 중요도는 1~9로 표현하며 숫자가 클수록 중요하다는 뜻입니다.
>* location은 0 이상 (현재 대기목록에 있는 작업 수 - 1) 이하의 값을 가지며 대기목록의 가장 앞에 있으면 0, 두 번째에 있으면 1로 표현합니다.

## 어떻게 접근할 것인가?

>* 그림을 그려보니 일단 FIFO이 맞다.
>* 근데 순서대로 꺼내면서 그것보다 우선순위가 높은 친구가 있는지 확인을 해야하는데 그것을 어떻게 할 것인가가 광건이다.
>* 그리고 매번 queue에 priorities의 인덱스를 넣어주고 하나씩 꺼내면서 값이랑 비교해주는 방법을 쓰려고 한다. 
>* 조금 더럽지만 한번 짜보자.

## queue 활용 코드 (점수: 35점, 나머지 시간초과)

    #include <string>
    #include <vector>
    #include <queue>
    using namespace std;

    int solution(vector<int> priorities, int location) {

        //일단 map에 인덱스를 키로 하는 친구를 다 넣어놓고 큐에도 다 넣어준다.
        queue<int> q;
        for(int i = 0; i < priorities.size(); i++)q.push(i);

        int order = 0;
        while(!q.empty()){
            int q_front = q.front();
            int prior = priorities[q_front];
            for(int i = 0; i < priorities.size(); i++){
                if(prior < priorities[i]){
                    q.push(q_front);
                    prior = -1;
                    break;
                }
            }
            q.pop();
            if(prior != -1){
                order ++;
                if(q_front == location)return order;
            }
        }

        return order;
    }

 **자신보다 높은 점수가 있는지 확인하는 과정이 너무 오래걸리는 것 같다..** 

## 맵, 큐 활용 코드(점수: 100점)

**max를 생성하고 맥스가 뭔지 map을 통해 확인할 수 있게 했다.**

    #include <string>
    #include <vector>
    #include <queue>
    #include <map>
    #include <iostream>
    using namespace std;

    int solution(vector<int> priorities, int location) {
        queue<int> q;
        map<int, int> m;
        int max = 0;
        int order = 0;

        for(int i = 0; i < priorities.size(); i++){
            q.push(i);
            if(m[priorities[i]] == m.end()->second) m[priorities[i]] = 1;
            else m[priorities[i]] ++;
            if(priorities[i] > max) max = priorities[i];
        }

        while(!q.empty()){
            int q_front = q.front();
            int prior = priorities[q_front];
            q.pop();

            if(prior == max){
                order ++;
                if(q_front == location) return order;
                if(--m[prior] == 0){
                    for(int i = prior-1; i > 0; i--){
                        if(m[i] != m.end()->second){
                        max = i;
                        break;
                        } 
                    }   
                }
            }
            else q.push(q_front);
        }
        return order;
    }


## 느낀점

>* 처음에 코드 짜고 딱 각이 나왔었다... 
>* 사실 시간 초과의 원인이 뭔지도 알았는데 괜히 다른 방식으로 짜려고 하려다가 시간이 더 걸렸다. 
>* 중간중간에 내가 어떻게 접근하고 있는지 머리 속으로 정리하는 것이 필요한 것 같다.
