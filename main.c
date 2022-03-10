#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int comp = 0;
int mov = 0;

void funcrandom(long long int* a, int n) {              //��������� ������� � ������������ �������
    for (int i = 0; i < n; i++) {
        a[i] = (long long int)rand() * rand() * rand();
    }
}

void funcright(long long int* a, int n) {               //��������� ���������������� �������
    int sign;
    for (int i = 0; i < n; i++) {
         if (i == 0) {
             a[i] = (long long int)rand() * rand() * rand();
         } else {
             sign = rand() % 2;
             if (!sign) sign = -1;
             a[i] = (long long int)((labs(a[i - 1]) + rand() * rand() % (9223372036854775808u - labs(a[i - 1]))) * sign);
         }
    }
}

void funcback(long long int* a, int n) {                //��������� �������, ���������������� � �������� �������
    int sign;
    for (int i = 0; i < n; i++) {
         if (i == 0) {
             a[i] = (long long int)rand() * rand() * rand();
         } else {
             sign = rand() % 2;
             if (!sign) sign = -1;
             a[i] = (long long int)((labs(a[i - 1]) - (long long int)rand() * rand() % labs(a[i - 1])) * sign);
         }
    }
}

void bubble(long long int* a, int n) {                  //���������� "�������"
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            comp++;
            if (labs(a[j]) > labs(a[j + 1])) {
                mov++;
                a[j] += a[j + 1];
                a[j + 1] = a[j] - a[j + 1];
                a[j] = a[j] - a[j + 1];
            }
        }
    }
}

void heapify(long long int* a, int n, int i) {          //���������� ����(����������� ������������� �������� �����)
    int largest = i;        //������������ �������(������)
    int l = 2 * i + 1;      //������ ������ �������
    int r = 2 * i + 2;      //������ ������� �������
    if (l < n) {                                        //���������� ������������ ������� � ������ �������
        comp++;
        if (labs(a[l]) > labs(a[largest])) largest = l;
    }
    if (r < n) {                                        //���������� ������������ ������� � ������� �������
        comp++;
        if (labs(a[r]) > labs(a[largest])) largest = r;
    }
    if (largest != i) {                                 //������ ������� ������������ ������� � ������(���� ��� �� ���������)
        mov++;
        a[largest] += a[i];
        a[i] = a[largest] - a[i];
        a[largest] = a[largest] - a[i];
        heapify(a, n, largest);
    }
}
void pyramid(long long int* a, int n) {
    for (int i = n / 2 - 1; i >= 0; i--)                //��������� ����
        heapify(a, n, i);
    for (int i = n - 1; i > 0; i--) {                   //������ ������� ������ � ��������� ������� � ���� � ���������� ��� �� ����
        mov++;
        a[0] += a[i];
        a[i] = a[0] - a[i];
        a[0] = a[0] - a[i];
        heapify(a, i, 0);                               //����� ��������� ����(���������� ������ ����)
    }
}

int main(void) {
    srand(time(NULL));
    printf("1.Bubble:\n");                              //���������� "�������" � ����� ������
    for (int n = 10; n <= 10000; n *= 10) {
        printf("  n = %d\n", n);
        long long int* a = calloc(n, sizeof(long long int));
        funcright(a, n);
        bubble(a, n);
        printf("    1.Items are already put in order: %d %d\n", comp, mov);
        comp = 0, mov = 0;
        funcback(a, n);
        bubble(a, n);
        printf("    2.Items are put in reverse order: %d %d\n", comp, mov);
        comp = 0, mov = 0;
        funcrandom(a,n);
        bubble(a, n);
        printf("    3.Items are arranged randomly: %d %d\n", comp, mov);
        comp = 0, mov = 0;
        funcrandom(a,n);
        bubble(a, n);
        printf("    4.Items are arranged randomly: %d %d\n", comp, mov);
        comp = 0, mov = 0;
        free(a);
    }
    printf("2.Pyramidal sorting:\n");                   //������������� ���������� � ����� ������
    for (int n = 10; n <= 10000; n *= 10) {
        printf("  n = %d\n", n);
        long long int* a = calloc(n, sizeof(long long int));
        funcright(a, n);
        pyramid(a, n);
        printf("    1.Items are already put in order: %d %d\n", comp, mov);
        comp = 0, mov = 0;
        funcback(a, n);
        pyramid(a, n);
        printf("    2.Items are put in reverse order: %d %d\n", comp, mov);
        comp = 0, mov = 0;
        funcrandom(a,n);
        pyramid(a, n);
        printf("    3.Items are arranged randomly: %d %d\n", comp, mov);
        comp = 0, mov = 0;
        funcrandom(a,n);
        pyramid(a, n);
        printf("    4.Items are arranged randomly: %d %d\n", comp, mov);
        comp = 0, mov = 0;
        free(a);
    }
    return 0;
}
