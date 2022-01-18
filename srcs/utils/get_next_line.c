#include "cub3D.h"
#define BUFF_SIZE 42
#define MAX_FD 256

int	error_free(char *ptr)
{
	free(ptr);
	return (-1);
}

int	cutting(char **buf_store, char **line, char *ptr_next)
{
	char	*tmp;

	*ptr_next = '\0';
	*line = ft_strdup(*buf_store);
	if (!(*line))
		return (error_free(*buf_store));
	tmp = *buf_store;
	if (*(ptr_next + 1) != '\0')
		*buf_store = ft_strdup(ptr_next + 1);
	if (!(*buf_store))
		return (error_free(tmp));
	free(tmp);
	return (1);
}

int	last_cutting(char **buf_store, char **line)
{
	if (*buf_store == NULL)
		return (0);
	else if (**buf_store == '\0')
	{
		free(*buf_store);
		*buf_store = NULL;
		*line = NULL;
		return (0);
	}
	*line = ft_strdup(*buf_store);
	if (!(*line))
		return (error_free(*buf_store));
	free(*buf_store);
	*buf_store = NULL;
	return (1);
}

int	if_rtn_read_zero(char **buf_store, char **line)
{
	char	*tmp;

	if (*buf_store == NULL)
		return (0);
	tmp = ft_strchr(*buf_store, '\n');
	if (tmp)
		return (cutting(buf_store, line, tmp));
	return (last_cutting(buf_store, line));
}

int	get_next_line(int fd, char **line)
{
	char		buf[BUFF_SIZE + 1];
	static char	*buf_store[MAX_FD];
	ssize_t		rtn_read;
	char		*tmp;

	if (fd > MAX_FD || fd < 0 || !line || BUFF_SIZE <= 0)
		return (-1);
	rtn_read = read(fd, buf, BUFF_SIZE);
	if (!buf_store[fd])
		buf_store[fd] = ft_strdup("");
	while (rtn_read > 0)
	{
		buf[rtn_read] = '\0';
		tmp = buf_store[fd];
		buf_store[fd] = ft_strjoin(buf_store[fd], buf);
		free(tmp);
		tmp = ft_strchr(buf_store[fd], '\n');
		if (tmp)
			return (cutting(&buf_store[fd], line, tmp));
		rtn_read = read(fd, buf, BUFF_SIZE);
	}
	if (rtn_read == 0)
		return (if_rtn_read_zero(&buf_store[fd], line));
	free(buf_store[fd]);
	buf_store[fd] = NULL;
	return (-1);
}
