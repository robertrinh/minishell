/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isdigit.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: qtrinh <qtrinh@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 17:45:20 by qtrinh        #+#    #+#                 */
/*   Updated: 2022/10/21 16:53:01 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

/* int main(void)
{
    char    str;

    str = 'a';
    if(ft_isdigit(str))
        printf("own functie: DONG DONG DONG\n");
    else
        printf("own functie: This is a pen\n");
    if(isdigit(str))
        printf("OG functie: DONG DONG DONG\n");
    else
        printf("OG functie: This is a pen\n");
}
 */