#include <iostream>

using namespace std;

struct Node
{
    int parent, left, right;
};

void printPre(int target, Node tree[])
{
    printf("%d ", target);
    if(tree[target].left != 0) printPre(tree[target].left, tree);
    if(tree[target].right != 0) printPre(tree[target].right, tree);

    return;
}

void printIn(int target, Node tree[])
{
    if(tree[target].left != 0) printPre(tree[target].left, tree);
    printf("%d ", target);
    if(tree[target].right != 0) printPre(tree[target].right, tree);

    return;
}

void printPost(int target, Node tree[])
{
    if(tree[target].left != 0) printPre(tree[target].left, tree);
    if(tree[target].right != 0) printPre(tree[target].right, tree);
    printf("%d ", target);

    return;
}

int main(int argc, char** argv)
{
    int V; // 정점의 수
    scanf("%d", &V);

    Node tree[V + 1];
    for(register int i = 0; i <= V; ++i) 
    {
        tree[i].parent = tree[i].left = tree[i].right = 0;
    }

    int parent, child;
    for(register int i = 0; i < V - 1; ++i)
    {
        scanf("%d %d", &parent, &child);
        tree[child].parent = parent;
        if(tree[parent].left == 0) tree[parent].left = child;
        else tree[parent].right = child;
    }

    printPre(1, tree);
    printf("\n");
    printIn(1, tree);
    printf("\n");
    printPost(1, tree);
    printf("\n");

    return 0;
}

