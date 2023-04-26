#include <cstdint>
#include <vector>
#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <iterator>
#include <iostream>
#include <istream>
#include <sstream>
#include <string>

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
     * @params op The operation computed for each index of the table, can be SUM, MIN or MAX
     * @params id The identity of the operation, used when query is called
     * @return None
     */
    SparseTable(const std::vector<uint32_t> &initialArr,
                uint32_t (*op)(const uint32_t, const uint32_t),  uint32_t id);

private:
    Matuint32T* m_sparseTableData;
    uint32_t (*m_op)(
    const     uint32_t,
    const     uint32_t);    // op is the name of the attribute,
                            // https://stackoverflow.com/questions/12772372/c-class-that-has-a-pointer-to-a-function-as-an-attribute
    const uint32_t OP_IDENTITY; // if op=MAX then set it to 0, else if MIN set to MAXUINT32 if sum set to 0                            
};



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


uint32_t seed;
#define R UINT32_MAX
#define A 1664525
#define C 1013904223

uint32_t RngNext() {
    seed = (A * seed + C) % R;
    return seed;
}

int main(int argc, char* argv[]) {
    uint32_t sparseTableWidth {0};
    std::string op;         // operation that can be MIN, MAX or SUM
    uint32_t numOps {0};    // total number of operations
    uint32_t freqRangeQuery {0};
    uint32_t freqRangeUpdt {0};
    std::string curLine;     // current testset in a testcase;
    uint32_t curIter {0};    // current testcase
    std::vector<uint32_t> zerothRow;

    while (std::getline(std::cin, curLine), !curLine.empty()) {
        std::stringstream ss(curLine);
        ss >> seed >> sparseTableWidth >> op >> numOps >> freqRangeQuery >>
            freqRangeUpdt;    // parse testset
        zerothRow.reserve(
            sparseTableWidth);    // https://stackoverflow.com/questions/13029299/stdvectorresize-vs-stdvectorreserve
        auto m = (sparseTableWidth << 2);

        /*
         * We use pushback here because reserve only allocates memory, but won't create the
         * necessary indexes until needed.
         */
         zerothRow.push_back(seed%m); // Na primeira chamada, essa função deve retornar X[0]=S.
        for (auto i {1}; i < sparseTableWidth; ++i) {
            zerothRow.push_back(RngNext() % m);
        };
        uint32_t (*function)(const uint32_t, const uint32_t);
        uint32_t id;
        if (op == "MIN") {
            function = [](const uint32_t X, const uint32_t Y) {
                return X > Y ? Y : X;
            };
            id = UINT32_MAX;
        } else if (op == "MAX") {
            function = [](const uint32_t X, const uint32_t Y) {
                return X > Y ? X : Y;
            };
            id = 0;
        } else {
            function = [](const uint32_t X, const uint32_t Y) {
                return X + Y;
            };
            id = 0;
        }
        SparseTable st {zerothRow, function, id};
        uint32_t result;
        std::cout << "caso" << " " << curIter << '\n';
        for (uint32_t curOp {0}; curOp < numOps; ++curOp) {
            if (RngNext() % (freqRangeQuery + freqRangeUpdt) < freqRangeQuery) {
                auto lower = RngNext() % sparseTableWidth;
                auto higher = lower + 1  + (RngNext() % (sparseTableWidth - lower));
                result = st.Query(lower, higher);
            } else {
                auto targetIndex = RngNext() % sparseTableWidth;
                auto newValue = RngNext() % m;
                st.Upd(targetIndex, newValue);
                result = st.Query(targetIndex, sparseTableWidth);
            }
            std::cout << result << '\n';
        };
        std::cout << '\n';    // blank line, signals end of current testcase
        curIter++;
        zerothRow.clear();
    }
};
