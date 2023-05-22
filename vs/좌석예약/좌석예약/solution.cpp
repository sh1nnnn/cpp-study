#include <cstring>
#include <queue>
#include <list>

#define DEBUG 0

using namespace std;

struct Position
{
	int row, col;

	bool operator<(const Position& p)const
	{
		if (row == p.row) return col > p.col;
		return row > p.row;
	}
};

struct Reservation
{
	int id;
	int num;
	list<Position> pos;

	void init()
	{
		id = num = 0;
		pos.clear();
	}
}reservation[50001];

struct Result {
	int id;
	int num;
};

bool cinema[2000][100];
int cinemaCnt[2000];
int N;

int dr[] = {-1, 0, 0, 1};
int dc[] = {0, -1, 1, 0};

void init(int __N)
{
	N = __N;
	memset(cinema, false, sizeof(cinema));
	for(register int i = 0 ; i < 2000; ++i) cinemaCnt[i] = 100;
	for (register int i = 0; i < 50001; ++i) reservation[i].init();
}

Result reserveSeats(int mID, int K)
{
	Result res;
	res.id = 0;
	res.num = 0;

	// 1번 영화관부터 search
	for (register int i = 0; i < N; ++i)
	{
		// 남은 좌석보다 K가 큰 경우 다음 영화관 search
		if (cinemaCnt[i] < K) continue;

		// 남은 좌석 중 가장 번호가 작은 좌석 search
		bool visited[100];
		memcpy(visited, cinema[i], sizeof(cinema[i]));
		priority_queue<Position> q;
		bool isSuccess = false;
		while (!isSuccess)
		{
			priority_queue<Position> emptyQ;
			swap(q, emptyQ);

			bool check = false;
			for (register int j = 0; j < 100; ++j)
			{
				if (!visited[j])
				{
					q.push({ j / 10, j % 10 });
					visited[j] = true;
					check = true;
					break;
				}
			}
			if (!check) break;

			int cnt = 0;
			list<Position> seatList;
			while (!q.empty())
			{
				Position pos = q.top();
				q.pop();
				seatList.push_back(pos);
				if (++cnt == K)
				{
					reservation[mID].id = i;
					res.id = i + 1;
					reservation[mID].num = seatList.front().row * 10 + seatList.front().col;
					res.num = seatList.front().row * 10 + seatList.front().col + 1;
					swap(reservation[mID].pos, seatList);
					isSuccess = true;
					for (Position p : reservation[mID].pos) cinema[i][p.row * 10 + p.col] = true;
					cinemaCnt[i] -= K;
					break;
				}

				int r = 0, c = 0;
				for (register int k = 0; k < 4; ++k)
				{
					r = pos.row + dr[k];
					c = pos.col + dc[k];

					if (r < 0 || r >= 10 || c < 0 || c >= 10 || visited[r * 10 + c]) continue;

					q.push({ r, c });
					visited[r * 10 + c] = true;
				}
			}
		}

		if (isSuccess) break;
	}

#if DEBUG
	printf("reserveSeats() result : id[%d], num[%d]\n", res.id, res.num);
#endif
	return res;
}

Result cancelReservation(int mID)
{
	Result res;
	res.id = 0;
	res.num = 0;

	res.id = reservation[mID].id;
	cinemaCnt[res.id] += reservation[mID].pos.size();
	for (Position p : reservation[mID].pos)
	{
		int index = p.row * 10 + p.col;
		cinema[res.id][index] = false;
		res.num += index + 1;
	}

#if DEBUG
	printf("cancelReservation() result : id[%d], num[%d]\n", ++res.id, res.num);
#endif
	res.id++;
	return res;
}