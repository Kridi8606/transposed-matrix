#include <iostream>
#include <stdexcept>
#include <limits>
#include <new>

using namespace std;

int **concat_rows(
    const int * const *lhs, size_t n1, size_t m1,
    const int * const *rhs, size_t n2, size_t m2
);
int **read_matrix(size_t n, size_t m);
void show_concat_result(
    int **a, size_t n1, size_t m1,
    size_t n2, size_t m2
);

void size_t_sum_check(size_t n1, size_t n2);
template<typename T> void nullptr_check(const T *a);

void free_matrix(int **a, size_t n);

int main()
{
    size_t n1 = 0, m1 = 0, n2 = 0, m2 = 0;
    int **lhs = nullptr;
    int **rhs = nullptr;
    int **res = nullptr;

    try
    {
        if (!(cin >> n1 >> m1 >> n2 >> m2) ||
            n1 == 0 || m1 == 0 || n2 == 0 || m2 == 0)
        {
            throw invalid_argument("Input error!");
        }

        lhs = read_matrix(n1, m1);
        rhs = read_matrix(n2, m2);

        res = concat_rows(lhs, n1, m1, rhs, n2, m2);
        show_concat_result(res, n1, m1, n2, m2);
    }
    catch (const bad_alloc &e)
    {
        cerr << "Memory allocation error: " << e.what() << '\n';
        free_matrix(res, n1 > n2 ? n1 : n2);
        free_matrix(lhs, n1);
        free_matrix(rhs, n2);
        return 2;
    }
    catch (const exception &e)
    {
        cerr << e.what() << '\n';
        free_matrix(res, n1 > n2 ? n1 : n2);
        free_matrix(lhs, n1);
        free_matrix(rhs, n2);
        return 1;
    }

    free_matrix(res, n1 > n2 ? n1 : n2);
    free_matrix(lhs, n1);
    free_matrix(rhs, n2);

    return 0;
}

int **concat_rows(
    const int * const *lhs, size_t n1, size_t m1,
    const int * const *rhs, size_t n2, size_t m2
)
{
    nullptr_check(lhs);
    nullptr_check(rhs);
    for (size_t i = 0; i < n1; i++)
    {
        nullptr_check(lhs[i]);
    }
    for (size_t i = 0; i < n2; i++)
    {
        nullptr_check(rhs[i]);
    }

    const size_t n = (n1 > n2) ? n1 : n2;
    int **res = nullptr;

    try
    {
        res = new int*[n]{};

        for (size_t i = 0; i < n; i++)
        {
            size_t len;

            if (i < n1 && i < n2)
            {
                size_t_sum_check(m1, m2);
                len = m1 + m2;
            }
            else if (i < n1)
            {
                len = m1;
            }
            else
            {
                len = m2;
            }

            res[i] = new int[len];
            size_t pos = 0;

            if (i < n1)
            {
                nullptr_check(lhs[i]);
                for (size_t j = 0; j < m1; j++)
                    res[i][pos++] = lhs[i][j];
            }

            if (i < n2)
            {
                nullptr_check(rhs[i]);
                for (size_t j = 0; j < m2; j++)
                    res[i][pos++] = rhs[i][j];
            }
        }
    }
    catch (...)
    {
        free_matrix(res, n);
        throw;
    }

    return res;
}

int **read_matrix(size_t n, size_t m)
{
    int **a = nullptr;

    try
    {
        a = new int*[n]{};

        for (size_t i = 0; i < n; i++)
        {
            a[i] = new int[m];

            for (size_t j = 0; j < m; j++)
            {
                if (!(cin >> a[i][j]))
                    throw invalid_argument("Input error!");
            }
        }
    }
    catch (...)
    {
        free_matrix(a, n);
        throw;
    }

    return a;
}

void show_concat_result(
    int **a, size_t n1, size_t m1,
    size_t n2, size_t m2
)
{
    cout << '\n';
    const size_t n = (n1 > n2) ? n1 : n2;

    for (size_t i = 0; i < n; i++)
    {
        size_t len;

        if (i < n1 && i < n2)
            len = m1 + m2;
        else if (i < n1)
            len = m1;
        else
            len = m2;

        for (size_t j = 0; j < len; j++)
            cout << a[i][j] << ' ';

        cout << '\n';
    }
}

void free_matrix(int **a, size_t n)
{
    if (a == nullptr)
        return;

    for (size_t i = 0; i < n; i++)
        delete[] a[i];

    delete[] a;
}

void size_t_sum_check(size_t n1, size_t n2)
{
    if (numeric_limits<size_t>::max() - n1 < n2)
        throw invalid_argument("Too large! Baka");
}

template<typename T>
void nullptr_check(const T *a)
{
    if (a == nullptr)
        throw invalid_argument("Null-po! Gah!..");
}
