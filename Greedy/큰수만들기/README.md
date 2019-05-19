## 문제 
어떤 숫자에서 k개의 수를 제거했을 때 얻을 수 있는 가장 큰 숫자를 구하려 합니다.

예를 들어, 숫자 1924에서 수 두 개를 제거하면 [19, 12, 14, 92, 94, 24] 를 만들 수 있습니다. 이 중 가장 큰 숫자는 94 입니다.

문자열 형식으로 숫자 number와 제거할 수의 개수 k가 solution 함수의 매개변수로 주어집니다. number에서 k 개의 수를 제거했을 때 만들 수 있는 수 중 가장 큰 숫자를 문자열 형태로 return 하도록 solution 함수를 완성하세요.

**제한 조건**
>* number는 1자리 이상, 1,000,000자리 이하인 숫자입니다.
>* k는 1 이상 number의 자릿수 미만인 자연수입니다.

**입출력 예**

| number | k | return |
|:--------|:--------|:--------|
| 1924 | 2 | 94 |
| 1231234 | 3 | 3234 |
| 4177252841 | 4 | 775841 |

## 문제 이해
>* 일단 숫자 중에 k개 만큼의 수를 빼야한다. 뭐를 뺄지 신중히 선택해야 한다.
>* 뭔가 가장 큰 숫자 이전에 있는 친구들을 다 빼줘야 하지 않을까?
>* 가장 큰 숫자 하나를 선택하고 나머지 숫자들 중에 또 가장 큰 숫자를 찾고 이를 반복하면 될 것같다.

## 방법은
1. number 전체 중에서 제일 큰 친구를 선택한다.
2. 큰 친구 앞에 있는 갯수 만큼 k를 빼준다.
3. 큰 친구 뒤에 있는 substring으로 number을 대체한다.
4. k가 0이 될때까지 위의  반복한다.

## 코드(점수: 100점)
    #include <string>
    #include <vector>

    using namespace std;
    string answer = "";

    string solution(string number, int k) {
        while(1){
            if(k <= 0) {
                answer += number;
                break;
            }
            else if(number.length() <= k) break;
            char max = '0';
            int max_i = 0;
            for(int i = 0; i <= k; i++){
                if(number[i] > max){
                    max = number[i];
                    max_i = i;
                    if(max == '9') break;
                }
            }
            answer += number[max_i];
            number = number.substr(max_i + 1, number.length());
            k = k - max_i;
        }
        return answer;
    }
    
## 느낀점
>* 이 문제도 하나가 계속 시간 초과가 떠서 애좀 먹었었다.
>* 처음에 recursion을 이용해서 짰는데 이를 while문으로 바꿔주는 것만으로 시간 초과가 풀렸다. 
>* 일단 풀어서 너무 다행이다. 이제 Greedy 한문제 남았는데 화이팅이다!!

