# Solver for Course-based University Timetabling Problem

This is a multi-start solver for the Course-based University Timetabling Problem.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Prerequisites

* g++ compiler
* These instructions are good for running the solver in a UNIX system and it was only tested in Ubuntu.

## Running the tests

Watch the file named "script.sh". It is the test script used to obtain the results in the paper submitted. 

To compile and run the tests simply execute the script
> ./script.sh

You may need to change the access permission to allow it to execute first:
> chmod +x script.sh

Also you may need create an empty folder named bin
> mkdir -p bin

This test script were made to gather the information about the neighborhoods implemented and store in files.

The information gathered in the tests are the following:

* Seed
* Information about the constructed solution (S = Yes, constructed solution is complete; N = No, constructed solution is not complete)
* Cost of the constructed solution
* Time spent on construction phase
* Cost of final solution
* Time spent on local search phase

## Running an instance separatedly

Go to src directory
> cd src

Create an empty folder named bin
> mkdir -p bin

Compile the code 
> make

run
> ./grasp infilename parameter outfilename solutionfilename > outfilename

* infilename      : name of instance file. *Usually instances/comp\**
* outfilename     : name of output file.
* solutionfilename: name of file which is the solution of solver 
* parameter can be:
	* Algorithm value
		* **0** - GMF-BH (GMF-B without checking Hard Constraints H1 and H3)
		* **1** - GMF-B
		* **2** - GMF-DH (GMF-D without checking Hard Constraints H1 and H3)
		* **3** - GMF-D
	
Example of a run:
> ./grasp instances/comp05.ctt 2 output.csv solution.res > output.csv

## Versioning

This is the version used for the work submitted to the ICCSA 2019 - The 19th International Conference on Computational Science and its Applications 

## Authors

* **Edmar Kampke** -  *CB-CTT reformulation as network flow model*
* **Leonardo Scheideger** - *Implementation of algorithms*
* **Geraldo Mauri** - *Advisor and Reviewer* 
* **Maria Boeres** - *Reviewer*


## Acknowledgments

* Federal University of Espírito Santo - UFES
* Labotim - Optimization Lab
* Fundação de Amparo à Pesquisa e Inovação do Espírito Santo - FAPES
* Conselho Nacional de Desenvolvimento Científico e Tecnológico - CNPq
* ITC-2007 - International Timetabling Competition