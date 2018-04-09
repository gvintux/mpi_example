#include <iostream>
#include <iomanip>
#include <cfloat>
#include <mpi.h>

using namespace std;

typedef double (*integrable)(double);

static double parabola(double x)
{ return x * x; }

typedef struct
{
    unsigned long long bstep;
    unsigned long long estep;
    double h;
    double a;
    double b;
    integrable f;
    double result;
} integration_args;

typedef enum
{
    TASK_UNKNOW, TASK_FINISHED
} TASK_TYPE;

int main(int argc, char *argv[])
{
    int rank, size;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    const unsigned long long steps = 100000000;
    double a = 0;
    double b = 1;
    double h = (b - a) / (steps * 1.0);
    double sum = 0;
    integrable f = parabola;
	if (!size) size++;
    unsigned int steps_per_thread = steps / (size - 1);
    if (rank != 0)
    {
        unsigned long long bstep = (rank - 1) * steps_per_thread;
        unsigned long long estep = bstep + steps_per_thread;
        double result = 0;
        for (unsigned long long i = bstep; i < estep; i++)
        {
            double x = a + i * h;
            result += h * f(x);
        }
        MPI_Send(&result, 1, MPI_DOUBLE, 0, TASK_FINISHED, MPI_COMM_WORLD);
    } else
    {
        double sum = 0;
        MPI_Status status;
        clock_t begin = clock();
        for (int i = 1; i < size; i++)
        {
            double result;
            MPI_Recv(&result, 1, MPI_DOUBLE, i, TASK_FINISHED, MPI_COMM_WORLD, &status);
            sum += result;
        }
        clock_t end = clock();
        cout << fixed << setprecision(DBL_DIG) << sum << endl;
        cout << fixed << setprecision(DBL_DIG) << double(end - begin) / (1.0 * CLOCKS_PER_SEC) << " seconds." << endl;
    }
    MPI_Finalize();
    return 0;
}
