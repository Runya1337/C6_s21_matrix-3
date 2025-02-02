#include <check.h>

#include "s21_matrix.h"

// Создание и удаление матрицы

START_TEST(create_matrix_positive) {
  matrix_t m = {0};
  int code = s21_create_matrix(3, 3, &m);
  ck_assert_int_eq(code, 0);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(create_matrix_single_element) {
  matrix_t m = {0};
  int code = s21_create_matrix(1, 1, &m);
  ck_assert_int_eq(code, 0);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(create_matrix_rectangle) {
  matrix_t m = {0};
  int code = s21_create_matrix(2, 3, &m);
  ck_assert_int_eq(code, 0);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(create_matrix_large) {
  matrix_t m = {0};
  int code = s21_create_matrix(1000, 1000, &m);
  ck_assert_int_eq(code, 0);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(create_matrix_zero_rows) {
  matrix_t m = {0};
  int code = s21_create_matrix(0, 3, &m);
  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(create_matrix_zero_cols) {
  matrix_t m = {0};
  int code = s21_create_matrix(3, 0, &m);
  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(create_matrix_negative_rows) {
  matrix_t m = {0};
  int code = s21_create_matrix(-3, 3, &m);
  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(create_matrix_negative_cols) {
  matrix_t m = {0};
  int code = s21_create_matrix(3, -3, &m);
  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(create_matrix_zero_size) {
  matrix_t m = {0};
  int code = s21_create_matrix(0, 0, &m);
  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(create_matrix_null_pointer) {
  int code = s21_create_matrix(3, 3, NULL);
  ck_assert_int_eq(code, 1);
}
END_TEST

double get_rand(double min, double max) {
  double val = (double)rand() / RAND_MAX;
  return min + val * (max - min);
}

START_TEST(create_matrix) {
  const int rows = rand() % 100 + 1;
  const int cols = rand() % 100 + 1;
  matrix_t m = {0};
  s21_create_matrix(rows, cols, &m);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      m.matrix[i][j] = 0;
      ck_assert_ldouble_eq_tol(0, m.matrix[i][j], 1e-07);
    }
  }
  ck_assert_int_eq(m.rows, rows);
  ck_assert_int_eq(m.columns, cols);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(create_normal) {
  int rows = 10;
  int columns = 10;
  matrix_t matrix = {0};
  int status1 = s21_create_matrix(rows, columns, &matrix);

  if (matrix.matrix) {
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < columns; ++j) {
        ck_assert(fabs(matrix.matrix[i][j]) < 1e-7);
      }
    }
    ck_assert_int_eq(matrix.rows, rows);
    ck_assert_int_eq(matrix.columns, columns);
    ck_assert_int_eq(status1, OK);
  } else {
    ck_assert_int_eq(status1, ERROR_CALC);
  }

  if (status1 == OK) s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(create_no_rows) {
  const int rows = 0;
  const int cols = 10;
  matrix_t m = {0};
  ck_assert_int_eq(s21_create_matrix(rows, cols, &m), NOTCORRECT);
}
END_TEST

START_TEST(create_no_cols) {
  const int rows = 10;
  const int cols = 0;
  matrix_t m = {0};
  ck_assert_int_eq(s21_create_matrix(rows, cols, &m), NOTCORRECT);
}
END_TEST

START_TEST(create_NOTCORRECT) {
  int rows = -10;
  int columns = 10;
  matrix_t matrix = {0};
  int status = s21_create_matrix(rows, columns, &matrix);

  ck_assert_int_eq(status, NOTCORRECT);

  if (status == OK) s21_remove_matrix(&matrix);
}
END_TEST

// Сравнение матриц

START_TEST(eq_matrix_identical) {
  matrix_t A = {0};
  matrix_t B = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  int code = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(code, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(eq_matrix_different) {
  matrix_t A = {0};
  matrix_t B = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  B.matrix[0][0] = 1.0;
  int code = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(code, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(eq_matrix_diff_sizes) {
  matrix_t A = {0};
  matrix_t B = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(2, 2, &B);
  int code = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(code, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(eq_matrix_near_equal) {
  matrix_t A = {0};
  matrix_t B = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  B.matrix[0][0] = 0.00000005;
  int code = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(code, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(eq_matrix_null_pointer) {
  matrix_t A = {0};
  s21_create_matrix(3, 3, &A);
  int code = s21_eq_matrix(&A, NULL);
  ck_assert_int_eq(code, 0);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(eq_matrix_identical_single_element) {
  matrix_t A = {0};
  matrix_t B = {0};
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);
  int code = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(code, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(eq_matrix_identical_one_column) {
  matrix_t A = {0};
  matrix_t B = {0};
  s21_create_matrix(2, 1, &A);
  s21_create_matrix(2, 1, &B);
  int code = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(code, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(eq_matrix_null_pointer_vs_matrix) {
  matrix_t B = {0};
  s21_create_matrix(1, 1, &B);
  int code = s21_eq_matrix(NULL, &B);
  ck_assert_int_eq(code, 0);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(eq_matrix_different_same_size) {
  matrix_t A = {0};
  matrix_t B = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  A.matrix[1][1] = 2.0;
  B.matrix[1][1] = 3.0;
  int code = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(code, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(eq_matrix_zero_size_vs_normal) {
  matrix_t A = {0};
  matrix_t B = {0};
  s21_create_matrix(0, 0, &A);
  s21_create_matrix(3, 3, &B);
  int code = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(code, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(eq_matrix) {
  const int rows = rand() % 100 + 1;
  const int cols = rand() % 100 + 1;
  matrix_t m = {0};
  s21_create_matrix(rows, cols, &m);
  matrix_t mtx = {0};
  s21_create_matrix(rows, cols, &mtx);

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      double rand_val = get_rand(DBL_MIN, DBL_MAX);
      m.matrix[i][j] = rand_val;
      mtx.matrix[i][j] = rand_val;
    }
  }
  ck_assert_int_eq(s21_eq_matrix(&m, &mtx), SUCCESS);
  s21_remove_matrix(&m);
  s21_remove_matrix(&mtx);
}
END_TEST

START_TEST(not_eq_1) {
  const int rows = rand() % 100 + 1;
  const int cols = rand() % 100 + 1;
  matrix_t m = {0};
  s21_create_matrix(rows, cols, &m);
  matrix_t mtx = {0};
  s21_create_matrix(rows, cols, &mtx);

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      m.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX) + 1;
      mtx.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX);
    }
  }
  ck_assert_int_eq(s21_eq_matrix(&m, &mtx), FAILURE);
  s21_remove_matrix(&m);
  s21_remove_matrix(&mtx);
}
END_TEST

START_TEST(not_eq_2) {
  const int rows1 = rand() % 100 + 1;
  const int cols1 = rand() % 100 + 1;
  matrix_t m = {0};
  s21_create_matrix(rows1, cols1, &m);
  const int rows2 = rand() % 100 + 1;
  const int cols2 = rand() % 100 + 1;
  matrix_t mtx = {0};
  s21_create_matrix(rows2, cols2, &mtx);

  for (int i = 0; i < rows1; ++i) {
    for (int j = 0; j < cols1; ++j) {
      m.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX) + 1;
    }
  }
  for (int i = 0; i < rows2; ++i) {
    for (int j = 0; j < cols2; ++j) {
      mtx.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX);
    }
  }
  ck_assert_int_eq(s21_eq_matrix(&m, &mtx), FAILURE);
  s21_remove_matrix(&m);
  s21_remove_matrix(&mtx);
}
END_TEST

// вычитание матриц

START_TEST(sub_matrix_same_size) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t result = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  int code = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(code, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sub_matrix_diff_size) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t result = {0};
  s21_create_matrix(3, 4, &A);
  s21_create_matrix(3, 3, &B);
  int code = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(code, 2);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(sub_matrix_null_A) {
  matrix_t B = {0};
  matrix_t result = {0};
  s21_create_matrix(3, 3, &B);
  int code = s21_sub_matrix(NULL, &B, &result);
  ck_assert_int_eq(code, 1);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(sub_matrix_null_B) {
  matrix_t A = {0};
  matrix_t result = {0};
  s21_create_matrix(3, 3, &A);
  int code = s21_sub_matrix(&A, NULL, &result);
  ck_assert_int_eq(code, 1);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(sub_matrix_null_result) {
  matrix_t A = {0};
  matrix_t B = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  int code = s21_sub_matrix(&A, &B, NULL);
  ck_assert_int_eq(code, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(sub_matrix_single_element) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t result = {0};
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);
  int code = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(code, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sub_matrix_zero_rows) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t result = {0};
  s21_create_matrix(0, 3, &A);
  s21_create_matrix(0, 3, &B);
  int code = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(code, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(sub_matrix_zero_columns) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t result = {0};
  s21_create_matrix(3, 0, &A);
  s21_create_matrix(3, 0, &B);
  int code = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(code, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(sub_matrix_large) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t result = {0};
  s21_create_matrix(1000, 1000, &A);
  s21_create_matrix(1000, 1000, &B);
  int code = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(code, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sub_matrix_negative_values) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t result = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  A.matrix[0][0] = -1;
  B.matrix[0][0] = -1;
  int code = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_double_eq(result.matrix[0][0], 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sum_matrix_same_size) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t result = {0};

  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);

  int code = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(code, 0);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sum_matrix_different_size) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t result = {0};

  s21_create_matrix(3, 3, &A);
  s21_create_matrix(2, 2, &B);

  int code = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(code, 2);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sum_matrix_null_A) {
  matrix_t B = {0};
  matrix_t result = {0};

  s21_create_matrix(3, 3, &B);

  int code = s21_sum_matrix(NULL, &B, &result);
  ck_assert_int_eq(code, 1);

  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sum_matrix_null_B) {
  matrix_t A = {0};
  matrix_t result = {0};

  s21_create_matrix(3, 3, &A);

  int code = s21_sum_matrix(&A, NULL, &result);
  ck_assert_int_eq(code, 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sum_matrix_null_result) {
  matrix_t A = {0};
  matrix_t B = {0};

  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);

  int code = s21_sum_matrix(&A, &B, NULL);
  ck_assert_int_eq(code, 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(sum_matrix_large) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t result = {0};

  s21_create_matrix(1000, 1000, &A);
  s21_create_matrix(1000, 1000, &B);

  int code = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(code, 0);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sum_matrix_negative_value) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t result = {0};

  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);

  // Присваиваю некоторым элементам отрицательные значения
  A.matrix[0][0] = -1.0;
  B.matrix[0][0] = -1.0;

  int code = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(code, 0);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sum_matrix_zero_value) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t result = {0};

  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);

  // Присваиваю всем элементам отрицательные значения
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.matrix[i][j] = 0.0;
      B.matrix[i][j] = 0.0;
    }
  }

  int code = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(code, 0);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sum_matrix_positive_value) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t result = {0};

  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);

  // Присваиваю всем элементам положительные значения
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.matrix[i][j] = 1.0;
      B.matrix[i][j] = 1.0;
    }
  }

  int code = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(code, 0);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sum_matrix_single_element) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t result = {0};

  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);

  A.matrix[0][0] = 1.0;
  B.matrix[0][0] = 1.0;

  int code = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(code, 0);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sum_matrix) {
  const int rows = rand() % 100 + 1;
  const int cols = rand() % 100 + 1;
  matrix_t m = {0};
  s21_create_matrix(rows, cols, &m);
  matrix_t mtx = {0};
  s21_create_matrix(rows, cols, &mtx);
  matrix_t check = {0};
  s21_create_matrix(rows, cols, &check);

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      m.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX);
      mtx.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX);
      check.matrix[i][j] = m.matrix[i][j] + mtx.matrix[i][j];
    }
  }
  matrix_t res = {0};

  ck_assert_int_eq(s21_sum_matrix(&m, &mtx, &res), OK);
  ck_assert_int_eq(s21_eq_matrix(&check, &res), SUCCESS);
  s21_remove_matrix(&m);
  s21_remove_matrix(&mtx);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(sum_matrix_1) {
  matrix_t A, B, R, R2;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);
  s21_create_matrix(1, 1, &R2);

  A.matrix[0][0] = 1.25;
  B.matrix[0][0] = 2.25;

  R2.matrix[0][0] = 3.5;

  s21_sum_matrix(&A, &B, &R);

  ck_assert(fabs(R.matrix[0][0] - R2.matrix[0][0]) < 1e-7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
  s21_remove_matrix(&R2);
}
END_TEST

START_TEST(sum_matrix_2) {
  matrix_t A, B, R, R2;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  s21_create_matrix(3, 3, &R2);

  A.matrix[0][0] = 0.25;
  A.matrix[0][1] = 1.25;
  A.matrix[0][2] = 2.25;
  A.matrix[1][0] = 3.25;
  A.matrix[1][1] = 4.25;
  A.matrix[1][2] = 5.25;
  A.matrix[2][0] = 6.25;
  A.matrix[2][1] = 7.25;
  A.matrix[2][2] = 8.25;

  B.matrix[0][0] = 9.65;
  B.matrix[0][1] = 8.65;
  B.matrix[0][2] = 7.65;
  B.matrix[1][0] = 6.65;
  B.matrix[1][1] = 5.65;
  B.matrix[1][2] = 4.65;
  B.matrix[2][0] = 3.65;
  B.matrix[2][1] = 2.65;
  B.matrix[2][2] = 1.65;

  R2.matrix[0][0] = 9.9;
  R2.matrix[0][1] = 9.9;
  R2.matrix[0][2] = 9.9;
  R2.matrix[1][0] = 9.9;
  R2.matrix[1][1] = 9.9;
  R2.matrix[1][2] = 9.9;
  R2.matrix[2][0] = 9.9;
  R2.matrix[2][1] = 9.9;
  R2.matrix[2][2] = 9.9;

  s21_sum_matrix(&A, &B, &R);

  ck_assert_int_eq(s21_eq_matrix(&R, &R2), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
  s21_remove_matrix(&R2);
}
END_TEST

START_TEST(sum_test_NOTCORRECT_matrix) {
  matrix_t A, B, R;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(2, 1, &B);

  A.matrix[0][0] = 1.25;
  B.matrix[0][0] = 2.25;

  int res = s21_sum_matrix(&A, &B, &R);

  ck_assert_int_eq(res, ERROR_CALC);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  //    s21_remove_matrix(&R);
}
END_TEST

START_TEST(sum_null) {
  matrix_t *A = NULL;
  matrix_t *B = NULL;
  matrix_t *R = NULL;
  int res = s21_sum_matrix(A, B, R);
  ck_assert_int_eq(res, NOTCORRECT);
}
END_TEST

// Вычитание матриц

START_TEST(sub_test_1) {
  matrix_t A, B, R, R2;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);
  s21_create_matrix(1, 1, &R2);

  A.matrix[0][0] = 1.25;
  B.matrix[0][0] = 2.25;

  R2.matrix[0][0] = -1;

  s21_sub_matrix(&A, &B, &R);

  ck_assert(fabs(R.matrix[0][0] - R2.matrix[0][0]) < 1e-7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
  s21_remove_matrix(&R2);
}
END_TEST

START_TEST(sub_test_2) {
  matrix_t A, B, R, R2;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  s21_create_matrix(3, 3, &R2);

  A.matrix[0][0] = 0.25;
  A.matrix[0][1] = 1.25;
  A.matrix[0][2] = 2.25;
  A.matrix[1][0] = 3.25;
  A.matrix[1][1] = 4.25;
  A.matrix[1][2] = 5.25;
  A.matrix[2][0] = 6.25;
  A.matrix[2][1] = 7.25;
  A.matrix[2][2] = 8.25;

  B.matrix[0][0] = 9.25;
  B.matrix[0][1] = 8.25;
  B.matrix[0][2] = 7.25;
  B.matrix[1][0] = 6.25;
  B.matrix[1][1] = 5.25;
  B.matrix[1][2] = 4.25;
  B.matrix[2][0] = 3.25;
  B.matrix[2][1] = 2.25;
  B.matrix[2][2] = 1.25;

  R2.matrix[0][0] = -9.0;
  R2.matrix[0][1] = -7.0;
  R2.matrix[0][2] = -5.0;
  R2.matrix[1][0] = -3.0;
  R2.matrix[1][1] = -1.0;
  R2.matrix[1][2] = 1.0;
  R2.matrix[2][0] = 3.0;
  R2.matrix[2][1] = 5.0;
  R2.matrix[2][2] = 7.0;

  s21_sub_matrix(&A, &B, &R);

  ck_assert_int_eq(s21_eq_matrix(&R, &R2), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
  s21_remove_matrix(&R2);
}
END_TEST

START_TEST(sub_test_NOTCORRECT_matrix) {
  matrix_t A, B, R;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(2, 1, &B);

  A.matrix[0][0] = 1.25;
  B.matrix[0][0] = 2.25;

  int res = s21_sub_matrix(&A, &B, &R);

  ck_assert_int_eq(res, ERROR_CALC);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(sub_null) {
  matrix_t *A = NULL;
  matrix_t *B = NULL;
  matrix_t *R = NULL;
  int res = s21_sub_matrix(A, B, R);
  ck_assert_int_eq(res, NOTCORRECT);
}
END_TEST

// Умножение матрицы на матрицу
START_TEST(test_mult_null_A) {
  matrix_t *A = NULL, B, result;
  s21_create_matrix(2, 2, &B);
  ck_assert_int_eq(s21_mult_matrix(A, &B, &result), 1);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_mult_null_B) {
  matrix_t A, *B = NULL, result;
  s21_create_matrix(2, 2, &A);
  ck_assert_int_eq(s21_mult_matrix(&A, B, &result), 1);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_mult_null_result) {
  matrix_t A, B, *result = NULL;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  ck_assert_int_eq(s21_mult_matrix(&A, &B, result), 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(mult_matrix_test_1) {
  matrix_t A, B, R, R2;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);
  s21_create_matrix(1, 1, &R2);

  A.matrix[0][0] = -1;
  B.matrix[0][0] = 2;

  R2.matrix[0][0] = -2;

  s21_mult_matrix(&A, &B, &R);

  ck_assert(fabs(R.matrix[0][0] - R2.matrix[0][0]) < 1e-7);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
  s21_remove_matrix(&R2);
}
END_TEST

START_TEST(mult_matrix_test_2) {
  matrix_t A, B, R, R2;
  s21_create_matrix(3, 2, &A);
  s21_create_matrix(2, 3, &B);
  s21_create_matrix(3, 3, &R2);

  A.matrix[0][0] = 0;
  A.matrix[0][1] = 1;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;
  A.matrix[2][0] = 6;
  A.matrix[2][1] = 7;

  B.matrix[0][0] = 9;
  B.matrix[0][1] = 8;
  B.matrix[0][2] = 7;
  B.matrix[1][0] = 6;
  B.matrix[1][1] = 5;
  B.matrix[1][2] = 4;

  R2.matrix[0][0] = 6;
  R2.matrix[0][1] = 5;
  R2.matrix[0][2] = 4;
  R2.matrix[1][0] = 51;
  R2.matrix[1][1] = 44;
  R2.matrix[1][2] = 37;
  R2.matrix[2][0] = 96;
  R2.matrix[2][1] = 83;
  R2.matrix[2][2] = 70;

  s21_mult_matrix(&A, &B, &R);

  ck_assert_int_eq(s21_eq_matrix(&R, &R2), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
  s21_remove_matrix(&R2);
}
END_TEST

START_TEST(mult_matrix_test_null) {
  matrix_t *A = NULL, *B = NULL, *R = NULL;
  ck_assert_int_eq(s21_mult_matrix(A, B, R), NOTCORRECT);
}
END_TEST

// Умножение матрицы на число
START_TEST(test_mult_float) {
  matrix_t A, B, result;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 1.0;
  A.matrix[1][0] = 1.0;
  A.matrix[1][1] = 1.0;
  double number = 0.5;
  s21_create_matrix(2, 2, &B);
  B.matrix[0][0] = 0.5;
  B.matrix[0][1] = 0.5;
  B.matrix[1][0] = 0.5;
  B.matrix[1][1] = 0.5;
  ck_assert_int_eq(s21_mult_number(&A, number, &result), 0);
  ck_assert(s21_eq_matrix(&B, &result));
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_mult_large) {
  matrix_t A, B, result;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1000000.0;
  A.matrix[0][1] = 1000000.0;
  A.matrix[1][0] = 1000000.0;
  A.matrix[1][1] = 1000000.0;
  double number = 1000000.0;
  s21_create_matrix(2, 2, &B);
  B.matrix[0][0] = 1000000000000.0;
  B.matrix[0][1] = 1000000000000.0;
  B.matrix[1][0] = 1000000000000.0;
  B.matrix[1][1] = 1000000000000.0;
  ck_assert_int_eq(s21_mult_number(&A, number, &result), 0);
  ck_assert(s21_eq_matrix(&B, &result));
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_mult_small) {
  matrix_t A, B, result;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 0.0000001;
  A.matrix[0][1] = 0.0000001;
  A.matrix[1][0] = 0.0000001;
  A.matrix[1][1] = 0.0000001;
  double number = 0.0000001;
  s21_create_matrix(2, 2, &B);
  B.matrix[0][0] = 0.00000000000001;
  B.matrix[0][1] = 0.00000000000001;
  B.matrix[1][0] = 0.00000000000001;
  B.matrix[1][1] = 0.00000000000001;
  ck_assert_int_eq(s21_mult_number(&A, number, &result), 0);
  ck_assert(s21_eq_matrix(&B, &result));
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_mult_random) {
  matrix_t A, B, result;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 3.2;
  A.matrix[0][1] = 4.5;
  A.matrix[1][0] = 6.7;
  A.matrix[1][1] = 8.9;
  double number = 2.0;
  s21_create_matrix(2, 2, &B);
  B.matrix[0][0] = 6.4;
  B.matrix[0][1] = 9.0;
  B.matrix[1][0] = 13.4;
  B.matrix[1][1] = 17.8;
  ck_assert_int_eq(s21_mult_number(&A, number, &result), 0);
  ck_assert(s21_eq_matrix(&B, &result));
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_mult_zero_result) {
  matrix_t A, B, result;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 0.0;
  A.matrix[0][1] = 0.0;
  A.matrix[1][0] = 0.0;
  A.matrix[1][1] = 0.0;
  double number = 2.0;
  s21_create_matrix(2, 2, &B);
  B.matrix[0][0] = 0.0;
  B.matrix[0][1] = 0.0;
  B.matrix[1][0] = 0.0;
  B.matrix[1][1] = 0.0;
  ck_assert_int_eq(s21_mult_number(&A, number, &result), 0);
  ck_assert(s21_eq_matrix(&B, &result));
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(mult_number_matrix) {
  const int rows = rand() % 100 + 1;
  const int cols = rand() % 100 + 1;
  matrix_t m = {0};
  s21_create_matrix(rows, cols, &m);
  matrix_t check = {0};
  s21_create_matrix(rows, cols, &check);
  double mult_number = get_rand(-10e5, 10e5);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      m.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX);
      check.matrix[i][j] = m.matrix[i][j] * mult_number;
    }
  }
  matrix_t res = {0};
  ck_assert_int_eq(s21_mult_number(&m, mult_number, &res), OK);
  ck_assert_int_eq(s21_eq_matrix(&check, &res), SUCCESS);
  s21_remove_matrix(&m);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(mult_number_test_1) {
  matrix_t A, R, R2;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &R2);

  A.matrix[0][0] = 1.25;

  R2.matrix[0][0] = -5;

  s21_mult_number(&A, -4, &R);

  ck_assert(fabs(R.matrix[0][0] - R2.matrix[0][0]) < 1e-7);
  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
  s21_remove_matrix(&R2);
}
END_TEST

START_TEST(mult_number_test_2) {
  matrix_t A, R, R2;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &R2);

  A.matrix[0][0] = 0.25;
  A.matrix[0][1] = 1.25;
  A.matrix[0][2] = 2.25;
  A.matrix[1][0] = 3.25;
  A.matrix[1][1] = 4.25;
  A.matrix[1][2] = 5.25;
  A.matrix[2][0] = 6.25;
  A.matrix[2][1] = 7.25;
  A.matrix[2][2] = 8.25;

  R2.matrix[0][0] = 1;
  R2.matrix[0][1] = 5;
  R2.matrix[0][2] = 9;
  R2.matrix[1][0] = 13;
  R2.matrix[1][1] = 17;
  R2.matrix[1][2] = 21;
  R2.matrix[2][0] = 25;
  R2.matrix[2][1] = 29;
  R2.matrix[2][2] = 33;

  s21_mult_number(&A, 4, &R);

  ck_assert_int_eq(s21_eq_matrix(&R, &R2), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
  s21_remove_matrix(&R2);
}
END_TEST

START_TEST(mult_number_test_3) {
  matrix_t A, R, R2;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(2, 3, &R2);

  A.matrix[0][0] = 0.25;
  A.matrix[0][1] = 1.25;
  A.matrix[0][2] = 2.25;
  A.matrix[1][0] = 3.25;
  A.matrix[1][1] = 4.25;
  A.matrix[1][2] = 5.25;

  R2.matrix[0][0] = 1;
  R2.matrix[0][1] = 5;
  R2.matrix[0][2] = 9;
  R2.matrix[1][0] = 13;
  R2.matrix[1][1] = 17;
  R2.matrix[1][2] = 21;

  s21_mult_number(&A, 4, &R);

  ck_assert_int_eq(s21_eq_matrix(&R, &R2), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
  s21_remove_matrix(&R2);
}
END_TEST

START_TEST(null_mult_num) {
  matrix_t *B = NULL;
  double num = 0;
  matrix_t *R = NULL;
  int res = s21_mult_number(B, num, R);
  ck_assert_int_eq(res, NOTCORRECT);
}
END_TEST

// Транспонирование матрицы

START_TEST(transpose_test_1) {
  matrix_t A, B, R;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);

  A.matrix[0][0] = 1.25;
  B.matrix[0][0] = 1.25;

  s21_transpose(&A, &R);
  ck_assert_int_eq(s21_eq_matrix(&R, &B), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
}
END_TEST

START_TEST(transpose_test_2) {
  matrix_t A, B, R;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);

  A.matrix[0][0] = 0.25;
  A.matrix[0][1] = 1.25;
  A.matrix[0][2] = 2.25;
  A.matrix[1][0] = 3.25;
  A.matrix[1][1] = 4.25;
  A.matrix[1][2] = 5.25;
  A.matrix[2][0] = 6.25;
  A.matrix[2][1] = 7.25;
  A.matrix[2][2] = 8.25;

  s21_transpose(&A, &R);

  B.matrix[0][0] = 0.25;
  B.matrix[1][0] = 1.25;
  B.matrix[2][0] = 2.25;
  B.matrix[0][1] = 3.25;
  B.matrix[1][1] = 4.25;
  B.matrix[2][1] = 5.25;
  B.matrix[0][2] = 6.25;
  B.matrix[1][2] = 7.25;
  B.matrix[2][2] = 8.25;

  ck_assert_int_eq(s21_eq_matrix(&R, &B), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
}
END_TEST

START_TEST(transpose_NOTCORRECT) {
  matrix_t A, B;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);
  A.columns = -1;

  int ret = s21_transpose(&A, &B);
  ck_assert_int_eq(ret, NOTCORRECT);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);

  ck_assert_int_eq(s21_transpose(NULL, NULL), NOTCORRECT);
}
END_TEST

// Минор матрицы и матрица алгебраических дополнений

START_TEST(compliment_test_1) {
  matrix_t A, B, R;
  s21_create_matrix(3, 3, &B);
  s21_create_matrix(3, 3, &A);
  B.matrix[0][0] = 1;
  B.matrix[0][1] = 2;
  B.matrix[0][2] = 3;
  B.matrix[1][0] = 0;
  B.matrix[1][1] = 4;
  B.matrix[1][2] = 2;
  B.matrix[2][0] = 5;
  B.matrix[2][1] = 2;
  B.matrix[2][2] = 1;

  A.matrix[0][0] = 0;
  A.matrix[0][1] = 10;
  A.matrix[0][2] = -20;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = -14;
  A.matrix[1][2] = 8;
  A.matrix[2][0] = -8;
  A.matrix[2][1] = -2;
  A.matrix[2][2] = 4;

  int code = s21_calc_complements(&B, &R);
  ck_assert_int_eq(code, OK);
  ck_assert_int_eq(s21_eq_matrix(&R, &A), SUCCESS);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(compliment_test_2) {
  matrix_t A, B, R;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);

  A.matrix[0][0] = 5;
  A.matrix[0][1] = -1;
  A.matrix[0][2] = 1;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 3;
  A.matrix[1][2] = 4;
  A.matrix[2][0] = 1;
  A.matrix[2][1] = 0;
  A.matrix[2][2] = 3;

  s21_calc_complements(&A, &R);

  B.matrix[0][0] = 9;
  B.matrix[0][1] = -2;
  B.matrix[0][2] = -3;
  B.matrix[1][0] = 3;
  B.matrix[1][1] = 14;
  B.matrix[1][2] = -1;
  B.matrix[2][0] = -7;
  B.matrix[2][1] = -18;
  B.matrix[2][2] = 17;

  ck_assert_int_eq(s21_eq_matrix(&R, &B), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
}
END_TEST

START_TEST(compliment_test_not_square) {
  matrix_t B, R;
  s21_create_matrix(2, 3, &B);

  B.matrix[0][0] = 1;
  B.matrix[0][1] = 2;
  B.matrix[0][2] = 3;
  B.matrix[1][0] = 0;
  B.matrix[1][1] = 4;
  B.matrix[1][2] = 2;

  int code = s21_calc_complements(&B, &R);

  ck_assert_int_eq(code, ERROR_CALC);
  s21_remove_matrix(&B);
  // s21_remove_matrix(&R);
}
END_TEST

START_TEST(compliment_test_1x1) {
  matrix_t A, B, R;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);

  A.matrix[0][0] = 5;

  s21_calc_complements(&A, &R);

  B.matrix[0][0] = 1;

  ck_assert_int_eq(s21_eq_matrix(&R, &B), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
}
END_TEST

START_TEST(null_compliments) {
  matrix_t *B = NULL;
  matrix_t *R = NULL;
  int res = s21_calc_complements(B, R);
  ck_assert_int_eq(res, NOTCORRECT);
}
END_TEST

START_TEST(s21_calc_compl_1) {
  matrix_t A, B, C;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &C);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 3.0;
  A.matrix[1][0] = 0.0;
  A.matrix[1][1] = 4.0;
  A.matrix[1][2] = 2.0;
  A.matrix[2][0] = 5.0;
  A.matrix[2][1] = 2.0;
  A.matrix[2][2] = 1.0;
  s21_calc_complements(&A, &B);
  C.matrix[0][0] = 0.0;
  C.matrix[0][1] = 10.0;
  C.matrix[0][2] = -20.0;
  C.matrix[1][0] = 4.0;
  C.matrix[1][1] = -14.0;
  C.matrix[1][2] = 8.0;
  C.matrix[2][0] = -8.0;
  C.matrix[2][1] = -2.0;
  C.matrix[2][2] = 4.0;
  int res = s21_eq_matrix(&B, &C);
  ck_assert_int_eq(res, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(s21_calc_compl_2) {
  matrix_t a = {0};
  s21_create_matrix(3, 3, &a);
  matrix_t res = {0};
  s21_create_matrix(3, 3, &res);
  matrix_t m;
  res.matrix[0][0] = 0;
  res.matrix[0][1] = 10;
  res.matrix[0][2] = -20;
  res.matrix[1][0] = 4;
  res.matrix[1][1] = -14;
  res.matrix[1][2] = 8;
  res.matrix[2][0] = -8;
  res.matrix[2][1] = -2;
  res.matrix[2][2] = 4;

  a.matrix[0][0] = 1;
  a.matrix[0][1] = 2;
  a.matrix[0][2] = 3;
  a.matrix[1][0] = 0;
  a.matrix[1][1] = 4;
  a.matrix[1][2] = 2;
  a.matrix[2][0] = 5;
  a.matrix[2][1] = 2;
  a.matrix[2][2] = 1;
  s21_calc_complements(&a, &m);
  ck_assert_int_eq(s21_eq_matrix(&res, &m), SUCCESS);
  s21_remove_matrix(&m);
  s21_remove_matrix(&a);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(empty) {
  matrix_t a = {0};
  matrix_t b = {0};
  ck_assert_int_eq(s21_calc_complements(&a, &b), NOTCORRECT);
}
END_TEST

START_TEST(size_mismatch) {
  matrix_t a = {0};
  matrix_t b = {0};
  s21_create_matrix(1, 2, &a);
  ck_assert_int_eq(s21_calc_complements(&a, &b), ERROR_CALC);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(complements) {
  const int size = 3;
  matrix_t m = {0};
  s21_create_matrix(size, size, &m);
  m.matrix[0][0] = 1;
  m.matrix[0][1] = 2;
  m.matrix[0][2] = 3;
  m.matrix[1][1] = 4;
  m.matrix[1][2] = 2;
  m.matrix[2][0] = 5;
  m.matrix[2][1] = 2;
  m.matrix[2][2] = 1;

  matrix_t expected = {0};
  s21_create_matrix(size, size, &expected);
  expected.matrix[0][1] = 10;
  expected.matrix[0][2] = -20;
  expected.matrix[1][0] = 4;
  expected.matrix[1][1] = -14;
  expected.matrix[1][2] = 8;
  expected.matrix[2][0] = -8;
  expected.matrix[2][1] = -2;
  expected.matrix[2][2] = 4;

  matrix_t res = {0};
  s21_calc_complements(&m, &res);

  ck_assert_int_eq(s21_eq_matrix(&expected, &res), SUCCESS);
  s21_remove_matrix(&m);
  s21_remove_matrix(&res);
  s21_remove_matrix(&expected);
}
END_TEST

// Определитель матрицы

START_TEST(determinant_test_1) {
  matrix_t A;
  double B, R = 1.25;
  s21_create_matrix(1, 1, &A);

  A.matrix[0][0] = 1.25;

  s21_determinant(&A, &B);
  ck_assert((fabs(B) - fabs(R)) < 1e-7);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_test_2) {
  matrix_t A;
  double B, R = -69;
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 0.25;
  A.matrix[0][1] = 1.25;
  A.matrix[0][2] = 2.25;
  A.matrix[1][0] = 3.25;
  A.matrix[1][1] = 10;
  A.matrix[1][2] = 5.25;
  A.matrix[2][0] = 6.25;
  A.matrix[2][1] = 7.25;
  A.matrix[2][2] = 8.25;

  s21_determinant(&A, &B);

  ck_assert((fabs(B) - fabs(R)) < 1e-7);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_test_2x2) {
  matrix_t A;
  double B, R = -2;
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 2;
  A.matrix[0][1] = 4;
  A.matrix[1][0] = -5;
  A.matrix[1][1] = -7;

  s21_determinant(&A, &B);

  ck_assert((fabs(B) - fabs(R)) < 1e-7);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_test_3x3_1) {
  matrix_t A;
  double B, R = -2;
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 2;
  A.matrix[0][1] = 4;
  A.matrix[0][2] = -6;
  A.matrix[1][0] = -5;
  A.matrix[1][1] = -7;
  A.matrix[1][2] = 5;
  A.matrix[2][0] = 3;
  A.matrix[2][1] = 5;
  A.matrix[2][2] = -6;

  s21_determinant(&A, &B);

  ck_assert((fabs(B) - fabs(R)) < 1e-7);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_test_3x3_2) {
  matrix_t A;
  double B, R = 25;
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = -3;
  A.matrix[0][1] = 4;
  A.matrix[0][2] = -6;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = -7;
  A.matrix[1][2] = 5;
  A.matrix[2][0] = -4;
  A.matrix[2][1] = 5;
  A.matrix[2][2] = -6;

  s21_determinant(&A, &B);

  ck_assert((fabs(B) - fabs(R)) < 1e-7);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_test_3x3_3) {
  matrix_t A;
  double B, R = 23;
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = -3;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = -6;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = -5;
  A.matrix[1][2] = 5;
  A.matrix[2][0] = -4;
  A.matrix[2][1] = 3;
  A.matrix[2][2] = -6;

  s21_determinant(&A, &B);

  ck_assert((fabs(B) - fabs(R)) < 1e-7);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_test_3x3_4) {
  matrix_t A;
  double B, R = -8;
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = -3;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 4;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = -5;
  A.matrix[1][2] = -7;
  A.matrix[2][0] = -4;
  A.matrix[2][1] = 3;
  A.matrix[2][2] = 5;

  s21_determinant(&A, &B);

  ck_assert((fabs(B) - fabs(R)) < 1e-7);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_test_4x4) {
  matrix_t A;
  double B, R = 18;
  s21_create_matrix(4, 4, &A);

  A.matrix[0][0] = 3;
  A.matrix[0][1] = -3;
  A.matrix[0][2] = -5;
  A.matrix[0][3] = 8;
  A.matrix[1][0] = -3;
  A.matrix[1][1] = 2;
  A.matrix[1][2] = 4;
  A.matrix[1][3] = -6;
  A.matrix[2][0] = 2;
  A.matrix[2][1] = -5;
  A.matrix[2][2] = -7;
  A.matrix[2][3] = 5;
  A.matrix[3][0] = -4;
  A.matrix[3][1] = 3;
  A.matrix[3][2] = 5;
  A.matrix[3][3] = -6;

  s21_determinant(&A, &B);

  ck_assert((fabs(B) - fabs(R)) < 1e-7);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_test_5x5) {
  matrix_t A;
  double B, R = -69.0 / 4.0;
  s21_create_matrix(5, 5, &A);

  A.matrix[0][0] = 0.25;
  A.matrix[0][1] = 1.25;
  A.matrix[0][2] = 2.25;
  A.matrix[0][3] = 3.25;
  A.matrix[0][4] = 2.25;
  A.matrix[1][0] = 3.25;
  A.matrix[1][1] = 10;
  A.matrix[1][2] = 5.25;
  A.matrix[1][3] = 5.25;
  A.matrix[1][4] = 5.25;
  A.matrix[2][0] = 6.25;
  A.matrix[2][1] = 7.25;
  A.matrix[2][2] = 8.25;
  A.matrix[2][3] = 6.25;
  A.matrix[2][4] = 6.25;
  A.matrix[3][0] = 6.25;
  A.matrix[3][1] = 7.25;
  A.matrix[3][2] = 8.25;
  A.matrix[3][3] = 6.25;
  A.matrix[3][4] = 7.25;
  A.matrix[4][0] = 6.25;
  A.matrix[4][1] = 7.25;
  A.matrix[4][2] = 8.25;
  A.matrix[4][3] = 6;
  A.matrix[4][4] = 8.25;

  s21_determinant(&A, &B);

  ck_assert((fabs(B) - fabs(R)) < 1e-7);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_not_square) {
  matrix_t A;
  double B;
  s21_create_matrix(4, 5, &A);
  int res = s21_determinant(&A, &B);
  ck_assert_int_eq(res, ERROR_CALC);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_test_4x4_2) {
  matrix_t a;
  double number;
  s21_create_matrix(4, 4, &a);
  a.matrix[0][0] = 1;
  a.matrix[0][1] = 2;
  a.matrix[0][2] = 3;
  a.matrix[0][3] = 13;
  a.matrix[1][0] = 4;
  a.matrix[1][1] = 5;
  a.matrix[1][2] = 6;
  a.matrix[1][3] = 16;
  a.matrix[2][0] = 7;
  a.matrix[2][1] = 8;
  a.matrix[2][2] = 90;
  a.matrix[2][3] = 19;
  a.matrix[3][0] = 1;
  a.matrix[3][1] = 7;
  a.matrix[3][2] = 7;
  a.matrix[3][3] = 17;

  s21_determinant(&a, &number);
  ck_assert_int_eq(number, 13608);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(null_determinate) {
  matrix_t *B = NULL;
  double re = 0;
  int res = s21_determinant(B, &re);
  ck_assert_int_eq(res, NOTCORRECT);
}
END_TEST

START_TEST(determinant_test_3) {
  const int size = 5;
  matrix_t m = {0};
  s21_create_matrix(size, size, &m);

  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++) m.matrix[i][j] = j;
  double res = 0;
  int code = s21_determinant(&m, &res);
  ck_assert_double_eq_tol(res, 0, 1e-6);
  ck_assert_int_eq(code, OK);

  s21_remove_matrix(&m);
}
END_TEST

START_TEST(determinant_test_4) {
  const int size = 4;
  matrix_t m = {0};
  s21_create_matrix(size, size, &m);

  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++) m.matrix[i][j] = j + i;

  double res = 0;
  int code = s21_determinant(&m, &res);
  ck_assert_double_eq_tol(res, 0, 1e-6);
  ck_assert_int_eq(code, OK);

  s21_remove_matrix(&m);
}
END_TEST

START_TEST(determinant_test_5) {
  const int size = 5;
  matrix_t m = {0};
  s21_create_matrix(size, size, &m);
  m.matrix[0][1] = 6;
  m.matrix[0][2] = -2;
  m.matrix[0][3] = -1;
  m.matrix[0][4] = 5;
  m.matrix[1][3] = -9;
  m.matrix[1][4] = -7;
  m.matrix[2][1] = 15;
  m.matrix[2][2] = 35;
  m.matrix[3][1] = -1;
  m.matrix[3][2] = -11;
  m.matrix[3][3] = -2;
  m.matrix[3][4] = 1;
  m.matrix[4][0] = -2;
  m.matrix[4][1] = -2;
  m.matrix[4][2] = 3;
  m.matrix[4][4] = -2;

  double res = 0;
  int code = s21_determinant(&m, &res);
  ck_assert_double_eq_tol(res, 2480, 1e-6);
  ck_assert_int_eq(code, OK);

  s21_remove_matrix(&m);
}
END_TEST

START_TEST(determinant_test_6) {
  const int size = 3;
  matrix_t m = {0};
  s21_create_matrix(size, size, &m);
  m.matrix[0][0] = 2;
  m.matrix[0][1] = 3;
  m.matrix[0][2] = 1;
  m.matrix[1][0] = 7;
  m.matrix[1][1] = 4;
  m.matrix[1][2] = 1;
  m.matrix[2][0] = 9;
  m.matrix[2][1] = -2;
  m.matrix[2][2] = 1;

  double res = 0;
  int code = s21_determinant(&m, &res);
  ck_assert_double_eq_tol(res, -32, 1e-6);
  ck_assert_int_eq(code, OK);

  s21_remove_matrix(&m);
}
END_TEST

START_TEST(determinant_test_7) {
  const int size = 2;
  matrix_t m = {0};
  s21_create_matrix(size, size, &m);
  m.matrix[0][0] = -5;
  m.matrix[0][1] = -4;
  m.matrix[1][0] = -2;
  m.matrix[1][1] = -3;

  double res = 0;
  int code = s21_determinant(&m, &res);
  ck_assert_double_eq_tol(res, 7, 1e-6);
  ck_assert_int_eq(code, OK);

  s21_remove_matrix(&m);
}
END_TEST

// Обратная матрица

START_TEST(inverse_1) {
  matrix_t A, B, C;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &C);
  C.matrix[0][0] = 44300.0 / 367429.0;
  C.matrix[0][1] = -236300.0 / 367429.0;
  C.matrix[0][2] = 200360.0 / 367429.0;
  C.matrix[1][0] = 20600.0 / 367429.0;
  C.matrix[1][1] = 56000.0 / 367429.0;
  C.matrix[1][2] = -156483.0 / 367429.0;
  C.matrix[2][0] = 30900.0 / 367429.0;
  C.matrix[2][1] = 84000.0 / 367429.0;
  C.matrix[2][2] = -51010.0 / 367429.0;
  A.matrix[0][0] = 2.8;
  A.matrix[0][1] = 1.3;
  A.matrix[0][2] = 7.01;
  A.matrix[1][0] = -1.03;
  A.matrix[1][1] = -2.3;
  A.matrix[1][2] = 3.01;
  A.matrix[2][0] = 0;
  A.matrix[2][1] = -3;
  A.matrix[2][2] = 2;
  s21_inverse_matrix(&A, &B);

  int res = s21_eq_matrix(&B, &C);
  ck_assert_int_eq(res, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(inverse_2) {
  matrix_t A, C;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &C);
  C.matrix[0][0] = 1.0;
  C.matrix[0][1] = -1.0;
  C.matrix[0][2] = 1.0;
  C.matrix[1][0] = -38.0;
  C.matrix[1][1] = 41.0;
  C.matrix[1][2] = -34.0;
  C.matrix[2][0] = 27.0;
  C.matrix[2][1] = -29.0;
  C.matrix[2][2] = 24.0;
  A.matrix[0][0] = 2.0;
  A.matrix[0][1] = 5.0;
  A.matrix[0][2] = 7.0;
  A.matrix[1][0] = 6.0;
  A.matrix[1][1] = 3.0;
  A.matrix[1][2] = 4.0;
  A.matrix[2][0] = 5.0;
  A.matrix[2][1] = -2.0;
  A.matrix[2][2] = -3.0;
  matrix_t B;
  s21_inverse_matrix(&A, &B);
  int res = s21_eq_matrix(&B, &C);
  ck_assert_int_eq(res, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(inverse_3) {
  const int size = 3;
  matrix_t m = {0};
  s21_create_matrix(size, size, &m);

  m.matrix[0][0] = 2;
  m.matrix[0][1] = 5;
  m.matrix[0][2] = 7;
  m.matrix[1][0] = 6;
  m.matrix[1][1] = 3;
  m.matrix[1][2] = 4;
  m.matrix[2][0] = 5;
  m.matrix[2][1] = -2;
  m.matrix[2][2] = -3;

  matrix_t res = {0};
  s21_inverse_matrix(&m, &res);

  matrix_t expected = {0};
  s21_create_matrix(size, size, &expected);
  expected.matrix[0][0] = 1;
  expected.matrix[0][1] = -1;
  expected.matrix[0][2] = 1;
  expected.matrix[1][0] = -38;
  expected.matrix[1][1] = 41;
  expected.matrix[1][2] = -34;
  expected.matrix[2][0] = 27;
  expected.matrix[2][1] = -29;
  expected.matrix[2][2] = 24;

  ck_assert_int_eq(s21_eq_matrix(&expected, &res), SUCCESS);

  s21_remove_matrix(&expected);
  s21_remove_matrix(&res);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(inverse_normal) {
  matrix_t m = {0};
  matrix_t expected = {0};
  int codec1, codec2;
  codec1 = s21_create_matrix(3, 3, &m);
  if (!codec1) codec2 = s21_create_matrix(3, 3, &expected);

  if (!codec1 && !codec2) {
    m.matrix[0][0] = 2;
    m.matrix[0][1] = 5;
    m.matrix[0][2] = 7;

    m.matrix[1][0] = 6;
    m.matrix[1][1] = 3;
    m.matrix[1][2] = 4;

    m.matrix[2][0] = 5;
    m.matrix[2][1] = -2;
    m.matrix[2][2] = -3;

    expected.matrix[0][0] = 1;
    expected.matrix[0][1] = -1;
    expected.matrix[0][2] = 1;

    expected.matrix[1][0] = -38;
    expected.matrix[1][1] = 41;
    expected.matrix[1][2] = -34;

    expected.matrix[2][0] = 27;
    expected.matrix[2][1] = -29;
    expected.matrix[2][2] = 24;
    matrix_t result = {0};
    int code = s21_inverse_matrix(&m, &result);

    ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);
    ck_assert_int_eq(code, OK);

    s21_remove_matrix(&m);
    s21_remove_matrix(&result);
    s21_remove_matrix(&expected);
  }
}
END_TEST

START_TEST(inverse_not_sqare) {
  matrix_t m = {0};
  matrix_t result = {0};
  int codec = s21_create_matrix(1, 4, &m);
  if (!codec) {
    int code = s21_inverse_matrix(&m, &result);
    ck_assert_int_eq(code, ERROR_CALC);
    s21_remove_matrix(&m);
  }
}
END_TEST

START_TEST(inverse_one_by_one) {
  matrix_t m = {0};
  matrix_t result = {0};
  int codec = s21_create_matrix(1, 1, &m);
  if (!codec) {
    m.matrix[0][0] = 1431.12312331;
    int code = s21_inverse_matrix(&m, &result);
    ck_assert_int_eq(result.matrix[0][0] == (1.0 / m.matrix[0][0]), 1);
    ck_assert_int_eq(code, OK);
    s21_remove_matrix(&m);
    s21_remove_matrix(&result);
  }
}
END_TEST

START_TEST(inverse_zero_det) {
  matrix_t m = {0};
  matrix_t result = {0};
  int codec = s21_create_matrix(1, 1, &m);
  if (!codec) {
    int code = s21_inverse_matrix(&m, &result);
    ck_assert_int_eq(code, ERROR_CALC);
    s21_remove_matrix(&m);
  }
}
END_TEST

START_TEST(inverse_NOTCORRECT) {
  matrix_t m = {0};
  matrix_t result = {0};
  int code = s21_inverse_matrix(&m, &result);
  ck_assert_int_eq(code, NOTCORRECT);
}
END_TEST

Suite 

*s21_matrix_test(void) {
  Suite *suite = suite_create("s21_matrix");
  TCase *tCase = tcase_create("s21_matrix");

  // Создание и удаление матрицы
  tcase_add_test(tCase, create_matrix_positive);
  tcase_add_test(tCase, create_matrix_single_element);
  tcase_add_test(tCase, create_matrix_rectangle);
  tcase_add_test(tCase, create_matrix_large);
  tcase_add_test(tCase, create_matrix_zero_rows);
  tcase_add_test(tCase, create_matrix_zero_cols);
  tcase_add_test(tCase, create_matrix_negative_rows);
  tcase_add_test(tCase, create_matrix_negative_cols);
  tcase_add_test(tCase, create_matrix_zero_size);
  tcase_add_test(tCase, create_matrix_null_pointer);

  tcase_add_test(tCase, create_matrix);
  tcase_add_test(tCase, create_normal);
  tcase_add_test(tCase, create_no_rows);
  tcase_add_test(tCase, create_no_cols);
  tcase_add_test(tCase, create_NOTCORRECT);

  // Сравнение матриц
  tcase_add_test(tCase, eq_matrix_identical);
  tcase_add_test(tCase, eq_matrix_different);
  tcase_add_test(tCase, eq_matrix_diff_sizes);
  tcase_add_test(tCase, eq_matrix_near_equal);
  tcase_add_test(tCase, eq_matrix_null_pointer);
  tcase_add_test(tCase, eq_matrix_identical_single_element);
  tcase_add_test(tCase, eq_matrix_identical_one_column);
  tcase_add_test(tCase, eq_matrix_null_pointer_vs_matrix);
  tcase_add_test(tCase, eq_matrix_different_same_size);
  tcase_add_test(tCase, eq_matrix_zero_size_vs_normal);

  tcase_add_test(tCase, eq_matrix);
  tcase_add_test(tCase, not_eq_1);
  tcase_add_test(tCase, not_eq_2);

  // // Суммирование матриц
  tcase_add_test(tCase, sum_matrix_same_size);
  tcase_add_test(tCase, sum_matrix_different_size);
  tcase_add_test(tCase, sum_matrix_null_A);
  tcase_add_test(tCase, sum_matrix_null_B);
  tcase_add_test(tCase, sum_matrix_null_result);
  tcase_add_test(tCase, sum_matrix_large);
  tcase_add_test(tCase, sum_matrix_negative_value);
  tcase_add_test(tCase, sum_matrix_zero_value);
  tcase_add_test(tCase, sum_matrix_positive_value);
  tcase_add_test(tCase, sum_matrix_single_element);

  tcase_add_test(tCase, sum_matrix);
  tcase_add_test(tCase, sum_matrix_1);
  tcase_add_test(tCase, sum_matrix_2);
  tcase_add_test(tCase, sum_test_NOTCORRECT_matrix);
  tcase_add_test(tCase, sum_null);
  tcase_add_loop_test(tCase, sum_matrix, 0, 10);

  // // Вычитание матриц
  tcase_add_test(tCase, sub_matrix_same_size);
  tcase_add_test(tCase, sub_matrix_diff_size);
  tcase_add_test(tCase, sub_matrix_null_A);
  tcase_add_test(tCase, sub_matrix_null_B);
  tcase_add_test(tCase, sub_matrix_null_result);
  tcase_add_test(tCase, sub_matrix_single_element);
  tcase_add_test(tCase, sub_matrix_zero_rows);
  tcase_add_test(tCase, sub_matrix_zero_columns);
  tcase_add_test(tCase, sub_matrix_large);
  tcase_add_test(tCase, sub_matrix_negative_values);

  tcase_add_test(tCase, sub_test_1);
  tcase_add_test(tCase, sub_test_2);
  tcase_add_test(tCase, sub_test_NOTCORRECT_matrix);
  tcase_add_test(tCase, sub_null);

  // // Умножение матрицы на число
  tcase_add_test(tCase, test_mult_float);
  tcase_add_test(tCase, test_mult_large);
  tcase_add_test(tCase, test_mult_small);
  tcase_add_test(tCase, test_mult_random);
  tcase_add_test(tCase, test_mult_zero_result);

  tcase_add_loop_test(tCase, mult_number_matrix, 0, 100);
  tcase_add_test(tCase, mult_number_test_1);
  tcase_add_test(tCase, mult_number_test_2);
  tcase_add_test(tCase, mult_number_test_3);
  tcase_add_test(tCase, null_mult_num);

  // Умножение матрицы на матрицу
  tcase_add_test(tCase, test_mult_null_A);
  tcase_add_test(tCase, test_mult_null_B);
  tcase_add_test(tCase, test_mult_null_result);

  tcase_add_test(tCase, mult_matrix_test_1);
  tcase_add_test(tCase, mult_matrix_test_2);
  tcase_add_test(tCase, mult_matrix_test_null);

  // Транспонирование матрицы

  tcase_add_test(tCase, transpose_test_1);
  tcase_add_test(tCase, transpose_test_2);
  tcase_add_test(tCase, transpose_NOTCORRECT);

  // Минор матрицы и матрица алгебраических дополнений

  tcase_add_test(tCase, compliment_test_1);
  tcase_add_test(tCase, compliment_test_2);
  tcase_add_test(tCase, compliment_test_not_square);
  tcase_add_test(tCase, compliment_test_1x1);
  tcase_add_test(tCase, null_compliments);
  tcase_add_test(tCase, s21_calc_compl_2);
  tcase_add_test(tCase, s21_calc_compl_1);
  tcase_add_test(tCase, complements);
  tcase_add_test(tCase, empty);
  tcase_add_test(tCase, size_mismatch);

  // Определитель матрицы

  tcase_add_test(tCase, determinant_test_1);
  tcase_add_test(tCase, determinant_test_2);
  tcase_add_test(tCase, determinant_test_3);
  tcase_add_test(tCase, determinant_test_4);
  tcase_add_test(tCase, determinant_test_5);
  tcase_add_test(tCase, determinant_test_6);
  tcase_add_test(tCase, determinant_test_7);
  tcase_add_test(tCase, null_determinate);
  tcase_add_test(tCase, determinant_test_2x2);
  tcase_add_test(tCase, determinant_test_3x3_1);
  tcase_add_test(tCase, determinant_test_3x3_2);
  tcase_add_test(tCase, determinant_test_3x3_3);
  tcase_add_test(tCase, determinant_test_3x3_4);
  tcase_add_test(tCase, determinant_test_4x4);
  tcase_add_test(tCase, determinant_test_4x4_2);
  tcase_add_test(tCase, determinant_test_5x5);
  tcase_add_test(tCase, determinant_not_square);

  // Обратная матрица

  tcase_add_test(tCase, inverse_1);
  tcase_add_test(tCase, inverse_2);
  tcase_add_test(tCase, inverse_3);
  tcase_add_test(tCase, inverse_normal);
  tcase_add_test(tCase, inverse_not_sqare);
  tcase_add_test(tCase, inverse_zero_det);
  tcase_add_test(tCase, inverse_NOTCORRECT);
  tcase_add_test(tCase, inverse_one_by_one);

  suite_add_tcase(suite, tCase);

  return suite;
}

int main() {
  Suite *suite = s21_matrix_test();
  SRunner *sRunner = srunner_create(suite);
  srunner_set_fork_status(sRunner, CK_NOFORK);
  srunner_run_all(sRunner, CK_VERBOSE);
  int total_tests = srunner_ntests_run(sRunner);
  int failed_tests = srunner_ntests_failed(sRunner);
  srunner_free(sRunner);
  printf("\nВсего тестов: %d\n", total_tests);
  printf("Провалено тестов: %d\n", failed_tests);

  return (failed_tests == 0) ? 0 : 1;
}
