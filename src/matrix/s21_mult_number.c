#include "../s21_matrix.h"

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int status = 0;
  if (s21_check_null_matrix(A) || result == NULL) {
    status = 1;
  } else if (s21_create_matrix(A->rows, A->columns, result) != 0) {
    status = 1;
  } else {
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        double mul = A->matrix[i][j] * number;
        result->matrix[i][j] = mul;
      }
    }
  }

  return status;
}