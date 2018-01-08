#include "Population.h"
#include "Chromosome.h"
#include "Configuration.h"
#include "CourseClass.h"
#include "Group.h"
#include "InOut.h"
#include "Settings.h"
#include "ClassesTime.h"
#include "MainWindow.h"
#include <time.h>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>

#include <conio.h>


void Population::run() {
	string errorMessage = "";
	if (!Configuration::getConfig().getFromFile(errorMessage)) {
//		IOStream.printText("Blad pliku\n");
		window->printInfo(errorMessage);
		return;
	}

	window->printInfo("Generator has started");
	initializeRandomPopulation();
//	InOut::clearConsole();
//	IOStream.printText("GENERATION: " + to_string(generetion) + "\n");
//	IOStream.printText("BEST FITNESS: " + to_string(bestFitness) + "\n");
	Chromosome* parent0 = nullptr;
	Chromosome* parent1 = nullptr;
	clock_t time = clock();
	while (bestChromosome->errorCounter > -1 && (bestFitness != 1.0) && !window->getStopGenerator(generation, (float(clock() - time) / CLOCKS_PER_SEC))) {
		vector<Chromosome*> offspring;
		offspring.resize(offspringSize);
		int size = offspringSize - 1;

		vector<bool> selectedOffspring;
		selectedOffspring.resize(populationSize);
		int random = 0;
		for (int i = 0; i < offspringSize; i++) {
			int x;
			do {
				random = rand() % populationSize;
			} while (isInBestChr(random) || selectedOffspring[random]);

			offspring[i] = chromosomes[random];
			selectedOffspring[random] = true;
		}

		for (int i = 0; i < size; i += 2) {


			if (rand() % 100 < 25) {
//				offspring[i]->smartMutation();
//				addToBestChr(offspring[i]);
//  				offspring[i + 1]->smartMutation();
				if (rand() % 100 < 50) {
					offspring[i]->copyChromosome(bestChromosome);
					offspring[i]->smartMutation();
					offspring[i]->clearAllExceptClasses();
					offspring[i]->createTimeLine();
					offspring[i]->calculateFitness();
//					addToBestChr(offspring[i]);
				}
				else {
					offspring[i]->smartMutation();
//					addToBestChr(offspring[i]);
				}
			}
			else {
				do
					random = rand() % populationSize;
				while (selectedOffspring[random]);

				parent0 = chromosomes[random];

				do
					random = rand() % populationSize;
				while (selectedOffspring[random]);

				parent1 = chromosomes[random];

				parent0->crossover(parent1, offspring[i], offspring[i + 1]);
			}

//			addToBestChr(offspring[i]);
//			addToBestChr(offspring[i + 1]);
		}

		if (offspringSize % 2) {
			do
				random = rand() % populationSize;
			while (selectedOffspring[random]);

			parent0 = chromosomes[random];

			do
				random = rand() % populationSize;
			while (selectedOffspring[random]);

			parent1 = chromosomes[random];

			offspring[offspring.size() - 1]->setDefaultValues();
			parent0->crossover(parent1, offspring[offspring.size() - 1]);
//			addToBestChr(offspring[offspring.size() - 1]);
		}

		for (int i = 0; i < size + 1; i ++)
			addToBestChr(offspring[i]);

		//		bestChromosome->calculateFitness();
		generation++;
		window->printGeneration(to_string(generation));
		window->printFitness(to_string(bestFitness));
		window->printErrors(to_string(bestChromosome->errorCounter));
	}
	time = clock() - time;
	float finalGenTime = float(time) / CLOCKS_PER_SEC;
	char text[30] = "";
	sprintf_s(text, 30, "%f", finalGenTime);
	string textGenTime(text);
	if (textGenTime.find('.') != string::npos)
		textGenTime.replace(textGenTime.begin() + textGenTime.find('.'), textGenTime.begin() + textGenTime.find('.') + 1, ",");

	window->printInfo("Generator has stopped. Time: " + textGenTime + "s, Fitness: " + to_string(bestFitness));

	bestChromosome->saveResult();
	
	//Configuration::getConfig().~Configuration();
}

