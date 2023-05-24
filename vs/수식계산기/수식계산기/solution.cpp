#include <cstring>
#include <unordered_map>

using namespace std;

#define DEBUG 1
#define MAX_LEN 200

// exp를 저장할 자료구조
// Point. 주어진 수식과 같은 수식들을 찾아야함

enum 
{
    AA = 0,
    BB,
    CC,
    AB,
    BC,
    CA,
    A,
    B,
    C,
    NUM
};

struct Expression
{
    int type[10] = { 0, };

    void set(int idx, int value)
    {
        memset(type, 0, sizeof(type));
        type[idx] = value;
    }

    int getRealValue()
    {
        int cntA = (type[AA] || type[AB] || type[CA] || type[A]) ? 1 : 0;
        int cntB = (type[BB] || type[AB] || type[BC] || type[B]) ? 1 : 0;
        int cntC = (type[CC] || type[BC] || type[CA] || type[C]) ? 1 : 0;

        return cntA + cntB + cntC;
    }

    int calcABC(int a, int b, int c)
    {
        return (type[AA] * a * a) + (type[BB] * b * b) + (type[CC] * c * c)
            + (type[AB] * a * b) + (type[BC] * b * c) + (type[CA] * c * a)
            + (type[A] * a) + (type[B] * b) + (type[C] * c) + type[NUM];
    }

    void operator+=(const Expression& e) {
        for (int i = 0; i < 10; i++)
            type[i] += e.type[i];
    }
    void operator-=(const Expression& e) {
        for (int i = 0; i < 10; i++)
            type[i] -= e.type[i];
    }
    void operator*=(const Expression& e) {
        type[AA] = type[A] * e.type[A];
        type[BB] = type[B] * e.type[B];
        type[CC] = type[C] * e.type[C];
        type[AB] = type[A] * e.type[B] + type[B] * e.type[A];
        type[BC] = type[B] * e.type[C] + type[C] * e.type[B];
        type[CA] = type[C] * e.type[A] + type[A] * e.type[C];
        type[A] = type[A] * e.type[NUM] + type[NUM] * e.type[A];
        type[B] = type[B] * e.type[NUM] + type[NUM] * e.type[B];
        type[C] = type[C] * e.type[NUM] + type[NUM] * e.type[C];
        type[NUM] = type[NUM] * e.type[NUM];
    }

}id2Exp[5001], stack[201];

char operationStack[200];
int cnt;
int stackTop, operationTop;

struct Hash
{
    unsigned long long operator()(const Expression& e) const
    {
        return e.type[NUM];
    }
};

struct Equal
{
    bool operator()(const Expression& e1, const Expression& e2) const
    {
        return memcmp(e1.type, e2.type, sizeof(e1.type)) == 0;
    }
};

unordered_map<Expression, int, Hash, Equal> expMap;

void init()
{
    expMap.clear();
    cnt = 0;
}

void calc()
{
    if (operationStack[operationTop] == '+') stack[stackTop - 1] += stack[stackTop];
    else if (operationStack[operationTop] == '-') stack[stackTop - 1] -= stack[stackTop];
    else if (operationStack[operationTop] == '*') stack[stackTop - 1] *= stack[stackTop];
    else return;

    --stackTop;
    --operationTop;
}

int addExpression(int mID, char mExpression[MAX_LEN + 1])
{
    stackTop = operationTop = 0;
    stack[stackTop].set(9, 0);

    register int i = 0;
    while (mExpression[i] != '\0')
    {
        // 1 ~ 5
        if (mExpression[i] > 48 && mExpression[i] < 54)
        {
            stack[++stackTop].set(9, mExpression[i] - '0');
            if (operationStack[operationTop] == '*') calc();
        }
        // A, B, C
        else if (mExpression[i] == 'A' || mExpression[i] == 'B' || mExpression[i] == 'C')
        {
            stack[++stackTop].set(mExpression[i] - 59, 1);
            if (operationStack[operationTop] == '*') calc();
        }
        // +, -, (, ), *
        else
        {
            if (mExpression[i] == '+' || mExpression[i] == '-')
            {
                if (operationTop) calc();
                operationStack[++operationTop] = mExpression[i];
            }
            else if (mExpression[i] == ')')
            {
                calc();
                --operationTop;
                if (operationStack[operationTop] == '*') calc();
            }
            else
            {
                operationStack[++operationTop] = mExpression[i];
            }
        }

        ++i;
    }

    if (operationTop) calc();

    id2Exp[mID] = stack[stackTop];
    auto iter = expMap.insert({ stack[stackTop], 0 }).first;
    iter->second++;

    if (iter->second == 1)
    {
#if DEBUG
        printf("add() result[%d]\n", id2Exp[mID].getRealValue() * -1);
#endif
        return id2Exp[mID].getRealValue() * -1;
    }
#if DEBUG
    printf("add() result[%d]\n", iter->second - 1);
#endif
    return iter->second - 1;
}

int calcExpression(int mID, int mA, int mB, int mC)
{
#if DEBUG
    printf("calc() result[%d]\n", id2Exp[mID].calcABC(mA, mB, mC));
#endif
    return id2Exp[mID].calcABC(mA, mB, mC);
}