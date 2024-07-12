#include "../s21_matrix.h"

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status = 0;
  if (s21_check_null_matrix(A) || s21_check_null_matrix(B) || result == NULL) {
    status = 1;
  } else {
    if (A->rows == B->rows && A->columns == B->columns) {
      int rows_result = A->rows;
      int columns_result = A->columns;
      if (s21_create_matrix(rows_result, columns_result, result) != 0) {
        status = 1;
      } else {
        for (int i = 0; i < result->rows; i++) {
          for (int j = 0; j < result->columns; j++) {
            result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
          }
        }
      }
    } else {
      status = 2;
    }
  }
  return status;
}