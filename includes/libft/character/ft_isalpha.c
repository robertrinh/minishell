/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isalpha.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: qtrinh <qtrinh@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 17:38:00 by qtrinh        #+#    #+#                 */
/*   Updated: 2022/10/21 16:53:00 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90)
		|| (c >= 97 && c <= 122))
		return (1);
	return (0);
}

/* int main(void)
{
    char    str;

    str = 'a';
    if(ft_isalpha(str))
        printf("eigen functie: letter, returnt 1\n");
    else
        printf("eigen functie: no letter, dus 0\n");

    if(isalpha(str))
        printf("OG functie: letter, returnt 1\n");
    else
        printf("OG functie: no letter, dus 0\n");
}
 */