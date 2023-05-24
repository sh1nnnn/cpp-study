#include <cstring>
#include <list>
#include <cmath>

using namespace std;

struct Airport
{
	int endAirport;
	int startTime;
	int travelTime;
	int price;

	void init()
	{
		endAirport = startTime = travelTime = price = 0;
	}
};

list<Airport> airport[60];
int link[60][60];
int minT;
int minP;
int N;

void init(int __N)
{
	N = __N;
	for (register int i = 0; i < N; ++i) airport[i].clear();
	memset(link, 0, sizeof(link));
}

void add(int mStartAirport, int mEndAirport, int mStartTime, int mTravelTime, int mPrice)
{
	airport[mStartAirport].push_back({ mEndAirport, mStartTime, mTravelTime, mPrice });
}

void getMinTravelTime(int start, int end, int curTime, int travelTime, bool visited[60])
{
	bool localVisited[60] = { false, };
	memcpy(localVisited, visited, sizeof(visited));

	if (start == end)
	{
		if (travelTime < minT) minT = travelTime;
		return;
	}
	for (auto ap : airport[start])
	{
		if (!visited[ap.endAirport])
		{
			localVisited[ap.endAirport] = true;
			if(curTime <= ap.startTime)
				getMinTravelTime(ap.endAirport, end, (ap.startTime + ap.travelTime) % 24, travelTime + (ap.startTime - curTime + ap.travelTime), localVisited);
			else
				getMinTravelTime(ap.endAirport, end, (ap.startTime + ap.travelTime) % 24, travelTime + (24 - curTime + ap.startTime + ap.travelTime), localVisited);
		}

	}
}

int minTravelTime(int mStartAirport, int mEndAirport, int mStartTime)
{
	minT = 2100000000;
	bool visited[60] = { false, };
	visited[mStartAirport] = true;
	getMinTravelTime(mStartAirport, mEndAirport, mStartTime, 0, visited);
	printf("minTravelTime() result[%d]\n", (minT == 2100000000) ? -1 : minT);
	return (minT == 2100000000) ? -1 : minT;
}

void getMinPrice(int start, int end, int price, bool visited[60])
{
	bool localVisited[60] = { false, };
	memcpy(localVisited, visited, sizeof(visited));
	if (start == end)
	{
		if (price < minP) minP = price;
		return;
	}
	for (auto ap : airport[start])
	{
		if(!visited[ap.endAirport])
		{
			localVisited[ap.endAirport] = true;
			getMinPrice(ap.endAirport, end, price + ap.price, localVisited);
		}
	}
}

int minPrice(int mStartAirport, int mEndAirport)
{
	minP = 2100000000;
	bool visited[60] = { false, };
	visited[mStartAirport] = true;
	getMinPrice(mStartAirport, mEndAirport, 0, visited);
	printf("minPrice() result[%d]\n", (minP == 2100000000) ? -1 : minP);
	return (minP == 2100000000) ? -1 : minP;
}