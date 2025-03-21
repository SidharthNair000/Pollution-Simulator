#include "Residential.h"

Residential::Residential() {
	population = 0;
	workers = 0;
}

void Residential::SetValues(int population, int workers) {
	this->population = population;
	this->workers = workers;
}

void Residential::ResetValues() {
	population = 0;
	workers = 0;
}

int Residential::GetPopulation() {
	return population;
}

int Residential::GetWorkers() {
	return workers;
}

bool Residential::UpdateResidential(Cell& cell) {
	population = cell.GetPopulation();
	workers = cell.GetWorkers();

	if (population >= 0 && cell.IsAdjToPowerline()) {
		population += 1;
		cell.SetPopulation(population);
		workers += 1;	// Assign 1 worker to the job
		cell.SetWorkers(workers);
		workers += population; // Each population produces 1 worker
		return true;
	}
	else if (population >= 0 && cell.IsAdjToCellsPopOne()) {
		population += 1;
		cell.SetPopulation(population);
		workers += 1;	// Assign 1 worker to the job
		cell.SetWorkers(workers);
		workers += population; // Each population produces 1 worker
		return true;
	}
	else if (population >= 1 && cell.IsAdjToCellsPopTwoOrMore()) {
		population += 1;
		cell.SetPopulation(population);
		workers += 1;	// Assign 1 worker to the job
		cell.SetWorkers(workers);
		workers += population; // Each population produces 1 worker
		return true;
	}
	else if (population >= 2 && cell.IsAdjToCellsPopFourOrMore()) {
		population += 1;
		cell.SetPopulation(population);
		workers += 1;	// Assign 1 worker to the job
		cell.SetWorkers(workers);
		workers += population; // Each population produces 1 worker
		return true;
	}
	/*
	else if (population >= 3 && cell.IsAdjToCellsPopSixOrMore()) {
		population += 1;
		cell.SetPopulation(population);
		workers += 1;	// Assign 1 worker to the job
		cell.SetWorkers(workers);
		workers += population; // Each population produces 1 worker
		return true;
	}
	else if (population >= 4 && cell.IsAdjToCellsPopEightOrMore()) {
		population += 1;
		cell.SetPopulation(population);
		workers += 1;	// Assign 1 worker to the job
		cell.SetWorkers(workers);
		workers += population; // Each population produces 1 worker
		return true;
	}
	*/
	return false;
}
