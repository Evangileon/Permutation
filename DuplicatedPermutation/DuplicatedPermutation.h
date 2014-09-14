/*
 * DuplicatedPermutation.h
 *
 *  Created on: Sep 13, 2014
 *      Author: Jun Yu
 */

#ifndef DUPLICATEDPERMUTATION_H_
#define DUPLICATEDPERMUTATION_H_

class DuplicatedPermutation {
public:
	DuplicatedPermutation();
	virtual ~DuplicatedPermutation();

	static void duplicatedPermutation(int A[], const int n, const int verbose);
	static int globalCount;
	static int visit(int A[], const int n, int verbose, int visitCount);
	static void newInput();
};

#endif /* DUPLICATEDPERMUTATION_H_ */
