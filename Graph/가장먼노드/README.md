## 문제
n개의 노드가 있는 그래프가 있습니다. 각 노드는 1부터 n까지 번호가 적혀있습니다. 1번 노드에서 가장 멀리 떨어진 노드의 갯수를 구하려고 합니다. 가장 멀리 떨어진 노드란 최단경로로 이동했을 때 간선의 개수가 가장 많은 노드들을 의미합니다.

노드의 개수 n, 간선에 대한 정보가 담긴 2차원 배열 vertex가 매개변수로 주어질 때, 1번 노드로부터 가장 멀리 떨어진 노드가 몇 개인지를 return 하도록 solution 함수를 작성해주세요.

**제한사항**
>* 노드의 개수 n은 2 이상 20,000 이하입니다.
>* 간선은 양방향이며 총 1개 이상 50,000개 이하의 간선이 있습니다.
>* vertex 배열 각 행 [a, b]는 a번 노드와 b번 노드 사이에 간선이 있다는 의미입니다.

**입출력 예**
| n | vertex | return |
|:--------|:--------|:--------|
| 6 | [[3, 6], [4, 3], [3, 2], [1, 3], [1, 2], [2, 4], [5, 2]] | 3 |

입출력 예 설명
예제의 그래프를 표현하면 아래 그림과 같고, 1번 노드에서 가장 멀리 떨어진 노드는 4,5,6번 노드입니다.
![사진](https://raw.githubusercontent.com/zoomKoding/zoomKoding.github.io/source/assets/_posts/graph-1.png)


## 문제 이해

>* 일단 각 노드의 최단 경로의 거리를 구해야 한다.
>* 모든 destination에 대한 최단 경로를 찾고 가장 멀리 있는 값(max)을 발견한 후에 max의 갯수를 구해라

## 방법은

>* BFS를 이용해보자
>* 그렇다면 그래프로 어떻게 표현할 것인가
>* 이번에는 Adjacency List를 linked list와 유사하게 표현해보자.
>* 이것은 이차원 어레이보다 공간할당을 최소화 하기 위함이다.
>* 엣지를 발견할 때마다 이전에 발견한 거리 d[y]가 x로 부터 한번 더 온 거리 d[x] + 1보다 크다면 d[y]를 교체해준다.
>* 마지막에 각 vertex까지의 경로 중 max를 발견한 후에 같은 친구를 return 해주자


## BFS 활용 코드 (점수 : 100점)

    #include <string>
    #include <vector>
    #include <queue>

    using namespace std;

    int solution(int n, vector<vector<int>> edge) {
        int answer = 0;
        int * d = new int[n + 1];
        queue<int> q;
        vector<queue<int>> v;
        for(int i = 0; i < n + 1; i++){
            v.push_back(queue<int>());
            d[i] = 50000;
        }
        d[1] = 0; 
        for(int i = 0; i < edge.size(); i++){
            v[edge[i][0]].push(edge[i][1]);
            v[edge[i][1]].push(edge[i][0]);
        }
        q.push(1);
        while(!q.empty()){
            int x = q.front();
            q.pop();
            while(!v[x].empty()){
                int y = v[x].front();
                v[x].pop();
                q.push(y);
                if(d[x] + 1 < d[y]) d[y] = d[x] + 1;
            }
        }
        int max = 0;
        for(int i = 1; i < n + 1; i++){
            if(d[i] > max) max = d[i];
        }

        for(int i = 1; i < n + 1; i++){
            if(d[i] == max) answer ++;
        }
        return answer;
    }

## 느낀점

>* 링크드 리스트로 adjacency list를 표현하기에 성공했다 예에~ 이게 훨씬 수월하고 빠른 듯하다!!
>* 오늘은 여러 문제를 도전했지만 그래도 그래프 한문제 성공한게 제일 뿌듯한듯하다! 
>* 남은 그래프 문제도 화이팅이다!
