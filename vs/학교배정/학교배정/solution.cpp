#include <cstring>
#include <queue>
#include <list>
#include <unordered_map>
#include <cmath>

#define DEBUG 0

using namespace std;

struct School
{
	int id, r, c;
	int distance;

	bool operator<(const School& s) const
	{
		if (distance == s.distance) return id > s.id;
		return distance > s.distance;
	}
}schools[10];

struct Student
{
	int id, r, c;
	int distance;
	int status, school;
	priority_queue<School> pq;

	void init()
	{
		id = r = c = distance = status = school = -1;
		priority_queue<School> emptyPQ;
		swap(pq, emptyPQ);
	}

	bool operator<(const Student& s) const
	{
		if (distance == s.distance) return id > s.id;
		return distance < s.distance;
	}
}students[10001];



int C, N;
int stIdx;
int schoolCnt[10];
unordered_map<int, int> stID2Idx;
priority_queue<Student> pq;

void init(int __C, int __N, int mX[], int mY[]) {
	C = __C;
	N = __N;
	
	stIdx = 0;
	stID2Idx.clear();
	memset(schoolCnt, 0, sizeof(schoolCnt));
	
	for (register int i = 0; i < 10001; ++i) students[i].init();
	for (register int i = 0; i < N; ++i)
	{
		schools[i].id = i;
		schools[i].r = mX[i];
		schools[i].c = mY[i];
		schools[i].distance = -1;
	}
	return;
}

void update(int id)
{
	priority_queue<Student> emptyPQ;
	swap(pq, emptyPQ);

	for (register int i = 0; i < stIdx; ++i)
	{
		pq.push(students[i]);
	}

	int cnt[10] = {0, };
	while (pq.top().id != id)
	{
		if (pq.top().status != -1) cnt[pq.top().school]++;
		pq.pop();
	}
	if (pq.top().status == -1) pq.pop();
	
	while(!pq.empty())
	{
		Student s = pq.top();
		pq.pop();

		if (s.status == -1) continue;
		
		priority_queue<School> schoolPQ = s.pq;
		while (true)
		{
			if (cnt[schoolPQ.top().id] < C)
			{
				cnt[schoolPQ.top().id]++;
				students[stID2Idx[s.id]].school = schoolPQ.top().id;
				break;
			}
			schoolPQ.pop();
		}
	}

	memcpy(schoolCnt, cnt, sizeof(cnt));
}

int add(int mStudent, int mX, int mY) {
	// 학생 생성
	int idx = stIdx;
	if (stID2Idx.count(mStudent) == 0) stID2Idx.insert(make_pair(mStudent, stIdx++));
	else idx = stID2Idx[mStudent];

	students[idx].id = mStudent;
	students[idx].r = mX;
	students[idx].c = mY;
	students[idx].status = 1;
	
	// 학생 우선순위 선택을 위한 max 거리 등록, 희망하는 학교 우선순위 등록
	// 학생 선택 우선순위
	// 1. 거리 값이 클 수록(학교와 가장 거리가 먼 값 기준)
	// 2. 학생 ID가 낮을 수록

	// 학교 배정 우선순위
	// 1. 거리가 가장 가까운
	// 2. 거리가 동일한 경우 학교 ID가 낮을 수록
	int maxDistance = 0;
	for (register int i = 0; i < N; ++i)
	{
		int distance = abs(mX - schools[i].r) + abs(mY - schools[i].c);
		if (maxDistance < distance) maxDistance = distance;
		students[idx].pq.push({ schools[i].id, schools[i].r, schools[i].c, distance });
	}
	students[idx].distance = maxDistance;
	
	if (schoolCnt[students[idx].pq.top().id] < C)
	{
		schoolCnt[students[idx].pq.top().id]++;
		students[idx].school = students[idx].pq.top().id;
	}
	else update(mStudent);
	
#if DEBUG
	printf("add() result[%d]\n", students[idx].school);
#endif
	return students[idx].school;
}

int remove(int mStudent) {
	int idx = stID2Idx[mStudent];

	students[idx].status = -1;
	update(mStudent);

#if DEBUG
	printf("remove() result[%d]\n", students[idx].school);
#endif
	return students[idx].school;
}

int status(int mSchool) {
#if DEBUG
	printf("status() result[%d]\n", schoolCnt[mSchool]);
#endif
	return schoolCnt[mSchool];
}