void Population::initializeRandomPopulation() {
	int rooms = Configuration::getConfig().numberOfRooms();

	for (int i = 0; i < populationSize; i++) {
		Chromosome * ch = chromosomePtr->randomChromosome();
		chromosomes[i] = ch;
		addToBestChr(ch);
	}
}

//Try to add to best chromosomes group
void Population::addToBestChr(Chromosome* tryToAdd) {

	float fitness = tryToAdd->getFitness();

	if (bestChromosomes.size() == bestChromosomesSize) {
		map < Chromosome*, float>::iterator it = bestChromosomes.begin();
		Chromosome* worstChromosome = it->first;

		for (it; it != bestChromosomes.end(); it++) {
			if (worstChromosome->getFitness() > it->first->getFitness()) {

				worstChromosome = it->first;
			}
		}

		if (fitness > worstChromosome->getFitness()) {
			bestChromosomes.erase(worstChromosome);
			bestChromosomes.insert(pair<Chromosome*, float>(tryToAdd, fitness));

			if (fitness > bestFitness) {
				bestFitness = fitness;
				bestChromosome = tryToAdd;
			}
		}



	}
	else { // vector bestChromosomes is not full
		bestChromosomes.insert(pair<Chromosome*, float>(tryToAdd, fitness));
		if (fitness > bestFitness) {
			bestFitness = fitness;
			bestChromosome = tryToAdd;
		}
	}

}


void Population::findBest() {
	if (bestChromosomes.size() == 0) bestChromosome = nullptr;
	Chromosome* currentBest = bestChromosomes.begin()->first;

}


Population::Population(int _populationSize, float _generationSize){
	populationSize = _populationSize;
	if (populationSize < 2) populationSize = 2;

	offspringSize = populationSize * _generationSize;
	if (offspringSize < 1) offspringSize = 1;

	bestChromosomesSize = (_populationSize - offspringSize) * BEST_CHROMOSOME_SIZE;
	if (bestChromosomesSize == 0) bestChromosomesSize = 1;
	
	if (bestChromosomesSize + offspringSize > populationSize)
		exit(1);

	chromosomes.resize(populationSize);
	//bestChromosomes.resize(bestChromosomesSize);
	generation = 0;
	bestFitness = -9999;
	stopGenerator = false;
	/*
	bestFitness = 0;
	bestChromosome = nullptr;
	*/
	Settings::getSettings().setTimeLineSize(NUMBER_OF_DAYS * HOURS_IN_DAY * SLOTS_IN_HOUR);
	
}

Population::Population(int _populationSize, float _generationSize, ThreadsConnection* pw) {
	populationSize = _populationSize;
	if (populationSize < 2) populationSize = 2;

	offspringSize = populationSize * _generationSize;
	if (offspringSize < 1) offspringSize = 1;

	bestChromosomesSize = (_populationSize - offspringSize) * BEST_CHROMOSOME_SIZE;
	if (bestChromosomesSize == 0) bestChromosomesSize = 1;

	if (bestChromosomesSize + offspringSize > populationSize)
		exit(1);

	chromosomes.resize(populationSize);
	//bestChromosomes.resize(bestChromosomesSize);
	generation = 0;
	bestFitness = -9999;
	stopGenerator = false;
	/*
	bestFitness = 0;
	bestChromosome = nullptr;
	*/
	Settings::getSettings().setTimeLineSize(NUMBER_OF_DAYS * HOURS_IN_DAY * SLOTS_IN_HOUR);
//	IOStream.setWindow(w);
//	window = w;
	window = pw;
}

Population::~Population(){
	for (vector<Chromosome*>::iterator it = chromosomes.begin(); it != chromosomes.end(); it++)
		delete *it;
}











// test

void Chromosome::printChromosome() {
	for (unordered_map<CourseClass*, int>::iterator it = classes.begin(); it != classes.end(); it++) {
		cout <<  it->second << ' ';
	}
}


void Population::printResult() {
	for (vector<Chromosome*>::iterator it = chromosomes.begin(); it != chromosomes.end(); it++) {
		(*it)->printChromosome();
		cout << endl;
	}

}