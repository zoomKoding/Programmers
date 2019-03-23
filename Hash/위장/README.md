## 문제

스파이들은 매일 다른 옷을 조합하여 입어 자신을 위장합니다.

예를 들어 스파이가 가진 옷이 아래와 같고 오늘 스파이가 동그란 안경, 긴 코트, 파란색 티셔츠를 입었다면 다음날은 청바지를 추가로 입거나 동그란 안경 대신 검정 선글라스를 착용하거나 해야 합니다.

스파이가 가진 의상들이 담긴 2차원 배열 clothes가 주어질 때 서로 다른 옷의 조합의 수를 return 하도록 solution 함수를 작성해주세요.

**제한사항**
>* clothes의 각 행은 [의상의 이름, 의상의 종류]로 이루어져 있습니다.
>* 스파이가 가진 의상의 수는 1개 이상 30개 이하입니다.
>* 같은 이름을 가진 의상은 존재하지 않습니다.
>* clothes의 모든 원소는 문자열로 이루어져 있습니다.
>* 모든 문자열의 길이는 1 이상 20 이하인 자연수이고 알파벳 소문자 또는 '_' 로만 이루어져 있습니다.
>* 스파이는 하루에 최소 한 개의 의상은 입습니다.


## 어떻게 접근할 것인가?

>* 모든 경우의 수를 세야하는데 어떻게 해야할까
>* 일단 맵을 이용해서 각 의상의 갯수를 세자
>* 센 후에 모든 경우의 수를 구해야 하는데 잘 모르겠다.. 일단은 다 세....
>* 30점 맞았다...



### 일일이 다 셌던 코드(복잡도 : O(n^3))

    #include <string>
    #include <vector>
    #include <iostream>
    #include <map>

    using namespace std;

    int solution(vector<vector<string>> clothes) {
        //맵을 만들어
        int sum = 0;
        map<string, int> m;
        vector<int> num;
        map<int, int> count;

        for(int i = 0; i < clothes.size(); i++){
            int value = m.find(clothes[i][1])->second;
            if(value == m.end()->second) m.insert(make_pair(clothes[i][1], 1));
            else m[clothes[i][1]] = value + 1;
        }
        for(auto i = m.begin(); i !=  m.end(); i++)num.push_back(i->second);
        for(int i = 0; i < num.size(); i++){
            count.insert(make_pair(num[i], i));
            sum += num[i];
        }



        for(int i = 0; i < num.size(); i++){
            map<int, int> temp;

            for(auto j = count.begin(); j !=  count.end(); j++){
                for(int k = j->second + 1; k < num.size(); k++){
                    int value = j->first*num[k];
                    temp.insert(make_pair(value, k));
                    sum += value;
                }
            }
            count.clear();
            for(auto j = temp.begin(); j !=  temp.end(); j++){
                count.insert(make_pair(j->first, j->second));
            }
        }

        return sum;
    }



## 수열을 활용하면.. (feat. 방돌이 윤호형)

>* 하도 안풀려서 갓윤호형한테 물어봤다
>* 윤호형 말이 옷을 입지 않는 경우도 추가해주면 경우의 수를 일일이 다 셀 필요 없지 않겠냐
>* ...
>* 맞다... 그래서 각 옷에 갯수를 하나 추가해줘서 그 종류를 입지 않는 경우도 포함시켰다
>* 그리고 다 입지 않은 경우는 하나이므로 마지막에 빼주면 끝이다

### 수열 활용 코드(복잡도: O(n))

    
    #include <string>
    #include <vector>
    #include <iostream>
    #include <map>
    
    using namespace std;
    
    int solution(vector<vector<string>> clothes) {
        //맵을 만들어
        int sum = 1;
        map<string, int> m;
        
        for(int i = 0; i < clothes.size(); i++){
            int value = m.find(clothes[i][1])->second;
            if(value == m.end()->second) m.insert(make_pair(clothes[i][1], 1));
            else m[clothes[i][1]] = value + 1;
        }
        for(auto i = m.begin(); i !=  m.end(); i++){
            sum *= (i->second +1);
        }
        
        return sum-1;
    }


## 느낀점

>* 수학적 사고력이 이래서 중요한가보다.
>* 창의력은 머리에 들어있는게 있어야 나온다.
>* 수학을 공부하자...
>* 윤호형은 존똑이다..
