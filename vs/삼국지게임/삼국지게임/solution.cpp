// N x N 영토, 각 영토마다 군주 이름과 병사의 수 존재
#include <cstring>

using namespace std;

int soldierCnt[625];
char monarchName[625][11];
int group[625];

bool alliance[25][25];
bool enemy[25][25];

int dx[8] = { -1, -1, -1, 1, 1, 1, 0, 0 };
int dy[8] = { -1, 0, 1, -1, 0, 1, -1, 1 };
int size;


void init(int N, int mSoldier[25][25], char mMonarch[25][25][11])
{
	size = N;
	for (register int i = 0; i < N * N; ++i)
	{
		soldierCnt[i] = 0;
		memset(monarchName[i], '0', 11);
	}

	for (register int i = 0; i < N * N; ++i)
	{
		for (register int j = 0; j < N * N; ++j)
		{
			alliance[i][j] = enemy[i][j] = false;
			if (i == j) alliance[i][j] = true;
		}
	}
	int idx = 0;
	for (register int i = 0; i < N; ++i)
	{
		for (register int j = 0; j < N; ++j)
		{
			idx = N * i + j;
			soldierCnt[idx] = mSoldier[i][j];
			strcpy(monarchName[idx], mMonarch[i][j]);
			group[idx] = idx;
		}
	}
}

void destroy()
{

}

int ally(char mMonarchA[11], char mMonarchB[11])
{
	// 이미 동맹이거나 A, B가 동일하면 -1 리턴
	// find A, B idx
	int idxA = 0, idxB = 0;
	for (register int i = 0; i < size * size; ++i)
	{
		if (strcmp(monarchName[i], mMonarchA) == 0)
		{
			idxA = i;
			break;
		}
	}
	for (register int i = 0; i < size * size; ++i)
	{
		if (strcmp(monarchName[i], mMonarchB) == 0)
		{
			idxB = i;
			break;
		}
	}

	// 동맹이라면 -1 리턴
	if (group[idxA] == group[idxB])
	{
		return -1;
	}
	
	// A, B가 서로 적대 관계이면 -2 리턴
	if (enemy[group[idxA]][group[idxB]])
	{
		return -2;
	}

	// 위 조건이 아니라면 동맹 구축 후 1리턴
	for (register int i = 0; i < size * size; ++i)
	{
		if (alliance[group[idxB]][i])
		{
			alliance[group[idxA]][i] = true;
			group[i] = group[idxA];
		}

		if (enemy[group[idxB]][i]) enemy[group[idxA]][i] = enemy[i][group[idxA]] = true;
	}

	return 1;
}

int attack(char mMonarchA[11], char mMonarchB[11], char mGeneral[11])
{
	// 공격이 발생하지 않으면 -1 리턴 = 동맹관계
	int idxA = 0, idxB = 0;
	for (register int i = 0; i < size * size; ++i)
	{
		if (strcmp(monarchName[i], mMonarchA) == 0)
		{
			idxA = i;
			break;
		}
	}
	for (register int i = 0; i < size * size; ++i)
	{
		if (strcmp(monarchName[i], mMonarchB) == 0)
		{
			idxB = i;
			break;
		}
	}

	// 동맹이라면 -1 리턴
	if (group[idxA] == group[idxB])
	{
		return -1;
	}

	// 서로의 영토가 인접하지 않다면 -2 리턴
	int ii = 0, jj = 0, ij = 0;
	bool isMatch = false;
	int cntA = 0;
	for (register int k = 0; k < 8; ++k)
	{
		ii = idxB / size + dx[k];
		jj = idxB % size + dy[k];
		if (ii >= 0 && ii < size && jj >= 0 && jj < size)
		{
			ij = ii * size + jj;
			if (alliance[group[idxA]][ij])
			{
				isMatch = true;
				cntA = cntA + soldierCnt[ij] / 2;
				soldierCnt[ij] = soldierCnt[ij] - soldierCnt[ij] / 2;
			}
		}
	}

	if (!isMatch)
	{
		return -2;
	}

	// 전투 발생 시 B 군인 수 구하기
	int cntB = 0;
	for (register int k = 0; k < 8; ++k)
	{
		ii = idxB / size + dx[k];
		jj = idxB % size + dy[k];
		if (ii >= 0 && ii < size && jj >= 0 && jj < size)
		{
			ij = ii * size + jj;
			if (alliance[group[idxB]][ij])
			{
				cntB = cntB + soldierCnt[ij] / 2;
				soldierCnt[ij] = soldierCnt[ij] - soldierCnt[ij] / 2;
			}
		}
	}

	// 적대관계 등록 및 영토 군주 변경
	enemy[group[idxA]][group[idxB]] = enemy[group[idxB]][group[idxA]] = true;
	if (cntA > cntB)
	{
		soldierCnt[idxB] = cntA - cntB;
		memset(monarchName[idxB], '0', 11);
		strcpy(monarchName[idxB], mGeneral);

		alliance[group[idxB]][idxB] = false;
		alliance[group[idxA]][idxB] = true;
		group[idxB] = group[idxA];
		return 1;
	}
	else
	{
		soldierCnt[idxB] = cntB - cntA;
		return 0;
	}
}

int recruit(char mMonarch[11], int mNum, int mOption)
{
	// option이 0이면 num명의 병사 모집후 해당 영토의 병사 수 리턴
	// option이 1이면 모든 동맹 영토에 num명 모집 후 동맹의 모든 병사 수 리턴
	int cnt = 0;

	// 군주 찾기
	int idx = 0;
	for (register int i = 0; i < size * size; ++i)
	{
		if (strcmp(monarchName[i], mMonarch) == 0)
		{
			idx = i;
			break;
		}
	}

	if (mOption == 0)
	{
		soldierCnt[idx] += mNum;
		cnt = soldierCnt[idx];
	}
	else
	{
		for (register int i = 0; i < size * size; ++i)
		{
			if (alliance[group[idx]][i])
			{
				soldierCnt[i] += mNum;
				cnt += soldierCnt[i];
			}
		}
	}

	return cnt;
}
