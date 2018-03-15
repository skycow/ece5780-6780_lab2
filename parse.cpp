#include <fstream>
#include <iostream>
#include <string>
#include <vector>

	struct TASK {
		std::string name;
		int comp;
		int per;
        bool released = true;
        int runtime = 0; //At the start =0
        int currDeadline; //At the start =period
        int NUMmissedDeadlines = 0; //At the start =0
        bool preemted = false;
	};

std::vector<TASK> priSort(std::vector<TASK> tosort);
std::vector<TASK> priSort2(std::vector<TASK> tosort);

int main(int argc, char** argv) {

	if (argc != 3) {
		std::cout << "Incorrect number of paramaters.\n";
		std::cout << "Usage: ./a.out <inputFile> <outputFile>\n";
		return -1;
	}

	std::ifstream infile(argv[1]);
	std::string line;
	int  numTasks, simTime;
	std::string store[3];


	std::vector<TASK> tasks;
	if (infile.is_open()) {

		std::getline(infile, line);
        numTasks = std::stoi(line);
		std::getline(infile, line);
        simTime = std::stoi(line);
		TASK newTask;
		while (std::getline(infile, line)) {
			size_t pos = 0;
			pos = line.find(", ");
			newTask.name = line.substr(0, pos);
			line.erase(0, pos + 2);
			pos = line.find(", ");
			newTask.comp = std::stoi(line.  substr(0, pos));
			line.erase(0, pos + 2);
			newTask.per = std::stoi(line);
            newTask.currDeadline = newTask.per;
			tasks.push_back(newTask);
		}
		


		infile.close();
	}
	else {
		std::cout << "Unable to open file.";
	}



    for(auto tsk : tasks){
        std::cout << tsk.name << " ";
        std::cout << tsk.comp << " ";
        std::cout << tsk.per << std::endl << std::endl;
    }

    std::cout << "-------" << std::endl;

    for(auto tsk2 : priSort(tasks)){
        std::cout << tsk2.name << " ";
        std::cout << tsk2.comp << " ";
        std::cout << tsk2.NUMmissedDeadlines << " ";
        std::cout << tsk2.per << std::endl << std::endl;
    }

    std::cout << simTime << std::endl;

    /// Read in file ///


    std::vector<TASK> priority = priSort2(tasks);
    int numPreemptions = 0;


    std::cout << "-------" << std::endl;

    for(auto tsk3 : priority){
        std::cout << tsk3.name << " ";
        std::cout << tsk3.comp << " ";
        std::cout << tsk3.NUMmissedDeadlines << " ";
        std::cout << tsk3.per << std::endl << std::endl;
    }

for (int i = 0; i < simTime; i++) //should i increment before or after?
{
	for (int t = 0; t < tasks.size(); t++)
	{
		if (priority[t].released)
		{
            std::cout << i << " : " << priority[t].name << " is running\n";
			priority[t].preemted = false; //task is currently running
			for (int t1 = 0; t1 < tasks.size(); t1++) //checking if a task was preemptively halted
			{
				if (t1 != t)
				{
					if (priority[t1].runtime != 0 && !priority[t1].preemted)
					{
						priority[t1].preemted = true;
						numPreemptions++;
                        std::cout << i << " : " << priority[t1].name << " is being preempted.\n";
					}
				}
			}
			priority[t].runtime += 1;
			if (priority[t].runtime == priority[t].comp)
			{
                std::cout << i << " : " << priority[t].name << " has completed execution.\n";
				if (priority[t].currDeadline != i + 1)
				{
					priority[t].released = false;
					priority[t].runtime = 0;
				}
				else
				{
					priority[t].currDeadline += priority[t].per;
                    priority[t].runtime = 0;
				}
			}
						if (priority[t].currDeadline == i)
			{
				priority[t].NUMmissedDeadlines += 1;
			}
			for (int k = 0; k < tasks.size(); k++)
			{
				if (priority[k].currDeadline == i)
				{
					if (priority[k].released)
					{
						priority[k].NUMmissedDeadlines += 1;
						priority[k].currDeadline += priority[k].per;
					}else{
                        priority[k].released = true;
                        std::cout << i << " : " << priority[k].name << " was released.\n";
                    }
				}
				else if (priority[k].currDeadline == i + 1)
				{
					priority[k].released = true;
                    std::cout << i << " : " << priority[k].name << " was released.\n";
				}
			}
			break;
		}
	}
    for (int k = 0; k < tasks.size(); k++)
	{
		if (priority[k].currDeadline == i +1)
		{
			priority[k].released = true;
               std::cout << i << " : " << priority[k].name << " was released.\n";
		}
	}
}

int missedDeadlines = 0;

for (auto i : tasks){
    
	missedDeadlines += i.NUMmissedDeadlines;
}

std::cout << "Missed Deadlines: " << missedDeadlines << std::endl;
std::cout << "Preemptions: " << numPreemptions << std::endl;

    //done and exit ///
	return 0;
}

std::vector<TASK> priSort(std::vector<TASK> tosort){
    TASK temp;
    bool changed = true;

    while(changed) {
        changed = false;
        for(int i = 0; i < tosort.size()-1; i++){
            if(tosort[i].per > tosort[i+1].per){
                temp = tosort[i];
                tosort[i] = tosort[i+1];
                tosort[i+1] = temp;
                changed = true;
            }
        }
    }
    return tosort;
}

std::vector<TASK> priSort2(std::vector<TASK> tosort){
    TASK temp;
    bool changed = true;

    while(changed) {
        changed = false;
        for(int i = 0; i < tosort.size()-1; i++){
            if(tosort[i].currDeadline > tosort[i+1].currDeadline){
                temp = tosort[i];
                tosort[i] = tosort[i+1];
                tosort[i+1] = temp;
                changed = true;
            }
        }
    }
    return tosort;
}