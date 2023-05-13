#include <cstring>
#include <queue>

using namespace std;

// 0 ~ N - 1 도시 존재
// 각 도시는 곡물을 저장하는 창고 존재
// 수도에서 관리가 각 도시의 존재하는 창고에서 곡물을 수거해감
// 각 도시끼리는 세금을 주고 받음
// 인접한 도시로의 이동은 1시각이 소요


// 관리 파견
// 관리의 파견보다 이동 완료 예정인 곡물이 우선!
// 이동 시간을 고려해서 도착시간에 모든 창고의 곡물이 0 이거나 파견할 도시가 없다면 대기
// 인접한 도시로의 이동은 1시각 소요
// 도착 시간을 기준으로 가장 곡물이 많을 것으로 예쌍되는 도시의 창고를 선택한다.
// 이미 관리가 파견된 도시는 배제
// 예상되는 곡물의 양이 같은 창고가 있다면 ID가 작은 창고가 우선
// 위 모든 조건 충족 시 관리 파견


struct City
{
    int storage;
    int expected;
    bool isManaged;

    void init()
    {
        storage = expected = 0;
        isManaged = false;
    }
}city[200];

// GET : target 도시에 tax 만큼 storage 채우기
// MOVE : 목적지로 이동
// HOME : 수도로 이동
// SEND : 매니저 파견
enum event
{
    GET, MOVE, HOME, SEND
};

struct CMD
{
    int type;
    int tax;
    int target;
    int time;

    bool operator <(const CMD& cmd) const
    {
        if (time == cmd.time) return type < cmd.type;
        return time < cmd.type;
    }
};

int managerCnt;
int managerMax;

priority_queue<CMD> cmdQueue;


/// <param name="N"> 도시의 개수 (10 <= N <= 200) </param>
/// <param name="M"> 왕실 소속 관리의 수 (1 <= M <= 50) </param>
void init(int N, int M)
{
    for (register int i = 0; i < N; ++i)
    {
        city[i].init();
    }

    managerMax = M;
    managerCnt = 0;
    cmdQueue = {};
}

void destroy()
{
}

void __run(int time)
{

}

int order(int tStamp, int mCityA, int mCityB, int mTax)
{
    // tStamp 시각 전까지 시뮬레이션 진행
    __run(tStamp - 1);

    // 세금 이벤트 발생
    // pq에 move 이벤트 넣기
    CMD cmd;
    cmd.type = MOVE;
    cmd.tax = mTax;
    cmd.target = mCityB;
    cmd.time = tStamp;
    int distance = abs(mCityA - mCityB);
    
    if (mCityB > mCityA || mCityB > distance)
    {
        city[mCityB].expected += mTax;
    }

    return city[0].storage;
}


int check(int tStamp)
{
    return city[0].storage;
}


int a;
int b;