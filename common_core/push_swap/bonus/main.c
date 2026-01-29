/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 08:17:59 by mfernand          #+#    #+#             */
/*   Updated: 2025/11/27 10:50:15 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

void	manage_input(t_stack_node **a, t_stack_node **b, char **av, int ac)
{
	char	*line;

	line = get_next_line(0);
	while (1)
	{
		if (!line)
			break ;
		if (!is_instructions(line))
		{
			if (line)
				free(line);
			if (ac == 2)
				free_errors(a, av, 1);
			free_errors(a, av, 0);
		}
		exec_instructions(line, a, b);
		free(line);
		line = get_next_line(0);
	}
}

void	free_stacks(t_stack_node **a, t_stack_node **b, char **av, int ac)
{
	if (ac == 2)
		free_tab(av);
	free_stack(a);
	free_stack(b);
}

int	main(int ac, char **av)
{
	t_stack_node	*a;
	t_stack_node	*b;

	a = NULL;
	b = NULL;
	if (ac == 1 || (ac == 2 && !av[1][0]))
		return (1);
	if (ac == 2)
	{
		av = ft_split(av[1], ' ');
		if (!av)
			exit(EXIT_FAILURE);
		init_stack_a(&a, av, 0, ac);
	}
	else
		init_stack_a(&a, av + 1, 0, ac);
	manage_input(&a, &b, av, ac);
	if (!(is_sorted(a) && stack_size(b) == 0))
		ft_putstr_fd("KO\n", 1);
	else
		ft_putstr_fd("OK\n", 1);
	free_stacks(&a, &b, av, ac);
	return (0);
}
