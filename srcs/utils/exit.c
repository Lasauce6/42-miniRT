# include "miniRT.h"

int message_error(char *format, char *detail, int exit_no)
{
	if (!detail)
		printf(format, STR_PROG_NAME);
	else
		printf(format, STR_PROG_NAME, detail);
	return (exit_no);
}

static void	free_lights(t_light **lights)
{
	t_light *tmp;
	t_light *l;

	l = *lights;
	while (l)
	{
		tmp = l;
		l = l->next;
		free(tmp);
	}
	*lights = 0;
}

int	error_failure(char *format, char *detail)
{
	
	exit(message_error(format, detail, EXIT_FAILURE));
}

int	error_failure_free_obj(char *format, char *detail, t_obj *obj)
{
	free(obj);
	exit(error_failure(format, detail));
}

int error_failure_free_light(char *format, char *detail, t_light *light)
{
	free(light);
	exit(error_failure(format, detail));
}


void	*free_table(t_data *data)
{
	if (!data)
		return (NULL);
	if (data->light)
		free_lights(&(data->light));
	if (data->objs)
		free_objects(&(data->objs));
	return (NULL);
}