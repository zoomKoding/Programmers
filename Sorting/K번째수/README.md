## 문제

배열 array의 i번째 숫자부터 j번째 숫자까지 자르고 정렬했을 때, k번째에 있는 수를 구하려 합니다.

예를 들어 array가 [1, 5, 2, 6, 3, 7, 4], i = 2, j = 5, k = 3이라면

>* array의 2번째부터 5번째까지 자르면 [5, 2, 6, 3]입니다.
>* 1에서 나온 배열을 정렬하면 [2, 3, 5, 6]입니다.
>* 2에서 나온 배열의 3번째 숫자는 5입니다.

배열 array, [i, j, k]를 원소로 가진 2차원 배열 commands가 매개변수로 주어질 때, commands의 모든 원소에 대해 앞서 설명한 연산을 적용했을 때 나온 결과를 배열에 담아 return 하도록 solution 함수를 작성해주세요.

**제한사항**
>* array의 길이는 1 이상 100 이하입니다.
>* array의 각 원소는 1 이상 100 이하입니다.
>* commands의 길이는 1 이상 50 이하입니다.
>*  commands의 각 원소는 길이가 3입니다.


## 어떻게 접근할 것인가?

>* 미리 sorting을 다 안해줘도
>* 매번 min을 찾고 그 다음 min을 찾는 것을 반복하면 다 안보고 찾을 수 있지 않을까?
>* 구간동안의 min을 찾는 일을 반복하는데
>* 이전 iteration의 min을 bound로 설정해서 값 array[k]이 bound<array[k]<min 되도록 하면 되지 않을까


**이게 더 빠를줄 알았는데 왜 n^3이지..** 

### 내 생각 코드(복잡도 : O(n^3), 점수: 56.7)

    #include <string>
    #include <vector>
    #include <iostream>
    using namespace std;

    vector<int> solution(vector<int> array, vector<vector<int>> commands) {
        vector<int> answer;
        for(int i = 0; i< commands.size(); i++){
            int min= 101;
            int bound = 0;
            for(int j = 0; j < commands[i][2]; j++){
                min = 101;
                for(int k = commands[i][0]-1; k <= commands[i][1]-1; k++){
                    if(array[k]<min && array[k]>bound)min = array[k];
                }
                bound = min;
            }
            answer.push_back(min);
        }
        return answer;
    }

### Sorting을 미리한 코드(복잡도: n^2logn, 점수: 100)

    #include <string>
    #include <vector>
    #include <iostream>
    #include <algorithm>
    using namespace std;

    vector<int> solution(vector<int> array, vector<vector<int>> commands) {
        vector<int> answer;
        for(int i = 0; i < commands.size(); i++){
            vector<int> copy = array;
            int start = commands[i][0]-1;
            int end = commands[i][1];
            int k = commands[i][2];

            sort(copy.begin()+start, copy.begin()+end);
            answer.push_back(copy[start+k-1]);
        }
        return answer;
    }

## 결론

>* 일단 전형적인 방법으로 접근해서 복잡도를 계산해본다.
>* 그리고 내 생각의 복잡도를 생각해봐야 한다.
>* 무턱대고 코딩하지 말자! 
