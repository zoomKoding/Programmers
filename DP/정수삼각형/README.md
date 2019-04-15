## 문제

위와 같은 삼각형의 꼭대기에서 바닥까지 이어지는 경로 중, 거쳐간 숫자의 합이 가장 큰 경우를 찾아보려고 합니다. 아래 칸으로 이동할 때는 대각선 방향으로 한 칸 오른쪽 또는 왼쪽으로만 이동 가능합니다. 예를 들어 3에서는 그 아래칸의 8 또는 1로만 이동이 가능합니다.

삼각형의 정보가 담긴 배열 triangle이 매개변수로 주어질 때, 거쳐간 숫자의 최댓값을 return 하도록 solution 함수를 완성하세요.

**제한사항**
>* 삼각형의 높이는 1 이상 500 이하입니다.
>* 삼각형을 이루고 있는 숫자는 0 이상 9,999 이하의 정수입니다.

## 어떻게 접근할 것인가?

>* dfs로 쭉 한번 훑고 오면 안되나?

## dfs 코드(복잡도 : , 정답율: 50점, 나머지 다 시간초과)

    #include <string>
    #include <vector>

    using namespace std;

    vector<vector<int>> triangle;

    int dfs(int depth, int index, int num){
        if(depth == triangle.size()) return num;

        int add1 = dfs(depth+1, index, num + triangle[depth][index]);
        int add2 = dfs(depth+1, index+1, num + triangle[depth][index+1]);
        return add1>add2 ? add1 : add2;
    }

    int solution(vector<vector<int>> _triangle) {
        triangle = _triangle;
        return dfs(1, 0, triangle[0][0]);
    }
    
    
## 그럼 또 다시 dp를 쓸 방법을 생각해봐야하는 것인가

>* 그럼 optimal substructure를 찾아야 한다.
>* 루트 노드부터 현재 노드까지 최대값을 저장해놓는다. 
>* 여러 길로 올 수 있는데 그중 최선의 값을 저장해서 optimal structure로 사용한다.
>* 마지막에 마지막 층에 있는 녀석 중에 최대값이 최선이다.
>* (optimal 값을 담을 array의 구조가 triangle이랑 같기 때문에 그냥 copy했다.)

## dp 활용 코드(복잡도: , 정답율: 100점)

    #include <string>
    #include <vector>

    using namespace std;

    int solution(vector<vector<int>> triangle) {
        vector<vector<int>> array = triangle; 
        array[0][0] = triangle[0][0];
        for(int i = 1; i < triangle.size(); i++){
            for(int j = 0; j < i; j++){
                int num1 = array[i-1][j]+ triangle[i][j];
                if(j == 0) array[i][j] = num1;
                else if(num1> array[i][j]) array[i][j] = num1;
                array[i][j+1] = array[i-1][j] + triangle[i][j+1];
            }
        }
        int max = 0, leaf = triangle.size()-1;
        for(int i = 0; i < array[leaf].size(); i++){
            if(array[leaf][i] > max) max = array[leaf][i];
        }
        return max;
    }

## 느낀점

>* 디피는 옵티멀 섭스트럭쳐를 잘 찾을 수 있다면 너무 활용도 높은 방법인 듯하다.
>* 디피는 진짜 많이 풀어봐서 감을 잡는게 중요할 것 같다.
>*

