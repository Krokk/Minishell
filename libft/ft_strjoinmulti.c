/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinmulti.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 18:31:43 by rfabre            #+#    #+#             */
/*   Updated: 2017/08/26 18:33:06 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoinmulti(char const *s1, char const *s2, char const *s3,
		char const *s4)
{
	char	*rslt;
	int		i;
	int		j;
	int		k;
	int		l;

	if (s1 != NULL && s2 != NULL && s3 != NULL && s4 != NULL)
	{
		j = ft_strlen(s1);
		k = ft_strlen(s2);
		l = ft_strlen(s3);
		i = ft_strlen(s4);
		if ((rslt = (char*)malloc(sizeof(char) * (j + k + l + i + 1))) == NULL)
			return (NULL);
		i = -1;
		while (*s1 != '\0')
			rslt[++i] = *s1++;
		while (*s2 != '\0')
			rslt[++i] = *s2++;
		while (*s3 != '\0')
			rslt[++i] = *s3++;
		while (*s4 != '\0')
			rslt[++i] = *s4++;
		rslt[++i] = '\0';
		return (rslt);
	}
	return (NULL);
}
