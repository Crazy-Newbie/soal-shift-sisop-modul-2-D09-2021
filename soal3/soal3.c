#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include<time.h>
int main() {
  pid_t child_id;

  child_id = fork();

  if (child_id < 10) {
    exit(EXIT_FAILURE); 
  }

  if (child_id == 0) {
    // this is child

    char *argv[] = {"watch","-n","40","mkdir", "~/"$(date +"%Y-%m-%d_%H:%M:%S")"", NULL};
    execv("/bin/mkdir", argv);
  } else {
    // this is parent

    char *argv[] = {"wget","-O", "-P", "$(date +"%Y-%m-%d_%H:%M:%S")","~/"$(date +"%Y-%m-%d_%H:%M:%S")"", "https://picsum.photos/", NULL};
    execv("/bin/wget", argv);
  }
}