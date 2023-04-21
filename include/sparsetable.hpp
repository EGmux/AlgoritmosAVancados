#ifndef SPARSE_TABLE_H
#define SPARSE_TABLE_H

#include <cstdint>
#include <vector>

typedef std::vector<std::vector<uint32_t>> Matuint32T;

class SparseTable {
public:
    /*
     *  Mutable method that given two valid indexes reconstruct partially the sparse table.
     *  @params curIndex The index that will be updated in the array
     *  @params updatedIndex The updated value of the targeted index
     *  @returns None
     */
    void Upd(uint32_t curIndex, uint32_t updatedIndex);

    /*
     *  Immutable method that returns one of the following computations for the specificed range:
     * MIN, MAX, SUM.
     *  @params lowerIndex The start of the range query
     *  @params highIndex The end of the range query
     *  @returns The computation result
     */
    uint32_t Query(uint32_t lowIndex, uint32_t highIndex);

    /*
     * Default constructor that construct the sparse table
     * @params initialArr The vector that will generate
     * the sparse table
     * @parmas op The operation computed for each index of the table, can be SUM, MIN or MAX
     * @return None
     */
    SparseTable(const std::vector<uint32_t> &initialArr,
                uint32_t (*op)(const uint32_t, const uint32_t));

private:
    Matuint32T* m_sparseTableData;
    uint32_t (*m_op)(
    const     uint32_t,
    const     uint32_t);    // op is the name of the attribute,
                            // https://stackoverflow.com/questions/12772372/c-class-that-has-a-pointer-to-a-function-as-an-attribute
};

#endif    // SPARSE_TABLE_H