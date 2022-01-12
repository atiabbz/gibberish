#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

const char* CHARSET =
    "abcdefghijklmnopqrstuvwxyz"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "0123456789"
    "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";

unsigned int randint(unsigned int min, unsigned int max) {
  // https://stackoverflow.com/a/17554531
  int r;
  const unsigned int range =
      (1 + max - min < RAND_MAX) ? 1 + max - min : RAND_MAX;
  const unsigned int buckets = RAND_MAX / range;
  const unsigned int limit = buckets * range;

  do {
    r = rand();
  } while (r >= limit);

  return min + (r / buckets);
}

void clear() {
  // The double-pipe means try second command if first one failed
  // cls for Windows cmd || clear for Bash-like shells
  system("cls || clear");
}

void help() {
  printf(
      "Usage: gibberish [OPTION]"
      "\n  -f, --fast  Prints strings of length in range [72, 99] before relinquishing"
      "\n              control in each iteration."
      "\n  -s, --slow  Prints one character and relinquishes control in each iteration."
      "\n  -h, --help  Prints this help-text."
      "\nPrint a stream of random characters from ASCII letters (upper and lower),"
      "\ndigits, and punctuation characters.\n");
}

void fast() {
  clear();
  while (1) {
    // https://python.org/dev/peps/pep-0008/#maximum-line-length
    int len = randint(72, 99);
    char buffer[len + 1];

    for (int i = 0; i < len; i++) {
      int c = randint(0, strlen(CHARSET));
      buffer[i] = CHARSET[c];
    }
    buffer[len] = '\0';

    printf("%s", buffer);
    Sleep(1);
  }
}

void slow() {
  clear();
  while (1) {
    int c = randint(0, strlen(CHARSET));
    printf("%c", CHARSET[c]);
    Sleep(1);
  }
}

int main(int argc, char* argv[]) {
  srand(time(NULL));

  if (argc == 1) {
    fast();
  } else if (argc == 2) {
    char* arg = argv[1];
    if (!strcmp("--slow", arg) || !strcmp("-s", arg)) {
      slow();
    } else if (!strcmp("--fast", arg) || !strcmp("-f", arg)) {
      fast();
    } else {
      help();
    }
  } else {
    help();
  }
}