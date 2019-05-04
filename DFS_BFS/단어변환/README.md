## 문제

두 개의 단어 begin, target과 단어의 집합 words가 있습니다. 아래와 같은 규칙을 이용하여 begin에서 target으로 변환하는 가장 짧은 변환 과정을 찾으려고 합니다.

예를 들어 begin이 hit, target가 cog, words가 [hot,dot,dog,lot,log,cog]라면 hit -> hot -> dot -> dog -> cog와 같이 4단계를 거쳐 변환할 수 있습니다.

두 개의 단어 begin, target과 단어의 집합 words가 매개변수로 주어질 때, 최소 몇 단계의 과정을 거쳐 begin을 target으로 변환할 수 있는지 return 하도록 solution 함수를 작성해주세요.


**제한사항**

>* 각 단어는 알파벳 소문자로만 이루어져 있습니다.
>* 각 단어의 길이는 3 이상 10 이하이며 모든 단어의 길이는 같습니다.
>* words에는 3개 이상 50개 이하의 단어가 있으며 중복되는 단어는 없습니다.
>* begin과 target은 같지 않습니다.
>* 변환할 수 없는 경우에는 0를 return 합니다.

## 어떻게 접근할 것인가?

>* 리컬션을 이용해서 DFS로 짜면 금방일듯하다.
>* 리컬션으로 미니멈 거리를 찾아서 return 해주면 될 것 같다.


### DFS 활용 코드(복잡도 : O(N+E))

#include <string>
#include <vector>

using namespace std;

string target;

int dfs(string begin, string target, int depth, vector<string> words){
if (begin.compare(target) == 0) return depth;
int times;
int value = 100000;
int min = 100000;
for(int i = 0; i < words.size(); i++){
int count = 0;
for(int j = 0; j < begin.length(); j++){
if(begin.at(j) == words[i].at(j)) count++;
}
if(count == begin.length() - 1) {
string send = words[i];
words[i] = "                        ";
value = dfs(send, target, depth+1, words);
}
if(value < min) min = value;
}
return min;    
}

int solution(string begin, string target, vector<string> words) {
int distance = dfs(begin, target, 0, words);
if(distance == 100000) return 0;
else return distance;
}


## 느낀점

>* 오랜만에 버그 때문에 진짜 화딱지가 났다..(segment fault)
>* segment fault는 참조 잘못됐을 때만 뜨는 줄 알았는데 실행시간이 길어질 때도 떴다??
>* 근데 일단은 내 알고리즘 자체는 나름 깔끔하게 잘짠거 같다(?)ㅋㅋ
>* 버그만 안떴으면 15분 컷도 가능했을것 같은데 다음에는 버그 없이 무난한 한판도 기대해본다.
