#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
int main(int argc, char argv[])
{
	int pipe_ping[2], pipe_pong[2];
	int cpid;
	char buf = '@';
	if (pipe(pipe_ping) < 0 || pipe(pipe_pong) < 0)
	{
		printf("Fail to create the pipe.\n");
		exit(-1);
	}
	cpid = fork();
	if (cpid == -1)
	{
		printf("Fail to fork.\n");
		exit(-1);
	}
	if (cpid == 0)
	{
		close(pipe_ping[1]);
		close(pipe_pong[0]);
		if (read(pipe_ping[0], &buf, 1) < 1)
		{
			printf("Fail to read \'Ping\'.\n");
			exit(-1);
		}
		printf("%d: received ping\n", getpid());
		if (write(pipe_pong[1], &buf, 1) < 1)
		{
			printf("Fail to write \'Pong\'.\n");
			exit(-1);
		}
		exit(0);
	}
	else
	{
		close(pipe_ping[0]);
		close(pipe_pong[1]);
		if (write(pipe_ping[1], &buf, 1) < 1)
		{
			printf("Fail to write \'Ping\'.\n");
			exit(-1);
		}
		if (read(pipe_pong[0], &buf, 1) < 1)
		{
			printf("Fail to read \'Pong\'.\n");
			exit(-1);
		}
		printf("%d: received pong\n", getpid());
		exit(0);
	}
}