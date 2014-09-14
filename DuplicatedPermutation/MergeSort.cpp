/*
 * MergeSort.c
 *
 *  Created on: Aug 28, 2014
 *      Author: Jun Yu
 */

//#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <sys/time.h>

static void TraditionalMergeSort(int A[], int p, int r);
static void TraditionalMerge(int A[], int p, int q, int r);
static void AuxiliaryMergeSort(int A[], int B[], int p, int r);
static void AuxiliaryMerge(int A[], int B[], int p, int q, int r);
static int doAlternateAuxiliaryMergeSort(int A[], int B[], int p, int r);
static void AlternateAuxiliaryMerge(int src[], int dest[], int p, int q, int r);

static void TraditionalMergeSort(int A[], int p, int r) {
	if (p >= r) {
		return;
	}

	int q = (p + r) / 2;
	TraditionalMergeSort(A, p, q);
	TraditionalMergeSort(A, q + 1, r);
	TraditionalMerge(A, p, q, r);
}

static void TraditionalMerge(int A[], int p, int q, int r) {
	int ls = q - p + 1;
	int rs = r - q;
	int *L = (int *) malloc(ls * sizeof(int));
	int *R = (int *) malloc(rs * sizeof(int));

	int i = 0;
	int j = 0;
	int k = 0;

	for (i = p; i <= q; i++)
		L[i - p] = A[i];
	for (i = q + 1; i <= r; i++)
		R[i - (q + 1)] = A[i];

	for (k = p, i = 0, j = 0; k <= r; k++) {
		if ((j >= rs) || ((i < ls) && (L[i] <= R[j])))
			A[k] = L[i++];
		else
			A[k] = R[j++];
	}
	free(L);
	free(R);
	return;
}

static void AuxiliaryMergeSort(int A[], int B[], int p, int r) {
	if (p >= r) {
		return;
	}

	int q = (p + r) / 2;
	AuxiliaryMergeSort(A, B, p, q);
	AuxiliaryMergeSort(A, B, q + 1, r);
	AuxiliaryMerge(A, B, p, q, r);
}

static void AuxiliaryMerge(int A[], int B[], int p, int q, int r) {
	int i = 0;
	int j = 0;
	int k = 0;

	for (i = p; i <= r; i++) {
		B[i] = A[i];
	}

	for (k = p, i = 0, j = 0; k <= r; k++) {
		if ((j > q) || ((i <= q) && (B[i] <= B[j])))
			A[k] = B[i++];
		else
			A[k] = B[j++];
	}
	return;
}

static int doAlternateAuxiliaryMergeSort(int A[], int B[], int p, int r) {
	int k = 0;

	if (p >= r) {
		return 0;
	}

	int q = (p + r) / 2;
	int h1 = doAlternateAuxiliaryMergeSort(A, B, p, q);
	int h2 = doAlternateAuxiliaryMergeSort(A, B, q + 1, r);

	int h = (h1 > h2) ? h1 : h2;

	if ((h & 1) == 0) {
		// even
		if (h1 > h2) {
			// copy B[q + 1 : r] to A
			for (k = q + 1; k <= r; k++) {
				A[k] = B[k];
			}
		}
		AlternateAuxiliaryMerge(A, B, p, q, r);
	} else {
		// odd
		if (h1 > h2) {
			// copy A[q + 1 : r] to B
			for (k = q + 1; k <= r; k++) {
				B[k] = A[k];
			}
		}
		AlternateAuxiliaryMerge(B, A, p, q, r);
	}

	return h + 1;
}

static void AlternateAuxiliaryMerge(int src[], int dest[], int p, int q,
		int r) {

	int i = 0;
	int j = 0;
	int k = 0;
	for (k = p, i = p, j = q + 1; k <= r; k++) {
		if ((j > r) || ((i <= q) && (src[i] <= src[j])))
			dest[k] = src[i++];
		else
			dest[k] = src[j++];
	}
	return;
}

void usage() {
	std::cout << "./MergeSort n\n";
}

static void printArray(int arr[], int n) {
	int k = 0;
	for (k = 0; k < n; ++k) {
		std::cout << arr[k];
	}
}

#define PRINT_ARRAY(arr, len) \
	do { \
		std::cout << #arr << " = { "; \
		printArray(arr, len); \
		std::cout << "}\n"; \
	} while(0)

void AlternateAuxiliaryMergeSort(int **A_ptr, int n) {
	if (n < 0 || A_ptr == NULL) {
		return;
	}
	int *A = *A_ptr;
	int *B = new int[n];
	int h = doAlternateAuxiliaryMergeSort(A, B, 0, n - 1);
	if ((h & 1) != 0) { // odd
		int* swap = *A_ptr;
		*A_ptr = B;
		B = swap;
	}
	delete [] B;
	if(n < 0) {
		printArray(*A_ptr, n);
	}
}
