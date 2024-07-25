/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkolida <dkolida@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 12:55:27 by dkolida           #+#    #+#             */
/*   Updated: 2024/07/25 12:55:44 by dkolida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_char(char *s1, char c)
{
	char	*c_str;
	char	*new_str;

	c_str = char_to_str(c);
	if (!c_str)
		return (NULL);
	new_str = ft_strjoin(s1, c_str);
	free(c_str);
	return (new_str);
}
