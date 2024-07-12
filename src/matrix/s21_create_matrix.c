#include "../s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int status = 0;
  if (rows <= 0 || columns <= 0 || result == NULL) {
    status = 1;
  } else {
    result->columns = columns;
    result->rows = rows;
    result->matrix = (double **)calloc(rows, sizeof(double *));
    if (!(result->matrix)) {
      status = 2;
    }
    for (int i = 0; i < rows; i++) {
      result->matrix[i] = (double *)calloc(columns, sizeof(double));
      if (!(result->matrix[i])) {
        status = 2;
      }
    }
    if (status == 2) {
      s21_remove_matrix(result);
    }
  }

  return status;
}
