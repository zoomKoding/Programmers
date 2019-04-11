## 문제

0 또는 양의 정수가 주어졌을 때, 정수를 이어 붙여 만들 수 있는 가장 큰 수를 알아내 주세요.

예를 들어, 주어진 정수가 [6, 10, 2]라면 [6102, 6210, 1062, 1026, 2610, 2106]를 만들 수 있고, 이중 가장 큰 수는 6210입니다.

0 또는 양의 정수가 담긴 배열 numbers가 매개변수로 주어질 때, 순서를 재배치하여 만들 수 있는 가장 큰 수를 문자열로 바꾸어 return 하도록 solution 함수를 작성해주세요.

**제한 사항**
>* numbers의 길이는 1 이상 100,000 이하입니다.
>* numbers의 원소는 0 이상 1,000 이하입니다.
>* 정답이 너무 클 수 있으니 문자열로 바꾸어 return 합니다.


## 어떻게 접근할 것인가?

>* sorting을 해야하는데 12, 123의 우선순위를 어떻게 지정해주지?
>* 번뜩이는 아이디어!! 
>* 길이를 비교해서 짧은 친구에는 0번째 값을 뒤에 추가해줘서 자리수를 맞추고 비교
>* 근데 이 코드는 35점을 맞았다.(코드가 사라짐...)
>* (121,12) 그리고 (212, 21)과 같은 수를 비교하는데 오류가 생겼다.

## 엥 잠깐만...
#### 아 근데 그냥 두 수를 가져가서 직접 앞뒤로 붙여보고 값을 비교해보면 되지 않나?
#### 121, 12 이면 12112과 12121을 비교하면 되지 않나?!!!

### 문뜩 코드(복잡도 : O(nlogn), 점수: 100)

    #include <string>
    #include <vector>
    #include <algorithm>

    using namespace std;

    bool myfunction(int a, int b){
        string str_a = to_string(a);
        string str_b = to_string(b);
        return stoi(str_a+str_b) > stoi(str_b+str_a);
    }

    string solution(vector<int> numbers) {
        string answer = "";
        sort(numbers.begin(), numbers.end(), myfunction);
        for(int i = 0; i < numbers.size(); i++)answer+=to_string(numbers[i]);
        if(answer.compare(0,1,"0")==0)return "0";
        return answer;
    }


## 결론

>* 단순히 원리를 생각하자.
>* 굳이 어렵게 접근하다가 천줄짠다.
>* 내 방법이 맞다고 확신하지 말자.
