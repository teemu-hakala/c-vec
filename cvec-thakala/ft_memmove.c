/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 14:35:21 by thakala           #+#    #+#             */
/*   Updated: 2022/10/16 12:19:57 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, uint64_t len)
{
	uint64_t	i;

	i = (uint64_t)(-1);
	if (src < dst)
		while (--len + 1)
			((char *)dst)[len] = ((char *)src)[len];
	else if (src > dst)
		while (++i < len)
			((char *)dst)[i] = ((char *)src)[i];
	return (dst);
}
