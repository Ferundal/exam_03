#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct	s_zone
{
	int		width;
	int		height;
	char	back_c;
	char*	array;

}				t_zone;

typedef struct	s_rect
{
	char	type;
	float	x;
	float	y;
	float	width;
	float	height;
	char	rect_c;

}				t_rect;

void set_value(int x, int y, t_zone* zone, char c)
{
	*(zone->array + y * zone->width + x) = c;
}

float ft_abs(float value)
{
	if (value < 0)
		return (-value);
	return (value);
}

void write_rect(t_zone* zone, t_rect* rect)
{
	int		y;
	int		x;

	y = 0;
	while (y < zone->height)
	{
		while (x < zone->width)
		{
			x = 0;
			set_value(x, y, zone, zone->back_c);
			if(rect->rect_c == 'R')
			{
				if ((x > rect->x && x < rect->x + rect->width) && \
					(y > rect->y && y < rect->y + rect->height))
					set_value(x, y, zone, rect->rect_c);
			}
			if ((ft_abs(rect->x - x) < 1 && (y > rect->y && y < rect->y + rect->height)) || \
				(ft_abs(rect->x + rect->width - x) < 1 && (y > rect->y && y < rect->y + rect->height)) || \
				(ft_abs(rect->y - y) < 1 && (x > rect->x && x < rect->x + rect->width)) || \
				(ft_abs(rect->y + rect->height - y) < 1 && (x > rect->x && x < rect->x + rect->width)))
				set_value(x, y, zone, rect->rect_c);
			++x;
		}
		++y;
	}
}

void	write_zone(t_zone* zone)
{
	int	y;

	y = 0;
	while (y < zone->height - 1)
	{
		write(1, zone->array, 1);
		//write(1, zone->array + y * zone->width, zone->width);
		//write(1, "\n", 1);
		++y;
	}
	write(1, zone->array + y * zone->width, zone->width);
}

int main(int argc, char** argv)
{
	FILE	*fd;
	t_zone	zone;
	t_rect	rect;
	int		status;

	status = 0;
	if (argc != 2)
	{
		write(1, "Error: argument\n", 16);
		return (1);
	}
	fd = fopen(*(argv + 1), "r");
	if (fd == NULL)
	{
		write(1, "Error: Operation file corrupted\n", 32);
		return (1);
	}
	status = fscanf(fd, "%d %d %c\n", &zone.width, &zone.height, &zone.back_c);
	if (status != 3 || zone.width < 0 || zone.width > 300 || zone.height < 0 || zone.height > 300)
	{
		write(1, "Error: Operation file corrupted\n", 32);
		return (1);
	}
	zone.array = (char*)malloc( sizeof(char) * zone.width * zone.height);
	if (zone.array == NULL)
		return (1);
	while ((status = fscanf(fd, "%c %f %f %f %f %c\n", &rect.type, &rect.x, &rect.y, &rect.width, &rect.height, &rect.rect_c)) == 6)
	{
		if ((rect.type != 'r' && rect.type != 'R') || rect.width <= 0 || rect.height <= 0)
		{
			write(1, "Error: Operation file corrupted\n", 32);
			return (1);
		}
		write_rect(&zone, &rect);
	}
	if (status != -1 && status != 6)
	{
		write(1, "Error: Operation file corrupted\n", 32);
		return (1);
	}
	write_zone(&zone);
	return (0);
}