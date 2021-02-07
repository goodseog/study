void test(unsigned char* FREQ, const unsigned char* BITMAP) {
  unsigned char memo[64] = {
    0, 
    1, 
    1, 2, 
    1, 2, 2, 3,
    1, 2, 2, 3, 2, 3, 3, 4,
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6
  };

  int wcur = 1000000;
  for(int y = 0 ; y < 6000 ; y += 6) {
    unsigned short stack[6] = {0, };
    int length = 0;
    for(int x = 0 ; x < 750 ; x++) {
      stack[0] = stack[0] << 8 | BITMAP[(y+0)*750 + x];
      stack[1] = stack[1] << 8 | BITMAP[(y+1)*750 + x];
      stack[2] = stack[2] << 8 | BITMAP[(y+2)*750 + x];
      stack[3] = stack[3] << 8 | BITMAP[(y+3)*750 + x];
      stack[4] = stack[4] << 8 | BITMAP[(y+4)*750 + x];
      stack[5] = stack[5] << 8 | BITMAP[(y+5)*750 + x];
      length += 8;

      while( length >= 6 ) {
        unsigned char value = 0;
        int shift = length - 6;
        unsigned short mask = ~(0xFFFF << shift);
        value += memo[stack[0] >> shift]; stack[0] &= mask;
        value += memo[stack[1] >> shift]; stack[1] &= mask;
        value += memo[stack[2] >> shift]; stack[2] &= mask;
        value += memo[stack[3] >> shift]; stack[3] &= mask;
        value += memo[stack[4] >> shift]; stack[4] &= mask;
        value += memo[stack[5] >> shift]; stack[5] &= mask;

        FREQ[--wcur] = value + 'J';
        length -= 6;
      }
    }
  }
}

// 0 - 36
void comp(unsigned char* COMP, const unsigned char* FREQ) {
  unsigned short buffer = 0;
  for(int i = 0, j = 0 ; i + 2 < 1000000 ; i += 3, j += 2) {
    buffer = (FREQ[i+0] - 'J') +
             ((FREQ[i+1] - 'J') * 37) +
             ((FREQ[i+2] - 'J') * 1369);    
    COMP[j+0] = buffer & 0xFF;
    COMP[j+1] = buffer >> 8;
  }
  COMP[666666] = FREQ[999999];
}

void decomp(unsigned char* FREQ, const unsigned char* COMP) {
  unsigned short buffer;
  for(int i = 0, j = 0 ; i + 2 < 1000000 ; i += 3, j += 2) {
    buffer = *((unsigned short*)(COMP + j));
    FREQ[i+0] = (buffer % 37) + 'J'; buffer /= 37;
    FREQ[i+1] = (buffer % 37) + 'J'; buffer /= 37;
    FREQ[i+2] = buffer + 'J';
  }
  FREQ[999999] = COMP[666666];
}
