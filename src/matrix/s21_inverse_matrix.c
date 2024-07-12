#include "../s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int status = 1;

  if (A != NULL && A->matrix != NULL && A->rows >= 1 && A->columns >= 1) {
    status = 2;
    double det = 0.0;
    s21_determinant(A, &det);
    if (fabs(det - 0) > 1e-7) {
      matrix_t temp;
      status = s21_calc_complements(A, &temp);
      if (status == 0) {
        matrix_t trans;
        status = s21_transpose(&temp, &trans);
        if (status == 0) {
          s21_mult_number(&trans, 1 / det, result);
        }
        s21_remove_matrix(&trans);
      }
      s21_remove_matrix(&temp);
    }
  }

  return status;
}