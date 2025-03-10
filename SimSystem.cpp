/*
The SimSystem class will manage the initialization of the city region, mutations onto the region per
time step (called with members of Residential, Industrial, Commerical, and Pollution classes), and
the printing of the region per refresh rate.

***MESSAGE TO PROGRAMMERS*** if config1.txt can't be found, try running this code in the CELL machine! make sure
that config1.txt and region1.csv are in the same directory.
*/

#include "SimSystem.h"

SimSystem::SimSystem() {
	regionLayout = "";
	timeLimit = 0;
	refreshRate = 0;
	totalPollution = 0;
	availableWorkers = 0;
	availableGoods = 0;
}

//Accessor and mutators for available workers of the entire region:

void SimSystem::SetAvailableWorkers(int availableWorkers) {
	this->availableWorkers = availableWorkers;
}

void SimSystem::AddAvailableWorkers(int availableWorkers) {
	this->availableWorkers += availableWorkers;
}

void SimSystem::RemoveAvailableWorkers(int availableWorkers) {
	this->availableWorkers -= availableWorkers;
}

int SimSystem::GetAvailableWorkers() {
	return availableWorkers;
}

//Accessor and mutators for available goods of the entire region:

void SimSystem::SetAvailableGoods(int availableGoods) {
	this->availableGoods = availableGoods;
}

void SimSystem::AddAvailableGoods(int availableGoods) {
	this->availableGoods += availableGoods;
}

void SimSystem::RemoveAvailableGoods(int availableGoods) {
	this->availableGoods -= availableGoods;
}

int SimSystem::GetAvailableGoods() {
	return availableGoods;
}

/*
This method prompts for and opens the file containing the simulation configuration. It stores each
configuration line into a string which is sliced to exclude the label and is assigned to its
respective private data object, converting the string into an integer if necessary.
*/
void SimSystem::ReadConfigFile() {
	ifstream configFile;
	string configFileName;
	cout << "Enter the simulation configuration file name: ";
	cin >> configFileName;
	configFile.open(configFileName);

	while (!configFile.is_open()) {
		cout << "This file is unable to be located. " << endl
			<< "Ensure that it's located in the same directory as the program files and try again: ";
		cin >> configFileName;
		configFile.open(configFileName);
	}

	string input;
	getline(configFile, input);
	regionLayout = input.substr(input.find(':') + 1);
	getline(configFile, input);
	timeLimit = stoi(input.substr(input.find(':') + 1));
	getline(configFile, input);
	refreshRate = stoi(input.substr(input.find(':') + 1));

	configFile.close();
}

/*
	This method opens the region layout file as specified in the configuration file. It then iterates
through each line of the file, appending each Cell of the row into a Cell vector, then it
appends the row vector into a vector of Cell vectors.
	After the region is initialized using the file, an iteration through each vector occurs again to
assign each individual Cell with each of its surrounding adjacent Cell pointers. Parameters are set within
if-statements to ensure that out-of-bounds elements aren't mutated; they would just remain as NULL.
*/
void SimSystem::InitializeRegion() {
	cout << regionLayout<< endl;
	if (regionLayout != "") {
		ifstream layoutFile;
		//path to enter for config file (on Marcus' laptop): C:\Users\weber\Downloads\config1.txt
		//FIXME: delete string "DELEGEregionLayout" and change parameter of layoutFile to regionLayout --- this is just so it works on VS
		//string DELETEregionLayout = "C:/Users/weber/Downloads/" + regionLayout;
		//layoutFile.open(DELETEregionLayout);
		layoutFile.open(regionLayout);

		string line;
		char cellSymbol;
		while (getline(layoutFile, line)) {
			vector<Cell> row;
			for (unsigned int i = 0; i < line.size(); i++) {
				Cell newCell;
				cellSymbol = line.at(i);
				if (cellSymbol != ',') {
					if (cellSymbol == ' ') {
						newCell.SetType(Cell::empty);
					}
					else if (cellSymbol == 'R') {
						newCell.SetType(Cell::residential);
					}
					else if (cellSymbol == 'I') {
						newCell.SetType(Cell::industrial);
					}
					else if (cellSymbol == 'C') {
						newCell.SetType(Cell::commercial);
					}
					else if (cellSymbol == '-') {
						newCell.SetType(Cell::road);
					}
					else if (cellSymbol == 'T') {
						newCell.SetType(Cell::powerline);
					}
					else if (cellSymbol == '#') {
						newCell.SetType(Cell::powerlineOverRoad);
					}
					else if (cellSymbol == 'P') {
						newCell.SetType(Cell::powerPlant);
					}
					row.push_back(newCell);
				}
			}
			region.push_back(row);
			row.clear();
		}
		layoutFile.close();

		AssignAdjacencies(region);
	}
}

