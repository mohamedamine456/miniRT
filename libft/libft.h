/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlachheb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 17:44:12 by mlachheb          #+#    #+#             */
/*   Updated: 2020/10/29 17:44:49 by mlachheb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>

int		ft_strlen(const char *s);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strcmp(const char *s1, const char *s2);
float	ft_atof(char *str);
void	ft_strrev(char *str);
void	*ft_memcpy(void *dest, const void *src, size_t n);

#endif
