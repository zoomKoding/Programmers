## 문제

한자리 숫자가 적힌 종이 조각이 흩어져있습니다. 흩어진 종이 조각을 붙여 소수를 몇 개 만들 수 있는지 알아내려 합니다.

각 종이 조각에 적힌 숫자가 적힌 문자열 numbers가 주어졌을 때, 종이 조각으로 만들 수 있는 소수가 몇 개인지 return 하도록 solution 함수를 완성해주세요.


**제한사항**
>* numbers는 길이 1 이상 7 이하인 문자열입니다.
>* numbers는 0~9까지 숫자만으로 이루어져 있습니다.
>* 013은 0, 1, 3 숫자가 적힌 종이 조각이 흩어져있다는 의미입니다.

## 어떻게 접근할 것인가?

>* 제일 고민됐던 부분은 일단 어떻게 모든 경우의 수를 만들 것인가이다.
>* 문자를 생성하는 것은 Recursion을 사용해야할 것 같은데 감이 잘 오지 않았다.
>* Recursion에 여태까지 사용했던 문자의 index도 같이 보내줘야 하나 했다.
>* 근데 그냥 index 따로 안보내주고 모든 숫자를 이용하기로 했다.
>* 그리고 나중에 소수 발견할 때 소수에 해당하는 친구를 다시 한번 확인해주는 식으로 하기로 했다.

### BF 활용 코드(복잡도 : O(...?))

    #include <string>
    #include <vector>
    #include <math.h>

    using namespace std;
    string numbers;
    vector<int> v;
    vector<int> answers;
    int num[10] = {0,};

    void num_find(int n, string s){
        if(n == numbers.length()) return;
        for(int i = 0; i < numbers.length(); i++){
            string temp = s + numbers.at(i);
            v.push_back(stoi(temp));
            num_find(n+1, temp);
        }
    }

    bool check(int n){
        string a  = to_string(n);
        int temp[10] = {0,};
        for(int i = 0; i < a.length(); i++){
            temp[a.at(i)-'0'] ++;
        }
        for(int i = 0; i < 10; i++){
            if(temp[i] > num[i]) return false;
        }

        return true;
    }

    int solution(string _numbers) {
        numbers = _numbers;
        int answer = 0;
        for(int i = 0; i < numbers.length(); i++)num[numbers.at(i)-'0'] ++;
        num_find(0, "");
        for(int i = 0; i < v.size(); i++){
            if(v[i] < 2) continue;
            for(int j = 0; j < answers.size(); j++){
                if(answers[j] == v[i]) {
                    v[i] = -1;
                    break;
                }
            }
            if(v[i] == -1) continue;
            for(int j = 2; j < v[i]; j++){
                if(v[i]%j == 0) {
                    v[i] = -1;
                    break;
                }
            }
            if(v[i] != -1){
                if(check(v[i])) {
                    answer ++;
                    answers.push_back(v[i]);
                }
            }
        }
        return answer;
    }

    
## 느낀점

>* 음.. 일단 엄청 시간 걸리고 더러워보이지만 이것도 방법이 될 수 있다는 생각을 항상 해야겠다..
>* 이게 답이라면 좀 많이 허무할 것 같긴 하다..ㅎㅎ
>* 암튼 일단 풀었으니까 기분 좋다!ㅎㅎ

