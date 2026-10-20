#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

/* log <file> <command> [ <args> ] 
 * 
 * Exécution de la commande "<command> <args>" et on duplique sa
 * sortie standard dans le fichier <file>.
 *
 * Exemple : gcc -std=c99 log.c ; rm toto ; ./a.out ./toto ls
 */

int main (int argc, char *argv[])
{  
  int pid, p[2], file;
  
  // création d'un pipe partagé par le père et le fils
  if(pipe(p) == -1) 
    { perror("pipe"); exit(EXIT_FAILURE); }  
  
  /* 
   *                ---------------------------
   * Fils: 1 ---> ( p[1]      PIPE      p[0] ( ---> Fils: <file>
   *                ---------------------------
   *
   */  
  
  // création d'un processus fils...
  if((pid = fork()) == -1) 
    { perror("fork"); exit(EXIT_FAILURE); }
  
  // le processus fils... 
  // ... éxécute la commande en redirigeant sa sortie standard dans le pipe
  if(pid == 0) { 
    dup2(p[1],1); // redirection de la sortie standard
    close(p[0]); close(p[1]);  // ne pas oublier les fermetures    
    execvp(argv[2],argv+2); // <command> remplace le processus fils    
    perror("execvp");
  }
    
  // le père... 
  // ... lit l'entrée du pipe, l'affiche et l'écrit dans un fichier
  file = open(argv[1], O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR);
  if(file == -1)
    { perror("open file"); exit(EXIT_FAILURE); }
  close(p[1]);  

  char c;
  // Nota Bene : lecture bloquante sur tube vide (je m'endors) !
  while (read(p[0],&c,1) == 1) { // renvoie 0 s'il n'y a plus d'écrivain
    write(1,&c,1); // affichage sur la sortie standard
    write(file,&c,1); // écriture dans le fichier
  }
  
  // ne pas oublier la fermeture des descripteurs restants...
  close(file); close(p[0]);   

  // j'attend la fin de mon fils...
  wait(NULL); 
  
  return EXIT_SUCCESS;
}
 

