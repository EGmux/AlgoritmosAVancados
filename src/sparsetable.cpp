#include "../include/sparsetable.hpp"
#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <iterator>

/*
 * first we generate the zeroth row, the intialArr data
 * second we apply dynamic programming to fill each new row
 * each row is filled with a computation that require log2(2^[curRow]) elements to compute the
 * result. we can fill the sparsetable, thus the number of total num of rows are
 * floor(log2(initialArr.size()))
 */
SparseTable::SparseTable(const std::vector<uint32_t>& intialArr,
                         uint32_t (*op)(const uint32_t, const uint32_t),const uint32_t id):
        m_op {op},OP_IDENTITY{id} {
    const uint32_t height = floor(log2(intialArr.size())) + 1;
    const uint32_t width = intialArr.size();
    m_sparseTableData = new Matuint32T(height,std::vector<uint32_t>(width));
    std::for_each(m_sparseTableData->begin(), m_sparseTableData->end(), [width](std::vector<uint32_t>&row){row.reserve(width
    );});
    std::copy(intialArr.begin(),
              intialArr.end(),
              (*m_sparseTableData)[0].begin());    // fills zeroth row, we need the ('s due to precedence issues
    uint32_t curIter{1};    
    for (uint32_t curRow {1}; curRow < height; ++curRow) {
        /*
         * briefly to compute for instance a index of the first row, each computation require two
         * elements, we would do the following get the value exactly on the above row in the same
         * collumn and the immediate neighbour to the right for the second row, each computation
         * require 4 elements, we get the value of the index above in the same collumn and the value
         * of the neighbour 1 index to the right, this works because the computation is
         * row0[0]+row0[1]+row0[2]+row0[3] this can be simplified to
         * (row0[0]+row0[1])+(row0[2]+row0[3]), but notice that can be simplified to row1[0]+row1[2]
         * notice the gap of 1 index, we increase this gap to 1 << (curRow -1) for the nth row.
         */
        for (uint32_t curCol {0}; curCol < width; ++curCol) {
            (*m_sparseTableData)[curRow][curCol]=
                m_op((*m_sparseTableData)[curRow-1][curCol],
                   (*m_sparseTableData)[curRow-1][curCol+ curIter]);
        };
        curIter = curIter << 1;
    };
}

/*
 * We start backwards, that is first compute the largest subarray that has power of 2 and 'fits' in
 * the range then compute the second largest subarray that still fits after you ignore the indexes
 * that were covered by the previous one repeat until the current index is either the end of array
 * or higher.
 */
uint32_t SparseTable::Query(uint32_t lowIndex, const uint32_t HIGH_INDEX) {
    uint32_t curIndex;
    uint32_t curAcc{OP_IDENTITY}; //whenever m_op(curAcc, val) is called it always return val
    auto height = (*m_sparseTableData).size();
    while(lowIndex < HIGH_INDEX){
        curIndex = floor(log2(HIGH_INDEX - lowIndex)); // auto find the row with the largest possible subquery
        curAcc = m_op(curAcc, (*m_sparseTableData)[curIndex][lowIndex]); 
        lowIndex+= 1 << curIndex; // equivalent of going to the next subquery
    }
    /* if(lowIndex==HIGH_INDEX){return m_op(curAcc,(*m_sparseTableData)[0][lowIndex-1]);} // the last subquery may be a single element vector */
    return curAcc;
};

/*
 * After one of the indexes in zeroth row has been updated we need to update the computations that
 * depend on it an analysis will show that it propagate similar to a rectangular triangle where the
 * height is the  column where the update happened, the next update is the below row and the
 * imediate left index and the next row after the first increase the number of neighbours that must
 * be updated, until the last, where all the columns to the left of the updated value are
 * re-computed, a tringular pattern is formed.
 */
void SparseTable::Upd(const uint32_t CUR_INDEX, const uint32_t UPDATED_INDEX) {
    (*m_sparseTableData)[0][CUR_INDEX] = UPDATED_INDEX;
    uint32_t curIter {1};
    auto height = (*m_sparseTableData).size();
    for (uint32_t curRow {1}; curRow < height; ++curRow) {
        for (uint32_t curCol {static_cast<uint32_t>(
                 std::max(0, static_cast<int>(CUR_INDEX) - static_cast<int>(curIter << 1) + 1))};
             curCol <= CUR_INDEX;
             ++curCol) {
                (*m_sparseTableData)[curRow][curCol]=
                m_op((*m_sparseTableData)[curRow - 1][curCol],
                     (*m_sparseTableData)[curRow - 1][curCol + curIter]);
        };
        curIter = curIter << 1;
    };
};