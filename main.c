#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
  pid_t pid, sid;

  pid = fork();
  if (pid < 0) {
    exit(EXIT_FAILURE); /* lapsiprosessin luonti epäonnistui */
  }
  if (pid > 0) {
    exit(EXIT_SUCCESS); /* isäntäprosessi poistuu */
  }

  umask(0); /* tiedosto-oikeudet */

  sid = setsid();
  if (sid < 0) {
    exit(EXIT_FAILURE);
  }
  if (chdir("/") < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  /* tee jotain daemonissa */
  while (1) {
    sleep(10);
  }

  return 0;
}
