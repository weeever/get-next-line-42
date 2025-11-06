/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidebonl <tidebonl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 13:05:35 by tidebonl          #+#    #+#             */
/*   Updated: 2025/11/05 16:30:59 by tidebonl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *check_stack(char **stack, char *result)
{
	int seed;
	char *tmp;

	tmp = NULL;
	if (*stack != NULL)
	{
		seed = ft_strchr(*stack , '\n');
		if (seed != -1)
		{
			result = ft_substr(*stack , 0, seed + 1);
			tmp = *stack;
			*stack = ft_substr(*stack, seed + 1, ft_strlen(*stack) - seed - 1);
			free (tmp);
			return (result);
		}
	}
	return (tmp);
}

char check_current_line(char *result, int fd, char **stack, char *buff)
{
	int i;
	char *result;

	i = 1;
	result = NULL;
	result = check_stack(stack, result);
	if (result != NULL)
		return (result);
	while (i > 0)
	{
		i = read(fd, buff, BUFFER_SIZE);
		if (i < 0)
		{
			if (*stack != NULL)
			{
				free(*stack);
				*stack = NULL;
			}
			return (NULL);
		}
		if (buff == NULL)
			return (NULL);
		buff[i] = '\0';
		if (i == 0)
		{
			if (*stack  && ft_strlen(*stack) > 0)
			{
				result = *stack ;
				*stack  = NULL;
				return (result);
			}
			if (*stack)
				free(*stack);
			*stack = NULL;
			return (NULL);
		}

	}
}
char *get_new_line(int fd, char **stack, char *buff)
{
	int i;
	char *tmp;
	char *result;
	int seed;


		seed = ft_strchr(buff, '\n');
		if (seed != -1)
		{
			tmp = ft_substr(buff , 0, seed + 1);
			result = ft_strjoin(*stack, tmp);
			free(tmp);

			tmp = *stack ;
			*stack  = ft_substr(buff, seed + 1, BUFFER_SIZE  - seed - 1);
			if (tmp != NULL)
				free (tmp);
			return (result);
		}
		tmp = *stack;
		*stack = ft_strjoin(*stack, buff);
		if (tmp != NULL)
			free(tmp);

	return (NULL);
}

char	*get_next_line(int fd)
{
	static char *stack = NULL;
	char *buff;
	char *result;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		if (stack != NULL)
		{
			free (stack);
			stack = NULL;
		}
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
	result = get_new_line(fd, &stack, buff);
	free(buff);
	return (result);
}

// int main(void)
// {
// 	int fd;
// 	char *line;

// 	fd = open("test.txt", O_RDONLY);
// 	printf("Line: %s\n", get_next_line(fd));
// 	printf("Line: %s\n", get_next_line(fd));
// 	printf("Line: %s\n", get_next_line(fd));
// 	printf("Line: %s\n", get_next_line(fd));
// 	printf("Line: %s\n", get_next_line(fd));
// 	printf("Line: %s\n", get_next_line(fd));

// 	close(fd);
// }
