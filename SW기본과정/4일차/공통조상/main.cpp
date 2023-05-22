#include<iostream>
#include<stdio.h>

using namespace std;

constexpr int MAXSIZE = 10000;
struct Node
{
    int parent;
    int left, right;
}nodes[MAXSIZE];
bool visited[MAXSIZE];

int DFS(int target)
{
    int answer = 1;

    if(nodes[target].left != 0) answer += DFS(nodes[target].left);
    if(nodes[target].right != 0) answer += DFS(nodes[target].right);

    return answer;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
    freopen("input.txt", "r", stdin);
	cin>>T;

    for(test_case = 1; test_case <= T; ++test_case)
	{

        int V; // 정점의 개수 (10 <= V <= 10000)
        int E; // 간선의 개수
        int T1, T2; // 공통 조상을 찾는 두개의 정점 번호
        scanf("%d %d %d %d", &V, &E, &T1, &T2);

        // init
        // TODO check V range
        for (register int i = 0; i < V; ++i)
        {
            nodes[i].parent = nodes[i].left = nodes[i].right = 0;
            visited[i] = false;
        }

        for (register int i = 0; i < E; ++i)
        {
            int parent, child;
            scanf("%d %d", &parent, &child);
            // cin >> parent >> child;
            nodes[child].parent = parent;
            if(nodes[parent].left == 0) nodes[parent].left = child;
            else nodes[parent].right = child;
        }

        // 타겟 노드 공동 부모 찾기
        int tmp = T1;
        visited[tmp] = true;
        while(tmp != 1)
        {
            tmp = nodes[tmp].parent;
            visited[tmp] = true;
        }

        tmp = T2;
        while(!visited[tmp])
        {
            tmp = nodes[tmp].parent;
        }

        printf("#%d %d %d\n", test_case, tmp, DFS(tmp));
    }
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}

