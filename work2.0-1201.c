#include <stdio.h>
#include <stdlib.h>

// 函数指针类型
typedef int (*compare_fn)(int, int);

// 函数声明
void traverse(int *a, int n);
int sum(int *a, int n);
int *reverse(int *a, int n);
int *slice(int *a, int n, int start, int end, int *outLen);
int *subarray(int *a, int n, int start, int num, int *outLen);
int findIndex(int *a, int n, int target);
int findLastIndex(int *a, int n, int target);
int max(int *a, int n);
int every(int *a, int n, int target, compare_fn cmp);
int some(int *a, int n, int target, compare_fn cmp);

// 比较函数
int compare_equal(int a, int b) { return a == b; }
int compare_greater_than(int a, int b) { return a > b; }
int compare_less_than(int a, int b) { return a < b; }

int main()
{
    int example[] = {11, 16, 24, 53, 16, 15, 21};
    int n = sizeof(example) / sizeof(example[0]);
    int subN = 7;

    printf("原数组：");
    traverse(example, n);
    int total = sum(example, n);
    printf("结果为：");
    printf("%d", total);
    printf("\n\n");

    printf("原数组：");
    traverse(example, n);
    int *p = reverse(example, n);
    printf("排序后：");
    traverse(p, n);
    printf("\n");

    printf("原数组：");
    traverse(example, n);
    int *p1 = slice(example, n, 1, 5, &n);
    printf("切片后：");
    traverse(p1, n);
    printf("\n");

    printf("原数组：");
    traverse(example, subN);
    int *p2 = subarray(example, subN, 2, 3, &n);
    printf("切片后：");
    traverse(p2, n);
    printf("\n");

    printf("原数组：");
    traverse(example, subN);
    int x = findIndex(example, subN, 16);
    if (x != -1)
    {
        printf("元素%d的首个下标为：%d\n", example[x], x);
    }
    else
    {
        printf("该元素不存在该数组\n");
    }
    printf("\n");

    printf("原数组：");
    traverse(example, subN);
    int y = findLastIndex(example, subN, 16);
    if (y != -1)
    {
        printf("元素%d的最后下标为：%d\n", example[y], y);
    }
    else
    {
        printf("该元素不存在该数组\n");
    }
    printf("\n");

    printf("原数组：");
    traverse(example, subN);
    int z = max(example, subN);
    printf("原数组中最大值为：%d\n", z);
    printf("\n");

    if (every(example, n, 16, compare_equal))
        printf("所有元素都等于 16\n");
    else
        printf("并非所有元素都等于 16\n");

    printf("\n");

    if (some(example, n, 20, compare_less_than))
        printf("存在小于目标值 20 的元素\n");
    else
        printf("没有找到符合条件的元素小于20\n");

    return 0;
}

/*====实现====*/

void traverse(int *a, int n)
{
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n");
}

int *reverse(int *a, int n)
{
    int *as = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) as[i] = a[n - i - 1];
    return as;
}

int sum(int *a, int n)
{
    int total = 0;
    for (int i = 0; i < n; i++) total += a[i];
    return total;
}

int *slice(int *a, int n, int start, int end, int *outLen)
{
    if (start < 0 || end < 0 || start > end || start > n)
    {
        printf("slice:非法参数\n");
        return NULL;
    }
    if (end <= n) *outLen = end - start;
    else *outLen = n - start;

    int *p = malloc(sizeof(int) * (*outLen));
    for (int i = 0; i < *outLen; i++) p[i] = a[i + start];
    return p;
}

int *subarray(int *a, int n, int start, int num, int *newLen)
{
    if (start < 0 || num <= 0 || start >= n)
    {
        printf("subarray:非法参数\n");
        return NULL;
    }
    if (start + num > n) *newLen = n - start;
    else *newLen = num;

    int *ph = malloc(sizeof(int) * (*newLen));
    for (int i = 0; i < *newLen; i++) ph[i] = a[i + start];
    return ph;
}

int findIndex(int *a, int n, int target)
{
    for (int i = 0; i < n; i++) if (a[i] == target) return i;
    return -1;
}

int findLastIndex(int *a, int n, int target)
{
    for (int i = n - 1; i >= 0; i--) if (a[i] == target) return i;
    return -1;
}

int max(int *a, int n)
{
    if (n == 0) return -1;
    int max = a[0];
    for (int i = 1; i < n; i++) if (a[i] > max) max = a[i];
    return max;
}

int every(int *a, int n, int target, compare_fn cmp)
{
    for (int i = 0; i < n; i++) if (!cmp(a[i], target)) return 0;
    return 1;
}

int some(int *a, int n, int target, compare_fn cmp)
{
    for (int i = 0; i < n; i++) if (cmp(a[i], target)) return 1;
    return 0;
}