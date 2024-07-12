#include "../s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  int status = 0;
  if (s21_check_null_matrix(A) || result == NULL) {
    status = 1;
  } else if (A->rows == A->columns) {
    *result = s21_determinant_helper(A);
  } else {
    status = 2;
  }

  return status;
}

double s21_determinant_helper(matrix_t *A) {
  double result = 0.0;
  double pre_result;
  if (A->rows == 1) {
    result = A->matrix[0][0];
  } else {
    matrix_t tmp;
    s21_create_matrix(A->rows - 1, A->columns - 1, &tmp);
    for (int i = 0; i < A->columns; i++) {
      s21_get_matrix(0, i, A, &tmp);
      if (A->rows - 1 == 2) {
        pre_result = s21_two_size_matrix(&tmp);
        if (i % 2) {
          result -= A->matrix[0][i] * pre_result;
        } else {
          result += A->matrix[0][i] * pre_result;
        }
      } else {
        if (i % 2) {
          result -= A->matrix[0][i] * s21_determinant_helper(&tmp);
        } else {
          result += A->matrix[0][i] * s21_determinant_helper(&tmp);
        }
      }
    }
    s21_remove_matrix(&tmp);
  }
  return result;
}

void s21_get_matrix(int rows_index, int collumn_index, matrix_t *A,
                    matrix_t *result) {
  int result_row = 0;
  int result_collumn = 0;
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      if (i == rows_index || j == collumn_index) {
        continue;
      } else {
        result->matrix[result_row][result_collumn] = A->matrix[i][j];
        result_collumn++;
        if (result_collumn == result->columns) {
          result_row++;
          result_collumn = 0;
        }
      }
    }
  }
}

double s21_two_size_matrix(matrix_t *A) {
  return (A->matrix[0][0] * A->matrix[1][1] -
          A->matrix[0][1] * A->matrix[1][0]);
}
