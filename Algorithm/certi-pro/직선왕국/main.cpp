#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define CMD_INIT 100
#define CMD_DESTROY 200
#define CMD_ORDER 300
#define CMD_CHECK 400

extern void init(int N, int M);
extern void destroy();
extern int order(int tStamp, int mCityA, int mCityB, int mTax);
extern int check(int tStamp);


// solution start
#include <vector>
#include <cstring>
#include <queue>

using namespace std;
// M명의 관리들이 수도로 곡물을 옮김
// 관리들은 왕실에서 대기하며 매 시각 아래와 같은 일을 함
// 해당 시각에 이동 완료 예정인 곡물이 있다면 이동이 완료되길 기다림(대기!)
// 이동시간을 고려한 도착시간에 모든 창고의 곡물이 0이 예상되거나 파견할 도시가 없다면 대기
// 도착 시각을 기준으로 가장 곡물이 많을 것으로 예상되는 도시의 창고로 출발(이미 관리가 파견 중인 도시는 제외)
// 예상되는 도시의 곡물 양이 동일하면 ID가 작은 도시로 출발
// 관리 1명만 파견

struct City
{
    int curStorage;
    int epStorage;
    bool isManaged;

    void init()
    {
        curStorage = 0;
        epStorage = 0;
        isManaged = false;
    }
}city[200];

struct CMD
{
    int cmdType;
    int time;
    int cityID;
    int tax;

    bool operator <(const CMD& c) const
    {
        if(time == c.time)
        {
            return cmdType > c.cmdType;
        }
        return time > c.time;
    }
};


int curTime;
int managerCnt;
int managerMax;

// priority_queue

void init(int N, int M)
{
    for(register int i = 0; i < N; ++i) city[i].init();
    curTime = 0;
    managerMax = M;
    managerCnt = 0;
}

void __run()
{

}

void destroy()
{
}

int order(int tStamp, int mCityA, int mCityB, int mTax)
{
    // N개의 도시 0번이 수도, 숫자가 작을 수록 수도에 가까움
    // A -> B 도시로 세납 (t 시각 소요, 수도 제외)


    // mCityB에 (tStamp + mCityA, mCityB 거리) 시각 이후 mTax 만큼의 곡물을 채움
    int diff = abs(mCityA - mCityB);
    


    // tStamp 시각 현재 수도에 있는 곡물의 양 반환

    return -1;
}

int check(int tStamp)
{
    return -1;
}

// solution end


static int run()
{
	int C;
	int isOK = 0;
	int cmd, ret, chk;

	int mN, mM;
	int mTStamp;

	int mCityA, mCityB, mTax;

	scanf("%d", &C);

	for (int c = 0; c < C; ++c)
	{
		scanf("%d", &cmd);
		switch (cmd)
		{
		case CMD_INIT:
			scanf("%d %d ", &mN, &mM);
			init(mN, mM);
			isOK = 1;
			break;

		case CMD_ORDER:			
			scanf("%d %d %d %d", &mTStamp, &mCityA, &mCityB, &mTax);
			ret = order(mTStamp, mCityA, mCityB, mTax);
			scanf("%d", &chk);
			if (ret != chk)
				isOK = 0;
			break;

		case CMD_CHECK:
			scanf("%d", &mTStamp);
			ret = check(mTStamp);
			scanf("%d", &chk);
			if (ret != chk)
				isOK = 0;
			break;

		default:
			isOK = 0;
			break;
		}
	}
	destroy();
	return isOK;
}

int main()
{
	setbuf(stdout, NULL);
	freopen("sample_input.txt", "r", stdin);

	int T, MARK;
	scanf("%d %d", &T, &MARK);

	for (int tc = 1; tc <= T; tc++)
	{
		if (run()) printf("#%d %d\n", tc, MARK);
		else printf("#%d %d\n", tc, 0);
	}
	return 0;
}