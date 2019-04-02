## 문제

H-Index는 과학자의 생산성과 영향력을 나타내는 지표입니다. 어느 과학자의 H-Index를 나타내는 값인 h를 구하려고 합니다. 위키백과1에 따르면, H-Index는 다음과 같이 구합니다.

어떤 과학자가 발표한 논문 n편 중, h번 이상 인용된 논문이 h편 이상이고 나머지 논문이 h번 이하 인용되었다면 h가 이 과학자의 H-Index입니다.

어떤 과학자가 발표한 논문의 인용 횟수를 담은 배열 citations가 매개변수로 주어질 때, 이 과학자의 H-Index를 return 하도록 solution 함수를 작성해주세요.

**제한사항**
>* 과학자가 발표한 논문의 수는 1편 이상 1,000편 이하입니다.
>* 논문별 인용 횟수는 0회 이상 10,000회 이하입니다.



## 어떻게 접근할 것인가?

>* citation 횟수가 큰 순서대로 정렬한 다음에
>* 하나씩 꺼내보면서
>* 실제 인덱스(i+1)가 citation 횟수(citation[i])보다 커지는 순간 
>* 그 바로 전 인덱스(i)를 H-Index라고 하자



**다 돌았는데도 없으면 그것은 H-index가 size랑 같다는 뜻...!** 

### 코드(복잡도 : O(nlogn), 점수: 100)

    #include <string>
    #include <vector>
    #include <algorithm>

    using namespace std;

    bool myfunction(int a , int b){
        return a > b;
    }

    int solution(vector<int> citations) {
        sort(citations.begin(), citations.end(), myfunction);
        for(int i = 0; i < citations.size(); i++){
            if(citations[i]< i+1) return i;
        }
        return citations.size();
    }

## 결론

>* 문제를 이해하고 한번 쭉 적어보면서 시나리오를 짜보자!

