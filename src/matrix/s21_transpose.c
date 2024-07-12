#include "../s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
  int status = 0;
  if (s21_check_null_matrix(A) || result == NULL) {
    status = 1;
  } else {
    status = s21_create_matrix(A->columns, A->rows, result);
    if (status == 0) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[j][i] = A->matrix[i][j];
        }
      }
    }
  }
  return status;
}