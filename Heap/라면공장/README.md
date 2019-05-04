## 문제

매운 것을 좋아하는 Leo는 모든 음식의 스코빌 지수를 K 이상으로 만들고 싶습니다. 모든 음식의 스코빌 지수를 K 이상으로 만들기 위해 Leo는 스코빌 지수가 가장 낮은 두 개의 음식을 아래와 같이 특별한 방법으로 섞어 새로운 음식을 만듭니다.

>  섞은 음식의 스코빌 지수 = 가장 맵지 않은 음식의 스코빌 지수 + (두 번째로 맵지 않은 음식의 스코빌 지수 * 2)

Leo는 모든 음식의 스코빌 지수가 K 이상이 될 때까지 반복하여 섞습니다.
Leo가 가진 음식의 스코빌 지수를 담은 배열 scoville과 원하는 스코빌 지수 K가 주어질 때, 모든 음식의 스코빌 지수를 K 이상으로 만들기 위해 섞어야 하는 최소 횟수를 return 하도록 solution 함수를 작성해주세요.

**제한사항**

>* scoville의 길이는 1 이상 1,000,000 이하입니다.
>* K는 0 이상 1,000,000,000 이하입니다.
>* scoville의 원소는 각각 0 이상 1,000,000 이하입니다.
>* 모든 음식의 스코빌 지수를 K 이상으로 만들 수 없는 경우에는 -1을 return 합니다.

## 어떻게 접근할 것인가?

>* 큐에 넣어서 한번 쭉 넣었다 뺏다를 하면 좋을 것 같다.
>* 근데 큐에서 뺄 때 가장 작은 두개를 빼줘야하는데 그럼 priority queue(heap)을 사용하면 좋을 것 같다.

## 힙 활용 코드(복잡도 : O(nlogn), 점수: 100)

    #include <string>
    #include <vector>
    #include <queue>

    using namespace std;

    int solution(vector<int> scoville, int K) {
        priority_queue<int, vector<int>, greater<int>> pq;
        for(int i= 0; i < scoville.size(); i++)pq.push(scoville[i]);
        int times = 0;
        while(!pq.empty()){
            if(pq.top() < K && pq.size() ==1) break;
            int num[2];
            for(int i = 0 ; i < 2; i++){
                num[i] = pq.top();
                pq.pop();
            }        
            if(num[0] >= K) return times;
            pq.push(num[0]+num[1]*2);
            times++;
        }
        return -1;
    }


## 결론

>* queue의 필요성을 느끼는데 queue에서 꺼낼 때 sorting이 된 상태로 빼고 싶다면 heap이 답이다.
>* heap은 참 좋은 아이이다. 나중에 유용하게 쓸 수 있을 것 같다. 
