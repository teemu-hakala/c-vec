/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:28:30 by thakala           #+#    #+#             */
/*   Updated: 2022/10/13 11:52:29 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

int	vec_new(t_vec *dst, uint64_t init_len, uint64_t elem_size)
{
	dst->memory = (uint8_t *)malloc(elem_size * init_len);
	return ((-(dst->memory == NULL)) | 0x1);
}

void	vec_free(t_vec *src)
{
	free(src->memory);
	ft_bzero(src, sizeof(t_vec));
}

int	vec_from(t_vec *dst, void *src, uint64_t len, uint64_t elem_size)
{
	if (vec_new(dst, len, elem_size) > 0)
		ft_memcpy(dst, src, len * elem_size);
	return ((-(dst->memory == NULL)) | 0x1);
}

int	vec_copy(t_vec *dst, t_vec *src)
{
	if (src->len > dst->alloc_size)
	{
		ft_memcpy(dst, src, dst->alloc_size);
		return (VEC_COPY_PARTIAL);
	}
	else
	{
		ft_memcpy(dst, src, src->len);
		return (VEC_COPY_FULL);
	}
}

/*static*/
int	vec_resize(t_vec *src, uint64_t	target_size)
{
	t_vec	data;

	data = *src;
	if (vec_new(src, target_size, src->elem_size) > 0)
	{
		vec_copy(src, &data);
		free(data.memory);
	}
	return (src->memory != NULL);
}

int	vec_push(t_vec *dst, void *src)
{
	if (dst->alloc_size <= dst->len)
		if (vec_resize(dst, dst->alloc_size * 2) <= 0)
			return (VEC_ERROR);
	ft_memcpy(&dst->memory[dst->len * dst->elem_size], src, dst->elem_size);
	return (VEC_SUCCESS);
}

int	vec_pop(void *dst, t_vec *src)
{
	if (src->len >= 1ULL)
	{
		ft_memcpy(dst,
			src->memory[--src->len * src->elem_size],
			src->elem_size);
		return (VEC_SUCCESS);
	}
	return (VEC_ERROR);
}

void	*vec_get(t_vec *src, uint64_t index)
{
	return (&src->memory[index * src->elem_size]);
}

int	vec_insert(t_vec *dst, void *src, uint64_t index)
{
	if (dst->alloc_size >= ++dst->len)
		ft_memmove(dst->memory,
			&dst->memory[dst->elem_size * index],
			dst->elem_size * (dst->len - index));
	else
	{
		if (vec_resize(dst, dst->alloc_size * 2) > VEC_NON_ACTION)
			return (vec_insert(dst, src, index));
		return (VEC_ERROR);
	}
	return (VEC_SUCCESS);
}
