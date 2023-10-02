/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkedlist_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 18:12:49 by mtaib             #+#    #+#             */
/*   Updated: 2023/10/02 22:21:26 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"

t_dirs		*lstnew(char	 *key, char *path)
{
	t_dirs	*newnode;

	newnode = malloc(sizeof(t_dirs));
	if (!newnode)
		return (0);
	newnode->key = key;
	newnode->path = path;
	newnode->next = 0;
	return (newnode);
}

void	lstadd_back(t_dirs **lst, t_dirs *newnode)
{
	t_dirs	*tmp;

	tmp = *lst;
	if (*lst)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = newnode;
	}
	else
		*lst = newnode;
}


