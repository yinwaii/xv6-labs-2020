#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
void prime(int pipe_base_read)
{
	int base;
	if (read(pipe_base_read, &base, sizeof(int)) < sizeof(int))
		exit(0);
	printf("prime %d\n", base);
	int pipe_base[2];
	int cpid, i;
	if (pipe(pipe_base) < 0)
	{
		printf("Fail to create pipe.\n");
		exit(-1);
	}
	cpid = fork();
	if (cpid < 0)
	{
		printf("Fail to fork.\n");
		exit(-1);
	}
	if (cpid != 0)
	{
		close(pipe_base[0]);
		while (read(pipe_base_read, &i, sizeof(int)) == sizeof(int))
		{
			if (i % base != 0)
				write(pipe_base[1], &i, sizeof(int));
		}
		close(pipe_base[1]);
	}
	else
	{
		close(pipe_base[1]);
		prime(pipe_base[0]);
	}
	wait(0);
	exit(0);
}
int main(int argc, char argv[])
{
	int pipe_base[2];
	int cpid, i;
	if (pipe(pipe_base) < 0)
	{
		printf("Fail to create pipe.\n");
		exit(-1);
	}
	cpid = fork();
	if (cpid < 0)
	{
		printf("Fail to fork.\n");
		exit(-1);
	}
	if (cpid != 0)
	{
		close(pipe_base[0]);
		for (i = 2; i < 36; i++)
		{
			write(pipe_base[1], &i, sizeof(int));
		}
		close(pipe_base[1]);
	}
	else
	{
		close(pipe_base[1]);
		prime(pipe_base[0]);
	}
	wait(0);
	exit(0);
}