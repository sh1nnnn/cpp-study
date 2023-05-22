#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define CMD_INIT 1
#define CMD_HIRE 2
#define CMD_FIRE 3
#define CMD_UPDATE_SOLDIER 4
#define CMD_UPDATE_TEAM 5
#define CMD_BEST_SOLDIER 6

extern void init();
extern void hire(int mID, int mTeam, int mScore);
extern void fire(int mID);
extern void updateSoldier(int mID, int mScore);
extern void updateTeam(int mTeam, int mChangeScore);
extern int bestSoldier(int mTeam);

/////////////////////////////////////////////////////////////////////////
#include<list>
#include<algorithm>
#include<cstring>
using namespace std;

list<int> team[6][6];
list<int>::iterator it[100001];
int soldiers[100001];

void init()
{
    memset(soldiers, 0, sizeof(soldiers));

    for (register int i = 1; i < 6; i++)
    {
        for (register int j = 1; j < 6; j++)
        {
            team[i][j].clear();
        }
    }
}

void hire(int mID, int mTeam, int mScore)
{
    it[mID] = team[mTeam][mScore].insert(team[mTeam][mScore].begin(), mID);
    soldiers[mID] = mTeam;
}

void fire(int mID)
{
    *it[mID] = 0;
}

void updateSoldier(int mID, int mScore)
{
    fire(mID);
    hire(mID, soldiers[mID], mScore);
}

void updateTeam(int mTeam, int mChangeScore)
{
    if (mChangeScore > 0)
    {
        for (int i = 4; i > 0; i--)
        {
            if (i + mChangeScore > 5) team[mTeam][5].splice(team[mTeam][5].begin(), team[mTeam][i]);
            else team[mTeam][i + mChangeScore].splice(team[mTeam][i + mChangeScore].begin(), team[mTeam][i]);
        }
    }
    else if(mChangeScore < 0)
    {
        for (int i = 2; i < 6; i++)
        {
            if (i + mChangeScore < 1) team[mTeam][1].splice(team[mTeam][1].begin(), team[mTeam][i]);
            else team[mTeam][i + mChangeScore].splice(team[mTeam][i + mChangeScore].begin(), team[mTeam][i]);
        }
    }
}

int bestSoldier(int mTeam)
{
    int bestId = 0;
    for (int i = 5; i > 0; i--)
    {
        if (team[mTeam][i].empty()) continue;
        bestId = *max_element(team[mTeam][i].begin(), team[mTeam][i].end());
        if (bestId == 0) continue;
        break;
    }
    return bestId;
}
/////////////////////////////////////////////////////////////////////////

static bool run()
{
    int numQuery;

    int mID, mTeam, mScore, mChangeScore;

    int userAns, ans;

    bool isCorrect = false;

    scanf("%d", &numQuery);

    for (int i = 0; i < numQuery; ++i)
    {
        int cmd;
        scanf("%d", &cmd);
        switch (cmd)
        {
        case CMD_INIT:
            init();
            isCorrect = true;
            break;
        case CMD_HIRE:
            scanf("%d %d %d", &mID, &mTeam, &mScore);
            hire(mID, mTeam, mScore);
            break;
        case CMD_FIRE:
            scanf("%d", &mID);
            fire(mID);
            break;
        case CMD_UPDATE_SOLDIER:
            scanf("%d %d", &mID, &mScore);
            updateSoldier(mID, mScore);
            break;
        case CMD_UPDATE_TEAM:
            scanf("%d %d", &mTeam, &mChangeScore);
            updateTeam(mTeam, mChangeScore);
            break;
        case CMD_BEST_SOLDIER:
            scanf("%d", &mTeam);
            userAns = bestSoldier(mTeam);
            scanf("%d", &ans);
            if (userAns != ans)
            {
                isCorrect = false;
            }
            break;
        default:
            isCorrect = false;
            break;
        }
    }

    return isCorrect;
}

int main()
{
    setbuf(stdout, NULL);
    freopen("sample_25_input.txt", "r", stdin);

    int T, MARK;
    scanf("%d %d", &T, &MARK);

    for (int tc = 1; tc <= T; tc++)
    {
        int score = run() ? MARK : 0;
        printf("#%d %d\n", tc, score);
    }

    return 0;
}