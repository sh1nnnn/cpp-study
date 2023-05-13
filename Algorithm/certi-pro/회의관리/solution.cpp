#include <set>
#include <string>
#include <unordered_map>

#define CLOSEMEETING 0
#define OPENMEETING 1

struct MEETING
{
    std::string name;
    int startTime;
    int endTime;
    int state;
    std::set<int> members;
}meetings[10001];

int meetingCertiPointer;
unordered_map <string, int> meetingCerti;

void init()
{
    meetingCertiPointer = 0;
}


// 회의 등록 : 회의를 시스템에 등록한다. 등록할 때 시작 시간, 종료 시간, 참석자 목록이 주어진다.
int addMeeting(char mMeeting[MAXL], int M, char mMemberList[MAXM][MAXL], int mStartTime, int mEndTime)
{
    int meetingIdx = meetingCerti[mMeeting] = ++meetingCertiPointer;
    meetings[meetingIdx].name = mMeeting;
    meetings[meetingIdx].startTime = mStartTime;
    meetings[meetingIdx].endTime = mEndTime;
    meetings[meetingIdx].state = OPENMEETING;
    meetings[meetingIdx].members.clear();

    
    


}

// 회의 취소 : 회의를 취소한다. 취소된 회의는 시스템에서 삭제된다.
int cancelMeeting(char mMeeting[MAXL])
{

}

// 참석자 추가 및 삭제 : 사용자를 참석자 목록에 추가하거나 삭제한다.
int changeMeetingMember(char mMeeting[MAXL], char mMember[MAXL])
{

}

// 회의 시간 변경 : 시작 시간과 종료 시간을 변경한다.
int changeMeeting(char mMeeting[MAXL], int mStartTime, int mEndTime)
{

}

// 회의 찾기 : 특정 시간 후 사용자가 참석하는 가장 먼저 시작되는 회의를 찾는다.
void checkNextMeeting(char mMember[MAXL], int mTime, char mResult[MAXL])
{

}
