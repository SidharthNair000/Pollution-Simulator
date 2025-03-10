#include "Commercial.h"

Commercial::Commercial() {
    population = 0;
    workers = 0;
    goods = 0;
}

void Commercial::SetValues(int population, int workers, int goods) {
    this->population = population;
    this->workers = workers;
    this->goods = goods;
}

void Commercial::ResetValues() {
    population = 0;
    workers = 0;
    goods = 0;
}

int Commercial::GetPopulation() {
    return population;
}

int Commercial::GetWorkers() {
    return workers;
}

int Commercial::GetGoods() {
    return goods;
}

bool Commercial::HasEnoughWorkers(int availableWorkers) {
    return availableWorkers >= 1;
}

bool Commercial::HasEnoughGoods(int availableGoods) {
    return availableGoods > 1;
}

bool Commercial::UpdateCommercial(Cell& cell, int availableWorkers, int availableGoods) {
    population = cell.GetPopulation();
    workers = cell.GetWorkers();
    goods = cell.GetGoods();

    if (population >= 0 && cell.IsAdjToPowerline() && HasEnoughWorkers(availableWorkers) && HasEnoughGoods(availableGoods)) {
        population += 1;
        cell.SetPopulation(population);
        workers += 1;
        cell.SetWorkers(workers);
        goods += 1;
        cell.SetGoods(goods);
        return true;
    }
    else if (population >= 0 && cell.IsAdjToCellsPopOne() && HasEnoughWorkers(availableWorkers) && HasEnoughGoods(availableGoods)) {
        population += 1;
        cell.SetPopulation(population);
        workers += 1;
        cell.SetWorkers(workers);
        goods += 1;
        cell.SetGoods(goods);
        return true;
    }
    else if (population >= 1 && cell.IsAdjToCellsPopTwoOrMore() && HasEnoughWorkers(availableWorkers) && HasEnoughGoods(availableGoods)) {
        population += 1;
        cell.SetPopulation(population);
        workers += 1;
        cell.SetWorkers(workers);
        goods += 1;
        cell.SetGoods(goods);
        return true;
    }
    return false;
}

