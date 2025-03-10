#include "Industrial.h"

Industrial::Industrial() {
    population = 0;
    workers = 0;
    goods = 0;
}

void Industrial::SetValues(int population, int workers, int goods) {
    this->population = population;
    this->workers = workers;
    this->goods = goods;
}

int Industrial::GetPopulation() {
    return population;
}

int Industrial::GetWorkers() {
    return workers;
}

int Industrial::GetGoods() {
    return goods;
}

void Industrial::ResetValues() {
    population = 0;
    workers = 0;
    goods = 0;
}

// Function to check if a cell has at least 2 available workers
bool Industrial::HasEnoughWorkers(int availableWorkers) {
    return availableWorkers >= 2;
}

// Function to update the industrial cell based on specified conditions
bool Industrial::UpdateIndustrial(Cell& cell, int availableWorkers) {
    population = cell.GetPopulation();
    workers = cell.GetWorkers();

    if (population >= 0 && cell.IsAdjToPowerline() && HasEnoughWorkers(availableWorkers)) {
        population += 1;
        cell.SetPopulation(population);
        workers += 2; // Assign 2 workers to the job
        cell.SetWorkers(workers);
        goods += population; // Each population produces one good
        return true;
    }
    else if (population >= 0 && cell.IsAdjToCellsPopOne() && HasEnoughWorkers(availableWorkers)) {
        population += 1;
        cell.SetPopulation(population);
        workers += 2; // Assign 2 workers to the job
        cell.SetWorkers(workers);
        goods += population; // Each population produces one good
        return true;
    }
    else if (population >= 1 && cell.IsAdjToCellsPopTwoOrMore() && HasEnoughWorkers(availableWorkers)) {
        population += 1;
        cell.SetPopulation(population);
        workers += 2; // Assign 2 workers to the job
        cell.SetWorkers(workers);
        goods += population; // Each population produces one good
        return true;
    }
    else if (population >= 2 && cell.IsAdjToCellsPopFourOrMore() && HasEnoughWorkers(availableWorkers)) {
        population += 1;
        cell.SetPopulation(population);
        workers += 2; // Assign 2 workers to the job
        cell.SetWorkers(workers);
        goods += population; // Each population produces one good
        return true;
    }
    return false;
}
