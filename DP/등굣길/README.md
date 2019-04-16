## 문제

계속되는 폭우로 일부 지역이 물에 잠겼습니다. 물에 잠기지 않은 지역을 통해 학교를 가려고 합니다. 집에서 학교까지 가는 길은 m x n 크기의 격자모양으로 나타낼 수 있습니다.

아래 그림은 m = 4, n = 3 인 경우입니다.

가장 왼쪽 위, 즉 집이 있는 곳의 좌표는 (1, 1)로 나타내고 가장 오른쪽 아래, 즉 학교가 있는 곳의 좌표는 (m, n)으로 나타냅니다.

격자의 크기 m, n과 물이 잠긴 지역의 좌표를 담은 2차원 배열 puddles이 매개변수로 주어질 때, 학교에서 집까지 갈 수 있는 최단경로의 개수를 1,000,000,007로 나눈 나머지를 return 하도록 solution 함수를 작성해주세요.

**제한사항**
>* 격자의 크기 M, N은 1 이상 100 이하인 자연수입니다.
>* 물에 잠긴 지역은 0개 이상 10개 이하입니다.
>* 집과 학교는 물에 잠기지 않았습니다.

## 어떻게 접근할 것인가?

>* bfs를 이용해서 거리를 하나씩 늘려가면서 훑어보자(좌우상하)
>* 굳이 이미 거쳐간 지점은 확인할 필요 없게 해당지점까지 가는 최단거리를 적어놓자(array에 저장)
>* 최단거리가 아니거나 array 밖으로 빠지면 버려!

## queue 코드(복잡도 : , 정답율: 50점, 나머지 다 시간초과)

    #include <string>
    #include <vector>
    #include <queue>
    #include <iostream>

    using namespace std;
    int** array;
    queue<pair<int, int>> q;

    int bfs(int m, int n){
        int count = 0;
        q.push(make_pair(1,1));
        while(!q.empty()){
            //일단 하나꺼내
            pair <int,int> r = q.front(); 
            int cur_dist = array[r.first][r.second];
            if(r.first == m && r.second == n) count++;
            q.pop();
            //사방향으로 보내버려
            //좌
            if(cur_dist + 1 <= array[r.first-1][r.second]){
                array[r.first-1][r.second] = cur_dist+1;
                q.push(make_pair(r.first-1, r.second));
            }
            //우
            if(cur_dist + 1 <= array[r.first+1][r.second]){
                array[r.first+1][r.second] = cur_dist+1;
                q.push(make_pair(r.first+1, r.second));
            }
            //상
            if(cur_dist + 1 <= array[r.first][r.second-1]){
                array[r.first][r.second-1] = cur_dist+1;
                q.push(make_pair(r.first, r.second-1));
            }
            //하
            if(cur_dist + 1 <= array[r.first][r.second+1]){
                array[r.first][r.second+1] = cur_dist+1;
                q.push(make_pair(r.first, r.second+1));
            }

        }
        return count;
    } 


    int solution(int m, int n, vector<vector<int>> puddles) {
        //웅덩이랑 판 테두리를 -1로 만들어버려
        array = new int*[m+2];
        for(int i = 0; i < m+2; i++)array[i] = new int[n+2];
        for(int i = 0; i < m+2; i++){
            for(int j = 0; j < n+2; j++) array[i][j] = -1;
            
        }
        for(int i = 1; i < m+1; i++){
            for(int j = 1; j < n+1; j++) array[i][j] = 1000;
        }

        //웅덩이: -1, 집: 0
        for(int i = 0; i < puddles.size(); i++)array[puddles[i][0]][puddles[i][1]] = -1;
        array[1][1] = 0;

        return bfs(m,n)%1000000007;

    }
    
## 더 효율적으로?

>* 문뜩 떠오른 생각인데 이미 같은 길을 간 친구들을 queue에 넣지 말고 그냥 값만 저장해주면 어떤가
>* 그럼 그 길을 간 대표 한명이 가면 나머지 사람은 갈필요 없이 결과를 더 금방 볼 수 있다.
>* 짜보자...

## dp 활용 코드(복잡도: , 정답율: 100점)

    #include <string>
    #include <vector>
    #include <queue>
    #include <iostream>

    using namespace std;
    int** array;
    int** ways;
    queue<pair<int, int>> q;

    void to_array(int dist, int org_i, int org_j, int i, int j){
        if(dist <= array[i][j]){
            if(dist == array[i][j]){
                ways[i][j] += ways[org_i][org_j];
                ways[i][j] %= 1000000007;
            }
            else{
                ways[i][j] = ways[org_i][org_j];
                array[i][j] = dist;
                q.push(make_pair(i, j));
            }
        }
    }

    int bfs(int m, int n){
        int count = 0;
        q.push(make_pair(1,1));
        while(!q.empty()){
            pair <int,int> r = q.front();
            int cur_dist = array[r.first][r.second];
            if(r.first == m && r.second == n) return ways[r.first][r.second];
            q.pop();
            to_array(cur_dist+1, r.first, r.second, r.first-1, r.second);
            to_array(cur_dist+1, r.first, r.second, r.first+1, r.second);
            to_array(cur_dist+1, r.first, r.second, r.first, r.second-1);
            to_array(cur_dist+1, r.first, r.second, r.first, r.second+1);
        }
        return count;
    }


    int solution(int m, int n, vector<vector<int>> puddles) {
        array = new int*[m+2];
        ways = new int*[m+2];
        for(int i = 0; i < m+2; i++)array[i] = new int[n+2];
        for(int i = 0; i < m+2; i++)ways[i] = new int[n+2];
        for(int i = 0; i < m+2; i++){
            for(int j = 0; j < n+2; j++) array[i][j] = -1;
        }
        for(int i = 1; i < m+1; i++){
            for(int j = 1; j < n+1; j++){
                array[i][j] = 1000;
                ways[i][j] = 0;
            }
        }
        for(int i = 0; i < puddles.size(); i++)array[puddles[i][0]][puddles[i][1]] = -1;
        array[1][1] = 0;
        ways[1][1] = 1;
        return bfs(m,n);
    }

**야스..!! 개 잘 짰다고 생각했...**

## 미친코드(어떤 갓성님이 짠 코드인가)

    #include <string>
    #include <vector>
    #define mod 1000000007;
    using namespace std;

    int dy[101][101];
    bool map[101][101];
    int solution(int m, int n, vector<vector<int>> puddles) {
        for(int i=0; i<puddles.size(); i++) map[puddles[i][1]][puddles[i][0]] = 1;
        dy[1][1] = 1;
        for(int i=1; i<=n; i++){
            for(int j=1; j<=m; j++){
                if(i==1 && j==1) continue;
                if(map[i][j] == 1) continue;
                dy[i][j] = (dy[i-1][j] + dy[i][j-1]) % mod;
            }
        }
        return dy[n][m];
    }

>* 좌측 끝부터 순서대로 읽으면서 큐이런거 다 안쓰고 바로 위와 좌에 있는 원소를 그냥 더했다.
>* 큐 안쓰고 이런식으로 해도 어차피 필요한 워와 옆 원소의 값들은 다 구해지기 때문에
>* 순서 대로 읽어도 된다는... 충격적인 사실.. 20줄 코드에 녹았다.

## 느낀점

>* 손수 연산과정을 따라가면서 뭔가 중복된 연산이 존재한다 싶으면 빨리 DP로 갈아타자.
>* 생각을 할 때 좀 더 많이 생각해야 한다. 내꺼가 제일 효율적이라는 말은 **거짓말이고 재앙이다.**
>* DP를 이제는 어느정도 이해한 것 같아서 다행이다.


