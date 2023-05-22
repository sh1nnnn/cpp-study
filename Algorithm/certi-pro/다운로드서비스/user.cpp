#include <vector>

// 트리구조 필요
//
struct DownloadService
{
	int ID;
	bool isPC;
	std::vector<DownloadService> child;
};


int mTime;

// finish - 완료 여부 (0: 진행 중, 1: 완료)
// param - finish 종속 변수
// finish == 0, param: 남아 있는 다운로드 크기
// finish == 1, param: 완료된 시각(mTime)
struct Result {
	int finish;
	int param;
};

// 100 <= mCapa <= 50000
// 서버 ID = 0
// mTime = 0
// 서버는 mCapa의 전송 속도를 가진다.
void init(int mCapa)
{
	mTime = 0;

}

// mTime까지 다운로드 진행 후 mParentID에 mID 노드 추가
void addHub(int mTime, int mParentID, int mID)
{

}

int removeHub(int mTime, int mID)
{
	return -1;
}

void requestDL(int mTime, int mParentID, int mpcID, int mSize)
{
}

// mTime 시각에 mpcID의 PC 상태를 확인하는 함수
// 
Result checkPC(int mTime, int mpcID)
{
	Result res;
	res.finish = 0;
	res.param = 0;

	return res;
}

void process()
{

}