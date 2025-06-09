#include "../inc/minishell.h"

size_t	ft_strlcat(char *dst, char *src, size_t dstsize)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	i;

	if (dstsize <= 0)
		return (ft_strlen(src));
	dest_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	i = 0;
	if (dstsize <= dest_len)
		return (dstsize + src_len);
	while (src[i] && dest_len + i < dstsize - 1)
	{
		dst[dest_len + i] = src[i];
		i++;
	}
	dst[dest_len + i] = '\0';
	return (dest_len + src_len);
}

size_t	ft_strlcpy(char *dst, char *src, size_t dstsize)
{
	size_t	i;
	size_t	slen;

	i = 0;
	slen = ft_strlen(src);
	if (!dstsize)
		return (slen);
	while (i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (slen);
}

static int	ft_check_len(char *s1, char *s2)
{
	int	lenght;

	lenght = ft_strlen(s1) + ft_strlen(s2) + 1;
	return (lenght);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*join;
	int		lenght;

	if (!s1 || !s2)
		return (NULL);
	lenght = ft_check_len(s1, s2);
	join = malloc(lenght);
	if (!join)
		return (NULL);
	ft_strlcpy(join, s1, ft_strlen(s1) + 1);
	ft_strlcat(join, s2, lenght);
	return (join);
}


static int	ft_words_count(char *s, char c)
{
	int	i;
	int	count;

	if (!s)
		return (0);
	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && s[i] && s[i + 1] == c)
			count++;
		else if (s[i] != c && s[i + 1] == '\0')
			count++;
		i++;
	}
	return (count);
}

static int	ft_lenght(char *s, char c)
{
	int	i;
	int	len;

	if (!s)
		return (0);
	i = 0;
	len = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c)
			break ;
		if (s[i] != c)
			len++;
		i++;
	}
	return (len);
}

static char	**ft_free(char **word, unsigned int i)
{
	while (i--)
		free(word[i]);
	free(word);
	return (NULL);
}

char	**ft_split(char *s, char c)
{
	t_var	p;

	p.i = 0;
	p.len = 0;
	p.n = 0;
	p.words = ft_words_count(s, c);
	p.sp = (char **)malloc(sizeof(char *) * (p.words + 1));
	if (!p.sp)
		return (NULL);
	while (p.i < p.words)
	{
		p.x = 0;
		p.len = ft_lenght(s + p.n, c);
		p.sp[p.i] = (char *)malloc(p.len + 1);
		if (!p.sp[p.i])
			return (ft_free(p.sp, p.i));
		while (s[p.n] && s[p.n] == c)
			p.n++;
		while (s[p.n] && s[p.n] != c)
			p.sp[p.i][p.x++] = s[p.n++];
		p.sp[p.i][p.x] = '\0';
		p.i++;
	}
	p.sp[p.i] = (NULL);
	return (p.sp);
}

char	*ft_strchr( char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s && fd >= 0)
	{
		write(fd, s, ft_strlen(s));
	}
}

void	ft_putchar_fd(char c, int fd)
{
	if (fd >= 0)
		write(fd, &c, 1);
}
