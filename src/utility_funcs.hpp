#ifndef UTILITY_FUNCS_HEADER_FILE
#define UTILITY_FUNCS_HEADER_FILE

#include <vector>

/* transpose_vector_of_vectors
  
  take a column vector:
  |v1|
  |v2|
  |v3|
  |v4|
  |v5|
  and return a row vector |v1, v2, v3, v4, v5|
  
  parameters:
    col_vector, the column vector to transpose
  
  return:
    row_vector, the transposed input column vector
*/
template <typename type>
auto transpose_vector_of_vectors(const std::vector<std::vector<type>>& col_vector) -> std::vector<std::vector<type>> {
    
    // allocate correct size in memory
    std::vector<std::vector<type>> row_vector(col_vector[0].size(), std::vector<type>(col_vector.size()));
    // transpose
    for(size_t i{0}; i < col_vector.size(); ++i) {   
        for (size_t j{0}; j < col_vector[i].size(); ++j) {
            row_vector[j][i] = col_vector[i][j];
        }
    }
    return row_vector;
}

#endif // UTILITY_FUNCS_HEADER_FILE