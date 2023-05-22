#include<iostream>
#include<stdio.h>

using namespace std;

struct Node
{
    int parent, left, right;
    char str;
}tree[100];

char answer[100];
int answerIdx;

void getStr(int idx)
{
    if(tree[idx].left != 0) getStr(tree[idx].left);
    // printf("%c", tree[idx].str);
    answer[answerIdx++] = tree[idx].str;
    if(tree[idx].right != 0) getStr(tree[idx].right);
}

int main(int argc, char** argv)
{
	int test_case;
	freopen("input.txt", "r", stdin);
	for(test_case = 1; test_case <= 10; ++test_case)
	{
        int N; // 정점의 수
        scanf("%d", &N);

        for (register int i = 0; i <= N; ++i)
        {
            tree[i].parent = tree[i].left = tree[i].right = 0;
            tree[i].str = '\0';
            answer[i] = '\0';
        }
        answerIdx = 0;

        int parent, left, right;
        char str;
        for (register int i = 0 ; i < N ; ++i)
        {
            scanf("%d %c", &parent, &str);
            tree[parent].str = str;
            if(cin.get() != '\n') 
            {
                scanf("%d", &tree[parent].left);
                if(cin.get() != '\n') scanf("%d", &tree[parent].right);
            }
        }

        getStr(1);

        printf("#%d", test_case);
        for(register int i = 0; i < answerIdx; ++i) printf("%c", answer[i]);
        printf("\n");
    }
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}