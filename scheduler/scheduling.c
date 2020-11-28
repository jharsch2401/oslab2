#include <stdlib.h>
#include <stdio.h>
#include<unistd.h>
#include<string.h>


void add(int queue[], int index, int n){
	int spot = 0;
	while(queue[spot] != -1){
		spot++;
	}
	if(spot < n)
		queue[spot] = index;
}

void remov(int queue[], int n){
	int spot = 1;
	while(queue[spot] != -1 || spot != n){
		queue[spot-1] = queue[spot];
		spot++;
	}
	queue[spot-1] = -1;

}

int findMax(int queue[], int n){
	for(int i = 1; i < n; i++){
		if(queue[i] == -1)
			return i-1;
	}
	return n-1;
}

int isContained(int queue[], int index, int n){
	for(int i = 0; i < n; i++){
		if(queue[i] == index)
			return 1;
	}
	return 0;
}

void fcfs(int n, int p[][4]){

	//FILE *fp;
	//fp = fopen("answer.txt", "w");
//	if(!fp){
//		printf("FAILURE\n");
//	}
	int runtimes[n][3];
	for(int i = 0; i < n; i++){
		runtimes[i][0] = p[i][1]/2;
		runtimes[i][1] = p[i][2];
		runtimes[i][2] = p[i][1]-runtimes[i][0];
	}

	int isBlocking[n];

	int queue[n];

	for(int i = 0; i < n; i++){
		isBlocking[i] = -1;
		queue[i] = -1;
	}
	int checker;
	int time = 0;
	int done = 0;
	
	printf("test1\n");
	while(!done){
		printf("test2\n");
		printf("%d ", time);
		printf("test3\n");
		for(int i = 0; i < n; i++){
			if(p[i][3] == time)
				add(queue, i, n);
			}
		printf("test4\n");
		for(int j = 0; j < n; j++){
			if(isContained(queue, j, n)){
				if(queue[0] == j){
					printf("%d: running ", j);
					if(runtimes[j][0] != 0){
						runtimes[j][0]--;
						if(runtimes[j][0] == 0){
							remov(queue, n);
							add(isBlocking, j, n);
						}
					}
					else{
						runtimes[j][2]--;
						if(runtimes[j][2] == 0){
							remov(queue, n);
						}
					}
				}
				else{
					printf("%d: ready ", j);
				}
			}
			else if(isContained(isBlocking, j, n)){
				printf("%d: blocking ", j);
				runtimes[j][1]--;
				if(runtimes[j][1] == 0){
					remov(isBlocking, n);
					add(queue, j, n);
				}
			}
		}
		printf("\n");
		time++;
		checker = 0;
		for(int k = 0; k < n; k++){
			if(runtimes[k][2] != 0)
				checker++;
		}

		if(checker == 0){
			done = 1;	
		}

	}

	//fclose(fp);

}

void rr(int n, int p[][4]){
	
}

void sjf(int n, int p[][4]){
	
}

int main( int argc, char *argv[] ){

	//reading in file to get 2D array of processes
	FILE *fpm;
	int num;
	fpm = fopen(argv[1], "r");
	fscanf(fpm, "%d", &num);
	int procs[num][4];
	for(int i = 0; i < num; i++){
		fscanf(fpm, "%d %d %d %d", &procs[i][0], &procs[i][1], &procs[i][2], &procs[i][3]);
	}
	fclose(fpm);

	if(atoi(argv[2])==0)
		fcfs(num, procs);
	if(atoi(argv[2])==1)
		rr(num, procs);
	if(atoi(argv[2])==2){
		sjf(num, procs);
	}


	return 0;
}