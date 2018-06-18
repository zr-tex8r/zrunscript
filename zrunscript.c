/*
 * This is file 'zrunscript.c'.
 * Copyright (c) 2018 Takayuki YATO (aka. "ZR")
 *   GitHub:   https://github.com/zr-tex8r
 *   Twitter:  @zr_tex8r
 *
 * This software is distributed under the MIT License.
 */
#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <windows.h>

static char program[] = "zrunscript";
static char white[] = " \t=";

static char line[1024];
static char cfg_file[512];
static char scr_file[512];
static char exe_file[512];

int main (int argc, char *argv[]) {
  int k, len;
  char *p, *psext;
  const char **nargv;
  FILE *fcfg, *fscr;

  GetModuleFileNameA(NULL, cfg_file, sizeof(cfg_file) - sizeof(program) - 6);

  /* prepare string scr_file */
  strcpy(scr_file, cfg_file);
  if ((psext = strrchr(scr_file, '.')) == NULL)
     goto Error;

  /* make string cfg_file */
  if ((p = strrchr(cfg_file, '\\')) == NULL)
     goto Error;
  strcpy(p + 1, program);
  strcat(cfg_file, ".cfg");

  /* read cfg_file */
  exe_file[0] = '\0';
  if ((fcfg = fopen(cfg_file, "r")) == NULL)
    goto Error_cfg;
  while (fgets(line, sizeof(line), fcfg) != NULL) {
    if (line[0] != '.')
      continue;
    /* parse line */
    if ((p = strrchr(line, '\n')) == NULL)
      goto Error_cfg;
    *p = '\0';
    len = strcspn(line, white);
    p = line + len;
    len = strspn(p, white);
    *p = '\0';
    if (*(p += len) == '\0')
      goto Error_cfg;
    strcpy(psext, line);
    /* file check */
    if ((fscr = fopen(scr_file, "r")) == NULL)
      continue;
    fclose(fscr);
    if ((len = strlen(p)) > sizeof(exe_file) + 5)
      goto Error;
    /* set string exe_file */
    strcpy(exe_file, p);
    if (p[len - 4] != '.')
      strcat(exe_file, ".exe");
    break;
  }
  fclose(fcfg);

  /* check for exe_file */
  if (exe_file[0] == '\0') {
    psext[0] = '\0';
    fprintf(stderr, "%s: no script file '%s.*'", program, scr_file);
    return EXIT_FAILURE;
  }

  /* run the interpreter */
  if ((nargv = malloc(sizeof(char *) * (argc + 2))) == NULL)
    goto Error;
  nargv[0] = exe_file;
  nargv[1] = scr_file;
  for (k = 1; k < argc; k++) {
    nargv[k + 1] = argv[k];
  }
  nargv[argc + 1] = NULL;
  if ((k = _spawnvp(_P_WAIT, nargv[0], nargv)) < 0)
    fprintf(stderr, "%s: can't run %s", program, exe_file);
  return k;

Error_cfg:
  fprintf(stderr, "%s: bad config file '%s'\n", program, cfg_file);
  fcloseall();
  return EXIT_FAILURE;

Error:
  fprintf(stderr, "%s: internal error\n", program);
  fcloseall();
  return EXIT_FAILURE;
}
