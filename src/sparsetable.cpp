#include "../include/sparsetable.hpp"
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <array>
/*
* first we generate the zeroth row, the intialArr data
* second we apply dynamic programming to fill each new row
* each row is filled with a computation that require log2(2^[curRow]) elements to compute the result. 
* we can fill the sparsetable, thus the number of total num of rows are floor(log2(initialArr.size()))
*/
SparseTable::SparseTable(const std::vector<uint32_t>& intialArr, uint32_t(*op)(const uint32_t, const uint32_t) ):m_op{}
{
    const uint32_t numRows = floor(log2(intialArr.size())) + 1;
    m_sparseTableData.resize((floor(log2(intialArr.size()+1) + intialArr.size()))); // prealloc the matrix
    std::copy(intialArr.begin(), intialArr.end(), m_sparseTableData[0].begin()); // fills zeroth row
    for(uint32_t curRow{1}; curRow <= numRows; ++curRow){
        /*
        * briefly to compute for instance a index of the first row, each computation require two elements, we would do the following
        * get the value exactly on the above row in the same collumn and the immediate neighbour to the right
        * for the second row, each computation require 4 elements, we get the value of the index above in the same collumn
        * and the value of the neighbour 1 index to the right, this works because the computation is row0[0]+row0[1]+row0[2]+row0[3]
        * this can be simplified to (row0[0]+row0[1])+(row0[2]+row0[3]), but notice that can be simplified to row1[0]+row1[2]
        * notice the gap of 1 index, we increase this gap to 1 << (curRow -1) for the nth row.
        */
        for(uint32_t curCol{0}; curCol + (curCol << 1) <=  intialArr.size(); ++curCol){
            m_sparseTableData[curRow][curCol] = op(m_sparseTableData[curRow - 1][curCol],m_sparseTableData[curRow -1][curCol + (1 << (curRow -1))]);
        };
    };
}

/*
* We start backwards, that is first compute the largest subarray that has power of 2 and 'fits' in the range
*  then compute the second largest subarray that still fits after you ignore the indexes that were covered by the previous one
*   repeat until the current index is either the end of array or higher.
*/
uint32_t SparseTable::Query( uint32_t lowIndex, const uint32_t HIGH_INDEX){
    uint32_t curIndex;
    uint32_t curAcc;
    while(lowIndex < HIGH_INDEX){
        curIndex = log2(HIGH_INDEX - lowIndex);
        curAcc = m_op(curAcc,m_sparseTableData[curIndex][lowIndex]);
        lowIndex += (1 << curIndex); 
    };
    return curAcc; 
};

/*
* After one of the indexes in zeroth row has been updated we need to update the computations that depend on it
* an analysis will show that it propagate similar to a rectangular triangle where the height is the  column where
* the update happened, the next update is the below row and the imediate left index and the next row after the first 
* increase the number of neighbours that must be updated, until the last, where all the columns to the left of the 
* updated value are re-computed.
*/
void SparseTable::Upd(const uint32_t CUR_INDEX, const uint32_t UPDATED_INDEX){
    m_sparseTableData[0][CUR_INDEX] = UPDATED_INDEX;
    uint32_t curIter{1};
    for(uint32_t curRow{1}; curRow < m_sparseTableData.size(); ++curRow){
        for(uint32_t curCol{static_cast<uint32_t>(std::max(0,static_cast<int>(curIter) - (1 << curIter) -1))}; curCol < CUR_INDEX; ++curCol){
            m_sparseTableData[curRow][curCol] = m_op(m_sparseTableData[curRow - 1][curCol],m_sparseTableData[curRow -1][curCol + (1 << (curRow -1))]);
        };
    };       
};