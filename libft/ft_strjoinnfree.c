/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinnfree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remi <remi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 02:32:45 by rfabre            #+#    #+#             */
/*   Updated: 2017/08/15 16:54:55 by remi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoinnfree(char *s1, char *s2, size_t len, char b12)
{
	char	*s;
	char	*ret;
	char	*tmp1;
	char	*tmp2;

	s = (char*)malloc(sizeof(char) * (ft_strlen(s1) + len));
	ret = s;
	tmp1 = s1;
	tmp2 = s2;
	while (*s1)
		*s++ = *s1++;
	while (*s2 && len--)
		*s++ = *s2++;
	if (ft_strchr(&b12, '1') || b12 == 'b')
		{
			ft_strdel(&s1);
			ft_putstr("free1");
		}
	if (ft_strchr(&b12, '2') || b12 == 'b')
	{
		free(s2);
		ft_putstr("safree");
	}
	return (ret);
}