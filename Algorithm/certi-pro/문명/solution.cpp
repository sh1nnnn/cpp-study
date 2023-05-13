#include <iostream>
#include <unordered_map>
#include <list>

#define MAX_MAP 1002
#define MAX_IDX 60001

using namespace std;

int dr[] = {0, 0, 1, -1};
int dc[] = {1, -1, 0, 0};

int map[MAX_MAP][MAX_MAP];
unordered_map<int, int> id2idx;
int idx2id[MAX_IDX];
list<pair<int, int>> pos[MAX_IDX];
int idx = 0;

void init(int N)
{
    for(register int r = 0; r < N; ++r)
    {
        for(register int c = 0; c < N; ++c)
        {
            map[r][c] = 0;
        }
    }

    id2idx.clear();
    for(register int i = 0; i < idx; ++i)
    {
        pos[i].clear();
        idx2id[i] = 0;
    }

    idx = 0;
}

int newCivilization(int r, int c, int mID)
{
    unordered_map<int, int> civilizationCheck;
    int ret = 0;

    int mapCheck = 0;    
    for(register int d = 0; d < 4; ++d)
    {
        mapCheck = map[r + dr[d]][c + dc[d]]; 
        if(mapCheck != 0)
        {
            ++civilizationCheck[mapCheck];
        }
    }

    // 새 문명 건설
    if(civilizationCheck.empty())
    {
        ++idx;
        idx2id[idx] = mID;
        id2idx[mID] = idx;

        map[r][c] = idx;
        pos[idx].push_back(make_pair(r, c));

        ret = mID;
    }
    // 기존 문명에 병합
    else
    {
        int minIdx = MAX_IDX + 1;
        int maxCnt = 0;

        for(auto civil : civilizationCheck)
        {
            if(civil.second > maxCnt)
            {
                minIdx = civil.first;
                maxCnt = civil.second;
            }
            else if(civil.second == maxCnt)
            {
                if(idx2id[minIdx] > idx2id[civil.first])
                {
                    minIdx = civil.first;
                    maxCnt = civil.second;
                }
            }
        }

        map[r][c] = minIdx;
        pos[minIdx].push_back(make_pair(r, c));
        ret = idx2id[minIdx];
    }

    return ret;
}

int removeCivilization(int mID)
{
    int targetIdx = 0;
    targetIdx = id2idx[mID];

    // 이미 사라진 문명인지 체크 사라진 경우 or 존재하지 않는 경우 0 리턴
    if(pos[targetIdx].empty())
    {
        return 0;
    }

    // 문명이 존재하는 경우 점유하고 있는 땅의 개수 리턴
    // 해당 문명이 소유하고 있는 모든 땅 -> 빈땅 처리
    int cnt = 0;
    for(auto deleteRC : pos[targetIdx])
    {
        ++cnt;
        map[deleteRC.first][deleteRC.second] = 0;
    }

    pos[targetIdx].clear();
    id2idx[mID] = 0;
    idx2id[targetIdx] = 0;

    return cnt;
}

int getCivilization(int r, int c)
{
    int targetIdx = map[r][c];

    // 어느 문명도 점유하지 않은 경우 0 리턴
    if(targetIdx == 0)
    {
        return 0;
    }

    // 해당 땅을 점유하고 있는 문명의 고유 번호 리턴
    return idx2id[targetIdx];
}

int getCivilizationArea(int mID)
{
    int targetIdx = 0;
    targetIdx = id2idx[mID];
    // 문명 mID가 존재하지 않는 경우 0 리턴
    if(pos[targetIdx].empty())
    {
        return 0;
    }

    // mID가 점유하고 있는 땅의 개수 리턴
    return pos[targetIdx].size();
}

int mergeCivilization(int mID1, int mID2)
{
    // mID2 -> mID1 머지
    // 머지 후 mID1 이 소유한 땅 개수 리턴
    int mIdx1 = id2idx[mID1];
    int mIdx2 = id2idx[mID2];

    if(pos[mIdx1].size() >= pos[mIdx2].size())
    {
        for(auto position : pos[mIdx2])
        {
            map[position.first][position.second] = mIdx1;
        }

        pos[mIdx1].splice(pos[mIdx1].begin(), pos[mIdx2]);
        id2idx[mID2] = 0;
    }
    else
    {
        for(auto position : pos[mIdx1])
        {
            map[position.first][position.second] = mIdx2;
        }

        pos[mIdx2].splice(pos[mIdx2].begin(), pos[mIdx1]);
        id2idx[mID1] = mIdx2;
        idx2id[mIdx2] = mID1;
        id2idx[mID2] = 0;
    }

    // for(auto mergeRC : pos[mIdx2])
    // {
    //     map[mergeRC.first][mergeRC.second] = mIdx1;
    //     pos[mIdx1].push_back(mergeRC);
    // }


    // pos[mIdx2].clear();
    // id2idx[mID2] = 0;
    // idx2id[mIdx2] = 0;

    return pos[id2idx[mID1]].size();
}