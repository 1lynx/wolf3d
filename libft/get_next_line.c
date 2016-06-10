/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrandria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/08 14:17:52 by nrandria          #+#    #+#             */
/*   Updated: 2016/02/15 13:03:47 by nrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_gnl				*gnl_create(int fd, t_gnl *new)
{
	if (fd == -10 && new->l)
	{
		*new->l = ft_strsub(new->s, 0, (new->i));
		return (new);
	}
	if (!new)
	{
		if (!(new = (t_gnl *)malloc(sizeof(t_gnl) * 1)))
			return ((t_gnl *)NULL);
		new->s = ft_strnew(0);
		new->fd = fd;
		new->next = NULL;
		new->tmp = NULL;
		new->l = NULL;
	}
	new->ret = 1;
	new->i = 0;
	ft_strdel(&new->tmp);
	return (new);
}

static t_gnl				*gnl_choose(int fd, t_gnl *node)
{
	static t_gnl			*root;
	t_gnl					*gnl;
	t_gnl					*new;

	if (fd == -10)
		return (root);
	if (fd == -42)
		return (root = node);
	if (!(root = gnl_create(fd, root)))
		return ((t_gnl *)NULL);
	gnl = root;
	while (gnl->fd != fd && gnl->next)
		gnl = gnl->next;
	if (gnl->fd != fd && !(new = NULL))
	{
		if (!(new = gnl_create(fd, NULL)))
			return ((t_gnl *)NULL);
		gnl->next = new;
		return (new);
	}
	gnl = gnl_create(fd, gnl);
	return (gnl);
}

static int					gnl_delete(t_gnl *clear)
{
	t_gnl					*root;
	t_gnl					*tmp;
	t_gnl					*prev;
	t_gnl					*next;

	root = gnl_choose(-10, NULL);
	next = root->next;
	prev = NULL;
	tmp = root;
	while (tmp->fd != clear->fd)
	{
		prev = tmp;
		tmp = prev->next;
		next = tmp->next;
	}
	if (prev)
		prev->next = next;
	else
		gnl_choose(-42, next);
	ft_strdel(&clear->s);
	ft_memdel((void **)&clear);
	return (0);
}

static int					gnl_free(void)
{
	t_gnl					*root;
	t_gnl					*destroy;

	if (!(root = gnl_choose(-10, NULL)))
		return (0);
	while (root->next)
	{
		destroy = root;
		root = root->next;
		ft_strdel(&destroy->s);
		ft_strdel(&destroy->tmp);
		ft_memdel((void **)&destroy);
	}
	ft_strdel(&root->s);
	ft_strdel(&root->tmp);
	ft_memdel((void **)&root);
	return (0);
}

int							get_next_line(int fd, char **line)
{
	t_gnl					*g;

	if (fd == -10)
		return (gnl_free());
	if (fd < 0 || BUFF_SIZE < 1 || !(g = gnl_choose(fd, NULL)) ||
			read(fd, g->buf, 0) < 0)
		return (-1);
	while (!(ft_strchr(g->s, '\n')) &&
			(g->ret = read(fd, g->buf, BUFF_SIZE)) > 0)
	{
		g->buf[g->ret] = '\0';
		g->tmp = g->s;
		g->s = ft_strjoin(g->tmp, g->buf);
		ft_strdel(&g->tmp);
	}
	while (g->s[g->i] && g->s[g->i] != '\n')
		g->i++;
	if (g->ret == 0 && g->i == 0)
		return (gnl_delete(g));
	g->l = line;
	gnl_create(-10, g);
	g->tmp = g->s;
	g->s = (g->tmp[g->i] == '\0') ? ft_strnew(0) :
		ft_strsub(g->tmp, (g->i + 1), (ft_strlen(g->tmp) - g->i));
	return (1);
}
