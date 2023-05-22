#include <cstring>
#include <queue>

#define MAX_N 100
#define DEBUG 1

using namespace std;

struct Node
{
    int row, col;
    int energy;

    bool operator<(const Node& n)const
    {
        if (energy == n.energy)
        {
            if (row == n.row) return col > n.col;
            return row > n.row;
        }
        return energy < n.energy;
    }
};

int energy[101][101];
int type[101][101];
bool visited[101][101];
int dr[] = { 1, -1, 0, 0 };
int dc[] = {0, 0, 1, -1};
int N;

priority_queue<Node> pq;
queue<Node> q;
int cnt[3];

void init(int __N, int mDish[MAX_N][MAX_N])
{
    N = __N;
    cnt[1] = cnt[2] = 0;
    // 각 셀에는 에너지 소비량 정보 존재
    // 어네지 소비량 : 해당 셀에서 세균이 생성될 때 필요한 번식 에너지의 소비량
    // 타겟 세균 : 파란 세균, 빨간 세균
    // 번식 에너지 : 약품이 지니고 있는 특수 에너지로 세균 생성에 사용됨
    for (register int i = 0; i < N; ++i)
    {
        for (register int j = 0; j < N; ++j)
        {
            energy[i + 1][j + 1] = mDish[i][j];
            type[i + 1][j + 1] = 0;
            visited[i + 1][i + 1] = false;
        }
    }
}

int dropMedicine(int mTarget, int mRow, int mCol, int mEnergy)
{
    // mTarget : 생성할 세균의 종류
    // mRow : 약품을 추가할 행
    // mCol : 약품을 추가할 열
    // mEnergy : 번식 에너지의 양
    
    // 다른 종류의 세균인 경우
    if (type[mRow][mCol] != mTarget && type[mRow][mCol] != 0)
    {
#if DEBUG
        printf("dropMedicine() result[%d]\n", cnt[mTarget]);
#endif
        return cnt[mTarget];
    }
    // 같은 종류이거나 비어있는 경우
    else
    {
        // 비어있는 경우 에너지 소비량만큼 번식 에너지 소비하고 세균생성
        if (type[mRow][mCol] == 0)
        {
            mEnergy -= energy[mRow][mCol];
            type[mRow][mCol] = mTarget;
            cnt[mTarget]++;
        }
        
        // 번식에너지가 남았으면, 주변 세균 활성화(4방 탐색)
        priority_queue<Node> clearPQ;
        queue<Node> clearQ;
        swap(pq, clearPQ);
        swap(q, clearQ);
        memset(visited, false, sizeof(visited));

        Node n;
        n.row = mRow;
        n.col = mCol;
        q.push(n);
        visited[n.row][n.col] = true;
        
        while (mEnergy > 0)
        {
            // 빈셀 인 경우 pq에 넣고, 같은 종류 세균인 경우 q에 넣고, 다른 세균인 경우 X
            Node nn = q.front();
            q.pop();
            for (register int i = 0; i < 4; ++i)
            {
                int r = nn.row + dr[i];
                int c = nn.col + dc[i];
                if (r < 1 || r > N || c < 1 || c > N || visited[r][c]) continue;

                Node nnn;
                nnn.row = r;
                nnn.col = c;
                nnn.energy = energy[r][c];

                if (type[r][c] == 0)
                {
                    visited[nnn.row][nnn.col] = true;
                    pq.push(nnn);
                }
                else if (type[r][c] == mTarget)
                {
                    q.push(nnn);
                    visited[nnn.row][nnn.col] = true;

                }
            }

            if (q.empty())
            {
                // 번식 가능한 곳이 없으면 종료
                if (pq.empty()) break;
                Node nnnn = pq.top();
                pq.pop();
                mEnergy -= nnnn.energy;
                type[nnnn.row][nnnn.col] = mTarget;
                cnt[mTarget]++;
                // 세균 생성하고 다시 활성화부터 진행
                q.push(nnnn);
                visited[nnnn.row][nnnn.col] = true;
            }
        }
    }

    // 접시 내의 종류가 mTarget인 세균의 총 개수
#if DEBUG
    printf("dropMedicine() result[%d]\n", cnt[mTarget]);
#endif
    return cnt[mTarget];
}

int cleanBacteria(int mRow, int mCol)
{
    // step 03. 번식 종료
    // 활성화된 모든 세균 비활성화
    // 셀이 비어있는 경우 세균이 소멸되지 않고 종료
    // 상하좌우 연결된 같은 종류의 세균을 모두 활성화 시키고 제거
    int mType = type[mRow][mCol];
    if (mType == 0) return -1;

    queue<Node> clearQ;
    swap(q, clearQ);
    memset(visited, false, sizeof(visited));

    Node n;
    n.row = mRow;
    n.col = mCol;
    q.push(n);
    visited[n.row][n.col] = true;
    type[n.row][n.col] = 0;
    cnt[mType]--;

    while(!q.empty())
    {
        Node nn = q.front();
        q.pop();
        for (register int i = 0; i < 4; ++i)
        {
            int r = nn.row + dr[i];
            int c = nn.col + dc[i];
            if (r < 1 || r > N || c < 1 || c > N || visited[r][c]) continue;

            Node nnn;
            nnn.row = r;
            nnn.col = c;

            if (type[r][c] == mType)
            {
                q.push(nnn);
                visited[nnn.row][nnn.col] = true;
                type[r][c] = 0;
                cnt[mType]--;
            }
        }
    }

#if DEBUG
    printf("clean() result[%d]", cnt[mType]);
#endif
    return cnt[mType];
}