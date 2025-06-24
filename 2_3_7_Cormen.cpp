/*
Алгоритм со временем работы O(n*lgn), который для заданногл
множества S из n целых чисел и другого целого числа x определяет,
имеюся ли в множестве S два элемента, сумма которых равна x.
*/
#include <bits/stdc++.h>

using namespace std;

#define sp ' '
#define nl '\n'

void merge(int A[], int p, int q, int r);
void merge_sort(int A[], int p, int r)
{
    int q;
    if(p < r)
    {
        q = (p + r) / 2;
        merge_sort(A, p, q);
        merge_sort(A, q+1, r);
        merge(A, p, q, r);
    } 
}

void merge(int A[], int p, int q, int r)
{
    int i,j,k;
    i = p;
    j = q + 1;
    k = p;

    int merged_list[8];

    while(i <= q && j <= r)
    {
        if(A[i] < A[j])
        {
            merged_list[k] = A[i];
            i++;
        } else {
            merged_list[k] = A[j];
            j++;
        }
        k++;
    }

    while(i <= q)
    {
        merged_list[k] = A[i];
        i++;
        k++;
    }

    while(j <= r) 
    {
        merged_list[k] = A[j];
        j++;
        k++;
    }
    
    for(int i = p; i < k; i++)
    {
        A[i] = merged_list[i];
    }
}


int main()
{  
    int S[8] = {3,41,52,26,38,57,9,49};
    int x; cin >> x;

    // Идея: 1) Отсортировать массив слиянием => O(n*lgn)
    //       2) В отсортированном массиве найти есть ли такая сумма a[i] + a[mid] == x => O(n*lgn)
    // Итог: T(n) = O(n*lgn) + O(n*lgn) = O(2*n*lgn) -> O(n*lgn) 

    // Сортируем исходный массив 
    merge_sort(S, 0, 7);


    // Ищем нужную пару элементов 
    for(int i = 0; i < 8; i++)
    {
        int low = i + 1;
        int high = 7;
        while (low <= high)
        {
            int mid = low + (high - low) / 2;
            if (S[i] + S[mid] == x)
            {
                cout << "YES" << nl;
                cout << S[i] << " + " << S[mid] << " = " << x << nl;
                return 0;
            }
            else if(S[i] + S[mid] < x)
            {
                low = mid + 1;
            }
            else
            {
                high = mid - 1;
            }
        }
    }
    cout << "NO" << nl;

    return 0; 
}
    
