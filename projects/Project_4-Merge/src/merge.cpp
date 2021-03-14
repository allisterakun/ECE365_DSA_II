#include <iostream>
#include <fstream>
#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <errno.h>

using namespace std;

bool dp[1001][1001];

int main(){
	string infilename, outfilename, A, B, C;
	ifstream inFile;
	ofstream outFile;
	cout << "Enter name of input file: ";
	cin >> infilename;
	cout << "Enter name of output file: ";
	cin >> outfilename;
	inFile.open(infilename.c_str());
	outFile.open(outfilename.c_str());

    if(!inFile.is_open() || !outFile.is_open()){
        if(!inFile.is_open() && !outFile.is_open()){
            fprintf(stderr, "ERROR: cannot open files: %s and %s, %s\n", infilename.c_str(), outfilename.c_str(), strerror(errno));
        }
        else if(!inFile.is_open()){
            fprintf(stderr, "ERROR: cannot open input file: %s, %s\n", infilename.c_str(), strerror(errno));
        }
        else if(!outFile.is_open()){
            fprintf(stderr, "ERROR: cannot open output file: %s, %s\n", outfilename.c_str(), strerror(errno));
        }
        inFile.close(); outFile.close();
        return -1;
    }
	else if (inFile.is_open() && outFile.is_open()) {
		while (inFile >> A && inFile >> B && inFile >> C) {

            // not a merge if the length doesn't match
            // also not a merge if the last letter doesn't match
			if ((A.length() + B.length()) != C.length() || (C[C.length()-1]!=A[A.length()-1] && C[C.length()-1]!=B[B.length()-1])) {
				outFile << "*** NOT A MERGE ***" << endl;
				continue;
			}

			// dp
			for (int i = 0; i < B.length()+1; i++) {
				for (int j = 0; j < A.length()+1; j++) {
					if (i == 0 && j > 0) {
						if (C[j-1] == A[j-1]) {
                            if(j == 1){
                                dp[i][j] = true;
                                continue;
                            }
                            else{
                                dp[i][j] = dp[i][j-1];
                                continue;
                            }
						}
					}
					else if (j == 0 && i > 0) {
						if (C[i-1] == B[i-1]) {
                            if(i == 1){
                                dp[i][j] = true;
                                continue;
                            }
                            else{
                                dp[i][j] = dp[i-1][j];
                                continue;
                            }
						}
					}
					    dp[i][j] = false;
				}
			}

			for (int i = 1; i < B.length()+1; i++) {
				for (int j = 1; j < A.length()+1; j++) {

					dp[i][j] = false;
					if (dp[i-1][j] || dp[i][j-1]) {
						if (B[i-1] == A[j-1] && C[i+j-1] == A[j-1]) {
							dp[i][j] = true;
						}
					    else if (dp[i-1][j]) {
							if (C[i+j-1] == B[i-1]) {
								dp[i][j] = true;
							}
						}
						else if (dp[i][j-1]) {
							if (C[i+j-1] == A[j-1]) {
								dp[i][j] = true;
							}
						}
					}
				}
			}

			// output
			if (dp[B.length()][A.length()]==1) {
				int m = B.length ();
				int n = A.length ();

				while (n > 0 && m >= 0) {
					if (dp[m][n] && (m == 0 || !dp[m-1][n])) {
						C[m+n-1] = toupper (C[m+n-1]);
						n--;
					}
					else
						m--;
				}
				outFile << C << endl;
			}
			else{
				outFile << "*** NOT A MERGE ***" << endl;
            }
		}
		
	}
	inFile.close();
	outFile.close();
	return 0;
}
