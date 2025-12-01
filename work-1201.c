#include <stdio.h>
#include <stdlib.h>

/*-------------------- 工具函数声明 --------------------*/
void traverse(const int *arr, int len);          // 打印数组
int sum(const int *arr, int len);                // 求和
int *reverse(const int *arr, int len);           // 反转数组（新内存）
int *slice(const int *arr, int len, int start, int end, int *out_len); // 切片
int *subarray(const int *arr, int len, int start, int num, int *out_len); // 子数组
int find_index(const int *arr, int len, int target);      // 首次出现下标
int find_last_index(const int *arr, int len, int target); // 最后一次出现下标
int max_value(const int *arr, int len);                   // 最大值
int every(const int *arr, int len, int target, int mode); // 是否“全部”满足关系
int some(const int *arr, int len, int target, int mode);  // 是否“存在”满足关系

/* 关系模式常量，让 every/some 语义清晰 */
enum {
    MODE_LT = 1, /* < */
    MODE_GT,     /* > */
    MODE_EQ      /* == */
};

/*-------------------- 主函数 --------------------*/
int main(void)
{
    int arr[] = {11, 16, 24, 53, 16, 15, 21};
    int len = sizeof(arr) / sizeof(arr[0]);

    /*---- 1. 遍历 + 求和 ----*/
    printf("【原数组】");
    traverse(arr, len);
    printf("数组之和：%d\n\n", sum(arr, len));

    /*---- 2. 反转 ----*/
    int *rev = reverse(arr, len);
    printf("【反转后】");
    traverse(rev, len);
    putchar('\n');

    /*---- 3. 切片：下标 [1..5) ----*/
    int slice_len;
    int *sli = slice(arr, len, 1, 5, &slice_len);
    printf("【切片[1..5)】");
    traverse(sli, slice_len);
    putchar('\n');

    /*---- 4. 子数组：从下标 2 开始取 3 个 ----*/
    int sub_len;
    int *sub = subarray(arr, len, 2, 3, &sub_len);
    printf("【子数组[2开始取3个]】");
    traverse(sub, sub_len);
    putchar('\n');

    /*---- 5. 查找 16 首次/末次出现 ----*/
    int first = find_index(arr, len, 16);
    int last  = find_last_index(arr, len, 16);
    printf("16 首次下标：%d，末次下标：%d\n\n", first, last);

    /*---- 6. 最大值 ----*/
    printf("数组最大值：%d\n\n", max_value(arr, len));

    /*---- 7. 全部/存在 判断 ----*/
    printf("是否“全部元素 == 16”？ %s\n",
           every(arr, len, 16, MODE_EQ) ? "true" : "false");
    printf("是否“存在元素 < 25”？  %s\n",
           some(arr, len, 25, MODE_LT) ? "true" : "false");

    /*---- 8. 释放动态内存 ----*/
    free(rev);
    free(sli);
    free(sub);
    return 0;
}

/*-------------------- 工具函数实现 --------------------*/
void traverse(const int *arr, int len)
{
    for (int i = 0; i < len; ++i) printf("%d ", arr[i]);
    putchar('\n');
}

int sum(const int *arr, int len)
{
    int s = 0;
    for (int i = 0; i < len; ++i) s += arr[i];
    return s;
}

int *reverse(const int *arr, int len)
{
    int *r = malloc(sizeof(int) * len);
    for (int i = 0; i < len; ++i) r[i] = arr[len - 1 - i];
    return r;
}

int *slice(const int *arr, int len, int start, int end, int *out_len)
{
    if (start < 0 || end < 0 || start > end || start > len) {
        printf("slice: 非法参数\n");
        *out_len = 0;
        return NULL;
    }
    if (end > len) end = len;
    *out_len = end - start;
    int *s = malloc(sizeof(int) * (*out_len));
    for (int i = 0; i < *out_len; ++i) s[i] = arr[start + i];
    return s;
}

int *subarray(const int *arr, int len, int start, int num, int *out_len)
{
    if (start < 0 || num <= 0 || start >= len) {
        printf("subarray: 非法参数\n");
        *out_len = 0;
        return NULL;
    }
    int avail = len - start;
    *out_len = (num > avail ? avail : num);
    int *s = malloc(sizeof(int) * (*out_len));
    for (int i = 0; i < *out_len; ++i) s[i] = arr[start + i];
    return s;
}

int find_index(const int *arr, int len, int target)
{
    for (int i = 0; i < len; ++i)
        if (arr[i] == target) return i;
    return -1;
}

int find_last_index(const int *arr, int len, int target)
{
    for (int i = len - 1; i >= 0; --i)
        if (arr[i] == target) return i;
    return -1;
}

int max_value(const int *arr, int len)
{
    if (len == 0) return -1;
    int m = arr[0];
    for (int i = 1; i < len; ++i)
        if (arr[i] > m) m = arr[i];
    return m;
}

int every(const int *arr, int len, int target, int mode)
{
    for (int i = 0; i < len; ++i) {
        int ok = 0;
        switch (mode) {
            case MODE_LT: ok = arr[i] <  target; break;
            case MODE_GT: ok = arr[i] >  target; break;
            case MODE_EQ: ok = arr[i] == target; break;
        }
        if (!ok) return 0;   /* 发现一个不满足即可返回 */
    }
    return 1; /* 全部满足 */
}

int some(const int *arr, int len, int target, int mode)
{
    for (int i = 0; i < len; ++i) {
        int ok = 0;
        switch (mode) {
            case MODE_LT: ok = arr[i] <  target; break;
            case MODE_GT: ok = arr[i] >  target; break;
            case MODE_EQ: ok = arr[i] == target; break;
        }
        if (ok) return 1;   /* 发现一个满足即可返回 */
    }
    return 0; /* 一个都没找到 */
}