// 2N개의 카드 존재(2 <= N <= 50,000)
#include<cstring>

constexpr int BASE_VALUE_INDEX = 0;
int baseValueDiff[50000][4]; // 절댓값이므로 4개

extern bool checkCards(int mIndexA, int mIndexB, int mDiff);

int parametricSearch(int targetIdx, int __high)
{
    int low = 0, high = __high;

    while (low < high)
    {
        int mid = (low + high) / 2;
        if (checkCards(BASE_VALUE_INDEX, targetIdx, mid)) high = mid;
        else low = mid + 1;
    }

    return low;
}

void updateZeroBaseDiff(int targetIdx, int diff)
{
    for (register int i = 0; i < 4; ++i)
    {
        if (baseValueDiff[diff][i] == 0)
        {
            baseValueDiff[diff][i] = targetIdx;
            break;
        }
    }
}

void playGame(int N)
{
    memset(baseValueDiff, 0, sizeof(baseValueDiff));

    for (register int target = 1; target < N * 2; ++target)
    {
        int diff = parametricSearch(target, N - 1);
        updateZeroBaseDiff(target, diff);
    }

    for (register int i = 0; i < N; ++i)
    {
        for (register int j = 0; j < 4; ++j)
        {
            for (register int k = j + 1; k < 4; ++k)
                if (checkCards(baseValueDiff[i][j], baseValueDiff[i][k], 0)) break;
        }
    }
}