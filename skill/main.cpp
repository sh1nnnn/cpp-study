// CPP Program to demonstrate the implementation in Map
// divyansh mishra --> divyanshmishra101010
#include <iostream>
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


int main()
{

    soldiers[0].id = 1;
    soldiers[0].score = 10;

    soldiers[1].id = 2;
    soldiers[1].score = 250;

    soldiers[2].id = 3;
    soldiers[2].score = 30;

    team[0].bestScoreSoldier.push(&soldiers[0]);
    team[0].bestScoreSoldier.push(&soldiers[1]);
    team[0].bestScoreSoldier.push(&soldiers[2]);


    // Soldier update;
    // update.id = -9;
    // update.score = -9;
    // team[0].bestScoreSoldier.push(&update);

    int id = team[0].bestScoreSoldier.top()->id;
    printf("%d", id);

    return 0;
}
