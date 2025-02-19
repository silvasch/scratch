#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include <uuid.h>

#ifdef __linux__
  #define TMP_DIR "/tmp/"
#elif
  #define TMP_DIR ""
#endif

#define TMP_DIR_LEN sizeof(TMP_DIR)

int main(int argc, char *argv[]) {
  if (strcmp(TMP_DIR, "") == 0) {
    fprintf(stderr, "unsupported operating system\n");
    return 1;
  }
  
  char *editor = getenv("EDITOR");
  if (editor == NULL) {
    editor = "nano";
  }

  uuid_t binuuid;
  uuid_generate_random(binuuid);
  char *uuid = malloc(UUID_STR_LEN);
  uuid_unparse_lower(binuuid, uuid);

  char file_path[TMP_DIR_LEN + UUID_STR_LEN + 3];
  sprintf(file_path, "%s%s.md", TMP_DIR, uuid);

  pid_t pid;
  pid = fork();

 
  if (pid < 0) {
    fprintf(stderr, "forking failed\n");
    return 1;
  } else if (pid == 0) {
    // char *args[] = { file_path, NULL };
    char *args[3];
    args[0] = editor;
    args[1] = file_path;
    args[2] = NULL;
    execvp(editor, args);
  } else {
    wait(NULL);
    printf("wrote scratch file to '%s'\n", file_path);
  }

  free(uuid);
  
  return 0;
}
