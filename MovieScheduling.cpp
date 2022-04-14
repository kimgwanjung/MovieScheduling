#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <algorithm>

using namespace std;
int k; // 스케줄 입력 개수
int d[50000];
struct schedule {
	int start, finish, pay; //영화 시작일, 끝나는날, 단가(출연료) 구조체
};
schedule s[50000];

int sort1(schedule a1, schedule a2) {
	if (a1.start < a2.start) return 1; //영화 시작일을 기준으로 정렬
	else if (a1.start == a2.start) return a1.finish < a2.finish; //같을 경우엔 끝나는 것이 빠른 것을 기준으로 정렬
	else return 0;
}

int find1(int t) { //t번째 영화부터 촬영 가능할 때 가장 높은 단가를 찾는다.
	if (d[t] != -1) return d[t]; //이미 구한 값이라면 그대로 반환한다.
	if (t == k) return 0; //영화가 마지막날이 넘어가면 0을 반환한다.
	d[t] = 0; //0으로 다시 초기화한다.
	int i;
	for (i = t; i < k; i++) { //영화가 끝나는 시점부터 바로 찍을 수 있는 영화를 찾는다.
		int lf = i + 1;
		int mid;
		int rt = k - 1;
		int final = s[i].finish; //s[next].a의 값이 final보다 큰 next를 찾는다. 이것은 이분탐색을 이용한다. 
		int next = k;
		while (lf <= rt) { //이분탐색
			mid = (lf + rt) / 2;
			if (s[mid].start > final) {
				rt = mid - 1;
				next = mid;
			}
			else lf = mid + 1;
		}
		d[t] = max(d[t], find1(next) + s[i].pay);
	}
	return d[t];
}

int main() {
	memset(d, -1, sizeof(d)); //for문 대신 memset으로 -1로 초기화
	scanf_s("%d", &k); //스케줄 개수 입력
	int i;
	for (i = 0; i < k; i++) { //시작일, 끝나는날, 출연료 입력
		scanf_s("%d %d %d", &s[i].start, &s[i].finish, &s[i].pay);
	}
	sort(s, s + k, sort1); //sort1을 기준으로 정렬한다.
	printf("%d", find1(0)); 
}