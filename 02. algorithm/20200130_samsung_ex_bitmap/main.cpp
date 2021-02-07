#include <memory.h>
#include <stdio.h>
#include <time.h>
#define TC 1  // it will be changed in evaluation

void test(unsigned char* FREQ, const unsigned char* BITMAP);
void comp(unsigned char* COMP, const unsigned char* FREQ);
void decomp(unsigned char* FREQ, const unsigned char* COMP);

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

static void clear(unsigned char* FREQ) {
  for (int y = 0; y < 1000; y++)
    for (int x = 0; x < 1000; x++) 
      FREQ[y * 1000 + x] = 0;
}

static int sample(const unsigned char* BITMAP, int x, int y) {
  unsigned char mask;

  if (((0 <= x) && (x <= 5999)) == 0) return -1;
  if (((0 <= y) && (y <= 5999)) == 0) return -1;

  mask = 0x80 >> (x % 8);
  x = x / 8;
  y = y * (6000 / 8);

  if ((BITMAP[y + x] & mask) == mask)
    return 1;
  else
    return 0;
}

static void add(unsigned char* FREQ, int x, int y) {
  if (((0 <= x) && (x <= 5999)) == 0) return;
  if (((0 <= y) && (y <= 5999)) == 0) return;

  x = x / 6;
  y = y / 6 * 1000;

  FREQ[y + x]++;
}

static void count(unsigned char* FREQ, const unsigned char* BITMAP) {
  for (int y = 0; y < 6000; y++)
    for (int x = 0; x < 6000; x++)
      if (sample(BITMAP, x, y) == 1) 
        add(FREQ, x, y);
}

// x 대칭
static void process1(unsigned char* FREQ) {
  for (int y = 0; y < 1000; y++)
    for (int x = 0; x < 500; x++) {
      unsigned char tmp = FREQ[y * 1000 + x];
      FREQ[y * 1000 + x] = FREQ[y * 1000 + (999 - x)];
      FREQ[y * 1000 + (999 - x)] = tmp;
    }
}

static void process2(unsigned char* FREQ) {
  for (int y = 0; y < 500; y++)
    for (int x = 0; x < 1000; x++) {
      unsigned char tmp = FREQ[y * 1000 + x];
      FREQ[y * 1000 + x] = FREQ[(999 - y) * 1000 + x];
      FREQ[(999 - y) * 1000 + x] = tmp;
    }
}

static void process3(unsigned char* FREQ) {
  for (int y = 0; y < 1000; y++)
    for (int x = 0; x < 1000; x++) FREQ[y * 1000 + x] += 'J';
}

static void build(unsigned char* FREQ, const unsigned char* BITMAP) {
  clear(FREQ);
  count(FREQ, BITMAP);
  process1(FREQ);
  process2(FREQ);
  process3(FREQ);
}

static unsigned int random(void) {
  static unsigned long long seed = 70;  // it will be changed in evaluation
  return ((unsigned int)((seed = seed * 685728378367ULL + 11ULL) >> 16));
}

int main(void) {
  static unsigned char BITMAP[4500000];
  static unsigned char dummy1[1026];
  static unsigned char FREQ1[1000000];
  static unsigned char dummy2[8597];
  static unsigned char FREQ2[1000000];
  static unsigned char dummy3[2329];
  static unsigned char FREQ3[1000000];
  static unsigned char dummy4[3352];
  static unsigned char COMP1[700000];
  static unsigned char dummy5[2607];
  static unsigned char COMP2[700000];

  int SCORE = 30000000 * TC;
  for (int tc = 0; tc < TC; tc++) {
    for (int c = 0; c < 4500000; c++) BITMAP[c] = random();

    build(FREQ1, BITMAP);
    clock_t begin = clock();
    test(FREQ2, BITMAP);
    comp(COMP1, FREQ2);
    memcpy(COMP2, COMP1, 700000);
    decomp(FREQ3, COMP2);

    SCORE += (clock() - begin) / (CLOCKS_PER_SEC / 1000);

    if (memcmp(FREQ1, FREQ2, 1000000) == 0) SCORE -= 20000000;
    if (memcmp(FREQ1, FREQ3, 1000000) == 0) SCORE -= 10000000;
  }
  printf("SCORE: %d\n", SCORE);

  return 0;
}
