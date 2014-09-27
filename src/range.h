#ifndef RANGE_H
#define RANGE_H

#include <glib.h>

typedef struct range {

	guint min;
	guint max;

} Range;

Range* range_new (guint min, guint max);
guint range_get_min (Range* range);
guint range_get_max (Range* range);
guint range_get_random_value (Range* range);
void range_free (Range* range);

#endif /* RANGE_H */