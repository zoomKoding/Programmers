## 문제

주어진 항공권을 모두 이용하여 여행경로를 짜려고 합니다. 항상 ICN 공항에서 출발합니다.

항공권 정보가 담긴 2차원 배열 tickets가 매개변수로 주어질 때, 방문하는 공항 경로를 배열에 담아 return 하도록 solution 함수를 작성해주세요.


**제한사항**

>* 모든 공항은 알파벳 대문자 3글자로 이루어집니다.
>* 주어진 공항 수는 3개 이상 10,000개 이하입니다.
>* tickets의 각 행 [a, b]는 a 공항에서 b 공항으로 가는 항공권이 있다는 의미입니다.
>* 주어진 항공권은 모두 사용해야 합니다.
>* 만일 가능한 경로가 2개 이상일 경우 알파벳 순서가 앞서는 경로를 return 합니다.
>* 모든 도시를 방문할 수 없는 경우는 주어지지 않습니다.

## 문제 이해

>* 항공권을 모두 이용하도록 Edge의 순서를 잘 정해야 할 것 같다.
>* 경로가 여러개 존재하면 그 중에 알파벳이 높은 순으로 있어야 하므로 어떻게 그래프를 잘 만들어봐야 한다.
>* 각 원소가 string으로 되있어서 array로 안되고 linked list로 해야할 것만 같다..(**시도했다가 호되게 당했다. 거의 3시간 순삭...**)
>* **여기서 제일 중요한 것은 가장 먼저인 Edge를 픽하는게 항상 정답이 아니다 즉, 다른 경우도 살펴봐야 한다.**

## 나만의 linked list 구현하기(map과 priority queue 활용)

>* 처음에 링크드 리스트를 구현하려다가 여러가지 에러에 봉착했다.. 뭐가 문제인지도 정확히 모를정도로 헤매다 왔다...
>* 나는 포인터를 정말 모르는 것 같다... 다시 공부해야한다 필히...
>* 그래서 내가 구현한 linked list는 map 안에 priority queue를 넣었다.
>* 들어가는 친구들은 Alphabetical Order 이여야하기 때문에 더더욱 이 방법이 좋겠다는 생각이 들었다.
>* Linked list 구현 모습

    map<string, priority_queue<string, vector<string>, greater<string>>>m;

>* 각 vertex 당 priority_queue가 하나씩 뒤에 붙어 있는 식이다! :) 
>* 처음에 도전했던 C++ 코드보다도 훨씬 짧아서 나름 만족하고 있다 ㅎㅎ
>* 물론 포인터를 쓰지 않는 것도 아주 좋았다...

## 방법은?

>* 일단 map에 모든 것들을 넣어라
>* 처음에는 그냥 당장 alphabetical order로 하나씩 끄집어 내려고 했는데 그러면 전체 항공권을 사용하지 못하는 경우가 발생한다. 때문에 이를 DFS해서 다른 경우도 봐줄 필요성이 있었다.
>* DFS를 할 때는 그래도 먼저 나온 경로를 먼저해보고 항공권을 다 안쓰면 다른 길도 도전하는 식으로 했다.
>* dfs 함수 내에서는 m[s]에서 먼저 다 꺼낸다음에 이용할 항공권 친구 하나 빼고 나머지를 다시 넣어서 Recursive하게 보낸다.

### DFS 활용 코드(점수: 100점)

    #include <string>
    #include <vector>
    #include <map>
    #include <queue>

    using namespace std;

    int t_size = 0;

    vector<string> dfs(string s, map<string, priority_queue<string, vector<string>, greater<string>>>m, vector<string> t){
        vector<string> v;
        t.push_back(s);
        if(m[s].empty()) return t;
        vector<string> temp;
        while(!m[s].empty()){
            temp.push_back(m[s].top());
            m[s].pop();
        }
        for(int i = 0; i < temp.size(); i++){
            map<string, priority_queue<string, vector<string>, greater<string>>>_m = m;
            for(int j = 0; j < temp.size(); j++){
            if(i != j)_m[s].push(temp[j]); 
            }
            v = dfs(temp[i], _m, t);
            if(v.size() == t_size + 1) break;
        }
        return v;
    }

    map<string, priority_queue<string, vector<string>, greater<string>>>m;
    
    vector<string> solution(vector<vector<string>> tickets) {
        vector<string> answer;
        t_size = tickets.size();
        for(int i = 0; i < tickets.size(); i++){
            m[tickets[i][0]].push(tickets[i][1]);
        }
        return dfs("ICN", m, answer);
    }


## 느낀점

>* 괜히 다른 사람들이 못푼게 아니었다. 일단 linked list를 구현하는 어려움을 처음 느껴봤다.
>* 포인터에 대해서 제대로 이해하지 못하는게 결국 내 코드에 대한 불신으로 이어졌다.
>* 코드를 그냥 다 갈아엎은게 한 5번은 되는 것 같다.
>* 그래도 나름의 방식으로 도전해본 것은 나름 뿌듯하다 ㅎㅎ 바쁜 와중에 한문제였고 map과 pq의 활용은 진짜 너무 기분좋다 ㅎㅎ
>* 고생한 만큼 많이 배웠길!!
