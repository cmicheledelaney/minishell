#include <stdio.h>
#include <unistd.h>
# include "libft/libft.h"

int main(void){
	char *line = NULL;
	int ret;

	ft_strlen("sss");
	while (ret = get_next_line(0,&line))
		printf("the return value is: %d ", ret);
	printf("the return value is: %d ", ret);
	return (0);
}
