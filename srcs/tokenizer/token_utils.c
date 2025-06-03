/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machouba <machouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 19:01:42 by machouba          #+#    #+#             */
/*   Updated: 2024/08/07 15:23:39 by machouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_token	*findlast_token(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

t_token	*token_before_last(t_token *list)
{
	t_token	*cur_token;

	cur_token = list;
	while (cur_token->next->next != NULL)
		cur_token = cur_token->next;
	return (cur_token);
}

int	check_pipe_errors(t_data *data, t_token *token)
{
	if (token->next && ft_isop(token->next->value) == TRUE)
	{
		if (token->next->next && token->next->next->type == PIPE)
			return (error_token(token->next, token->next->next->type),
				exit_stat(data), TRUE);
		else if (ft_isop(token->next->value) == TRUE
			&& token->next->next == NULL)
			return (error_token(token->next, NEWLINE_ERROR), exit_stat(data),
				TRUE);
	}
	return (FALSE);
}
