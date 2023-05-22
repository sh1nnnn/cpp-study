#include <queue>
#include <list>
#include <cstring>

#define DEBUG 1

using namespace std;

int numbers[200101];
int maxList[200101];
int minList[200101];

int N;

void init(int __N, int mValue[])
{
	N = __N;

	memset(numbers, 0, sizeof(numbers));
	memset(maxList, 0, sizeof(maxList));
	memset(minList, 0, sizeof(minList));

	numbers[N] = maxList[N] = minList[N] = mValue[N - 1];
	for (register int i = N - 1; i > 0; --i)
	{
		numbers[i] = mValue[i - 1];

		if (numbers[i] > maxList[i + 1]) maxList[i] = numbers[i];
		else maxList[i] = maxList[i + 1];

		if (numbers[i] < minList[i + 1]) minList[i] = numbers[i];
		else minList[i] = minList[i + 1];
	}
}

void add(int M, int mValue[])
{
	N += M;
	int valueIdx = M - 1;

	numbers[N] = maxList[N] = minList[N] = mValue[valueIdx];
	
	for (register int i = N - 1; i > N - M; --i)
	{
		numbers[i] = mValue[--valueIdx];

		if (numbers[i] > maxList[i + 1]) maxList[i] = numbers[i];
		else maxList[i] = maxList[i + 1];

		if (numbers[i] < minList[i + 1]) minList[i] = numbers[i];
		else minList[i] = minList[i + 1];
	}


	// To Do. 최적화 : add되기 전 마지막 값이 add된 값보다 최대, 최소 달성 시 return
	bool isMax = false, isMin = false;
	for (register int i = N - M; i > 0; --i)
	{
		// max 갱신
		if(!isMax)
		{
			if (numbers[i] > maxList[i + 1])
			{
				maxList[i] = numbers[i];
				isMax = true;

			}
			else maxList[i] = maxList[i + 1];
		}

		// min 갱신
		if(!isMin)
		{
			if (numbers[i] < minList[i + 1])
			{
				minList[i] = numbers[i];
				isMin = true;
			}
			else minList[i] = minList[i + 1];
		}

		if (isMax && isMin) break;
	}
}

void erase(int mFrom, int mTo)
{
	// To Do. 최적화 : mTo == N 인 경우, 바로 minmax 갱신
	int startIdx = mFrom - 1;
	if (N == mTo) maxList[startIdx + 1] = minList[startIdx + 1] = numbers[startIdx];
	else
	{
		int endIdx = N + mFrom - mTo - 1;
		int idx = mTo + 1;
		for (register int i = mFrom; i <= endIdx; ++i)
		{
			numbers[i] = numbers[idx];
			maxList[i] = maxList[idx];
			minList[i] = minList[idx++];
		}
	}

	N -= mTo - mFrom + 1;

	// To Do. 최적화
	bool isMax = false, isMin = false;
	if (maxList[startIdx] <= maxList[startIdx + 1]) isMax = true;
	if (minList[startIdx] >= minList[startIdx + 1]) isMin = true;
	for (register int i = startIdx; i > 0; --i)
	{
		if (isMax && isMin) break;

		// max 갱신
		if (!isMax)
		{
			if (numbers[i] > maxList[i + 1]) maxList[i] = numbers[i];
			else maxList[i] = maxList[i + 1];
		}

		// min 갱신
		if (!isMin)
		{
			if (numbers[i] < minList[i + 1]) minList[i] = numbers[i];
			else minList[i] = minList[i + 1];
		}
	}
}

int find(int K)
{
#if DEBUG
	printf("find() result[%d]\n", maxList[N - K + 1] - minList[N - K + 1]);
#endif
	return maxList[N - K + 1] - minList[N - K + 1];
}