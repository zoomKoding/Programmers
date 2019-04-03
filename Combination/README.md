
## Problem

코딩을 이용해서 조합을 계산해보자

### Formula(공식 제공)

* C(n, k) = C(n-1, k-1) + C(n-1, k) valid for 1 ≤ k ≤ n-1,  and
* C(n, n) = C(n, 0) = 1 valid for n ≥ 0.

## Pseudo-code using Recursive 

    CALCULATE_COMBINATIONS(n, k)

    if n is great or equal to 0 then
        if k is equal to n or 0 then 
            return 1
    if k is greater than 0 and k is less than n then
        return CALCULATE_COMBINATIONS(n-1, k-1) + CALCULATE_COMBINATIONS(n-1, k)

## Pseudo-code using Dynamic Programming

    CALCULATE_COMBINATIONS(n, k)

    for i <- 1 to k
        m[i,i] <- 1
    for i <- 0 to n
        m[i, 0] <- 1
    for i <- 2 to n
        for j <- 1 to k
            m[i,j] <- m[i-1, j-1] + m[i-1, j]

## Dynamic Programming Code의 Time Complexity

 - 반복문 두개로 끝나고 n번을 k번 돌기 때문에 nk + k + n 이다.
 - 이 때 k의 최대가 n이기 때문에 세타(n^2)라고 봐도 무방하다.
 
 ## 효율성 비교 코드(C언어)
 
     #include <stdio.h>
     #include <stdlib.h>
     #include <time.h>
     
     long long recursive(int n, int k){
         if(n >= 0){
            if(k == n || k == 0) return 1;
         }
         if(k > 0 && k < n) return recursive(n-1, k-1) + recursive(n-1, k);
         return 0;
     } 
     
     long long dynamic(int n, int k){
         long long **arr = (long long **)malloc((n+1) * sizeof(long long *)); 
         for (int i=0; i<n+1; i++) arr[i] = (long long *)malloc((k+1) * sizeof(long long)); 
         
         for(int i = 1; i < k+1; i++) arr[i][i] = 1;
         for(int i = 1; i < n+1; i++) arr[i][0] = 1;
         
         for(int i = 2; i < n+1; i++){
            for(int j = 1; j < k+1; j++) arr[i][j] = arr[i-1][j-1] + arr[i-1][j];
         }
         return arr[n][k];
     }
     
     int main(void) {
         int n, k;
         long long recur_result, dynam_result;
         double recur_time, dynam_time;
         clock_t start, end;
         
         printf("put n, k value : ");
         scanf("%d %d", &n, &k);
         
         start = clock(); 
         recur_result = recursive(n, k);
         end = clock();
         recur_time = (double)(end - start);
         
         start = clock(); 
         dynam_result = dynamic(n, k);
         end = clock();
         dynam_time = (double)(end - start);
         
         printf("recursive result : %lli, time : %.0fms\n", recur_result, recur_time);
         printf("dynamic result   : %lli, time : %.0fms\n", dynam_result, dynam_time);
     }
 
 
 ## 효율성 비교 결과
 
     put n, k value : 20 10
     recursive result : 184756, time : 2674ms
     dynamic result   : 184756, time : 13ms
     
- 압도적으로 dynamic programming 사용한 경우가 빠르다.
