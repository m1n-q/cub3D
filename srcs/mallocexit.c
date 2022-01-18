/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mallocexit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:17:22 by mishin            #+#    #+#             */
/*   Updated: 2022/01/18 15:22:47 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
void	*calloc_(size_t count, size_t size)
{
	void	*ret;

	ret = ft_calloc(count, size);
	if (!ret)
		exit(-1);
	return (ret);
}

char	*strdup_(char *s)
{
	char	*ret;

	if (!s)
		return (s);
	ret = ft_strdup(s);
	if (!ret)
		exit(-1);
	return (ret);
}

char	*strjoin_(const char *s1, const char *s2)
{
	char	*ret;

	ret = ft_strjoin(s1, s2);
	if (!ret)
		exit(-1);
	return (ret);
}

char	*substr_(char const *s, unsigned int start, size_t len)
{
	char	*ret;

	if (!s)
		return (NULL);
	ret = ft_substr(s, start, len);
	if (!ret)
		exit(-1);
}

//TODO: trim, atoi, split
