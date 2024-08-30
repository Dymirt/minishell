/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   groups_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkolida <dkolida@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 22:22:09 by dkolida           #+#    #+#             */
/*   Updated: 2024/08/30 21:34:41 by dkolida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_group	*group_init(int argc);
void	add_to_group(t_shell *shell, char *token, int is_end);
int		shell_groups_init(t_shell *shell, char **tokens);

void	group_input(t_shell *shell, char **tokens)
{
	int	tokens_c;
	int	i;
	int	*group_i;

	group_i = &shell->group_i;
	tokens_c = shell_groups_init(shell, tokens);
	shell->tokens_count = tokens_c;
	i = 0;
	while (tokens[i])
	{
		if (!shell->groups[*group_i])
			shell->groups[*group_i] = group_init(tokens_c);
		if (ft_strcmp(tokens[i], "<") == 0)
			shell->groups[*group_i]->in_file_name = ft_strdup(tokens[++i]);
		else if (ft_strcmp(tokens[i], ">") == 0)
			shell->groups[*group_i]->out_file_name = ft_strdup(tokens[++i]);
		else
			add_to_group(shell, tokens[i], i == tokens_c - 1);
		i++;
	}
	if (*group_i > 0)
		(*group_i)--;
}
//The group_i variable is used to keep track of the current group index later.

void	add_to_group(t_shell *shell, char *token, int is_end)
{
	int	*i;
	int	*arg_i;

	i = &shell->group_i;
	arg_i = &shell->groups[*i]->arg_i;
	if (ft_strcmp(token, "|") == 0 || is_end)
	{
		if ((is_end && ft_strcmp(token, "|") != 0)
			|| (((*arg_i) > 0)
				&& (ft_strcmp(shell->groups[*i]->args[(*arg_i) - 1], "echo")
					== 0)))
			shell->groups[*i]->args[(*arg_i)++] = ft_strdup(token);
		(*i)++;
	}
	else
		shell->groups[*i]->args[(*arg_i)++] = ft_strdup(token);
}

t_group	*group_init(int argc)
{
	t_group	*group;

	group = malloc(sizeof(t_group));
	if (!group)
		return (NULL);
	group->args = malloc(sizeof(char *) * (argc + 1));
	if (!group->args)
	{
		free(group);
		return (NULL);
	}
	while (argc >= 0)
		group->args[argc--] = NULL;
	group->arg_i = 0;
	group->in_file_name = NULL;
	group->out_file_name = NULL;
	return (group);
}

int	shell_groups_init(t_shell *shell, char **tokens)
{
	int	tokens_count;
	int	i;

	tokens_count = 0;
	while (tokens[tokens_count])
		tokens_count++;
	shell->groups = malloc(sizeof(t_group *) * (tokens_count + 1));
	if (!shell->groups)
		return (0);
	shell->group_i = 0;
	i = 0;
	while (i < tokens_count)
		shell->groups[i++] = NULL;
	return (tokens_count);
}
