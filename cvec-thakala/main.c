/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:50:41 by thakala           #+#    #+#             */
/*   Updated: 2022/10/16 17:38:57 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"
#include <string.h>

void	test_vec_new(void)
{
	t_vec	t1;

	assert(vec_new(&t1, 0, 0) == -1);
	assert(vec_new(&t1, 0, 1) > 0);
	assert(t1.memory == NULL);
	assert(vec_new(&t1, 1, 0) == -1);
	assert(vec_new(&t1, 10, 1) > 0);
	assert(t1.memory != NULL);
	vec_free(&t1);
	printf("test_vec_new successful!\n");
}

void	test_vec_free(void)
{
	t_vec	t1;

	assert(vec_new(&t1, 10, 1) > 0);
	vec_free(&t1);
	assert(t1.len == 0);
	assert(t1.alloc_size == 0);
	assert(t1.elem_size == 0);
	assert(t1.memory == NULL);
	printf("test_vec_free successful!\n");
}

void	test_vec_from(void)
{
	t_vec		t1;
	static int	base[] = {1, 2, 3, 4, 5};

	assert(vec_from(&t1, base, 5, sizeof(int)) > 0);
	assert(memcmp(t1.memory, base, sizeof(base)) == 0);
	vec_free(&t1);
	printf("test_vec_from successful!\n");
}

void	test_vec_copy(void)
{
	t_vec		t1;
	t_vec		t2;
	static int	base[] = {1, 2, 3, 4, 5};

	assert(vec_from(&t1, base, 5, sizeof(int)) > 0);
	assert(vec_new(&t2, 5, sizeof(int)) > 0);
	assert(vec_copy(&t2, &t1) > 0);
	assert(memcmp(t2.memory, base, sizeof(base)) == 0);
	vec_free(&t1);
	vec_free(&t2);
	printf("test_vec_copy successful!\n");
}

void	test_vec_resize(void)
{
	t_vec		t1;
	static int	base[] = {1, 2, 3, 4, 5};

	assert(vec_from(&t1, base, 5, sizeof(int)) > 0);
	assert(vec_resize(&t1, 100) > 0);
	assert(memcmp(t1.memory, base, sizeof(base)) == 0);
	vec_free(&t1);
	printf("test_vec_resize successful!\n");
}

void	test_vec_push(void)
{
	t_vec		t1;
	static int	base[] = {1, 2, 3, 4, 5};
	static int	expect[] = {2, 4};

	assert(vec_new(&t1, 1, sizeof(int)) > 0);
	vec_push(&t1, &base[1]);
	vec_push(&t1, &base[3]);
	assert(memcmp(t1.memory, expect, sizeof(expect)) == 0);
	vec_free(&t1);
	printf("test_vec_push successful!\n");
}

void	test_vec_pop(void)
{
	t_vec		t1;
	static int	base[] = {1, 2, 3, 4, 5};
	static int	expect = 0;

	assert(vec_new(&t1, 1, sizeof(int)) > 0);
	vec_push(&t1, &base[1]);
	vec_push(&t1, &base[3]);
	vec_pop(&expect, &t1);
	assert(expect == 4);
	vec_pop(&expect, &t1);
	assert(expect == 2);
	assert(t1.len == 0);
	vec_free(&t1);
	printf("test_vec_pop successful!\n");
}

void	test_vec_get(void)
{
	t_vec		t1;
	static int	base[] = {1, 2, 3, 4, 5};
	int			*expect;

	assert(vec_new(&t1, 1, sizeof(int)) > 0);
	vec_push(&t1, &base[1]);
	vec_push(&t1, &base[3]);
	expect = vec_get(&t1, 0);
	assert(*expect == 2);
	expect = vec_get(&t1, 1);
	assert(*expect == 4);
	assert(t1.len == 2);
	vec_free(&t1);
	printf("test_vec_get successful!\n");
}

void	test_vec_insert(void)
{
	t_vec		t1;
	static int	base[] = {1, 2, 3, 4, 5};
	static int	insert[] = {42, 666, 7};
	static int	expect[] = {1, 42, 2, 3, 666, 4, 5, 7};

	assert(vec_from(&t1, base, 5, sizeof(int)) > 0);
	vec_insert(&t1, &insert[0], 1);
	vec_insert(&t1, &insert[1], 4);
	vec_insert(&t1, &insert[2], 7);
	assert(memcmp(t1.memory, expect, sizeof(expect)) == 0);
	vec_free(&t1);
	printf("test_vec_insert successful!\n");
}

void	test_vec_remove()
{
	t_vec		t1;
	static int	base[] = {1, 2, 3, 4, 5};
	static int	insert[] = {42, 666, 7};

	assert(vec_from(&t1, base, 5, sizeof(int)) > 0);
	vec_insert(&t1, &insert[0], 1);
	vec_insert(&t1, &insert[1], 4);
	vec_insert(&t1, &insert[2], 7);
	vec_remove(&t1, 1);
	vec_remove(&t1, 3);
	vec_remove(&t1, 5);
	assert(memcmp(t1.memory, base, sizeof(base)) == 0);
	vec_free(&t1);
	printf("test_vec_remove successful!\n");
}

void	test_vec_append(void)
{
	t_vec		t1;
	t_vec		t2;
	static int	base1[] = {1, 2, 3};
	static int	base2[] = {4, 5, 6};
	static int	expect[] = {1, 2, 3, 4, 5, 6};

	assert(vec_from(&t1, base1, 3, sizeof(int)) > 0);
	assert(vec_from(&t2, base2, 3, sizeof(int)) > 0);
	assert(vec_append(&t1, &t2) > 0);
	assert(memcmp(t1.memory, expect, sizeof(expect)) == 0);
	vec_free(&t1);
	vec_free(&t2);
	printf("test_vec_append successful!\n");
}

void	test_vec_prepend(void)
{
	t_vec		t1;
	t_vec		t2;
	static int	base1[] = {1, 2, 3};
	static int	base2[] = {4, 5, 6};
	static int	expect[] = {4, 5, 6, 1, 2, 3};

	assert(vec_from(&t1, base1, 3, sizeof(int)) > 0);
	assert(vec_from(&t2, base2, 3, sizeof(int)) > 0);
	assert(vec_prepend(&t1, &t2) > 0);
	assert(memcmp(t1.memory, expect, sizeof(expect)) == 0);
	vec_free(&t1);
	vec_free(&t2);
	printf("test_vec_prepend successful!\n");
}

void	iter_tester(void *elem)
{
	(*(int *)elem)++;
}

void	test_vec_iter(void)
{
	t_vec		t1;
	static int	base[] = {1, 2, 3, 4, 5};
	static int	expect[] = {2, 3, 4, 5, 6};

	assert(vec_from(&t1, base, 5, sizeof(int)) > 0);
	vec_iter(&t1, iter_tester);
	assert(memcmp(t1.memory, expect, sizeof(expect)) == 0);
	vec_free(&t1);
	printf("test_vec_iter successful!\n");
}

void	map_tester(void *src)
{
	(*(int *)src)++;
}

void	test_vec_map(void)
{
	t_vec		t1;
	t_vec		t2;
	static int	base[] = {1, 2, 3, 4, 5};
	static int	expect[] = {2, 3, 4, 5, 6};

	assert(vec_from(&t1, base, 5, sizeof(int)) > 0);
	assert(vec_new(&t2, 5, sizeof(int)) > 0);
	vec_map(&t2, &t1, map_tester);
	assert(memcmp(t2.memory, expect, sizeof(expect)) == 0);
	vec_free(&t1);
	vec_free(&t2);
	printf("test_vec_map successful!\n");
}

static bool	filter_tester(void *src)
{
	return (*(int *)src % 2 == 0);
}

void	test_vec_filter(void)
{
	t_vec		t1;
	t_vec		t2;
	static int	base[] = {1, 2, 3, 4, 5};
	static int	expect[] = {2, 4};

	assert(vec_from(&t1, base, 5, sizeof(int)) > 0);
	assert(vec_new(&t2, 5, sizeof(int)) > 0);
	vec_filter(&t2, &t1, filter_tester);
	assert(memcmp(t2.memory, expect, sizeof(expect)) == 0);
	vec_free(&t1);
	vec_free(&t2);
	printf("test_vec_filter successful!\n");
}

void	reduce_tester(void *acc, void *src)
{
	*(int *)acc += *(int *)src;
}

void	test_vec_reduce(void)
{
	t_vec		t1;
	static int	base[] = {1, 2, 3, 4, 5};
	static int	result = 0;

	assert(vec_from(&t1, base, 5, sizeof(int)) > 0);
	vec_reduce(&result, &t1, reduce_tester);
	assert(result == 15);
	vec_free(&t1);
	printf("test_vec_reduce successful!\n");
}

static int	cmp(void *a, void *b)
{
	return ((long)*(int *)a - *(int *)b);
}

void	test_vec_sort(void)
{
	t_vec		t1;
	static int	base[] = {3, 2, 2, 7, 4};
	static int	expect[] = {2, 2, 3, 4, 7};

	assert(vec_from(&t1, base, 5, sizeof(int)) > 0);
	vec_sort(&t1, cmp);
	assert(memcmp(t1.memory, expect, sizeof(expect)) == 0);
	vec_free(&t1);
	printf("test_vec_sort successful!\n");
}

int	main(void)
{
	test_vec_new();
	test_vec_free();
	test_vec_from();
	test_vec_copy();
	test_vec_resize();
	test_vec_push();
	test_vec_pop();
	test_vec_get();
	test_vec_insert();
	test_vec_remove();
	test_vec_append();
	test_vec_prepend();
	test_vec_iter();
	test_vec_map();
	test_vec_filter();
	test_vec_reduce();
	test_vec_sort();
}
