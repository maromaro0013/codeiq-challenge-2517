#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct POINT {
  int x;
  int y;
}POINT_t;

// 素数判定
int isPrime(int num) {
  if (num == 1) {
    return 0;
  }
  if (num == 2) {
    return 1;
  }
  if (num%2 == 0) {
    return 0;
  }
  
  // 2より大きい奇数だけで良い
  int i = 0;
  for (i = 3; i < num; i += 2) {
    if (num%i == 0) {
      return 0;
    }
  }

  return 1;
}

// 指定の位置から数値を求める
int number_from_point(POINT p) {
  if (p.x == 0 && p.y == 0) {
    return 1;
  }

  if (p.y > p.x) {
    return pow(p.y+1, 2) - p.x;
  }

  return pow(p.x, 2) + 1 + p.y;
}

// 指定の数値から位置を求める
POINT point_from_number(int num) {
  if (num == 1) {
    POINT ret = {0, 0};
    return ret;
  }

  int z = (int)sqrt(num - 1);
  int t = (int)pow(z+1, 2) - z;

  POINT ret = {z, z};
  if (num < t) {
    ret.x = z;
    ret.y = z - (t - num);
  }
  else if (num > t) {
    ret.x = z - (num - t);
    ret.y = z;
  }

  return ret;
}

// 位置の重複チェック
int overlap_point_chk(POINT p, POINT* p_points, int points_count) {
  int i = 0;
  for (i = 0; i < points_count; i++) {
    if (p.x == p_points[i].x && p.y == p_points[i].y) {
      return 1;
    }
  }
  return 0;
}

// 位置と距離を指定して、周囲の素数の数を調べる
int around_from_point_and_diff(POINT p, int diff, POINT* p_points, int points_count) {
  int return_count = 0;

  // 周囲を見る
  int x = diff;
  int y = -diff;
  for (y = -diff; y <= diff; y++) {
    POINT tmp_point = {p.x+x, p.y+y};
    int num = number_from_point(tmp_point);
    if (isPrime(num)) {
      if (return_count < points_count) {
        p_points[return_count] = tmp_point;
        return_count++;
      }
    }
  }
  y = diff;

  for (x = diff; x >= -diff; x--) {
    POINT tmp_point = {p.x+x, p.y+y};
    int num = number_from_point(tmp_point);
    if (isPrime(num)) {
      if (return_count < points_count) {
        p_points[return_count] = tmp_point;
        return_count++;
      }
    }
  }
  x = -diff;

  for (y = diff; y >= -diff; y--) {
    POINT tmp_point = {p.x+x, p.y+y};
    int num = number_from_point(tmp_point);
    if (isPrime(num)) {
      if (return_count < points_count) {
        p_points[return_count] = tmp_point;
        return_count++;
      }
    }
  }
  y = -diff;

  for (x = -diff; x < diff; x++) {
    POINT tmp_point = {p.x+x, p.y+y};
    int num = number_from_point(tmp_point);
    if (isPrime(num)) {
      if (return_count < points_count) {
        p_points[return_count] = tmp_point;
        return_count++;
      }
    }
  }
  return return_count;
}

int main() {
  char input_str[256];
  POINT points[0xff];

  // 数値の入力を受け取る
  fgets(input_str, sizeof(input_str), stdin);
  int input_num = atoi(input_str);

  // 数値の位置を求める
  POINT num_point = point_from_number(atoi(input_str));

  memset(points, 0, sizeof(points));
  int prime_count = 0;
  int depth = 1;
  while (prime_count == 0 && depth < 0xffff) {
    prime_count = around_from_point_and_diff(num_point, depth, points, 0xff);
    depth++;
  }

  printf("test:%d\n", prime_count);
  int primes[256];
  int i = 0;
  for (i = 0; i < prime_count; i++) {
    primes[i] = number_from_point(points[i]);
  }

  // 昇順にソート(ふつうのバブルソート)
  for (i = 0; i < prime_count; i++) {
    int j = 0;
    for (j = i; j < prime_count - 1; j++) {
      if (primes[j] > primes[j + 1]) {
        int tmp = primes[j];
        primes[j] = primes[j + 1];
        primes[j + 1] = tmp;
      }
    }
  }

  for (i = 0; i < prime_count; i++) {
    printf("%d\n", primes[i]);
  }

  /*
  // 左隣の数値を求める
  if (num_point.x > 0) {
    POINT p = {num_point.x - 1, num_point.y};
    int num = number_from_point(p);
    if (isPrime(num)) {
      primes[prime_cnt] = num;
      prime_cnt += 1;
    }
  }

  // 右隣の数値を求める
  {
    POINT p = {num_point.x + 1, num_point.y};
    int num = number_from_point(p);
    if (isPrime(num)) {
      primes[prime_cnt] = num;
      prime_cnt += 1;
    }
  }

  // 上にある数値を求める
  if (num_point.y > 0) {
    POINT p = {num_point.x, num_point.y - 1};
    int num = number_from_point(p);
    if (isPrime(num)) {
      primes[prime_cnt] = num;
      prime_cnt += 1;
    }
  }
  
  // 下にある数値を求める
  {
    POINT p = {num_point.x, num_point.y + 1};
    int num = number_from_point(p);
    if (isPrime(num)) {
      primes[prime_cnt] = num;
      prime_cnt += 1;
    }
  }
  
  // 昇順にソート(ふつうのバブルソート)
  int i = 0;
  for (i = 0; i < prime_cnt; i++) {
    int j = 0;
    for (j = i; j < prime_cnt - 1; j++) {
      if (primes[j] > primes[j + 1]) {
        int tmp = primes[j];
        primes[j] = primes[j + 1];
        primes[j + 1] = tmp;
      }
    }
  }
  
  for (i = 0; i < prime_cnt; i++) {
    printf("%d", primes[i]);
    if (i < prime_cnt - 1) {
      printf(",");
    }
  }
  */

  return 0;
}
