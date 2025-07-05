/*
Алгоритм для подсчета кол-ва инверсий в заданной n-элементоной перестановке из целых чисел.
Реазицован путём модификации алгоритма сортировки слиянием.

T(n) = O(n*lgn)
*/
#include <bits/stdc++.h>

using namespace std;

#define IOS ios_base::sync_with_stdio(false); cin.tie(NULL)
#define sp ' '
#define nl '\n'

using ll = int64_t;

int cnt_inv(int a[], int start, int end);
int merge_inv(int a[], int start, int end, int mid);

int main(){
    IOS;
    int A[5] = {5,4,3,2,1};

    // Вывод исходного массива 

    for(int i = 0; i < 5; i++)
    {
        cout << A[i] << sp;
    }
    cout << nl;

    // Сортировка слиянием + подсчет кол-ва инверсий за O(n*lgn)
    int inversions = cnt_inv(A, 0, 4);

    // Вывод отсортиваронного массива 

    for(int i = 0; i < 5; i++)
    {
        cout << A[i] << sp;
    }
    cout << nl;


    cout <<  "Колво инверсий в А = " << inversions << nl;
    return 0;
}

int cnt_inv(int A[], int start, int end)
{
    int mid;
    if(start < end)
    {
        mid = (start + end) / 2;
        return cnt_inv(A, start, mid) + cnt_inv(A, mid + 1, end) + merge_inv(A, start, end, mid);
    }
    return 0;
}
int merge_inv(int A[], int start, int end, int mid)
{
    int range = mid + 1;
    int merged_list[5];
    int i,j,k;
    i = start;
    j = mid + 1;
    k = start;

    int inversions = 0;

    while(i <= mid && j <= end)
    {
        if(A[i] <= A[j]) 
        {
            merged_list[k] = A[i];
            i++;
        }
        else
        {
            // Идея
            /*
            Используем тот факт, что левый и правый подмассивы уже отсортированы
            
            Обозначим:
            r_j - текущий элемент из правого подмассива, который сравнивается с эл-ом из левого 
            l_i - элемент из левого подмассива, с которым сравнивается r_j.

            Принцип:
            Если r_j < l_i, то он меньше и всех идущих за l_i, т.е. r_j < l_i ... l_r(l_r - последний элемент в правом подмассиве). Это верно, так как левый и правы подмассивы уже были отсортированы
            Следовательно кол-во инверсии для текущего r_j равно (длина левого подмассива - i), где i - позиция l_i в левом подмассиве
            */
            inversions += range - i; 
            merged_list[k] = A[j];
            j++;
        }
        k++;
    }
    
    while(i <= mid)
    {
        merged_list[k] = A[i];
        i++;
        k++;
    }

    while(j <= end)
    {
        merged_list[k] = A[j];
        j++;
        k++;
    }

    for(int i = start; i < k; i++)
    {
        A[i] = merged_list[i];
    }

    return inversions;
}