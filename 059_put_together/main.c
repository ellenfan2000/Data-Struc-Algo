#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  counts_t * c = createCounts();
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    perror("Cannot Open file.");
    exit(EXIT_FAILURE);
  }
  char * line = NULL;
  size_t sz = 0;
  while (getline(&line, &sz, f) >= 0) {
    //remove "\n"
    if (strchr(line, '\n') != NULL) {
      line[strlen(line) - 1] = '\0';
    }

    addCount(c, lookupValue(kvPairs, line));
  }
  free(line);
  fclose(f);

  return c;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  if (argc < 3) {
    perror("Usage:");
    return EXIT_FAILURE;
  }
  kvarray_t * kv = readKVs(argv[1]);

  //count from 2 to argc (call the number you count i)
  counts_t * c;
  char * outputName;
  for (int i = 2; i < argc; i++) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    c = countFile(argv[i], kv);
    //   (call this result c)

    //compute the output file name from argv[i] (call this outName)
    outputName = computeOutputFileName(argv[i]);

    //open the file named by outName (call that f)
    FILE * f = fopen(outputName, "w");
    //print the counts from c into the FILE f
    printCounts(c, f);
    //close f
    fclose(f);
    //free the memory for outName and c
    free(outputName);
    freeCounts(c);
  }
  //free the memory for kv
  freeKVs(kv);
  return EXIT_SUCCESS;
}
