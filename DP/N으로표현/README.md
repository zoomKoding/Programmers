## 문제

아래와 같이 5와 사칙연산만으로 12를 표현할 수 있습니다.

12 = 5 + 5 + (5 / 5) + (5 / 5)
12 = 55 / 5 + 5 / 5
12 = (55 + 5) / 5

5를 사용한 횟수는 각각 6,5,4 입니다. 그리고 이중 가장 작은 경우는 4입니다.
이처럼 숫자 N과 number가 주어질 때, N과 사칙연산만 사용해서 표현 할 수 있는 방법 중 N 사용횟수의 최솟값을 return 하도록 solution 함수를 작성하세요.

**제한사항**
N은 1 이상 9 이하입니다.
number는 1 이상 32,000 이하입니다.
수식에는 괄호와 사칙연산만 가능하며 나누기 연산에서 나머지는 무시합니다.
최솟값이 8보다 크면 -1을 return 합니다.

## 어떻게 접근할 것인가?

>* Dynamic Programming을 배웠으므로 한번 적용해보자.
>* 먼저 N을 두개 썼을 때부터 8개 썼을 때까지 확인을 해보면 될 것 같다.
>* 그래서 연산하려는 값의 N의 갯수와 현재 iteration의 N의 갯수의 차이(diff)에 해당하는 원소를 operand로 하자.
>* 덧셈, 뺄셈, 나눗셈, 곱셈을 진행하면서 결과가 number와 같으면 i return.
>* 없다면 Hash에 넣어주자.

## 테스트 케이스로 고려해보면 좋을 것들

>* N : 5, number :  23, Return 5 // 5*5-(5+5)/5
>* N : 5, number :  83, Return 8 // (55+5) + 5*5 - (5+5)/5
>* N : 5, number :  87, Return 7 // (555+5)/5 - 5*5
>* N : 5, number :  127, Return 6 // 5*5*5 + (5+5)/5

**이 테스트 케이스 없었으면 생각을 못했을 경우가 있었다ㅠㅅㅠ**



### DP와 map 활용 코드(복잡도 : n^3)

    #include <string>
    #include <vector>
    #include <map>

    using namespace std;

    map< long long, int > m;
    vector<long long> v;
    int Ns[7];

    bool correct_check(long long result, int number, int i){
        if(result == number) return true;
        if(m[result] == 0){
            v.push_back(result);
            m[result] = i;
        }
        return false;
    }

    int solution(int N, int number) {
        m[N] = 1;
        v.push_back(N);
        Ns[0] = N;
        for(int i = 1; i < 7; i++)Ns[i] = N+Ns[i-1]*10;
        for(int i = 2; i < 9; i ++){
            int leng =  v.size();
            for(int j = 0; j < leng; j++){
                long long num_out = v[j];
                int diff = i-m[num_out];
                for(auto iter=m.begin();iter!=m.end();iter++){
                    if(iter->second != diff || iter->first == 0) continue;
                    long long operand = iter->first;
                    if(correct_check(num_out + operand, number, i)) return i;
                    if(correct_check(num_out - operand, number, i)) return i;
                    if(correct_check(num_out / operand, number, i)) return i;
                    if(correct_check(num_out * operand, number, i)) return i;
                    if(Ns[m[num_out]-1] == num_out){
                        if(correct_check(Ns[i-1], number, i)) return i;
                    }
                }       
            }
        } 
        return -1;
    }

## 느낀점

>* 일단 처음에 접근 방식이 잘못됐음을 깨달는데 너무 오랜 시간이 걸렸다.
>* 다양한 경우의 수를 생각하는 직관이 굉장히 중요할 것 같다.
>* 풀고 다른 사람의 풀이를 보니까 DFS를 이용해서 풀어서 문제 풀이 시간이 짧았던 경우를 봤는데
>* DFS도 배워봐야겠다.


