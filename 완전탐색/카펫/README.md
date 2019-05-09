## 문제

Leo는 카펫을 사러 갔다가 아래 그림과 같이 중앙에는 빨간색으로 칠해져 있고 모서리는 갈색으로 칠해져 있는 격자 모양 카펫을 봤습니다.

![사진](https://raw.githubusercontent.com/zoomKoding/zoomKoding.github.io/source/assets/_posts/brute-1.png)

Leo는 집으로 돌아와서 아까 본 카펫의 빨간색과 갈색으로 색칠된 격자의 개수는 기억했지만, 전체 카펫의 크기는 기억하지 못했습니다.

Leo가 본 카펫에서 갈색 격자의 수 brown, 빨간색 격자의 수 red가 매개변수로 주어질 때 카펫의 가로, 세로 크기를 순서대로 배열에 담아 return 하도록 solution 함수를 작성해주세요.

**제한사항**
>* 갈색 격자의 수 brown은 8 이상 5,000 이하인 자연수입니다.
>* 빨간색 격자의 수 red는 1 이상 2,000,000 이하인 자연수입니다.
>* 카펫의 가로 길이는 세로 길이와 같거나, 세로 길이보다 깁니다.

## 문제 이해

>* 안의 사각형과 바깥 사각형의 변은 각각 2씩 차이가 난다.
>* 안의 사각형의 양변을 구하면 바깥 사각형의 양변을 구할 수 있다.
>* 안의 사각형의 변은 각각 red의 약수이다
>* 약수 중에서 brown의 변도 잘 만들어주는 친구를 찾아랏

### 문뜩 코드(점수: 100점)

    #include <string>
    #include <vector>

    using namespace std;

    vector<int> solution(int brown, int red) {
        vector<int> answer;
        for(int i = 1; i < red + 1; i++){
            if(red % i == 0){
                int j = red / i;
                if((i + 2) * (j + 2) == brown + red){
                    answer.push_back(j + 2);
                    answer.push_back(i + 2);
                    break;
                }
            }
        }
        return answer;
    }
    
## 느낀점

>* 순식간..ㅎㅎ 재밌었다...ㅎㅎㅎㅎㅎ
>* 문뜩 떠오른 것이 정답이 될 때의 쾌감은 짜릿해..ㅎㅎ
