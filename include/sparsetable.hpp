#ifndef SPARSE_TABLE_H
#define SPARSE_TABLE_H

#include <vector>
#include <cstdint>

typedef std::vector<std::vector<uint32_t>> mat_uint32_t;

class sparseTable{
  public:
  /* 
   *  Mutable method that given two valid indexes reconstruct partially the sparse table.
   *  @params cur_index The index that will be updated in the array
   *  @params updated_index The updated value of the targeted index
   *  @returns None
   */
    void upd(const uint32_t cur_index, const uint32_t updated_index);

  /* 
   *  Immutable method that returns one of the following computations for the specificed range: MIN, MAX, SUM.
   *  @params lower_index The start of the range query
   *  @params high_index The end of the range query
   *  @returns The computation result
   */
    uint32_t query(cont uint32_t low_index, const uint32_t high_index);
  
    private:
    mat_uint32_t sparseTable;
}


#endif  // SPARSE_TABLE_H