#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define MAX_LEN 200

void init();
int addExpression(int mID, char mExpression[MAX_LEN + 1]);
int calcExpression(int mID, int mA, int mB, int mC);

#define CMD_INIT 100
#define CMD_ADD 200
#define CMD_CALC 300

static bool run()
{
    int query_num;
    scanf("%d", &query_num);

    int ret, ans;
    bool ok = false;

    for (int q = 0; q < query_num; q++)
    {
        int query;
        scanf("%d", &query);

        if (query == CMD_INIT)
        {
            init();
            ok = true;
        }
        else if (query == CMD_ADD)
        {
            int mID;
            char mExpression[MAX_LEN + 1];
            scanf("%d %s", &mID, mExpression);
            ret = addExpression(mID, mExpression);
            scanf("%d", &ans);
            if (ans != ret)
            {
                ok = false;
            }
        }
        else if (query == CMD_CALC)
        {
            int mID;
            int mA, mB, mC;
            scanf("%d %d %d %d", &mID, &mA, &mB, &mC);
            ret = calcExpression(mID, mA, mB, mC);
            scanf("%d", &ans);
            if (ans != ret)
            {
                ok = false;
            }
        }
    }
    return ok;
}

int main()
{
    setbuf(stdout, NULL);
    freopen("sample_input.txt", "r", stdin);
    int T, MARK;
    scanf("%d %d", &T, &MARK);

    for (int tc = 1; tc <= T; tc++)
    {
        int score = run() ? MARK : 0;
        printf("#%d %d\n", tc, score);
    }
    return 0;
}