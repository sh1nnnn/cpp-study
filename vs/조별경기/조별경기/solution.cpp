#include <list>
#include <cstring>
#include <vector>

using namespace std;

struct Player
{
	int score;
	int team;
}player[100001];

struct Team
{
	int score;
	list<int> playerList;
}team[100001];

void init(int N)
{
	for (register int i = 0; i <= N; ++i)
	{
		player[i].score = 0;
		player[i].team = i;
		team[i].score = 0;
		team[i].playerList.clear();
		team[i].playerList.push_back(i);
	}
}

void updateScore(int mWinnerID, int mLoserID, int mScore)
{
	team[player[mWinnerID].team].score += mScore;
	team[player[mLoserID].team].score -= mScore;
}

void unionTeam(int mPlayerA, int mPlayerB)
{
	int teamA = player[mPlayerA].team;
	int teamB = player[mPlayerB].team;

	if (team[teamA].playerList.size() < team[teamB].playerList.size())
	{
		for (auto i : team[teamA].playerList)
		{
			player[i].score += team[teamA].score - team[teamB].score;
			player[i].team = teamB;
		}
		//team[teamB].playerList.insert(team[teamB].playerList.end(), team[teamA].playerList.begin(),	team[teamA].playerList.end());
		team[teamB].playerList.splice(team[teamB].playerList.end(), team[teamA].playerList);
	}
	else
	{
		for (auto i : team[teamB].playerList)
		{
			player[i].score += team[teamB].score - team[teamA].score;
			player[i].team = teamA;
		}
		//team[teamA].playerList.insert(team[teamA].playerList.end(), team[teamB].playerList.begin(), team[teamB].playerList.end());
		team[teamA].playerList.splice(team[teamA].playerList.end(), team[teamB].playerList);
	}

	/*
	Team teamA = team[player[mPlayerA].team];
	Team teamB = team[player[mPlayerB].team];

	if(teamA.playerList.size() > teamB.playerList.size())
	{
		for (auto it = teamB.playerList.begin(); it != teamB.playerList.end(); ++it)
		{
			player[*it].score += teamB.score - team[player[mPlayerA].team].score;
			player[*it].team = player[mPlayerA].team;
		}
		team[player[mPlayerA].team].playerList.splice(team[player[mPlayerA].team].playerList.end(), teamB.playerList);
	}
	else
	{
		for (auto it = teamA.playerList.begin(); it != teamA.playerList.end(); ++it)
		{
			player[*it].score += teamA.score - team[player[mPlayerB].team].score;
			player[*it].team = player[mPlayerB].team;
		}
		team[player[mPlayerB].team].playerList.splice(team[player[mPlayerB].team].playerList.end(), teamA.playerList);
	}
	*/
}

int getScore(int mID)
{
	//printf("getScore() return[%d]\n", player[mID].score + team[player[mID].team].score);
	return player[mID].score + team[player[mID].team].score;
}
