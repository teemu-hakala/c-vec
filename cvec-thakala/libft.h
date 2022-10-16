/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 12:21:50 by thakala           #+#    #+#             */
/*   Updated: 2022/10/16 12:19:16 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdint.h>

void	ft_bzero(void *s, uint64_t n);
void	*ft_memcpy(void *dst, const void *src, uint64_t n);
void	*ft_memmove(void *dst, const void *src, uint64_t len);
void	*ft_memset(void *b, int c, uint64_t len);

#endif
