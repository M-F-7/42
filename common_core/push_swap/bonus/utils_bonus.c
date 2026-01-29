/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 08:25:50 by mfernand          #+#    #+#             */
/*   Updated: 2025/11/27 10:35:26 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

void	append_node(t_stack_node **stack, int n)
{
	t_stack_node	*node;
	t_stack_node	*last_node;

	if (!stack)
		return ;
	node = malloc(sizeof(t_stack_node));
	if (!node)
		return (free_stack(stack), exit(1), (void)0);
	node->next = NULL;
	node->value = n;
	if (!(*stack))
	{
		*stack = node;
		node->previous = NULL;
	}
	else
	{
		last_node = find_last(*stack);
		last_node->next = node;
		node->previous = last_node;
	}
}

void	init_stack_a(t_stack_node **a, char **av, int flag, int ac)
{
	long	n;
	int		i;

	(void)ac;
	i = 0;
	while (av[i])
	{
		if (only_digit(av[i]))
			free_errors(a, av, flag);
		n = ft_atol(av[i]);
		if (n > INT_MAX || n < INT_MIN)
			free_errors(a, av, flag);
		if (error_duplicate(*a, (int)n))
			free_errors(a, av, flag);
		append_node(a, (int)n);
		i++;
	}
}

bool	is_sorted(t_stack_node *stack)
{
	if (!stack)
		return (1);
	while (stack->next)
	{
		if (stack->value > stack->next->value)
			return (false);
		stack = stack->next;
	}
	return (true);
}
