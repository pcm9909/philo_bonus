#include "philosopher.h"

int	main(int argc, char **argv)
{
	t_resource	resource;

	if (argc == 5 || argc == 6)
	{
		validate_input(argv);
		preprocessing(argc, argv, &resource);
		fork_philos(&resource);
	}
	else
	{
		print_error(INPUT_ERR_3);
	}
	wait(NULL);
}
