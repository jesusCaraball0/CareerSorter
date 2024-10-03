#include<iostream>
#include<map>
#include<unordered_map>
#include<vector>
#include<string>

using namespace std;

// struct for keeping job title and salary together
struct Job {
	string jobTitle;
	int salary;
};

// struct with sorted vectors in both ascending and descending order
struct sortedSalaries {
	vector<Job> ascending;
	vector<Job> descending;
};

sortedSalaries sortJobSalaries(map<string, int>& jobSalaries);

void mergeSort(vector<int>& salaries, int begin, int end);
void merge(vector<int>& salaries, int low, int mid, int high);

void quickSort(vector<int>& salaries, int begin, int end);
int particionFunction(vector<int>& salaries, int low, int high);


// takes in map of jobs and salaries and returns a struct of sorted salaries, one in ascending
// using merge sort and one in descending using quick sort
sortedSalaries sortJobSalaries(map<string, int>& jobSalaries) {

	vector<int> salariesAscending;
	vector<int> salariesDescending;
	map<int, string> salaryToJobTitle;

	for (auto it = jobSalaries.begin(); it != jobSalaries.end(); it++) {
		salariesAscending.push_back(it->second);
		salariesDescending.push_back(it->second);
		salaryToJobTitle[it->second] = it->first;
	}

	mergeSort(salariesAscending, 0, int(salariesAscending.size() - 1));
	quickSort(salariesDescending, 0, int(salariesDescending.size() - 1));

	sortedSalaries sortedSalaries;

	for (int i = 0; i < salariesAscending.size(); i++) {
		
		Job topJob = { salaryToJobTitle[salariesAscending[i]], salariesAscending[i] };

		Job lastJob = { salaryToJobTitle[salariesDescending[i]], salariesDescending[i] };

		sortedSalaries.ascending.push_back(topJob);
		sortedSalaries.descending.push_back(lastJob);		
	}

	return sortedSalaries;
}


// functions to sort in ascending order via merge sort
void merge(vector<int>& salaries, int low, int mid, int high) {
	// initiate indices and create temporary vectors for merging
	int toBeMergedOne = mid - low + 1;
	int toBeMergedTwo = high - mid;
	vector<int> subVectorOne;
	vector<int> subVectorTwo;

	// copy data from salaries to temporary vectors
	for (int i = 0; i < toBeMergedOne; i++) {
		subVectorOne.push_back(salaries[low + i]);
	}
	for (int i = 0; i < toBeMergedTwo; i++) {
		subVectorTwo.push_back(salaries[mid + 1 + i]);
	}

	int indexSubVectorOne = 0, indexSubVectorTwo = 0;
	int indexMergedVector = low;

	// merge temporaries back into main vector
	while (indexSubVectorOne < toBeMergedOne && indexSubVectorTwo < toBeMergedTwo) {
		if (subVectorOne[indexSubVectorOne] <= subVectorTwo[indexSubVectorTwo]) {
			salaries[indexMergedVector] = subVectorOne[indexSubVectorOne];
			indexSubVectorOne++;
		}
		else {
			salaries[indexMergedVector] = subVectorTwo[indexSubVectorTwo];
			indexSubVectorTwo++;
		}
		indexMergedVector++;
	}

	// copy leftover elements from subVectorOne
	while (indexSubVectorOne < toBeMergedOne) {
		salaries[indexMergedVector] = subVectorOne[indexSubVectorOne];
		indexSubVectorOne++;
		indexMergedVector++;
	}

	// copy leftover elements from subVectorTwo
	while (indexSubVectorTwo < toBeMergedTwo) {
		salaries[indexMergedVector] = subVectorTwo[indexSubVectorTwo];
		indexSubVectorTwo++;
		indexMergedVector++;
	}

	subVectorOne.clear();
	subVectorTwo.clear();

}
void mergeSort(vector<int>& salaries, int begin, int end) {
	if (begin >= end) {
		return;
	}

	// recursively call merge sort by splitting salaries in half
	int middle = begin + (end - begin) / 2;
	mergeSort(salaries, begin, middle);
	mergeSort(salaries, middle + 1, end);
	merge(salaries, begin, middle, end);
}

// function to sort in descending order via quick sort
void quickSort(vector<int>& salaries, int begin, int end) {
	if (begin < end) {
		int particion = particionFunction(salaries, begin, end); // do the initial particion to apply quicksort recursively

		// recursively sort elements before and after particion
		quickSort(salaries, begin, particion - 1);
		quickSort(salaries, particion + 1, end);
	}
	return;
}
int particionFunction(vector<int>& salaries, int low, int high) {
	int pivot = salaries[high]; // last element is pivot
	int greater = low - 1; // index for greater element

	for (int j = low; j < high; j++) {
		// if current element is greater than or equal to pivot

		if (salaries[j] >= pivot) {
			greater++; // increment greater

			// swap current element with pivot if it's greater
			int temp = salaries[greater];
			salaries[greater] = salaries[j];
			salaries[j] = temp;
		}
	}

	// swap last element with greater
	int temp = salaries[greater + 1];
	salaries[greater + 1] = salaries[high];
	salaries[high] = temp;

	return (greater + 1);
}
