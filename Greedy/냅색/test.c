#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct item{
  int benefit;
  int weight;
  float value;
}Item;

void swap(Item* a, Item* b);
void quick_sort(Item* array, int start, int end);
float greedy(Item* array, int n, int w);
int dp(Item* array, int n, int w);
int bandb(Item* array, int n, int w);

void swap(Item* a, Item* b){
    Item tmp= *a;
    *a=*b;
    *b=tmp;
}

void quick_sort(Item* array, int start, int end){
  if(start>=end) return;

  int mid=(start+end)/2;
  float pivot=array[mid].value;

  swap(&array[start],&array[mid]);

  int p=start+1,q=end;

  while(1){
      while(array[p].value>=pivot){ p++; }
      while(array[q].value<pivot){ q--; }

      if(p>q) break;

      swap(&array[p],&array[q]);
  }

  swap(&array[start],&array[q]);
  quick_sort(array,start,q-1);
  quick_sort(array,q+1,end);
}

float greedy(Item* array, int n, int w){
  float benefit = 0;
  int left = w;
  for(int i = 0; i < n; i++){
    //만약 원소가 넘겨버리면 쪼개서 넣어
    if(array[i].weight > left) {
      benefit += array[i].value * left;
      break;
    }
    //안넘기면 다 넣어
    else{
      left -= array[i].weight;
      benefit += array[i].benefit;
      if(left == 0) break;
    }
  }
  return benefit;
}

int dp(Item* array, int n, int W){
  int ** B;
  B = (int**) malloc ((n+1) * sizeof(int*));
  for(int i = 0; i < n+1; i++) B[i] = (int*) malloc ((W+1) * sizeof(int));
  
  for(int i = 0; i < W; i++)B[0][i] = 0;
  for(int i = 1; i < n + 1; i++){
    B[i][0] = 0;
    for(int w = 1; w < W+1; w++){
        int _w = array[i-1].weight;
        int _b = array[i-1].benefit;
        if(w == 20) printf("%d, %d, %d, %d\n", _w, B[i-1][w], B[i-1][w-_w], _b);
        if(_w <= w){
            if(_b+B[i-1][w-_w]>B[i-1][w]) {
                B[i][w] = _b+B[i-1][w-_w];
                printf("1\n");
            }
            else {
                B[i][w] = B[i-1][w];
                printf("2\n");

            }
        }
        else {
            B[i][w] = B[i-1][w];
            printf("3\n");

        }
    }
  }
  for(int i= 0; i < W+1; i++){
      printf("%d ", i);
      for(int j = 0; j < n+1; j++){
          printf("%d ", B[j][i]);
      }
      printf("\n");
  }

  return B[n][W];
}

typedef struct NodeStruct
{
    int weight;
    int benefit;
    int index;
    float bound;
}Node;

#define MAX_SIZE 10000
 
Node heap[MAX_SIZE];
int size;

void heap_init() {
    size = 0;
}

void heap_swap(Node *a, Node *b) {
    Node tmp = *a;
    *a = *b;
    *b = tmp;
}

int push(Node value) {
    if (size + 1 > MAX_SIZE) return 0;
    heap[size] = value;
    int current = size;
    int parent = (size - 1) / 2;
    while (current > 0 && heap[current].bound > heap[parent].bound) {
        heap_swap(&heap[current], &heap[parent]);
        current = parent;
        parent = (parent - 1) / 2;
    }
    size++;
    return 1;
}

Node pop() {
    if (size <= 0) {
      Node temp;
      temp.benefit = -1;
      return temp;
    }

    Node ret = heap[0];
    size--;

    heap[0] = heap[size];
    int current = 0;
    int leftChild = current * 2 + 1;
    int rightChild = current * 2 + 2;
    int maxNode = current;

    while (leftChild < size) {
        if (heap[maxNode].bound < heap[leftChild].bound) maxNode = leftChild;
        if (rightChild < size && heap[maxNode].bound < heap[rightChild].bound) maxNode = rightChild;
        if (maxNode == current)break;
        else {
            heap_swap(&heap[current], &heap[maxNode]);
            current = maxNode;
            leftChild = current * 2 + 1;
            rightChild = current * 2 + 2;
        }
    }   
    return ret;
}

