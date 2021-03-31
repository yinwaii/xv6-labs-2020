#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
	const char error_message[] = "Please give an argument!\n";
	// int res;
	if (argc < 2)
	{
		write(1, error_message, strlen(error_message));
		exit(-1);
	}
	while(sleep(atoi(argv[1])) == 0)
		exit(0);
	exit(-1);
}