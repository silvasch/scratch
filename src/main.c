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

#define FILE_PATH_LEN sizeof(TMP_DIR) + UUID_STR_LEN + 11

char *get_editor() {
  char* editor = getenv("EDITOR");
  if (editor == NULL) {
    editor = "nano";
  }
  return editor;
}

char *get_uuid() {
  uuid_t binuuid;
  uuid_generate_random(binuuid);
  char *uuid = malloc(UUID_STR_LEN);
  uuid_unparse_lower(binuuid, uuid);
  return uuid;
}

void run_editor(char *editor, char file_path[FILE_PATH_LEN]) {
    char *args[3];
    args[0] = editor;
    args[1] = file_path;
    args[2] = NULL;
    execvp(editor, args);
}

int main(int argc, char *argv[]) {
  if (strcmp(TMP_DIR, "") == 0) {
    fprintf(stderr, "unsupported operating system.\n");
    return 1;
  }
  
  char *editor = get_editor();
  char *uuid = get_uuid();
   
  char file_path[FILE_PATH_LEN];
  sprintf(file_path, "%sscratch-%s.md", TMP_DIR, uuid);

  printf("creating scratch file in '%s'.\n", file_path);

  pid_t pid;
  pid = fork();
 
  if (pid < 0) {
    fprintf(stderr, "forking failed\n");
    return 1;
  } else if (pid == 0) {
    run_editor(editor, file_path);
  } else {
    wait(NULL);
  }

  free(uuid);
  
  return 0;
}
