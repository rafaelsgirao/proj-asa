#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
  if (argc != 2) {
    printf("Usage: %s <number of vertexes>\n", argv[0]);
    return 1;
  }

  int num_vertexes = atoi(argv[1]);

  // Generate a complete graph with num_vertexes vertexes
  printf("%d\n", num_vertexes);
  printf("%d\n", num_vertexes * (num_vertexes - 1) / 2);
  for (int i = 0; i < num_vertexes; i++) {
    for (int j = i + 1; j < num_vertexes; j++) {
      printf("%d %d %d\n", i + 1, j + 1, 1);
    }
  }

  return 0;
}

