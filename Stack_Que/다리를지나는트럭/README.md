## 문제

트럭 여러 대가 강을 가로지르는 일 차선 다리를 정해진 순으로 건너려 합니다. 모든 트럭이 다리를 건너려면 최소 몇 초가 걸리는지 알아내야 합니다. 트럭은 1초에 1만큼 움직이며, 다리 길이는 bridge_length이고 다리는 무게 weight까지 견딥니다.
※ 트럭이 다리에 완전히 오르지 않은 경우, 이 트럭의 무게는 고려하지 않습니다.

예를 들어, 길이가 2이고 10kg 무게를 견디는 다리가 있습니다. 무게가 [7, 4, 5, 6]kg인 트럭이 순서대로 최단 시간 안에 다리를 건너려면 다음과 같이 건너야 합니다.

경과 시간    다리를 지난 트럭    다리를 건너는 트럭    대기 트럭
0    []    []    [7,4,5,6]
1~2    []    [7]    [4,5,6]
3    [7]    [4]    [5,6]
4    [7]    [4,5]    [6]
5    [7,4]    [5]    [6]
6~7    [7,4,5]    [6]    []
8    [7,4,5,6]    []    []

따라서, 모든 트럭이 다리를 지나려면 최소 8초가 걸립니다.

solution 함수의 매개변수로 다리 길이 bridge_length, 다리가 견딜 수 있는 무게 weight, 트럭별 무게 truck_weights가 주어집니다. 이때 모든 트럭이 다리를 건너려면 최소 몇 초가 걸리는지 return 하도록 solution 함수를 완성하세요.
 
**제한사항**

>* bridge_length는 1 이상 10,000 이하입니다.
>* weight는 1 이상 10,000 이하입니다.
>* truck_weights의 길이는 1 이상 10,000 이하입니다.
>* 모든 트럭의 무게는 1 이상 weight 이하입니다.

## 어떻게 접근할 것인가?

>* 다리에 올라간 애들은 어떻게 표현할 것인가
>* 큐로 해서 큐 사이즈가 다리 사이즈 만큼 되면 빼내자
>* 만약 다리에 같이 올릴 수 있다면 다리에 올려주고, 아니라면 시간이 간 걸 알 수 있게 큐에 -1을 넣어주자.
>* 전체 사이즈 만큼 돌고 나면 마지막 트럭이 올려진것까지 확인하고 종료하자.


## queue 활용 코드 (점수: 100점)

    #include <vector>
    #include <queue>
    #include <iostream>

    using namespace std;

    int solution(int bridge_length, int weight, vector<int> truck_weights) {
        queue<int> bridge;
        int current_w = 0;
        int time = 0;
        int i = 0;
        while(i != truck_weights.size()){
            time ++;
            if(bridge.size() == bridge_length){
                if(bridge.front() != -1) current_w -= bridge.front();
                bridge.pop();
            }
            if(current_w + truck_weights[i] <= weight){
                current_w += truck_weights[i];
                bridge.push(truck_weights[i]);
                i++;
            }
            else bridge.push(-1);
        }
        time += bridge_length;
        return time;
    }

## 느낀점

>* 나는 바보다... 문제를 똑바로 안읽었다. 
>* 순서대로 라고 분명히 써있는데 내멋대로 제일 효율적으로 넣을 방법을 찾고 있었다.
>* 문제를 잘 읽고 머리로 생각하고 코딩하자.. 제발제발제발제발제발제발 ㅠㅠ
