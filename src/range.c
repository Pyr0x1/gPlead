#include <stdio.h>
#include <stdlib.h>
#include "range.h"

Range*
range_new (guint min, guint max)
{
	Range* new = (Range*) calloc (1, sizeof (Range));

	new->min = min;
	new->max = max;

	return new;
}

guint
range_get_min (Range* range)
{
	return range->min;
}

guint
range_get_max (Range* range)
{
	return range->max;
}

guint
range_get_random_value (Range* range)
{
	if (range->max != range->min)
		return (rand() % (range->max - range->min)) + range->min;
	else
		return range->max;	// if max == min the range is actually only a value
}

void
range_free (Range* range)
{
	free (range);

	return ;
}
