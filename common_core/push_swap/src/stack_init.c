/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 21:21:38 by mfernand          #+#    #+#             */
/*   Updated: 2025/11/27 05:33:00 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

long	ft_atol(const char *s)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	while ((*s == 32) || (*s >= 9 && *s <= 13))
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	while (ft_isdigit(*s))
		result = result * 10 + (*s++ - '0');
	return (result * sign);
}

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

void	init_stack_a(t_stack_node **a, char **av, int flag)
{
	long	n;
	int		i;

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
