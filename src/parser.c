#include "../include/parser.h"
#include "../include/builtin.h"
#include "../include/utils.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

bool isbuiltin(char *input) {
  size_t size = strlen(input);
  char cmd[100];

  for (size_t i = 0; i < size; ++i) {
    if (input[i] != '\t' && input[i] != ' ') {
      cmd[i] = input[i];
    } else {
      break;
    };
  };

  if (strncmp("exit", cmd, 4) == 0) {
    char **s = get_args(input);
    int n = atoi((char *)s);
    micro_exit(n);
    return true;
  };
  if (strncmp("echo", cmd, 4) == 0) {
    char **s = get_args(input);
    micro_echo(s);
    return true;
  };

  if (strncmp("type", cmd, 4) == 0) {
    char **s = get_args(input);
    if (micro_type(s[1]))
      printf("%s is a shell builtin", s[1]);
    else
      get_path(s[1]);

    return true;
  };

  return false;
};
char **get_args(char *input) {
  size_t size = strlen(input);

  char *word = (char *)malloc((30 + 1) * sizeof(char));
  char **args = (char **)malloc(200 * sizeof(char *));
 
  int word_counter = 0;
  int args_counter = 0;

  if (word == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(1);
  }

  for (int i = 0; i < size; ++i) {
    if (input[i] == '"') {
      continue;
    }
    if (isspace(input[i]) == 0) {
      word[word_counter++] = input[i];
    } else {
      word[word_counter + 1] = '\0';
      args[args_counter] = (char *)malloc((10 + 1) * sizeof(char));
      if (args[args_counter] == NULL) {
        fprintf(stderr, "Memory allocation failed for word %d\n", i);
        exit(1);
      }

      args[args_counter] = word;
      args_counter++;
      word_counter = 0;
    }
  };




  for (size_t i = 0; i < 10; i++) {

    printf("%s", args[i]);
  }


  return args;
};
