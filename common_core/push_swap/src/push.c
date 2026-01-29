/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 21:21:51 by mfernand          #+#    #+#             */
/*   Updated: 2025/11/27 05:30:55 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	push(t_stack_node **dst, t_stack_node **src)
{
	t_stack_node	*node;

	if (!*src)
		return ;
	node = *src;
	*src = (*src)->next;
	if (*src)
		(*src)->previous = NULL;
	node->previous = NULL;
	if (!*dst)
	{
		*dst = node;
		node->next = NULL;
	}
	else
	{
		node->next = *dst;
		node->next->previous = node;
		*dst = node;
	}
}

void	pa(t_stack_node **a, t_stack_node **b, bool print)
{
	push(a, b);
	if (!print)
		ft_printf("pa\n");
}

void	pb(t_stack_node **b, t_stack_node **a, bool print)
{
	push(b, a);
	if (!print)
		ft_printf("pb\n");
}