int bandb(Item* array, int n, int w){
  heap_init();
  int max_benefit = 0;
  int weight = 0;
  //queue 사이즈 할당해주기
  Node root;
  //root node 넣어줘
  root.weight = 0;
  root.benefit = 0;
  root.index = 0;
  for(int i = 0; i < n; i++){
    if(weight+array[i].weight > w){
      root.bound += (w-weight)*array[i].value;
      break;
    }
    else {
      root.bound += array[i].benefit;
      weight += array[i].weight;
    }
  }
  push(root);
  //q에서 꺼낸 원소가 -1이 아니라면 반복
  while(1){
    Node temp = pop();
    Node child[2];
    if(temp.benefit == -1) break;
    int index = temp.index + 1;
    printf("parent node : [%d, %d, %.0f, %d], current max : %d \n", temp.benefit, temp.weight, temp.bound, temp.index, max_benefit);
    if(temp.bound < max_benefit){
        printf("parent bound less than max_benefit\n", temp, weight, temp.index);
        continue;
    }
    if(temp.index == n){
        printf("parent out of range\n", temp.index);
        continue;
    }
    child[0].weight = temp.weight + array[index-1].weight;
    child[0].benefit = temp.benefit + array[index-1].benefit;
    child[1].weight = temp.weight;
    child[1].benefit = temp.benefit;

    //넣기로 하고 하나는 안넣기로해서 두번 작업해
    //꺼낸 원소의 weight과 w를 비교해서 넘으면 continue
    for(int i = 0; i < 2; i++){
      child[i].index = index;
      child[i].bound = child[i].benefit;
      if(w < child[i].weight)continue;
      
      //꺼낸 원소의 bound를 구하고 
      weight = child[i].weight;
      for(int j = index; j < n; j++){
        if(weight+array[j].weight > w){
          child[i].bound += (w-weight)*array[j].value;
          break;
        }
        else {
          child[i].bound += array[j].benefit;
          weight += array[j].weight;
        }
      }
        printf("child node[%d] : [%d, %d, %.0f, %d], current max : %d \n", i, child[i].benefit, child[i].weight, child[i].bound, child[i].index, max_benefit);

      //max_benefit보다 작으면 continue
      if(child[i].bound < max_benefit) continue;
      //benefit을 구하고 max_benefit 보다 크면 max_benefit 업데이트
      if(child[i].benefit > max_benefit)max_benefit = child[i].benefit;
      //push 해줘 
      push(child[i]);   
    }
  }
  //다돌았으면 결과 리턴해
  return max_benefit;
}

int main(void) {
  FILE *f;
  f = fopen("output.txt", "w"); // 출력을 저장할 파일을 만들어서 열기
  srand(time(NULL)); 
  clock_t start, end;
  float max_benefit;
  int W;
  int n[9] = {5, 100, 500, 1000, 3000, 5000, 7000, 9000, 10000};
  int sample_benefit[5] = {14, 6, 6, 6, 7};
  int sample_weight[5] = {2, 3, 3, 10, 12};
  int sample_value[5] = {7, 2, 2, 1, 1};
  
  Item items[10000];
  fprintf(f, "%-10s%-33s%-33s%-33s\n", "Time", "Greedy", "D.P.", "B. & B.");
  for(int i = 0; i < 1; i++){
    fprintf(f, "%-10d", n[i]);
    W = n[i]*4;
    for(int j = 0; j < n[i]; j++){
      items[j].benefit = rand() % 20 + 1;  
      items[j].weight = rand() % 20 + 1;
      items[j].value = (float)items[j].benefit / items[j].weight;
    }
    // for(int j = 0; j < n[i]; j++){
    //   items[j].benefit = sample_benefit[j];  
    //   items[j].weight = sample_weight[j];
    //   items[j].value = sample_value[j];
    // }
    quick_sort(items, 0, n[i]-1);
    if(i == 0){
      for(int p = 0; p < 10; p++){
        printf("item[%d] benefit = %d, weight = %d, value =%.0f\n", p, items[p].benefit, items[p].weight, items[p].value);
      }
    }
    for(int j = 0; j < 3; j++){
      start = clock(); 
      if(j==0)max_benefit = greedy(items, n[i], W);
      else if(j==1)max_benefit = dp(items, n[i], W);
      else max_benefit = bandb(items, n[i], W);
      end = clock();
      int time_solved = (int)end - start;
      if(time_solved>1000) time_solved = time_solved - time_solved%1000;
      fprintf(f, "%-15.0f / %-15d", max_benefit, time_solved);
      fflush(f);
    }
    fprintf(f, "\n");
  }  
  fclose(f);
}
