#include "ft_ls.h"
/* Calculate the number of columns needed to represent the current set
   of files in the current display width.  */

static size_t	calculate_columns (bool by_columns)
{
  size_t filesno;               /* Index into cwd_file.  */
  size_t cols;                  /* Number of files across.  */

  /* Normally the maximum number of columns is determined by the
     screen width.  But if few files are available this might limit it
     as well.  */
  size_t max_cols = MIN (max_idx, cwd_n_used);

  init_column_info ();

  /* Compute the maximum number of possible columns.  */
  for (filesno = 0; filesno < cwd_n_used; ++filesno)
    {
      struct fileinfo const *f = sorted_file[filesno];
      size_t name_length = length_of_file_name_and_frills (f);

      for (size_t i = 0; i < max_cols; ++i)
        {
          if (column_info[i].valid_len)
            {
              size_t idx = (by_columns
                            ? filesno / ((cwd_n_used + i) / (i + 1))
                            : filesno % (i + 1));
              size_t real_length = name_length + (idx == i ? 0 : 2);

              if (column_info[i].col_arr[idx] < real_length)
                {
                  column_info[i].line_len += (real_length
                                              - column_info[i].col_arr[idx]);
                  column_info[i].col_arr[idx] = real_length;
                  column_info[i].valid_len = (column_info[i].line_len
                                              < line_length);
                }
            }
        }
    }

  /* Find maximum allowed columns.  */
  for (cols = max_cols; 1 < cols; --cols)
    {
      if (column_info[cols - 1].valid_len)
        break;
    }

  return cols;
}