/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remi <remi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 17:26:28 by rfabre            #+#    #+#             */
/*   Updated: 2017/08/17 12:26:04 by remi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void get_request(char **request)
{
	int		ret;
	char	buf[2];

    *request = ft_strnew(1);
	while ((ret = read(0, &buf, 1)) && !ft_strchr(buf, '\n'))
    {
        buf[ret] = '\0';
        *request = ft_freejoin(*request, buf);
    }
	if (!ret)
	{
		free(*request);
		ft_putendl("DEBUG GET REQUEST");
	}

    if (*(*request))
    {
        ft_putstr(*request);
        ft_putstr("\n");
        free (*request);    
    }
    else
        free(*request);
    
}
    
            
int main(int ac, char **argv, char **venv)
{
    char *request;
    char **commands;

    while (1)
    {
    get_request(&request);  
    // free(request);
    if (ft_strstr(request, "exit"))
        {
            // free(request);
            return (0);     
               }
    }
    return (0);

}
