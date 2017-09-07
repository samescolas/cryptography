/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_base64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 17:56:52 by sescolas          #+#    #+#             */
/*   Updated: 2017/09/06 19:26:27 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ft_encrypt.h"
#include "libft.h"

unsigned char	ft_b64_e(int ix)
{
	return ((unsigned char)B64_ENC[(int)ix]);
}

/*
** 3 8-bit chars to 4 6-bit chars
*/
unsigned char	*ft_b64encode_chunk(unsigned char *msg, int len)
{
	unsigned char	ret[4];

	ret[0] = ft_b64_e((msg[0] >> 2));
	ret[1] = ft_b64_e((((msg[0] & 0x03) << 4) | ((msg[1] & 0xf0) >> 4)));
	if (len > 1)
		ret[2] = ft_b64_e((((msg[1] & 0x0f) << 2) | ((msg[2] & 0xc0) >> 6)));
	else
		ret[2] = '=';
	if (len > 2)
		ret[3] = ft_b64_e((msg[2] & 0x3f));
	else
		ret[3] = '=';
	return ((unsigned char *)ft_strdup((char *)ret));
}

unsigned char	*ft_b64encode(int fd)
{
	unsigned char	enc[1024];
	unsigned char	buf[4];
	int				ret;

	if (fd < 0)
		return ((void *)0); // need to classify this error : inappropriate file descriptor
	ft_bzero(&buf, 4);
	while ((ret = read(fd, &buf, 3)) > 0)
		ft_strncat((char *)enc, (char *)ft_b64encode_chunk(buf, ret), ret + 1);
	return ((unsigned char *)ft_strdup((char *)enc));
}

int		main(int argc, char **argv)
{
	printf("%s\n", ft_b64encode(STDIN_FILENO));
	return (0);
}

