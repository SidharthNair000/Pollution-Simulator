#ifndef COMMERCIAL_H
#define COMMERCIAL_H

#include "Cell.h"


class Commercial {
private:
    int goods;
    int population;
    int workers;


public:

    Commercial(); // Default Constructor
    void SetValues(int population, int workers, int goods);
    void ResetValues();
    int GetPopulation();
    int GetWorkers();
    int GetGoods();
    bool UpdateCommercial(Cell& cell, int availableWorkers, int availableGoods); // Updates Commercial
    //Bool Functions to check if there are available workers/goods.
    bool HasEnoughWorkers(int availableWorkers);
    bool HasEnoughGoods(int availableGoods);
};

#endif
