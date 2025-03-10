/*
The SimSystem class contains functions to control mutations to the city region. It includes
variables for the region layout, time limit, refresh rate, and the region itself.
*/

#ifndef SIM_SYSTEM_H
#define SIM_SYSTEM_H

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector>
#include "Industrial.h"
#include "Commercial.h"
#include "Residential.h"
#include "Pollution.h"

class SimSystem {
public:
	SimSystem();

	void SetAvailableWorkers(int availableWorkers);
	void AddAvailableWorkers(int availableWorkers);
	void RemoveAvailableWorkers(int availableWorkers);
	int GetAvailableWorkers();

	void SetAvailableGoods(int availableGoods);
	void AddAvailableGoods(int availableGoods);
	void RemoveAvailableGoods(int availableGoods);
	int GetAvailableGoods();

	void ReadConfigFile();
	void InitializeRegion();
	void AssignAdjacencies(vector<vector<Cell>>& region);
	void PrintRegion();
	void PrintRegionInfo();
	void CommenceTimeSteps();

	int availableWorkers;
	int availableGoods;
	int totalPollution;

private:
	string regionLayout;
	int timeLimit;
	int refreshRate;
	vector<vector<Cell>> region;
};

#endif
