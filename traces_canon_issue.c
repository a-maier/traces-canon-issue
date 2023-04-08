#include "nauty/traces.h"
#include "nauty/nausparse.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    DYNALLSTAT(int,lab,lab_sz);
    DYNALLSTAT(int,ptn,ptn_sz);
    DYNALLSTAT(int,orbits,orbits_sz);
    DEFAULTOPTIONS_TRACES(options);
    options.getcanon = TRUE;
    options.defaultptn = FALSE;

    TracesStats stats;

    const int n = 6;
    const int n_edges = 8;
    DYNALLOC1(int,lab,lab_sz,n,"malloc");
    DYNALLOC1(int,ptn,ptn_sz,n,"malloc");
    DYNALLOC1(int,orbits,orbits_sz,n,"malloc");

    const int m = SETWORDSNEEDED(n);
    nauty_check(WORDSIZE,m,n,NAUTYVERSIONID);

    SG_DECL(cg0);
    {
      SG_DECL(sg);
      SG_ALLOC(sg, n, n_edges, "malloc");
      sg.nv = n;
      sg.nde = n_edges;
      static const size_t V[] = {0, 1, 3, 4, 5, 7};
      static const int D[] = {1, 2, 1, 1, 2, 1};
      static const int E[] = {1, 0, 2, 1, 4, 3, 5, 4};
      memcpy(sg.v, V, n * sizeof(*V));
      memcpy(sg.d, D, n * sizeof(*D));
      memcpy(sg.e, E, n_edges * sizeof(*E));

      static const int LAB[] = {3, 0, 5, 4, 2, 1};
      memcpy(lab, LAB, n * sizeof(*LAB));
      static const int PTN[] = {1, 0, 1, 1, 1, 0};
      memcpy(ptn, PTN, n * sizeof(*PTN));
      Traces(&sg, lab, ptn, orbits, &options, &stats, &cg0);
    }
    printf("[");
    printf("%d", lab[0]);
    for(int i = 1; i < n; ++i) {
      printf(", %d", lab[i]);
    }
    printf("], [");

    SG_DECL(cg1);
    {
      SG_DECL(sg);
      SG_ALLOC(sg, n, n_edges, "malloc");
      sg.nv = n;
      sg.nde = n_edges;
      static const size_t V[] = {0, 1, 2, 4, 5, 7};
      static const int D[] = {1, 1, 2, 1, 2, 1};
      static const int E[] = {4, 2, 1, 3, 2, 0, 5, 4};
      memcpy(sg.v, V, n * sizeof(*V));
      memcpy(sg.d, D, n * sizeof(*D));
      memcpy(sg.e, E, n_edges * sizeof(*E));

      static const int LAB[] = {5, 1, 4, 3, 2, 0};
      memcpy(lab, LAB, n * sizeof(*LAB));
      Traces(&sg, lab, ptn, orbits, &options, &stats, &cg1);
    }
    printf("%d", lab[0]);
    for(int i = 1; i < n; ++i) {
      printf(", %d", lab[i]);
    }
    puts("]");

    if(aresame_sg(&cg0, &cg1) == TRUE) {
      return EXIT_SUCCESS;
    } else {
      puts("Not a canonical labelling!");
      return EXIT_FAILURE;
    }
}
