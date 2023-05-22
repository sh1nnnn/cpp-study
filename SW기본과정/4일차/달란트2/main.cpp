#include<iostream>
#include<stdio.h>

using namespace std;

int main(int argc, char** argv)
{
	int test_case;
	int T;
	freopen("input.txt", "r", stdin);
	cin>>T;
	for(test_case = 1; test_case <= T; ++test_case)
	{
		int N; // 달란트의 수 (10 <= N <= 100)
		int P; // 묶음 수 (P <= N)
		scanf("%d %d", &N, &P);

		long long answer = 1;
		int tmp = N / P;
		int tmp2 = N % P;

		for (register int i = 0; i < tmp2; ++i)	answer *= (tmp + 1);
		for (register int i = 0; i < P - tmp2; ++i) answer *= tmp;
		printf("#%d %lld\n", test_case, answer);
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}