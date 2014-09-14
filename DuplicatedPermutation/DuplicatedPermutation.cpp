/*
 * DuplicatedPermutation.cpp
 *
 *  Created on: Sep 13, 2014
 *      Author: evangileon
 */

#include <climits>

#include "DuplicatedPermutation.h"
#include "MergeSort.h"

DuplicatedPermutation::DuplicatedPermutation() {
	// TODO Auto-generated constructor stub

}

DuplicatedPermutation::~DuplicatedPermutation() {
	// TODO Auto-generated destructor stub
}

int DuplicatedPermutation::globalCount = 0;

int DuplicatedPermutation::visit(int A[], const int n, int verbose,
		int visitCount) {
	if (verbose > 0) {
		for (int i = 1; i <= n; i++) {
			if (A[i] > 0)
				std::cout << A[i] << " ";
		}
		std::cout << std::endl;
	}
	return visitCount + 1;
}

/**
 * size of A must be n + 1, because of the sentiment element
 */
void DuplicatedPermutation::duplicatedPermutation(int raw_A[], const int n,
		const int verbose) {
	if (n <= 0 || raw_A == NULL) {
		return;
	}
	int *A = new int[n + 1];
	A[0] = INT_MIN;
	for (int i = 0; i < n; ++i) {
		A[i + 1] = raw_A[i];
	}

	AlternateAuxiliaryMergeSort(&A, n + 1);

	while (true) {
		int j = n - 1;
		for (j = n - 1; j >= 0; j--) {
			if (A[j] < A[j + 1]) {
				break;
			}
		}
		if (j == 0) {
			break; // end combination iteration
		}

		int l = n;
		for (l = n; l > j; l--) {
			if (A[j] < A[l]) {
				break;
			}
		}
		std::swap(A[j], A[l]);

		// reverse A[j + 1] : A[n]
		int half = (j + 1 + n) / 2;
		for (int i = j + 1; i <= half; ++i) {
			std::swap(A[i], A[i + half]);
		}

		visit(A, n, verbose, globalCount);
	}
	delete[] A;
}

void DuplicatedPermutation::newInput() {
	globalCount = 0;
}

int main(int argc, char **argv) {
	std::string line;
	int count = 0;
	std::vector<int> firstLineParams;
	std::vector<int> secondLineParams;

	while (std::getline(std::cin, line)) {
		if (line == "") {
			break;
		}

		count++;

		if (count == 1) {
			firstLineParams.clear();
			std::istringstream ticker(line);
			std::copy(std::istream_iterator<int>(ticker),
					std::istream_iterator<int>(),
					std::back_inserter(firstLineParams));
			if (firstLineParams.size() != 2) {
				std::cout << "Invalid input: " << line << std::endl;
				break;
			}

		} else if (count == 2) {
			int n = firstLineParams[0];
			int v = firstLineParams[1];

			DuplicatedPermutation::newInput();
			int *raw_A = new int[n];
			secondLineParams.clear();
			std::istringstream ticker(line);
			std::copy(std::istream_iterator<int>(ticker),
					std::istream_iterator<int>(),
					std::back_inserter(secondLineParams));
			for (int i = 0; i < secondLineParams.size(); ++i) {
				raw_A[i] = secondLineParams[i];
			}

			struct timeval startTime;
			struct timeval endTime;
			unsigned long long t = 0;

			gettimeofday(&startTime, NULL);
			DuplicatedPermutation::duplicatedPermutation(raw_A, n, v);
			gettimeofday(&endTime, NULL);

			t = (1000 * (endTime.tv_sec - startTime.tv_sec)
					+ (endTime.tv_usec - startTime.tv_usec) / 1000);

			std::cout << DuplicatedPermutation::globalCount << " " << t
					<< std::endl;

			delete[] raw_A;
			count = 0;
			firstLineParams.clear();
			secondLineParams.clear();
		}
	}
}

