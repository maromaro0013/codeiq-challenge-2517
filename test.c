#include <stdio.h>
#include <stdlib.h>
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

// 位置と距離を指定して、周囲の素数の数を調べる
int around_from_point_and_diff(POINT p, int diff, POINT* p_points, int points_count) {
  // 第一象限
  int x = 0;
  int y = 0;
  for (x = diff; x >= 0; x--) {
    if (p.y+y >= 0) {
      POINT tmp_point = {p.x+x, p.y+y};
      int num = number_from_point(tmp_point);
      if (isPrime(num)) {
        return 1;
      }
    }
    y--;
  }

  // 第二象限
  x = 0;
  y = 0;
  for (x = diff; x >= 0; x--) {
    POINT tmp_point = {p.x+x, p.y+y};
    int num = number_from_point(tmp_point);
    if (isPrime(num)) {
      return 1;
    }
    y++;
  }

  // 第三象限
  x = 0;
  y = 0;
  for (x = -diff; x <= 0; x++) {
    if (p.x+x >= 0) {
      POINT tmp_point = {p.x+x, p.y+y};
      int num = number_from_point(tmp_point);
      if (isPrime(num)) {
        return 1;
      }
    }
    y++;
  }

  // 第四象限
  x = 0;
  y = 0;
  for (x = -diff; x <= 0; x++) {
    if (p.x+x >= 0 && p.y+y >= 0) {
      POINT tmp_point = {p.x+x, p.y+y};
      int num = number_from_point(tmp_point);
      if (isPrime(num)) {
        return 1;
      }
    }
    y--;
  }

  return 0;
}

int main() {
  char input_str[256];
  POINT points[0xff];

  // 数値の入力を受け取る
  fgets(input_str, sizeof(input_str), stdin);
  int input_num = atoi(input_str);

  int prime_cnt = 0;
  int primes[4] = {0,0,0,0};

  // 数値の位置を求める
  POINT num_point = point_from_number(atoi(input_str));

  int is_prime = around_from_point_and_diff(num_point, 2, points, 0xff);

  if (is_prime) {
    printf("true");
  }
  else {
    printf("false");
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
  printf("\n");

  return 0;
}
