#include "include/sparsetable.hpp"
#include <cmath>

/*
* first we generate the zeroth row, the intialArr data
* second we apply dynamic programming to fill each new row
* each row is filled with a computation that require log2(2^[curRow]) elements to compute the result. 
* we can fill the sparsetable, thus the number of total num of rows are floor(log2(initialArr.size()))
*/
sparseTable::sparseTable(const std::vector<uint32_t> intialArr, uint32_t(*op)(const uint32_t, const uint32_t) )
{
    const uint32_t numRows = floor(log2(intialArr.size())) + 1;
    std::copy(intialArr.begin(), intialArr.end(), sparseTableData[0]); // fills zeroth row
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
            sparseTableData[curRow][curCol] = op(sparseTableData[curRow - 1][curCol],sparseTableData[curRow -1][curCol + (1 << (curRow -1))]);
        };
    };
}

/*
* To split the original range in two subranges we do the following
*  
*/
uint32_t sparseTable::query(const uint32_t lowIndex, const uint32_t highIndex){
    
}
