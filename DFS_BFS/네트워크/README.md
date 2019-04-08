## 문제

네트워크란 컴퓨터 상호 간에 정보를 교환할 수 있도록 연결된 형태를 의미합니다. 예를 들어, 컴퓨터 A와 컴퓨터 B가 직접적으로 연결되어있고, 컴퓨터 B와 컴퓨터 C가 직접적으로 연결되어 있을 때 컴퓨터 A와 컴퓨터 C도 간접적으로 연결되어 정보를 교환할 수 있습니다. 따라서 컴퓨터 A, B, C는 모두 같은 네트워크 상에 있다고 할 수 있습니다.

컴퓨터의 개수 n, 연결에 대한 정보가 담긴 2차원 배열 computers가 매개변수로 주어질 때, 네트워크의 개수를 return 하도록 solution 함수를 작성하시오.

**제한사항**
컴퓨터의 개수 n은 1 이상 200 이하인 자연수입니다.
각 컴퓨터는 0부터 n-1인 정수로 표현합니다.
i번 컴퓨터와 j번 컴퓨터가 연결되어 있으면 computers[i][j]를 1로 표현합니다.
computer[i][i]는 항상 1입니다.

입출력 예
>* n    computers                           return
>* 3    [[1, 1, 0], [1, 1, 0], [0, 0, 1]]    2
>* 3    [[1, 1, 0], [1, 1, 1], [0, 1, 1]]    1

## 어떻게 접근할 것인가?

>* 모든 원소를 빠짐없이 다 훑어야 한다.
>* connection이 없으면 root를 다르게 해서 한번 더 훑어줘야 한다.
>* DFS든 BFS든 훑을 수만 있으면 된다.
>* 다 훑었는지 확인하기 위해 visited라는 array를 만들어서 방문 안된 친구를 root로 훑자!
>* 이번에는 BFS를 써보기로 했다. 한번도 안써봤다..ㅎㅎ

**사실 DFS가 더 효율적일지 BFS가 더 효율적인지 판단이 잘 안선다.**

### BFS 활용 코드(복잡도 : O(N+E))

    #include <string>
    #include <vector>
    #include <iostream>
    #include <queue>

    using namespace std;

    vector<vector<int>> computers;
    queue<int> q;
    bool *visited;
    int n;
    int count = 0;
    
    //나름 내가 짠 bfs ㅎㅎ
    void bfs(int index){
        q.push(index);
        visited[index] = true;
        while(!q.empty()){
            int temp = q.front();
            q.pop();
            for(int i = 0 ; i < n ; i++){
                if(computers[temp][i] == 1 && !visited[i] && i != temp ){
                    q.push(i);
                    visited[i] = true;
                }
            }
        }
    }

    int solution(int _n, vector<vector<int>> _computers) {
        computers = _computers;
        n = _n;
        visited = new bool[n];
        
        //초기화
        for(int i = 0; i < n; i ++) visited[i] = false;
        
        //방문 안한 원소는 root로 해서 bfs 진행
        for(int i = 0; i < n; i++){
            if(!visited[i]) {
                bfs(i);
                count++;
            }
        }
        return count;
    }

    
## 느낀점

>* 나름 이제 이해는 됐는데 언제 DFS를 쓰고 BFS를 쓰는지 감이 잘 안온다.
>* 더 많은 예제를 풀어봐야겠다.

