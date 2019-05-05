## 문제

라면 공장에서는 하루에 밀가루를 1톤씩 사용합니다. 원래 밀가루를 공급받던 공장의 고장으로 앞으로 k일 이후에야 밀가루를 공급받을 수 있기 때문에 해외 공장에서 밀가루를 수입해야 합니다.

해외 공장에서는 향후 밀가루를 공급할 수 있는 날짜와 수량을 알려주었고, 라면 공장에서는 운송비를 줄이기 위해 최소한의 횟수로 밀가루를 공급받고 싶습니다.

현재 공장에 남아있는 밀가루 수량 stock, 밀가루 공급 일정(dates)과 해당 시점에 공급 가능한 밀가루 수량(supplies), 원래 공장으로부터 공급받을 수 있는 시점 k가 주어질 때, 밀가루가 떨어지지 않고 공장을 운영하기 위해서 최소한 몇 번 해외 공장으로부터 밀가루를 공급받아야 하는지를 return 하도록 solution 함수를 완성하세요.

dates[i]에는 i번째 공급 가능일이 들어있으며, supplies[i]에는 dates[i] 날짜에 공급 가능한 밀가루 수량이 들어 있습니다.


**제한사항**

>* stock에 있는 밀가루는 오늘(0일 이후)부터 사용됩니다.
>* stock과 k는 2 이상 100,000 이하입니다.
>* dates의 각 원소는 1 이상 k 이하입니다.
>* supplies의 각 원소는 1 이상 1,000 이하입니다.
>* dates와 supplies의 길이는 1 이상 20,000 이하입니다.
>* k일 째에는 밀가루가 충분히 공급되기 때문에 k-1일에 사용할 수량까지만 확보하면 됩니다.
>* dates에 들어있는 날짜는 오름차순 정렬되어 있습니다.
>* dates에 들어있는 날짜에 공급되는 밀가루는 작업 시작 전 새벽에 공급되는 것을 기준으로 합니다. 예를 들어 9일째에 밀가루가 바닥나더라도, 10일째에 공급받으면 10일째에는 공장을 운영할 수 있습니다.
>* 밀가루가 바닥나는 경우는 주어지지 않습니다.

## 문제 이해

>* 음.. 날짜가 가면서 stock이 줄어드는데 k 날까지 언제, 몇번 공급 받는게 최선의 선택인지를 찾는 문제이다. 
>* 

## 방법은?(초기)

>* Node라는 구조체를 만들어서 복잡다양하게 엄청 까다롭게 문제를 풀어보자.. 4시간 만에 시간초과 메모리 초과...

## 힙 활용 코드(시간초과, 메모리초과, 점수: 26점)

    #include <string>
    #include <vector>
    #include <queue>
    #include <iostream>


    using namespace std;

    struct Node{
    int stock;
    int date;
    int index;
    int count;
    };

    struct cmp{
        bool operator()(Node t, Node u){
        // bool a;
        // if(t.count > u.count) a = true;
        // else if(t.count == u.count){
        //     if(t.index < u.index) a = true;
        //     else a = false;
        // }
        // else a = false;
        // return a;
        return t.count > u.count;
        }
    };

    int solution(int stock, vector<int> dates, vector<int> supplies, int k) {
        int answer = 100000;
        priority_queue< Node, vector<Node>,  cmp > pq;

        Node root;
        root.stock = stock;
        root.date = 0;
        root.index = 0;
        root.count = 0;
        pq.push(root);

        while(!pq.empty()){
            Node temp;
            temp = pq.top();
            if(temp.count >= answer - 1)break;
            // cout << "[s, d, i, c] : [" << temp.stock << ", " << temp.date << ", " << temp.index << ", " << temp.count << "]"<<endl;
            pq.pop();

            int current_s = temp.stock - (dates[temp.index]-temp.date);

            Node child[2];
            child[0].stock = current_s + supplies[temp.index];
            child[0].date = dates[temp.index];
            child[0].count = temp.count+1;
            child[0].index = temp.index+1;
            child[1].stock = current_s;
            child[1].date = dates[temp.index];
            child[1].count = temp.count;
            child[1].index = temp.index+1;
            for(int i = 0; i < 2; i++){
                if(child[i].index == dates.size()) {
                    if(child[i].stock >= k - child[i].date){
                        if(answer > child[i].count) answer = child[i].count;
                    }
                    continue;
                }

                current_s = child[i].stock - (dates[child[i].index]-child[i].date);
                if(current_s < 0) continue;
                if(child[i].count >= answer - 1)continue;

                // if(current_s >= k - dates[child[i].index]) return child[i].count;
                // cout << "[s, d, i, c] : [" << child[i].stock << ", " << child[i].date << ", " << child[i].index << ", " << child[i].count << "]";
                // cout << " current stock : "<< current_s<< endl;

                pq.push(child[i]);
            }
        }
        return answer;
    }

## 일주일 만에 다시 도전!

>* 이번에는 복잡하게 하지 않아보려고 했다.
>* for문을 통해 공급 날짜와 다음 공급 날짜와의 차이를 구하고(dates_diff) 그 다음 공급까지 공급 안하고 버틸만 한지 본다.
>* 버틸만 하면 그냥 priority queue에 넣고 다음 공급날짜로 이동~
>* 못버티겠으면 priority queue 에서 현재 dates_diff를 감당할 때까지 공급을 받는다.(answer을 증가시켜)
>* priority queue에서 계속 맥스를 걸러줄 것이기 때문에 믿고 돌렸다. 

## Simply 힙 활용 코드(점수: 100점)

    #include <string>
    #include <vector>
    #include <queue> 

    using namespace std;

    int solution(int stock, vector<int> dates, vector<int> supplies, int k) {
        int answer = 0;
        priority_queue< int > pq;
        int dates_diff = dates[0];
        for(int i = 0; i < dates.size(); i++){
            stock -= dates_diff;
            if(stock >= k - dates[i]) break;

            if(i == dates.size()-1) dates_diff = k - dates[i];
            else dates_diff = dates[i+1] - dates[i];

            pq.push(supplies[i]);   
            while(stock < dates_diff){
                answer ++;
                stock += pq.top();
                pq.pop();
            }
        }
        return answer;
    }


## 결론

>* 결국에 풀었다...
>* 그냥 내가 priority queue를 이해 잘못한 줄 알고 공부를 하려고 했는데 알고 있었다..!
>* 문제를 이해하고 접근하니까 요즘 문제를 풀면서 겪는 허송세월이 줄어듬을 느낀다.
>* 어제 오늘 너무 보람찼다.. 남은 문제들도 화이팅해보자!!

