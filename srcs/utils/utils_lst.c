/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:15:45 by mishin            #+#    #+#             */
/*   Updated: 2022/01/18 18:15:46 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	lst_get_len(t_lst *node)
{
	int	i;

	i = 0;
	while (node)
	{
		node = node->next;
		i++;
	}
	return (i);
}

t_lst	*lst_get_tail(t_lst *node)
{
	if (!node)
		return (NULL);
	while (node->next)
		node = node->next;
	return (node);
}

// t_lst 리스트 객체를 생성해서 객체 멤버 content를 입력해주고
// 리스트의 맨 뒤(tail)에 연결해준다
// head가 NULL이면 head에 추가된다
// 무조건 head를 리턴하니 리턴값을 헤드로 잘 받아서 쓰자
t_lst	*lst_add_back(t_lst *head, char *content)
{
	t_lst	*new;
	t_lst	*tail;

	if (!content)
		return (NULL);
	new = (t_lst *)calloc_(1, sizeof(t_lst));
	new->content = strdup_(content);
	new->next = NULL;
	new->prev = NULL;
	if (head)
	{
		tail = lst_get_tail(head);
		new->prev = tail;
		tail->next = new;
	}
	else
		head = new;
	return (head);
}

void	lst_print(t_lst *head)
{
	t_lst	*node;

	node = head;
	while (node)
	{
		printf("%s\n", node->content);
		node = node->next;
	}
}

void	lst_clear(t_lst **head)
{
	t_lst	*tmp;
	t_lst	*node;

	node = *head;
	while (node)
	{
		free(node->content);
		tmp = node;
		node = node->next;
		free(tmp);
	}
	*head = NULL;
}
