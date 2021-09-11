#include "stdio.h"

// For segrigating data in batch of 4
int main()
{
    // size_t myDataOtherSize = (12 % 4);
    size_t myDataOtherSize = 23;
    if (myDataOtherSize > 4)
    {
        for (size_t i = 0; i < myDataOtherSize; i++)
        {
            printf("This is no : %d\n", (i % 4));
            if (((i + 1) % 4) == 0)
            {
                printf("the iteration no: %d\n", i);
                printf("hello gaurav\n");
            }
        }
        if ((myDataOtherSize % 4) != 0)
        {
            size_t newIteratorSize = ((myDataOtherSize % 4));
            size_t newIteratorNum = (myDataOtherSize - (myDataOtherSize % 4));
            printf("Printing the no : %d, and % d\n", newIteratorSize, newIteratorNum);
        }
    }

    // printf("Printing the no : %d\n", myDataOtherSize);
    return 0;
}
