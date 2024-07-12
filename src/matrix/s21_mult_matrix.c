#include "../s21_matrix.h"

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status = 0;
  if (s21_check_null_matrix(A) || s21_check_null_matrix(B) || result == NULL) {
    status = 1;
  } else if (A->columns == B->rows &&
             !(s21_create_matrix(A->rows, B->columns, result))) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < B->columns; j++) {
        for (int l = 0; l < B->rows; l++)
          result->matrix[i][j] =
              result->matrix[i][j] + A->matrix[i][l] * B->matrix[l][j];
      }
    }
  } else {
    status = 2;
  }
  return status;
}