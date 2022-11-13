#include<stdio.h>
#include<stdlib.h>
#include<time.h>


#define N 5 // N 个进程 
#define M 3 // M 种资源 用来生成n*m二维数组，Max[i,j] 表示i进程需要多少j资源


int print_one_dim_matrix(int matrix[], const char *a) {
    // 参数a用来传入字符串的地址
    printf("%s A\t B\t C\t\n \t[", a);
    for (int i = 0; i < M; i++) {
        printf(" %d", matrix[i]);
        if (i != 2) {
            printf("\t");
        }
    }
    printf("]\n");

    for (int i = 0; i < 30; i++) {
        printf("-");
    }
    printf("\n");
    return 1;
}

int print_two_dim_matrix(int matrix[N][M], const char *a) {
    printf("%s\n", a);
    printf("进程\t A\t B\t C\t \n");
    for (int i = 0; i < N; i++) {
        printf("  %d\t", i);
        for (int j = 0; j < M; j++) {
            printf(" %d\t", matrix[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < 30; i++) {
        printf("-");
    }
    printf("\n");
    return 1;
}

int main() {
    srand((unsigned int)time(NULL)); 

    // 生成资源最大可用量矩阵Available
    int Available[M];
    for (int i = 0; i < M; i++) {
        Available[i] = (rand() % 10) + 1; // 生成范围[1, 10]
    }

    // 打印资源最大可用数量矩阵Available
    print_one_dim_matrix(Available, "Available");

    // todo 生成最大资源需求矩阵Max
    int Max[N][M];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            Max[i][j] = (rand() % Available[j]) + 1; // 取值范围[1, Available[j]] 
        }
    }

    // 打印进程对资源最大需求矩阵Max
    print_two_dim_matrix(Max, "Max");

    // todo 生成初始分配矩阵
    int Allocation[N][M];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            int temp = rand() % 2;
            if (temp == 1) {
                if (Available[j] > 0) { //若仍有未分配的才进行计算
                    int a = (rand() % Max[i][j]) + 1; // 从Max的范围里取值
                    int temp_check = Available[j] - a;
                    if (temp_check >= 0) {
                        Allocation[i][j] = a; // 如果当前资源仍可用 则分配
                        Available[j] = temp_check; // 分配后资源可用量需要减去分配大小
                    }
                    else {
                        Allocation[i][j] = 0; // 需求太高，无法分配资源，赋0
                    }
                }
                else {
                    Allocation[i][j] = 0; // 无分配 赋0
                }
            }
            else {
                Allocation[i][j] = 0; // 50%的概率直接赋予0
            }
        }
    }

    // 打印进程初始分配矩阵Allocation
    print_two_dim_matrix(Allocation, "Allocation");

    // todo 生成分配矩阵后的需要矩阵Need
    int Need[N][M];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            Need[i][j] = Max[i][j] - Allocation[i][j]; // 仍需求 = 最大需求-已分配
        }
    }
    // 打印进程的需要矩阵Need
    print_two_dim_matrix(Need, "Need");

    // 打印资源目前任然可用的资源Available
    print_one_dim_matrix(Available, "Available");

    int list[N] = {999,999,999,999,999}; // 用于存储进程顺序
    int isDeadlock = 0;
    int p = 0;
    int checkcheck = 1;
    while(checkcheck) {
        for (int i = 0; i < N; i++) {
            if (Need[i][0] <= Available[0] && Need[i][1] <= Available[1] && Need[i][2] <= Available[2] && Need[i][0]!= 999 ) {
                // 满足可还条件时
                printf("\n当前满足条件的进程是：%d\n", i);
                printf("分别对应  A\t B\t C\t \n \t  %d\t %d\t %d\t\n", Allocation[i][0], Allocation[i][1], Allocation[i][2]);
                Available[0] = Allocation[i][0] + Available[0];
                Available[1] = Allocation[i][1] + Available[1];
                Available[2] = Allocation[i][2] + Available[2];
                // printf("当前循环第%d次\n", i);
                print_one_dim_matrix(Available, "Available");
                Need[i][0] = 999; // 将Need第一个需要资源设为999作为标记，跳过满足条件的进程
                for (int j = 0; j < N; j++) {
                    if (list[j] == 999) {
                        list[j] = i;
                        if (list[N - 1] != 999) {
                            printf("find it");
                            checkcheck == 0;
                            break;
                        }
                        break;
                    }
                    
                }
                printf("\n");
                printf("当前列表状态：\n");
                for (int i = 0; i < N; i++) {
                    printf("%d ", list[i]);
                }
                p++;
                break; // 找到了可用的，添加到顺序列表中。 重新循环查找
            }
            else {
                isDeadlock++;
                if (isDeadlock > 6) {
                    checkcheck = 0; //while循环结束
                }
            }

        }
    }
    if (list[N - 1] == 999) {
        printf("\nDeadlock\n");
    }

    return 0;


}// main end

