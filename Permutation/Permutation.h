/*
 * Permutation.h
 *
 *  Created on: Sep 13, 2014
 *      Author: evangileon
 */

#ifndef PERMUTATION_H_
#define PERMUTATION_H_

class Permutation {
public:
	Permutation();
	virtual ~Permutation();

private:
	static int visit(int A[], const int n, const int k, int verbose,
			int visitCount);
	static void doPermute(int A[], const int n, int i, int count, const int k,
			const int verbose);
public:
	static int globalCount;
	static void permute(int A[], const int n, const int k, const int verbose);
	static void newInput() { globalCount = 0; }
	static void combination(int A[], int i, const int n, const int k, const int verbose);
};

#endif /* PERMUTATION_H_ */
