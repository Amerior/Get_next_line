/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdu <sdu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 19:33:51 by sdu               #+#    #+#             */
/*   Updated: 2025/01/04 16:04:49 by sdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_free(char *buffer, char *end)
{
	char	*temp;

	temp = ft_strjoin(buffer, end);
	free(buffer);
	return (temp);
}

static char	*ft_next(char *buffer)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	line = ft_calloc((ft_strlen(buffer) - i + 1), sizeof(*buffer));
	if (!line)
		return (NULL);
	j = 0;
	while (buffer[i])
		line[j++] = buffer[++i];
	line[j] = '\0';
	free(buffer);
	return (line);
}

static char	*ft_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
		line[i++] = '\n';
	return (line);
}

static char	*read_file(int fd, char *res)
{
	char	*buffer;
	int		read_byte;

	if (!res)
		res = ft_calloc(1, 1);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	read_byte = 1;
	while (read_byte > 0)
	{
		read_byte = read(fd, buffer, BUFFER_SIZE);
		if (read_byte == -1)
		{
			free(buffer);
			free(res);
			return (NULL);
		}
		buffer[read_byte] = '\0';
		res = ft_free(res, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*buffers[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffers[fd] = read_file(fd, buffers[fd]);
	if (!buffers[fd])
		return (NULL);
	line = ft_line(buffers[fd]);
	buffers[fd] = ft_next(buffers[fd]);
	return (line);
}

// #include <fcntl.h>
// #include <stdio.h>
// #include <stdlib.h>

// #define MAXIMUM 5

// int	main(void)
// {
// 	int		fds[MAXIMUM];
// 	char	*line;
// 	int		i;
// 	char	*files[MAXIMUM] = {"file1.txt", "file2.txt", "file3.txt",
// 			"file4.txt", "file5.txt"};

// 	i = 0;
// 	while (i < MAXIMUM)
// 	{
// 		fds[i] = open(files[i], O_RDONLY);
// 		if (fds[i] == -1)
// 		{
// 			perror("CA MARCHE PAS YA UN PB CHEF");
// 			return (1);
// 		}
// 		i++;
// 	}
// 	i = 0;0
// 	while (i < MAXIMUM)
// 	{
// 		printf("Fichier actuel : %s\n", files[i]);
// 		while ((line = get_next_line(fds[i])) != NULL)
// 		{
// 			printf("Contenu : %s", line);
// 			free(line);
// 		}
// 		i++;
// 	}
// 	i = 0;
// 	while (i < MAXIMUM)
// 	{
// 		close(fds[i]);
// 		i++;
// 	}
// 	return (0);
// }

// int	main(void)
// {
// 	int fd1, fd2;
// 	char *line1, *line2;
// 	fd1 = open("file1.txt", O_RDONLY);
// 	if (fd1 == -1)
// 	{
// 		perror("PROBLEME file1.txt");
// 		return (1);
// 	}
// 	fd2 = open("file2.txt", O_RDONLY);
// 	if (fd2 == -1)
// 	{
// 		perror("PROBLEME file2.txt");
// 		close(fd1);
// 		return (1);
// 	}
// 	// Read and print lines from both files
// 	while (1)
// 	{
// 		line1 = get_next_line(fd1);
// 		if (line1)
// 		{
// 			printf("file1.txt: %s", line1);
// 			free(line1);
// 		}
// 		line2 = get_next_line(fd2);
// 		{
// 			printf("file2.txt: %s", line2);
// 			free(line2);
// 		}
// 		// Break the loop when both files reach EOF
// 		if (!line1 && !line2)
// 		{
// 			break ;
// 		}
// 	}
// 	close(fd1);
// 	close(fd2);
// 	return (0);
// }