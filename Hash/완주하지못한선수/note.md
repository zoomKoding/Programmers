## 문제

수많은 마라톤 선수들이 마라톤에 참여하였습니다. 단 한 명의 선수를 제외하고는 모든 선수가 마라톤을 완주하였습니다.

마라톤에 참여한 선수들의 이름이 담긴 배열 participant와 완주한 선수들의 이름이 담긴 배열 completion이 주어질 때, 완주하지 못한 선수의 이름을 return 하도록 solution 함수를 작성해주세요.

**제한사항**
>* 마라톤 경기에 참여한 선수의 수는 1명 이상 100,000명 이하입니다.
>* completion의 길이는 participant의 길이보다 1 작습니다.
>* 참가자의 이름은 1개 이상 20개 이하의 알파벳 소문자로 이루어져 있습니다.
>* 참가자 중에는 동명이인이 있을 수 있습니다.


## 어떻게 접근할 것인가?

>* completion을 다 hashmap에 넣는다.(이름을 key로 한다.)
>* 동명이인의 가능성이 있으므로 value를 같은 이름의 수로 한다.
>* participant를 hashmap에서 find하는데 find 결과값이 1보다 작은 경우를 return한다.



### sort 활용 코드(복잡도 : O(n))

**<C++>**

    #include <string>
    #include <vector>
    #include <map>
    #include <iostream>
    using namespace std;


    string solution(vector<string> participant, vector<string> completion) {
        map<string, int> m;
        //completion을 넣어
        for(int i = 0; i < completion.size(); i++){
            int x = m.find(completion[i])->second; 
            if(x == m.end()->second) m.insert(make_pair(completion[i], 1) );
            else m[completion[i]]=x+1;
        }

        //participant를 검색해
        for(int i = 0; i < participant.size(); i++){
            int x = m.find(participant[i])->second; 
            if(x == 0 || x == m.end()->second) return participant[i];
            else m[participant[i]]=--x;
        }
    }
    
**<JAVA>**

import java.util.*;

    class Solution {
        public String solution(String[] participant, String[] completion) {
            String answer = "";
            Map<String, Integer> hm = new HashMap<>();   
            for(int i = 0; i< completion.length; i++){
                if(hm.get(completion[i]) == null){
                    hm.put(completion[i], 1);
                }
                else{
                    int num = hm.get(completion[i]) + 1;
                    hm.put(completion[i], num);
                }
            }

            for(int i = 0; i< participant.length; i++){
                if(hm.get(participant[i]) == null) return participant[i]; 
                int num = hm.get(participant[i]);
                if(num > 0){
                    hm.put(participant[i], --num);
                }
                else{
                    return participant[i];
                }
            }
            return answer;
        }
    }

## hashmap

 >* hashmap으로 따로 인덱싱이 되있는 상태로 넣어놓으니 확실히 search에 효율적이다.
 >* key 값에 해당하는 값이 있는지 확인하는 용도로 써도 되서 사실상 value값이 깊은 의미를 가지지 않을 때도 있다.
 
 ## 첫 문제를 풀며
 
 - 참 나는 코딩을 못한다는 생각이 든다.
 - 앞으로 많은 문제가 남았는데 프로그래머스가 이야기하는 것처럼 코딩에 능통해지고 싶다. 
