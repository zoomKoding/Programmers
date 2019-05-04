## 문제

스트리밍 사이트에서 장르 별로 가장 많이 재생된 노래를 두 개씩 모아 베스트 앨범을 출시하려 합니다. 노래는 고유 번호로 구분하며, 노래를 수록하는 기준은 다음과 같습니다.

1. 속한 노래가 많이 재생된 장르를 먼저 수록합니다.
2. 장르 내에서 많이 재생된 노래를 먼저 수록합니다.
3. 장르 내에서 재생 횟수가 같은 노래 중에서는 고유 번호가 낮은 노래를 먼저 수록합니다.

노래의 장르를 나타내는 문자열 배열 genres와 노래별 재생 횟수를 나타내는 정수 배열 plays가 주어질 때, 베스트 앨범에 들어갈 노래의 고유 번호를 순서대로 return 하도록 solution 함수를 완성하세요.

**제한사항**

>* genres[i]는 고유번호가 i인 노래의 장르입니다.
>* plays[i]는 고유번호가 i인 노래가 재생된 횟수입니다.
>* genres와 plays의 길이는 같으며, 이는 1 이상 10,000 이하입니다.
>* 장르 종류는 100개 미만입니다.
>* 장르에 속한 곡이 하나라면, 하나의 곡만 선택합니다.
>* 모든 장르는 재생된 횟수가 다릅니다.

## 문제 이해

>* 일단 장르 별로 순위를 매길 수 있는 방법을 찾아야 할 것 같다.
>* 그리고 장르 내에서의 많이 재생한 1등, 2등을 찾을 수 있으면 좋을 것 같다.
>* 장르 별로 순위를 매기려면 장르 이름이 같은 친구들의 재생 횟수를 다 더하고 sort해야 한다.
>* 장르 내의 1위와 2위를 담을 수 있는 그릇이 있어야 한다.

## 방법은?

>* 같은 장르 이름의 친구들의 플레이 횟수를 더하기 위해서 해쉬맵을 하나 만들었다(m).
>* 해쉬맵으로 각 이름의 1등인 친구의 index를 저장할 m_1, 2등의 index를 저장할 m_2를 만들었다.(장르와 인덱스를 담아야하므로 벡터는 조금 힘들 것 같았다.)
>* 처음에 정보를 m에 넣어주고, m_1과 m_2를 위해 비교를 진행해서 해당하는 위치에 정보를 넣어준다.
>* 장르 종류를 담는 vector(kind)를 만들어서 장르의 재생 횟수를 바탕으로 sorting한다.
>* kind를 전체 훑으면서 m_1과 m_2에 있는 친구들을 answer에 push_back한다.


### Hashmap & sorting 활용 코드(복잡도 : O(n^2))

    #include <string>
    #include <vector>
    #include <map>
    #include <algorithm>

    using namespace std;

    map<string, int> m;
    map<string, int> m_count;
    map<string, int> m_1;
    map<string, int> m_2;
    vector<string> kinds;

    bool compare(string a, string b){
        return m[a] > m[b];
    }

    vector<int> solution(vector<string> genres, vector<int> plays) {
        vector<int> answer;
        for(int i = 0; i < genres.size(); i++){
            int x = m.find(genres[i])->second;
            if(x == m.end()->second) {
                kinds.push_back(genres[i]);
                m[genres[i]] =  plays[i];
                m_count[genres[i]] = 1;
            }
            else {
                m[genres[i]] = x + plays[i];
                m_count[genres[i]] ++;
            }

            int num1 = m_1.find(genres[i])->second;
            int num2 = m_2.find(genres[i])->second;
            if(num1 == m_1.end()->second) m_1[genres[i]] = i;
            else {
                if(plays[num1] < plays[i]){
                    m_1[genres[i]] = i;
                    m_2[genres[i]] = num1;
                }
                else{
                    if(num2 == m_2.end()->second) m_2[genres[i]] = i;
                    else if(plays[num2] < plays[i]) m_2[genres[i]] = i;  
                }
            }
        }
        sort(kinds.begin(), kinds.end(), compare);
        for(int i = 0; i < kinds.size(); i++){
            answer.push_back(m_1[kinds[i]]);
            if(m_count[kinds[i]] > 1) answer.push_back(m_2[kinds[i]]);
        }
        return answer;
    }

## 느낀점

>* 해쉬를 풀면서 초반에는 Level 3를 내가 감히 어떻게 건드려 했는데 이제는 무서움도 안느끼면서 쑥쑥 풀어냈다ㅎㅎ 뿌듯하다.
>* 해쉬를 배운 것은 이번 코딩 공부의 큰 수확이었다.
>* 해쉬의 장점과 쓸 수 있는 상황에 대해서 어느정도 감을 잡은 것 같은데 내가 정말 효율적으로 해쉬 쓸 수 있는 상황들을 생각해낼 수 있으면 좋겠다.
>* 그동안 Hash 푸느라 고생했어ㅎㅎ 일단 해쉬 마무리이다:)
