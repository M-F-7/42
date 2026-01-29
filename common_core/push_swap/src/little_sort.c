/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   little_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 05:40:45 by mfernand          #+#    #+#             */
/*   Updated: 2025/11/27 07:00:35 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	little_sort(t_stack_node **a, t_stack_node **b, int size)
{
	if (size == 3)
		sort_three(a);
	else if (size == 4)
		sort_four(a, b, size);
	else if (size == 5)
		sort_five(a, b, size);
}

void	sort_three(t_stack_node **a)
{
	t_stack_node	*biggest_node;

	biggest_node = find_max(*a);
	if (biggest_node == *a)
		ra(a, false);
	else if ((*a)->next == biggest_node)
		rra(a, false);
	if ((*a)->value > (*a)->next->value)
		sa(a, false);
}

void	sort_four(t_stack_node **a, t_stack_node **b, int size)
{
	t_stack_node	*min;

	min = find_min_idx(a);
	move_min(a, find_min_by_idx(a, min), size);
	size--;
	pb(b, a, false);
	sort_three(a);
	pa(a, b, false);
}

void	sort_five(t_stack_node **a, t_stack_node **b, int size)
{
	t_stack_node	*min;

	min = find_min_idx(a);
	move_min(a, find_min_by_idx(a, min), size);
	pb(b, a, false);
	size--;
	min = find_min_idx(a);
	move_min(a, find_min_by_idx(a, min), size);
	pb(b, a, false);
	sort_three(a);
	pa(a, b, false);
	pa(a, b, false);
	if ((*a)->value > (*a)->next->value)
		sa(a, false);
}
