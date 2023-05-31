#include "get_next_line.h"

char	*get_next_line(int fd)
{
	ssize_t		player;
	char		*buffer;
	static char	*stash;
	char		*line;
	player = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	stash = ft_well_read(fd, player, buffer, stash);
	if (!stash)
		return (NULL);
	line = line_return(stash);
	stash = new_stash(stash);
	return(line);
}

char *ft_well_read(int fd, ssize_t player, char *buffer, char *stash)
{
	char *temp;
	temp = ""; // NULL
	//int i = 1;

	while (player != 0)
	{
		player = read(fd, buffer, BUFFER_SIZE);
		temp = stash;
		if (player == -1)
		{
			free (buffer);
			return (NULL);
		}
		buffer[player] = '\0';
		if (temp == NULL)
		{
			// temp = malloc(1 * sizeof(char));
			// free(temp);
			// temp = "\0";
			temp = ft_calloc(1, 1);
		}
		
		//printf("%d : %s\n", i, stash);
		stash = ft_strjoin(temp, buffer);
		free(temp);
		//i++;
		if (ft_where_backslash_n(stash) != -1)
			break ;
	}
	free(buffer);
	return (stash);
}

int	ft_where_backslash_n(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '\n')
		{
			//printf("%d ", i);
			return (i);
		}
		i++;
	}
	return (-1);
}

char *line_return(char *stash)
{
	int loc;
	char *res;

	if (!stash || stash[0] == '\0')
		return (NULL);
	loc = ft_where_backslash_n(stash);
	if (loc == -1)
	{
		res = ft_substr(stash, 0, ft_strlen(stash));
		//printf("without n | return = %d | res = %s | result gnl = ", loc, res);
	}
	else
	{
		res = ft_substr(stash, 0, loc + 1);
		//printf("with: %d ", loc);
	}
	return (res);
}

char *new_stash(char *stash)
{
	char *temp;
	int loc;

	loc = ft_where_backslash_n(stash);
	if (!stash)
		return (NULL);
	if (loc == -1)
	{
		free(stash);
		return (NULL);
	}
	//printf("stash = %s\n", stash);
	loc++;
	temp = ft_substr(stash, loc, ft_strlen(stash) - loc);
	//printf("stash = %s\n", tmp);
	if (!temp)
		return (NULL);
	free(stash);
	return (temp);
}

int	main	(void)
{
	int fd;
	fd = open("text.txt", O_RDONLY);
	int i;
	i = 0;

	while (i < 2)
	{
		printf("%s", get_next_line(fd));
		//get_next_line(fd);
		//printf("\n");
		i++;
	}
	//get_next_line(fd);
	system ("leaks a.out");
	//get_next_line(fd);
	//printf("%s\n", get_next_line(fd));
	//printf("%s\n", get_next_line(fd));
	return (0);
}