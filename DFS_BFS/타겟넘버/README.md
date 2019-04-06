## 문제

n개의 음이 아닌 정수가 있습니다. 이 수를 적절히 더하거나 빼서 타겟 넘버를 만들려고 합니다. 예를 들어 [1, 1, 1, 1, 1]로 숫자 3을 만들려면 다음 다섯 방법을 쓸 수 있습니다.

>* -1+1+1+1+1 = 3
>* +1-1+1+1+1 = 3
>* +1+1-1+1+1 = 3
>* +1+1+1-1+1 = 3
>* +1+1+1+1-1 = 3

사용할 수 있는 숫자가 담긴 배열 numbers, 타겟 넘버 target이 매개변수로 주어질 때 숫자를 적절히 더하고 빼서 타겟 넘버를 만드는 방법의 수를 return 하도록 solution 함수를 작성해주세요.

**제한사항**
* 주어지는 숫자의 개수는 2개 이상 20개 이하입니다.
* 각 숫자는 1 이상 50 이하인 자연수입니다.
* 타겟 넘버는 1 이상 1000 이하인 자연수입니다.

## 어떻게 접근할 것인가?

>* numbers에 있는 원소가 +일때 -일때를 모두 고려해줘야 한다.
>* 이를 위해서 numbers에 있는 원소를 2^갯수 만큼 모두 경로를 탐색해줘야한다. 
>* 처음부터 끝까지 가는 모든 경우를 확인하기 위해서 DFS를 이용하기로 했다. 

**말이 DFS지 그냥 내가 이해하고 있는 recursive를 이용해서 진행했다.ㅜㅜ**

### DFS 활용 코드(복잡도 : 2^n)

    #include <string>
    #include <vector>

    using namespace std;

    vector<int> numbers;
    int target;

    int dfs(int sum, int depth){
        if(depth == numbers.size()){
            if(sum == target) return 1;
            else return 0;
        }
        return dfs(sum + numbers[depth], depth+1) + dfs(sum - numbers[depth], depth+1);
    }

    int solution(vector<int> _numbers, int _target) {
        numbers = _numbers;
        target = _target;
        return dfs(0, 0);
    }
    
## 느낀점

>* 얕게 공부하고 짠 것치고 상당히 만족스럽다 ㅋㅋㅋ
>* 일단 오랜만에 빠른 시간 내에 문제를 푼 것에 만족하지만 앞으로 닥칠 Level 3 문제들이 너무 무섭다.
>* 좀 더 BFS와 DFS에 대해 공부해 봐야겠다. 

