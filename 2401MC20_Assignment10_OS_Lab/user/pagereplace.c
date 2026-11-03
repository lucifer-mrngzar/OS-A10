#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define N 20
#define MAXF 5

int ref[N] = {
  7, 0, 1, 2, 0, 3, 0, 4, 2, 3,
  0, 3, 2, 1, 2, 0, 1, 7, 0, 1
};

int results[3][3][2];

void
simulate(char *name, int algorithm, int nf)
{
  int frame[MAXF];
  int last[MAXF];
  int next[MAXF];
  int i, j, k;
  int hit, faults = 0, hits = 0;
  int pointer = 0;
  int victim, farthest, found;

  for(i = 0; i < nf; i++){
    frame[i] = -1;
    last[i] = -1;
  }

  printf("\n%s - %d FRAMES\n", name, nf);
  printf("Page\tFrames\t\tResult\n");

  for(i = 0; i < N; i++){
    hit = 0;
    victim = -1;

    for(j = 0; j < nf; j++){
      if(frame[j] == ref[i]){
        hit = 1;
        victim = j;
        break;
      }
    }

    if(hit){
      hits++;
      if(algorithm == 1)
        last[victim] = i;
    }
    else{
      faults++;

      for(j = 0; j < nf; j++){
        if(frame[j] == -1){
          victim = j;
          break;
        }
      }

      if(victim == -1){
        if(algorithm == 0){
          victim = pointer;
          pointer = (pointer + 1) % nf;
        }
        else if(algorithm == 1){
          victim = 0;
          for(j = 1; j < nf; j++){
            if(last[j] < last[victim])
              victim = j;
          }
        }
        else{
          farthest = -1;
          victim = 0;

          for(j = 0; j < nf; j++){
            found = 0;
            next[j] = N + 1;

            for(k = i + 1; k < N; k++){
              if(ref[k] == frame[j]){
                next[j] = k;
                found = 1;
                break;
              }
            }

            if(!found){
              victim = j;
              farthest = N + 1;
              break;
            }

            if(next[j] > farthest){
              farthest = next[j];
              victim = j;
            }
          }
        }
      }

      frame[victim] = ref[i];

      if(algorithm == 1)
        last[victim] = i;
    }

    printf("%d\t", ref[i]);

    for(j = 0; j < nf; j++){
      if(frame[j] == -1)
        printf("- ");
      else
        printf("%d ", frame[j]);
    }

    if(hit)
      printf("\tHIT\n");
    else
      printf("\tFAULT\n");
  }

  results[nf - 3][algorithm][0] = hits;
  results[nf - 3][algorithm][1] = faults;

  printf("Hits: %d | Faults: %d | Hit ratio: %d%% | Fault ratio: %d%%\n",
         hits, faults, hits * 100 / N, faults * 100 / N);
}

int
main(void)
{
  int nf;

  printf("\n===== PAGE REPLACEMENT ALGORITHMS =====\n");
  printf("Reference string: 7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1\n");

  for(nf = 3; nf <= 5; nf++){
    simulate("FIFO", 0, nf);
    simulate("LRU", 1, nf);
    simulate("OPTIMAL", 2, nf);
  }

  printf("\n===== FINAL COMPARISON TABLE =====\n");
  printf("Frames  Algorithm  Hits  Faults  Hit ratio  Fault ratio\n");

  for(nf = 3; nf <= 5; nf++){
    int a;
    char *names[] = {"FIFO", "LRU", "OPTIMAL"};

    for(a = 0; a < 3; a++){
      int h = results[nf - 3][a][0];
      int f = results[nf - 3][a][1];

      printf("%d       %s       %d     %d       %d%%        %d%%\n",
             nf, names[a], h, f, h * 100 / N, f * 100 / N);
    }
  }

  exit(0);
}
