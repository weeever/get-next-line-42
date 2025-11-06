/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidebonl <tidebonl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 13:09:32 by tidebonl          #+#    #+#             */
/*   Updated: 2025/11/06 10:36:01 by tidebonl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

char	*check_stack(char **stack, char *result);
char	*get_next_line(int fd);
int		push_new_line(char **stack, char *buff, char **result);
char	*check_current_line(int fd, char **stack, char *buff);
int		ft_strlen(const char *src);
char	*ft_strdup(const char *source);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strchr(const char *str, int to_find);
#endif
