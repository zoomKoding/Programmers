## 문제

전화번호부에 적힌 전화번호 중, 한 번호가 다른 번호의 접두어인 경우가 있는지 확인하려 합니다.

전화번호가 다음과 같을 경우, 구조대 전화번호는 영석이의 전화번호의 접두사입니다.

>* 구조대 : 119
>* 박준영 : 97 674 223
>* 지영석 : 11 9552 4421

전화번호부에 적힌 전화번호를 담은 배열 phone_book 이 solution 함수의 매개변수로 주어질 때, 어떤 번호가 다른 번호의 접두어인 경우가 있으면 false를 그렇지 않으면 true를 return 하도록 solution 함수를 작성해주세요.



## 검색을 위해서 뭐를 써야하는가?(sorting?)

>* 처음에는 사이즈로 작은 순으로 정렬을 하고 사이즈로 진행하려고 했다.
>* size로 정렬하고 size가 작은 친구(i)부터 다른 친구(j)와 비교하려고 했다.
>* 문자를 일일이 비교하려고 하니 for문이 하나 더 필요했다.
>* 결과적으로 복잡도는 for문 3개로 n의 3승이 됐다...
>* 당연히 정답은 모르겠는데 효율성 바닥으로 80점 맞았다.

### sort 활용 코드(복잡도 : O(n^3))

    #include <string>
    #include <vector>
    #include <map>
    #include <algorithm>
    #include <iostream>

    using namespace std;

    bool compare(string a, string b){
        return a.size()< b.size();
    }

    bool solution(vector<string> phone_book) {
        for(int i = 0; i < phone_book.size(); i++){
            cout<< i << ":"<< phone_book[i]<< endl;
        }
        int book_size = phone_book.size();
        //sorting을 해서 넣어볼까?
        for(int i = 0; i < phone_book.size(); i++){
            //길이가 짧은 애들을 앞으로
            sort(phone_book.begin(), phone_book.end(), compare);
        }
        // printf("%d\n", phone_book.size());
        for(int i = 0; i< book_size; i++){
            for(int j = i + 1; j < book_size; j++){
                int k;
                for(k = 0; k < phone_book[i].length(); k++){
                    // printf("i = %d, j = %d, k = %d\n", i, j, k);
                    // cout<<phone_book[i]<<endl;
                    // cout<<phone_book[j]<<endl;
                    if(phone_book[i].at(k) != phone_book[j].at(k)){
                        // cout << "pass"<< endl;
                        break;
                    }
                }
                // cout<<phone_book[i].length()<<endl;
                // cout<<k<<endl;
                if(k == phone_book[i].length()) {
                    // cout << "return false" << endl;
                    return false;
                }
            }
        }
        return true;
    }

## Search에는 역시 해쉬?

>* 이번에는 해쉬를 이용했다.
>* 해쉬의 key말고 value에 넣는게 의미가 없으니까 사실 해쉬를 쓰는게 맞나 라는 의문이 들었는데 일단 보자
>* 처음에는 넣은 뒤에 vector을 sorting도 하면 빠르지 않을까 했는데 sorting 시간 때문에 fail!
>* 다 빼고 해쉬에 넣고 해쉬에 있는지만 확인하는 식으로 가보자
>* 확인할때 글자 개수를 이용해서 i길이 만큼의 substring을 생성
>* 생성한 substring를 해쉬맵에 find해서 있으면 return false!

### hashmap 활용 코드(복잡도 : O(n^2))

    #include <string>
    #include <vector>
    #include <map>
    #include <algorithm>
    #include <iostream>

    using namespace std;

    bool solution(vector<string> phone_book) {
        int book_size = phone_book.size();
        //max, min은 검색하는 for문을 위해서 만듬
        map<string, int> m;
        int max = 0;
        int min = phone_book[0].length();

        //해쉬맵에 넣어
        for(int i = 0; i < phone_book.size(); i++){
            int len = phone_book[i].length();
            if(len > max) max = len;
            if(len < min) min = len;
            m.insert(make_pair(phone_book[i], 1) );
        }

        //글자수 만큼을 찾아
        for(int i = min; i <= max; i++){
            for(int j = 0; j < phone_book.size(); j++){
                //string의 길이가 글자수보다 짧으면 패스
                if(phone_book[j].length()<i) continue;
                string x = phone_book[j].substr(0, i);
                //substr이 string이랑 같으면 패스
                if(x.compare(phone_book[j]) == 0) continue;
                //해쉬맵에 존재하면 return false
                if(m.find(x)->second == 1){
                    return false;
                }
            }
        }
        return true;
    }

## 느낀점

>1. 해쉬맵의 value가 없더라도 효율을 위해서 쓸수있다.
>2. sorting을 하는 게 오히려 시간을 늘릴수도 있다.
>3. 나는 아직 많이 엄청 많이 부족하다
