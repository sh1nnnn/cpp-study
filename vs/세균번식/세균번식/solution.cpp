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
    // �� ������ ������ �Һ� ���� ����
    // ����� �Һ� : �ش� ������ ������ ������ �� �ʿ��� ���� �������� �Һ�
    // Ÿ�� ���� : �Ķ� ����, ���� ����
    // ���� ������ : ��ǰ�� ���ϰ� �ִ� Ư�� �������� ���� ������ ����
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
    // mTarget : ������ ������ ����
    // mRow : ��ǰ�� �߰��� ��
    // mCol : ��ǰ�� �߰��� ��
    // mEnergy : ���� �������� ��
    
    // �ٸ� ������ ������ ���
    if (type[mRow][mCol] != mTarget && type[mRow][mCol] != 0)
    {
#if DEBUG
        printf("dropMedicine() result[%d]\n", cnt[mTarget]);
#endif
        return cnt[mTarget];
    }
    // ���� �����̰ų� ����ִ� ���
    else
    {
        // ����ִ� ��� ������ �Һ񷮸�ŭ ���� ������ �Һ��ϰ� ���ջ���
        if (type[mRow][mCol] == 0)
        {
            mEnergy -= energy[mRow][mCol];
            type[mRow][mCol] = mTarget;
            cnt[mTarget]++;
        }
        
        // ���Ŀ������� ��������, �ֺ� ���� Ȱ��ȭ(4�� Ž��)
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
            // �� �� ��� pq�� �ְ�, ���� ���� ������ ��� q�� �ְ�, �ٸ� ������ ��� X
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
                // ���� ������ ���� ������ ����
                if (pq.empty()) break;
                Node nnnn = pq.top();
                pq.pop();
                mEnergy -= nnnn.energy;
                type[nnnn.row][nnnn.col] = mTarget;
                cnt[mTarget]++;
                // ���� �����ϰ� �ٽ� Ȱ��ȭ���� ����
                q.push(nnnn);
                visited[nnnn.row][nnnn.col] = true;
            }
        }
    }

    // ���� ���� ������ mTarget�� ������ �� ����
#if DEBUG
    printf("dropMedicine() result[%d]\n", cnt[mTarget]);
#endif
    return cnt[mTarget];
}

int cleanBacteria(int mRow, int mCol)
{
    // step 03. ���� ����
    // Ȱ��ȭ�� ��� ���� ��Ȱ��ȭ
    // ���� ����ִ� ��� ������ �Ҹ���� �ʰ� ����
    // �����¿� ����� ���� ������ ������ ��� Ȱ��ȭ ��Ű�� ����
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