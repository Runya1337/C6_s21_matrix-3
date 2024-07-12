#include "../s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int status = 1;
  if (A == NULL || B == NULL) {
    status = 0;
  } else if ((A->rows != B->rows) || (A->columns != B->columns)) {
    status = 0;
  } else {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 0.0000001) {
          status = 0;
        }
      }
    }
  }
  return status;
}