void SimSystem::AssignAdjacencies(vector<vector<Cell>>& regionToAssign) {
	Cell* topLeft = nullptr;
	Cell* top = nullptr;
	Cell* topRight = nullptr;
	Cell* left = nullptr;
	Cell* right = nullptr;
	Cell* botLeft = nullptr;
	Cell* bot = nullptr;
	Cell* botRight = nullptr;
	for (unsigned int i = 0; i < regionToAssign.size(); i++) {
		for (unsigned int j = 0; j < regionToAssign.at(i).size(); j++) {
			if (i > 0 && j > 0) {
				topLeft = &regionToAssign.at(i - 1).at(j - 1);
				regionToAssign.at(i).at(j).SetTopLeftAdj(topLeft);
			}
			if (i > 0) {
				top = &regionToAssign.at(i - 1).at(j);
				regionToAssign.at(i).at(j).SetTopAdj(top);
			}
			if (i > 0 && j < regionToAssign.at(i).size() - 1) {
				topRight = &regionToAssign.at(i - 1).at(j + 1);
				regionToAssign.at(i).at(j).SetTopRightAdj(topRight);
			}
			if (j > 0) {
				left = &regionToAssign.at(i).at(j - 1);
				regionToAssign.at(i).at(j).SetLeftAdj(left);
			}
			if (j < regionToAssign.at(i).size() - 1) {
				right = &regionToAssign.at(i).at(j + 1);
				regionToAssign.at(i).at(j).SetRightAdj(right);
			}
			if (i < regionToAssign.size() - 1 && j > 0) {
				botLeft = &regionToAssign.at(i + 1).at(j - 1);
				regionToAssign.at(i).at(j).SetBotLeftAdj(botLeft);
			}
			if (i < regionToAssign.size() - 1) {
				bot = &regionToAssign.at(i + 1).at(j);
				regionToAssign.at(i).at(j).SetBotAdj(bot);
			}
			if (i < regionToAssign.size() - 1 && j < regionToAssign.at(i).size() - 1) {
				botRight = &regionToAssign.at(i + 1).at(j + 1);
				regionToAssign.at(i).at(j).SetBotRightAdj(botRight);
			}
		}
	}
}

/*
This method prints the region grid (a 2D vector object) by iterating through the columns per
iteration of the rows and outputting a dereference of the column object.
*/
void SimSystem::PrintRegion() {
	vector<vector<Cell>>::iterator itRow;
	vector<Cell>::iterator itCol;
	for (itRow = region.begin(); itRow != region.end(); itRow++) {
		for (itCol = itRow->begin(); itCol != itRow->end(); itCol++) {
			if (itCol->GetPopulation() >= 10) {
				cout << itCol->GetPopulation() << " ";
			}
			else if (itCol->GetPopulation() > 0) {
				cout << itCol->GetPopulation() << "  ";
			}
			else {
				cout << itCol->GetSymbol() << "  ";
			}
		}
		cout << endl;
	}
}

/*
This method iterates through the region 2D vector to access each Cell's numbers of available
workers and available goods to display per time step.
*/
void SimSystem::PrintRegionInfo() {
	cout << "Available workers: " << availableWorkers << endl;
	cout << "Available goods: " << availableGoods << endl;
	cout << "Total pollution level: " << totalPollution << endl;
}

