#ifndef GAMEPATH_H
#define GAMEPATH_H

#include <glib.h>

gint** generate_random_path (guint num_col, guint num_row);
void free_path (gint** path, guint num_col, guint num_row);

#endif /* GAMEPATH_H */