#include "../s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int status = 0;
  if (s21_check_null_matrix(A) || result == NULL) {
    status = 1;
  } else if (A->rows == A->columns) {
    s21_create_matrix(A->columns, A->rows, result);
    if (A->rows == 1 && A->columns == 1) {
      result->matrix[0][0] = 1;
    } else {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          matrix_t minor;
          double determinant = 0;
          s21_create_matrix(A->columns - 1, A->rows - 1, &minor);
          s21_get_matrix(i, j, A, &minor);
          s21_determinant(&minor, &determinant);
          result->matrix[i][j] = pow(-1, (i + 1 + j + 1)) * determinant;
          s21_remove_matrix(&minor);
        }
      }
    }
  } else {
    status = 2;
  }
  return status;
}
