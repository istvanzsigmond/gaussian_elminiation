#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void loadMatrix(FILE *infile, double *mat, int rows, int cols) {

    int i,j;

    for( j = 0; j < rows; j++) {

        for( i = 0; i < cols; i++) {

            fscanf(infile,"%lf",&(mat[cols * j  + i]));
        }
    }
}

double* Identity(int N) {

    double* I = (double*)malloc(N * N * sizeof(double));

    for (int j = 0; j < N; j++) {

	    for (int i = 0; i < N; i++) {

		if (i == j)

		     I[i * N + j] = 1;
		else

		     I[i * N + j] = 0;
	    }
    }

return I;
}

void invers(double* matrix, double* I, int N) {

    int asd1;
    double asd2;
    double asd3;

    for (int j = 0; j < N; j++) {

        asd1 = j;
        for (int i = j + 1; i < N; i++) {

            if (matrix[i * N + j] > matrix[asd1 * N + j]) {

                asd1 = i;
            }
        }

        if (fabs(matrix[asd1 * N + j]) < 0.000005) {

            printf("\n Szerintem szingularis..\n");
            exit(1);
        }

        if (asd1 != j) {

            for (int k = 0; k < N; k++) {

                asd2 = matrix[j * N + k];
                matrix[j * N + k] = matrix[asd1 * N + k];
                matrix[asd1 * N + k] = asd2;
                asd2 = I[j * N + k];
                I[j * N + k] = I[asd1 * N + k];
                I[asd1 * N + k] = asd2;
            }
        }

        for (int i = 0; i < N; i++) {

            if (i != j) {

                asd3 = matrix[i * N + j];
                for (int k = 0; k < N; k++) {

                    matrix[i * N + k] -= (matrix[j * N + k] / matrix[j * N + j]) * asd3;
                    I[i * N + k] -= (I[j * N + k] / matrix[j * N + j]) * asd3;
                }
            }

            else {

                asd3 = matrix[i * N + j];
                for (int k = 0; k < N; k++) {

                    matrix[i * N + k] /= asd3;
                    I[i * N + k] /= asd3;
                }
            }
        }
    }
}

void result(double* matrix, int N)   {

    printf("Az inverz: \n");

    printf("\n");

    for (int i = 0; i < N; i++) {

        for (int j = 0; j < N; j++) {

            printf("r[]=%lf \t", matrix[i * N + j]);
        }

        printf("\n");
    }

}

int main(int argc, char** argv) {

    int i = 0;
    int j = 0;
    int M,N;

    double* matrix;

    M = atoi(argv[1]);
    N = atoi(argv[2]);

    if (argc != 4)
    {
        fprintf(stderr, "matmul M N matrix.dat\n");
        exit(-1);
    }

    matrix = (double*)malloc(M * N * sizeof(double));
    FILE *mf = fopen(argv[3], "r");

    loadMatrix(mf, matrix , M, N);

    if (M == 0 || N == 0) {

        printf("Nezzuk at azokat a tagokat megegyszer ha lehet.");
        return 1;
    }

    for (j = 0; j < M; j++) {

        for (i = 0; i < N; i++) {

            printf("m[%d]=%lf \t", j * M  + i, matrix[j * N  + i]);
        }

        printf("\n");
    }

    printf("\n");

    double* I = Identity(N);

    invers(matrix, I, N);
    result(I, N);

    free(matrix);
    free(I);
    fclose(mf);
    return 0;
}

