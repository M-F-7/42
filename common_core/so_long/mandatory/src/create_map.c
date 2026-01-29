/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 13:03:52 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/03 23:27:25 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static t_maplist	*maplist_add(t_maplist **lst, char *line)
{
	t_maplist	*node;
	t_maplist	*last;

	node = malloc(sizeof(t_maplist));
	if (!node)
		return (NULL);
	node->line = line;
	node->next = NULL;
	if (!*lst)
		*lst = node;
	else
	{
		last = *lst;
		while (last->next)
			last = last->next;
		last->next = node;
	}
	return (node);
}

static void	remove_nl(char *line)
{
	size_t	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}

static void	maplist_clear(t_maplist *lst)
{
	t_maplist	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst->line);
		free(lst);
		lst = tmp;
	}
}

char	**maplist_to_tab(t_maplist *lst, int size)
{
	char		**map;
	int			i;
	t_maplist	*tmp;

	i = 0;
	tmp = lst;
	map = malloc(sizeof(char *) * (size + 1));
	if (!map)
		return (NULL);
	while (tmp)
	{
		map[i] = ft_strdup(tmp->line);
		if (!map[i])
		{
			map[i] = NULL;
			free_tab(map);
			return (NULL);
		}
		i++;
		tmp = tmp->next;
	}
	map[i] = NULL;
	return (map);
}

char	**create_map(int fd)
{
	t_maplist	*lst;
	char		*line;
	int			size;
	char		**map;

	lst = NULL;
	size = 0;
	line = get_next_line(fd);
	if (!line)
		return (NULL);
	if (ft_strlen(line) > 100)
		return (free(line), NULL);
	while (line)
	{
		remove_nl(line);
		if (!maplist_add(&lst, line))
			return (maplist_clear(lst), NULL);
		size++;
		line = get_next_line(fd);
	}
	map = maplist_to_tab(lst, size);
	maplist_clear(lst);
	return (map);
}
