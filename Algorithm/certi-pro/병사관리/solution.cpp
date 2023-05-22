#include <queue>
#include <vector>

using namespace std;

struct Soldier
{
    int id;
    int team;
    int score;
    int status;

    bool operator<(const Soldier& s)const
    {
        if(score != s.score)
        {
            return score < s.score;
        }

        return id < s.id;
    }
}soldiers[100000];

struct Team
{
    priority_queue<Soldier*> bestScoreSoldier;
    vector<Soldier*> teamSoldiers;

}team[5];

void init()
{
    for(register int i = 0; i < 5; ++i)
    {
        priority_queue<Soldier*> bestScoreSoldier;
        swap(team[i].bestScoreSoldier, bestScoreSoldier);
        team[i].teamSoldiers.clear();
    }
    
    for(register int i = 0; i < 100000; ++i)
    {
        soldiers[i].id = soldiers[i].score = soldiers[i].team = soldiers[i].status = 0;
    }

}

// 호출 횟수 : 100,000 이하
void hire(int mID, int mTeam, int mScore)
{
    soldiers[mID].id = mID;
    soldiers[mID].team = mTeam;
    soldiers[mID].score = mScore;
    soldiers[mID].status = 1;

    team[mTeam].bestScoreSoldier.push(&soldiers[mID]);
    team[mTeam].teamSoldiers.push_back(&soldiers[mID]);
}

// 호출 횟수 : 100,000 이하
void fire(int mID)
{
    soldiers[mID].status = 0;
}

// 호출 횟수 : 100,000 이하
void updateSoldier(int mID, int mScore)
{
    soldiers[mID].score = mScore;
}

// 호출 횟수 : 100,000 이하
void updateTeam(int mTeam, int mChangeScore)
{
    for(register int i = 0; i < team[mTeam].teamSoldiers.size(); ++i)
    {
        if(team[mTeam].teamSoldiers[i]->score + mChangeScore > 5) team[mTeam].teamSoldiers[i]->score = 5;
        else if(team[mTeam].teamSoldiers[i]->score + mChangeScore < 1) team[mTeam].teamSoldiers[i]->score = 1;
        else team[mTeam].teamSoldiers[i]->score = team[mTeam].teamSoldiers[i]->score + mChangeScore;
    }
}

// 호출 횟수 : **100 이하**
int bestSoldier(int mTeam)
{
    Soldier update;
    update.id = -9;
    update.score = -9;
    team[mTeam].bestScoreSoldier.push(&update);

    int id = team[mTeam].bestScoreSoldier.top()->id;
    return id;
}