/*
In development: time step method to update each cell according to adjacency rules, using methods from the other classes
*/
void SimSystem::CommenceTimeSteps() {
	int timeCounter = 0;
	int refreshCounter = 0;
	Industrial industry;
	Commercial commerce;
	Residential residence;
	PollutionLevels pollution;

	vector<vector<Cell>> regionCopy;
	vector<vector<Cell>> regionAtStartOfStep; //previous time step
	bool breakOutOfLoops = false;

	while (timeCounter < timeLimit) {
		regionAtStartOfStep = region;
		AssignAdjacencies(regionAtStartOfStep);

		for (unsigned int i = 0; i < region.size(); i++) {
			for (unsigned int j = 0; j < region.at(i).size(); j++) {

				regionCopy = regionAtStartOfStep;
				AssignAdjacencies(regionCopy);

				if (availableWorkers >= 1 && availableGoods >= 1) {
					if ((region.at(i).at(j)).GetType() == Cell::commercial) {
						commerce.SetValues((regionCopy.at(i).at(j)).GetPopulation(),
							(regionCopy.at(i).at(j)).GetWorkers(),
							(regionCopy.at(i).at(j)).GetGoods());
						if (commerce.UpdateCommercial((regionCopy.at(i).at(j)), availableWorkers, availableGoods)) {
							(region.at(i).at(j)).SetPopulation(commerce.GetPopulation());
							(region.at(i).at(j)).SetWorkers(commerce.GetWorkers());
							(region.at(i).at(j)).SetGoods(commerce.GetGoods());
							availableWorkers -= 1;
							availableGoods -= 1;
							regionCopy = regionAtStartOfStep;
							breakOutOfLoops = true;
							break;
						}
						commerce.ResetValues();
					}
				}
				else if (availableWorkers >= 2) {
					if ((region.at(i).at(j)).GetType() == Cell::industrial) {
						industry.SetValues((regionCopy.at(i).at(j)).GetPopulation(),
							(regionCopy.at(i).at(j)).GetWorkers(),
							(regionCopy.at(i).at(j)).GetGoods());
						if (industry.UpdateIndustrial((regionCopy.at(i).at(j)), availableWorkers)) {
							(region.at(i).at(j)).SetPopulation(industry.GetPopulation());
							(region.at(i).at(j)).SetWorkers(industry.GetWorkers());
							(region.at(i).at(j)).SetGoods(industry.GetGoods());
							availableWorkers -= 2;
							availableGoods += 1;
							regionCopy = regionAtStartOfStep;
							breakOutOfLoops = true;
							break;
						}
						industry.ResetValues();
					}
				}
				else if ((region.at(i).at(j)).GetType() == Cell::residential) {
					residence.SetValues((regionCopy.at(i).at(j)).GetPopulation(), (regionCopy.at(i).at(j)).GetWorkers());
					if (residence.UpdateResidential(regionCopy.at(i).at(j))) {
						(region.at(i).at(j)).SetPopulation(residence.GetPopulation());
						(region.at(i).at(j)).SetWorkers(residence.GetWorkers());
						availableWorkers += 1;
						regionCopy = regionAtStartOfStep;
						breakOutOfLoops = true;
						break;
					}
					residence.ResetValues();
				}

				// C:\Users\weber\Downloads\config1.txt

				//FIXME: Pollution Updates
				//totalPollution += 1;
			}
			if (breakOutOfLoops) {
				breakOutOfLoops = false;
				break;
			}
		}
		timeCounter += 1;
		refreshCounter += 1;

		if (refreshCounter == refreshRate) {
			cin.get();
			cout << "Time Step #" << timeCounter << ':' << endl;
			PrintRegion();
			PrintRegionInfo();
			cout << "Press [enter] to continue." << endl;

			refreshCounter = 0;
		}
	}
	cin.get();
}
