#include <stdio.h>
#include <stdlib.h>
#include "range.h"

Range*
range_new (guint min, guint max)
{
	Range* new = (Range*) calloc (1, sizeof (Range));

	new->min = min;
	if (min > max)
		new->max = min;
	else
		new->max = max;

	return new;
}

gint
range_get_min (Range* range)
{
	if (!range)
		return -1;
	
	return range->min;
}

gint
range_get_max (Range* range)
{
	if (!range)
		return -1;
	
	return range->max;
}

gint
range_get_random_value (Range* range)
{
	if (!range)
		return -1;
	
	if (range->max != range->min)
		return (rand() % (range->max - range->min)) + range->min;
	else
		return range->max;	// if max == min the range is actually only a value
}

void
range_free (Range* range)
{
	if (!range)
		return;
	
	free (range);

	return;
}

