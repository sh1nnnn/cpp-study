// N명의 토너먼트 선수 (4 <= N <= 131,072)
// N은 2의 거듭제곱으로 주어짐 (N = 2^M, 2 <= M <= 17)
// M=2 -> 4판
// M=3 -> 12판
// M=4 -> 

// N : 토너먼트에 참가한 선수들의 수
// mOrder : 토너먼트 대진표 리스트
// mOrder[0] 가장 왼쪽 선수, mOrder[N - 1] 가장 오른쪽 선수
void modifyTournament(int N, int mOrder[])
{
    // mOrder copy -> rebase
    // halfIndex 잡고 pair 대진 잡아주기
    int rebase[N] = {};
    int halfIndex = N/2;

    // pair <N/2이하 랭커, N/2 초과 랭커>
    while(true)
    {
        for(int i = 0; i < N; i += 2)
        {
            // 위너 루저 인덱스 잡기
            // 
        }
    }
    


}

// mIndexA, B : 대진표에서 변경할 두 선수의 mOrder[] 인덱스
extern void swapOrder(int mIndexA, int mIndexB);