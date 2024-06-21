#include "philosopher.h"

void	validate_input(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		if (ft_atoi(argv[i]) <= 0)
		{
			print_error(INPUT_ERR_1);
		}
		j = 0;
		while (argv[i][j])
		{
			if (ft_isdigit(argv[i][j]) == 0)
			{
				print_error(INPUT_ERR_2);
			}
			j++;
		}
		i++;
	}
}