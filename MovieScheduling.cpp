#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <algorithm>

using namespace std;
int k; // ������ �Է� ����
int d[50000];
struct schedule {
	int start, finish, pay; //��ȭ ������, �����³�, �ܰ�(�⿬��) ����ü
};
schedule s[50000];

int sort1(schedule a1, schedule a2) {
	if (a1.start < a2.start) return 1; //��ȭ �������� �������� ����
	else if (a1.start == a2.start) return a1.finish < a2.finish; //���� ��쿣 ������ ���� ���� ���� �������� ����
	else return 0;
}

int find1(int t) { //t��° ��ȭ���� �Կ� ������ �� ���� ���� �ܰ��� ã�´�.
	if (d[t] != -1) return d[t]; //�̹� ���� ���̶�� �״�� ��ȯ�Ѵ�.
	if (t == k) return 0; //��ȭ�� ���������� �Ѿ�� 0�� ��ȯ�Ѵ�.
	d[t] = 0; //0���� �ٽ� �ʱ�ȭ�Ѵ�.
	int i;
	for (i = t; i < k; i++) { //��ȭ�� ������ �������� �ٷ� ���� �� �ִ� ��ȭ�� ã�´�.
		int lf = i + 1;
		int mid;
		int rt = k - 1;
		int final = s[i].finish; //s[next].a�� ���� final���� ū next�� ã�´�. �̰��� �̺�Ž���� �̿��Ѵ�. 
		int next = k;
		while (lf <= rt) { //�̺�Ž��
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
	memset(d, -1, sizeof(d)); //for�� ��� memset���� -1�� �ʱ�ȭ
	scanf_s("%d", &k); //������ ���� �Է�
	int i;
	for (i = 0; i < k; i++) { //������, �����³�, �⿬�� �Է�
		scanf_s("%d %d %d", &s[i].start, &s[i].finish, &s[i].pay);
	}
	sort(s, s + k, sort1); //sort1�� �������� �����Ѵ�.
	printf("%d", find1(0)); 
}