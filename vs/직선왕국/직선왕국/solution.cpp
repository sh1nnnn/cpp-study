#include <cstring>
#include <queue>

using namespace std;

// 0 ~ N - 1 ���� ����
// �� ���ô� ��� �����ϴ� â�� ����
// �������� ������ �� ������ �����ϴ� â���� ��� �����ذ�
// �� ���ó����� ������ �ְ� ����
// ������ ���÷��� �̵��� 1�ð��� �ҿ�


// ���� �İ�
// ������ �İߺ��� �̵� �Ϸ� ������ ��� �켱!
// �̵� �ð��� ����ؼ� �����ð��� ��� â���� ��� 0 �̰ų� �İ��� ���ð� ���ٸ� ���
// ������ ���÷��� �̵��� 1�ð� �ҿ�
// ���� �ð��� �������� ���� ��� ���� ������ ���ֵǴ� ������ â�� �����Ѵ�.
// �̹� ������ �İߵ� ���ô� ����
// ����Ǵ� ��� ���� ���� â�� �ִٸ� ID�� ���� â�� �켱
// �� ��� ���� ���� �� ���� �İ�


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

// GET : target ���ÿ� tax ��ŭ storage ä���
// MOVE : �������� �̵�
// HOME : ������ �̵�
// SEND : �Ŵ��� �İ�
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


/// <param name="N"> ������ ���� (10 <= N <= 200) </param>
/// <param name="M"> �ս� �Ҽ� ������ �� (1 <= M <= 50) </param>
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
    // tStamp �ð� ������ �ùķ��̼� ����
    __run(tStamp - 1);

    // ���� �̺�Ʈ �߻�
    // pq�� move �̺�Ʈ �ֱ�
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