#include<iostream>
#include<stdio.h>

using namespace std;
constexpr int MAX_N = 10;
int info[2][MAX_N];

int main(int argc, char** argv)
{
	int test_case;
	int T;

	freopen("input.txt", "r", stdin);
	cin>>T;
	for(test_case = 1; test_case <= T; ++test_case)
	{
		// 자성체 n개 존재
		// 각 자성체 위치 x
		// 자성체로부터 물체에 작용하는 인력, F = G * m1 * m2 / (d * d), G는 양의 상수
		// 물체는 인력이 더 큰 쪽으로 움직이다가 인력이 같아지면 멈춤

		int N; // 자성체 N개 (2 <= N <= 10)
		scanf("%d", &N);

		for(register int i = 0; i < N; ++i)
		{
			info[0][i] = 0;
			info[1][i] = 0;
		}

		for(register int i = 0; i < N; ++i)
		{
			scanf("%d", &info[0][i]);
		}

		for(register int i = 0; i < N; ++i)
		{
			scanf("%d", &info[1][i]);
		}


	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}