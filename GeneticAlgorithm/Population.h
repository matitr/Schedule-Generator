#pragma once
#ifndef POPULATION_H
#define POPULATION_H

#include "InOut.h"
#include <vector>
#include <list>
#include <map>
#include <unordered_map>

#define FAIL 0
#define SUCCESS 1
#define POPULATION 100
#define PERCENTAGE_OF_CROSSOVERS 0.7
#define BEST_CHROMOSOME_SIZE 0.8

class Chromosome;
class MainWindow;
class ThreadsConnection;

class Population{
	bool stopGenerator;

	vector<Chromosome*> chromosomes;
	map<Chromosome*, float> bestChromosomes;
	Chromosome* chromosomePtr;
	int generation;
	int populationSize;
	int bestChromosomesSize;
	int offspringSize;

	float bestFitness;
	Chromosome* bestChromosome;

	
public:
	ThreadsConnection* window;
	void run();
	void initializeRandomPopulation();
	void addToBestChr(Chromosome*);
	bool isInBestChr(int position){
		if (bestChromosomes.find(chromosomes[position]) != bestChromosomes.end()) return true;
		else return false;
	}
	void findBest();
	void setStopGenerator() { stopGenerator = true; }

	//inline Chromosome* bestChromosome() { return bestChromosomes.rbegin()->second; }
	//inline float bestFitness() { return bestChromosomes.rbegin()->first; }
	
	Population(int popSize, float offspringSize);
	Population(int, float, ThreadsConnection*);
	~Population();
	// test
	void printResult();
};


#endif