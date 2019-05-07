## 문제

초 단위로 기록된 주식가격이 담긴 배열 prices가 매개변수로 주어질 때, 가격이 떨어지지 않은 기간은 몇 초인지를 return 하도록 solution 함수를 완성하세요.

**제한사항**
>* prices의 각 가격은 1 이상 10,000 이하인 자연수입니다.
>* prices의 길이는 2 이상 100,000 이하입니다.

## 어떻게 접근할 것인가?

>* 가격이 떨어지는 시점까지 계속 count해라
>* 가격이 안떨어지면 그냥 끝까지 다 더해라

## 방법은?

>* 그냥 for문 두개?

### 코드(복잡도: O(N^2))

    #include <string>
    #include <vector>

    using namespace std;

    vector<int> solution(vector<int> heights) {
        vector<int> answer;
        for(int i = 0; i < heights.size(); i++){
            int count = 0;
            for(int j = i ; j > -1; j--){
                if(heights[i] < heights[j]) {
                    count = j+1;
                    break;
                }
            }
            answer.push_back(count);  
        }
        return answer;
    }



## 결론

>* 음 오늘 stack/queue가 이렇게 끝나게 될줄은 몰랐다 ㅎㅎ
>* 일단 stack/queue 문제를 stack이랑 queue를 쓰지 않고 풀었는데 몰라서 그렇게 한 것이 아니라는 나름의 자신감이 있다..ㅎㅎ
>* 나머지 문제도 뚝딱뚝딱 재밌게 해보자:)
