#include "cub3D.h"

void	printing_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		printf("arr element is: %s\n",arr[i]);
		i++;
	}

}


void	printing_nbr_arr(int *arr)
{
	int	i;

	i = 0;
	while (i <= 2)
	{
		printf("arr element is: %d\n",arr[i]);
		i++;
	}

}
