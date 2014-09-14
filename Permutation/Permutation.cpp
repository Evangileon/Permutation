/*
 * Permutation.cpp
 *
 *  Created on: Sep 13, 2014
 *      Author: evangileon
 */

#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <iostream>

#include <sys/time.h>

#include "Permutation.h"

Permutation::Permutation() {
	// TODO Auto-generated constructor stub
	globalCount = 0;
}

Permutation::~Permutation() {
	// TODO Auto-generated destructor stub
}

int Permutation::globalCount = 0;

int Permutation::visit(int A[], const int n, const int k, int verbose,
		int visitCount) {
	if (verbose > 0) {
		for (int i = 1; i <= k; i++) {
			if (A[i] > 0)
				std::cout << A[i] << " ";
		}
		std::cout << std::endl;
	}
	return visitCount + 1;
}

void Permutation::doPermute(int A[], const int n, int i, int count, const int k,
		const int verbose) {
	if (i == (n + 1)) {
		globalCount = visit(A, n, k, verbose, globalCount);
		return;
	}

	if (count == k) {
		globalCount = visit(A, n, k, verbose, globalCount);
		return;
	}

	for (int j = i; j <= n; j++) {
		int tmp = A[j];
		A[j] = A[i];
		A[i] = tmp;
		doPermute(A, n, i + 1, count + 1, k, verbose);
		tmp = A[j];
		A[j] = A[i];
		A[i] = tmp;
	}
}

void Permutation::permute(int A[], const int n, const int k,
		const int verbose) {
	for (int i = 0; i < n + 1; i++) {
		A[i] = i;
	}
	doPermute(A, n, 1, 0, k, verbose);
}

void Permutation::combination(int A[], int i, const int n, const int k,
		const int verbose) {
	if (k == 0) {
		globalCount = visit(A, n, k, verbose, globalCount);
		return;
	}

	if (i < k) {
		return;
	}

	A[i] = i;
	combination(A, i - 1, n, k - 1, verbose);
	A[i] = 0;
	combination(A, i - 1, n, k, verbose);
}

int main(int argc, char **argv) {
	std::string line;
	while (std::getline(std::cin, line)) {
		if (line == "") {
			break;
		}

		std::vector<int> params;
		std::istringstream ticker(line);
		std::copy(std::istream_iterator<int>(ticker),
				std::istream_iterator<int>(), std::back_inserter(params));

		if (params.size() != 3) {
			std::cout << "Invalid input: " << line << std::endl;
			break;
		}

		int n = params[0];
		int k = params[1];
		if (k > n) {
			std::cout << "k no larger than n!" << std::endl;
			break;
		}
		int v = params[2];

		Permutation::newInput();
		int *A = new int[n + 1];

		struct timeval startTime;
		struct timeval endTime;
		unsigned long long t = 0;

		gettimeofday(&startTime, NULL);
		if (v == 0 || v == 2) {
			Permutation::permute(A, n, k, v);
		} else {
			Permutation::combination(A, 1, n, k, v);
		}
		gettimeofday(&endTime, NULL);

		t = (1000 * (endTime.tv_sec - startTime.tv_sec)
				+ (endTime.tv_usec - startTime.tv_usec) / 1000);

		std::cout << Permutation::globalCount << " " << t << std::endl;
	}
}

