#include "philo_one.h"

void		error()
{
	write(1, "Error\nWrong arguments\n", 22);
}

int			ft_is_wrong_smb(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int			pars_args(t_com *com, char **argv)
{
	int		i;

	i = 1;
	com->meal_nmb = -1;
	while (argv[i] != NULL)
	{
		if (ft_is_wrong_smb(argv[i]))
			return (1);
		if (i == 1 && (com->phil_nmb = ft_atoi(argv[1])) < 2)
			return (1);
		else if (i == 2 && ((com->time_die = ft_atoi(argv[2])) < 0))
			return (1);
		else if (i == 3 && (com->time_eat = ft_atoi(argv[3])) < 0)
			return (1);
		else if (i == 4 && (com->time_sleep = ft_atoi(argv[4])) < 0)
			return (1);
		else if (i == 5 && (com->meal_nmb = ft_atoi(argv[5])) <= 0)
			return (1);
		i++;
	}
	return (0);
}
