#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include "time_diff.h"

/***********************************************************************
*******
  Demonstrates how to crack an encrypted password using a simple
  "brute force" algorithm. Works on passwords that consist only of 2
uppercase
  letters and a 2 digit integer. Your personalised data set is included
in the
  code. 

  Compile with:
    cc -o CrackAZ99-With-Data CrackAZ99-With-Data.c -lcrypt

  If you want to analyse the results then use the redirection operator
to send
  output to a file that you can view using an editor or the less
utility:

    ./CrackAZ99-With-Data > results.txt

  Dr Kevan Buckley, University of Wolverhampton, 2018
************************************************************************
******/
int n_passwords = 4;

char *encrypted_passwords[] = {

"$6$KB$fYVGmlgHhiFcEuDQJbdpUmnDxr5PfJcpafqkV4jpPAclGbeUp2q1leLD6Kv/RvaTCl/3njIV6q6QYTQasgcXP/",
"$6$KB$mGCjBgRWMrxx0PUcCrR4593ee9eDFZ2ucOsAvEQN3EWObtFJtFEJc2J.2Po2/IGnndZtglnkoqtUgiDBJAW550",
"$6$KB$EACH/wmffjgt7C4lrKfSXOPeMLaw7cbbNM6maSs3Yvz./NWl1P/qPi5CqeOX.sJAffOP/HzJm2obcm6O9ya5J0",
"$6$KB$wPnwkxTiWR3VKiv17MQbGicu/7.8a5eucGmL02kLylDLNRE3nyKcRFLK/3cedv6dVfL9YwL1Jn.beIgIO2ref."
};

/**
 Required by lack of standard function in C.   
*/

void substr(char *dest, char *src, int start, int length){
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}

/**
 This function can crack the kind of password explained above. All
combinations
 that are tried are displayed and when the password is found, #, is put
at the 
 start of the line. Note that one of the most time consuming operations
that 
 it performs is the output of intermediate results, so performance
experiments 
 for this kind of program should not include this. i.e. comment out the
printfs.
*/

void crack(char *salt_and_encrypted){
  int a, x, y, z;     // Loop counters
  char salt[7];    // String used in hashing the password. Need space
  char plain[7];   // The combination of letters currently being checked
  char *enc;       // Pointer to the encrypted password
  int count = 0;   // The number of combinations explored so far

  substr(salt, salt_and_encrypted, 0, 6);
	for(a='A'; a<='Z'; a++){
	  for(x='A'; x<='Z'; x++){
	    for(y='A'; y<='Z'; y++){
	      for(z=0; z<=99; z++){
		sprintf(plain, "%c%c%c%02d", a, x, y, z);
		enc = (char *) crypt(plain, salt);
		count++;
		if(strcmp(salt_and_encrypted, enc) == 0){
		  printf("#%-8d%s %s\n", count, plain, enc);
		} else {
		  printf(" %-8d%s %s\n", count, plain, enc);
		}
	      }
	    }
	  }
	}	
	printf("%d solutions explored\n", count);
}

int main(int argc, char *argv[]){
struct timespec start, finish;
  long long int difference;   
  int account = 0;
  clock_gettime(CLOCK_MONOTONIC, &start);

  int i;

  for(i=0;i<n_passwords;i<i++) {
    crack(encrypted_passwords[i]);}

  clock_gettime(CLOCK_MONOTONIC, &finish);
  time_difference(&start, &finish, &difference);
  printf("accumulated %dp\n", account);
  printf("run lasted %9.5lfs\n", difference/1000000000.0);
  return 0;

  }




