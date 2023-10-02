/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_elements.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 10:11:35 by mtaib             #+#    #+#             */
/*   Updated: 2023/10/02 20:54:23 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"
#include <stdio.h>

void	free_list(t_dirs **head)
{
	t_dirs	*tmp;
	
	while (*head)
	{
		tmp = *head;
		free(tmp->key);
		free(tmp->path);
		*head = (*head)->next;
		free(tmp);
	}
	free(*head);
}
