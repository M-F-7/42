/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 21:21:56 by mfernand          #+#    #+#             */
/*   Updated: 2025/11/27 07:00:27 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	choose_sort(t_stack_node **a, t_stack_node **b)
{
	int	size;

	if (!is_sorted(*a))
	{
		size = stack_size(*a);
		if (size == 2)
			sa(a, false);
		else if (size > 2 && size <= 5)
			little_sort(a, b, size);
		else
			sort_stacks(a, b);
	}
}

int	main(int ac, char **av)
{
	static t_stack_node	*a = NULL;
	static t_stack_node	*b = NULL;

	if (ac == 1 || (ac == 2 && !av[1][0]))
		return (1);
	if (ac == 2)
	{
		av = ft_split(av[1], ' ');
		if (!av)
			exit(EXIT_FAILURE);
		init_stack_a(&a, av, 1);
	}
	else
		init_stack_a(&a, av + 1, 0);
	choose_sort(&a, &b);
	if (ac == 2)
		free_tab(av);
	free_stack(&a);
	return (0);
}
