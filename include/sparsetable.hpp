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
    uint32_t query(const uint32_t low_index, const uint32_t high_index);
  
 /* 
  * Default constructor that construct the sparse table
  * @params initialArr The vector that will generate 
  * the sparse table
  * @parmas op The operation computed for each index of the table, can be SUM, MIN or MAX
  * @return None
  */
    sparseTable(const std::vector<uint32_t> initialArr, uint32_t(*op)(const uint32_t, const uint32_t));

    private:
    mat_uint32_t sparseTableData;
};

#endif  // SPARSE_TABLE_H