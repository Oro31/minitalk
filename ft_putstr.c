#include <unistd.h>

void	ft_putstr(int fd, char c)
{
	char	d;

	d = c;
	write(fd, &d, 1);
	//write(fd, "\n", 1);
}
