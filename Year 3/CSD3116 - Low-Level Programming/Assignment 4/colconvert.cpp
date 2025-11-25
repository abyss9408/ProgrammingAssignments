/*
  colconvert.cpp
  Optimized implementation of directed to undirected graph conversion
  Author: Bryan Ang Wei Ze
  Date: 2025-11-19
*/
void opt_col_convert_single_threaded(int *G, int dim)
{
    int i, j;
    for (i = 0; i < dim; i+=4)
    {
        for (j = 0; j < dim; j+=4)
        {
            for (int i1 = i; i1 < i+4 && i1 < dim; ++i1)
            {
                for (int j1 = j; j1 < j+4 && j1 < dim; ++j1)
                {
                    int temp1 = G[j1 * dim + i1];
                    int temp2 = G[i1 * dim + j1];
                    G[j1 * dim + i1] = temp1 || temp2;
                }
            }
        }
    }
}