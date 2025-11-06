/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidebonl <tidebonl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 13:05:35 by tidebonl          #+#    #+#             */
/*   Updated: 2025/11/06 11:04:59 by tidebonl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*check_stack(char **stack, char *result)
{
	int		seed;
	char	*tmp;

	tmp = NULL;
	if (*stack != NULL)
	{
		seed = ft_strchr(*stack, '\n');
		if (seed != -1)
		{
			result = ft_substr(*stack, 0, seed + 1);
			tmp = *stack;
			*stack = ft_substr(*stack, seed + 1, ft_strlen(*stack) - seed - 1);
			free (tmp);
			return (result);
		}
	}
	return (tmp);
}

int	check_end_file(int i, char **stack, char **result)
{
	if (i < 0)
	{
		if (*stack != NULL)
		{
			free(*stack);
			*stack = NULL;
		}
		return (1);
	}
	if (i == 0)
	{
		if (*stack && ft_strlen(*stack) > 0)
		{
			*result = *stack ;
			*stack = NULL;
			return (1);
		}
		if (*stack)
			free(*stack);
		*stack = NULL;
		*result = NULL;
		return (1);
	}
	return (-1);
}

char	*check_current_line(int fd, char **stack, char *buff)
{
	int		i;
	char	*result;

	i = 1;
	result = NULL;
	result = check_stack(stack, result);
	if (result != NULL)
		return (result);
	while (i > 0)
	{
		i = read(fd, buff, BUFFER_SIZE);
		if (check_end_file(i, stack, &result) == 1)
			return (result);
		if (buff == NULL)
			return (NULL);
		buff[i] = '\0';
		if (push_new_line(stack, buff, &result) == 1)
			return (result);
	}
	return (result);
}

int	push_new_line(char **stack, char *buff, char **result)
{
	char	*tmp;
	int		seed;

	seed = ft_strchr(buff, '\n');
	if (seed != -1)
	{
		tmp = ft_substr(buff, 0, seed + 1);
		*result = ft_strjoin(*stack, tmp);
		free(tmp);
		tmp = *stack ;
		*stack = ft_substr(buff, seed + 1, BUFFER_SIZE - seed - 1);
		if (tmp != NULL)
			free (tmp);
		return (1);
	}
	tmp = *stack;
	*stack = ft_strjoin(*stack, buff);
	if (tmp != NULL)
		free(tmp);
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*stack = NULL;
	char		*buff;
	char		*result;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
	{
		if (stack != NULL)
			free (stack);
		return (NULL);
	}
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
	{
		if (stack != NULL)
		{
			free(stack);
			stack = NULL;
		}
		return (NULL);
	}
	result = check_current_line(fd, &stack, buff);
	free (buff);
	return (result);
}
