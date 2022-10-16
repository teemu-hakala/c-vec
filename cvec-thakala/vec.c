/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:28:30 by thakala           #+#    #+#             */
/*   Updated: 2022/10/16 12:02:45 by thakala          ###   ########.fr       */
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

int	vec_remove(t_vec *src, uint64_t index)
{
	ft_memcpy(&src->memory,
		&src->memory[src->elem_size * (src->len - index)],
		src->elem_size * (src->len - index));
	return (VEC_SUCCESS);
}

int	vec_append(t_vec *dst, t_vec *src)
{
	uint64_t	dst_prev_len;

	dst_prev_len = dst->len;
	if (vec_resize(dst, dst->len + src->len) > 0)
		ft_memcpy(&dst->memory[dst_prev_len],
			&src->memory,
			dst->elem_size * src->len);
	return ((-(dst->memory == NULL)) | 0x1);
}

int vec_prepend(t_vec *dst, t_vec *src)
{
	return (vec_append(src, dst));
}

void	vec_iter(t_vec *src, void (*f) (void *))
{
	uint64_t	c;

	c = 0;
	while (c < src->len)
		f(vec_get(src, c++));
}

int	vec_map(t_vec *dst, t_vec *src, void (*f) (void *))
{
	uint64_t	c;

	vec_copy(dst, src);
	c = 0;
	while (c < src->len)
		f(&dst[dst->elem_size * c++]);
	return (VEC_SUCCESS);
}

int	vec_filter(t_vec *dst, t_vec *src, bool (*f)(void *))
{
	uint64_t	c;
	void		*data;

	c = -1;
	while (++c < src->len)
	{
		data = src->memory[src->elem_size * c];
		if (f(data))
			vec_push(dst, data);
	}
}

void	vec_reduce(void *acc, t_vec *src, void (*f)(void *, void *))
{
	uint64_t	c;

	c = -1;
	while (++c < src->len)
		f(acc, src->memory[src->elem_size * c]);
}

static int	vec_swap(uint64_t elem_size, void *a, void *b)
{
	uint8_t		*swap;

	swap = (uint8_t *)malloc(sizeof(uint8_t) * elem_size);
	if (swap == NULL)
		return (VEC_ERROR);
	ft_memcpy(swap, a, elem_size);
	ft_memcpy(a, b, elem_size);
	ft_memcpy(b, swap, elem_size);
	return (VEC_SUCCESS);
}

int	vec_sort(t_vec *src, int (*f)(void *, void *))
{
	uint64_t	c;

	if (src->len == 0)
		return ;
	c = -1;
	while (++c < src->len - 1)
	{
		if (f(src->memory[src->elem_size * c],
				src->memory[src->elem_size * (c + 1)] > 0))
		{
			if (vec_swap(src->elem_size,
					src->memory[src->elem_size * c],
					src->memory[src->elem_size * (c + 1)]) < VEC_NON_ACTION)
				return (VEC_ERROR);
			c = -1;
		}
	}
}
