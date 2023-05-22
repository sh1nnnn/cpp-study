// N x N ����, �� ���丶�� ���� �̸��� ������ �� ����
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
	// �̹� �����̰ų� A, B�� �����ϸ� -1 ����
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

	// �����̶�� -1 ����
	if (group[idxA] == group[idxB])
	{
		return -1;
	}
	
	// A, B�� ���� ���� �����̸� -2 ����
	if (enemy[group[idxA]][group[idxB]])
	{
		return -2;
	}

	// �� ������ �ƴ϶�� ���� ���� �� 1����
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
	// ������ �߻����� ������ -1 ���� = ���Ͱ���
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

	// �����̶�� -1 ����
	if (group[idxA] == group[idxB])
	{
		return -1;
	}

	// ������ ���䰡 �������� �ʴٸ� -2 ����
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

	// ���� �߻� �� B ���� �� ���ϱ�
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

	// ������� ��� �� ���� ���� ����
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
	// option�� 0�̸� num���� ���� ������ �ش� ������ ���� �� ����
	// option�� 1�̸� ��� ���� ���信 num�� ���� �� ������ ��� ���� �� ����
	int cnt = 0;

	// ���� ã��
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
