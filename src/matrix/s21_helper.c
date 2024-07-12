#include "../s21_matrix.h"

int s21_check_null_matrix(matrix_t *A) {
  int status = 0;
  if (A == NULL || A->columns <= 0 || A->rows <= 0) {
    status = 1;
  }
  return status;
}