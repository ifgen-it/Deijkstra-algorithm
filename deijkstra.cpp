#include <iostream>
#include <cstdio>

using namespace std;

// count of nodes
const int Nodes = 7;

// equal endless (infinity)
const int E = 88;

// Start and Terminate nodes
 int S = 1;
 int T = 7;

// Current node
int C = 0;
// Current distance
int DistC = 0;

void PrintArr(int Arr[][Nodes], int Nodes);
void PrintPath(int Path[], int Nodes);
int MinTempDist(int Path[], int Perm[], int Nodes);


int main(){
	
	printf("DEIJKSTRA algorithm\nSearching the shortest path in oriented graph\n"
	       "------------------------------------\n");
	// Weight matrix
	// 0 means the same node
	int W[Nodes][Nodes] = {
		                   0, 7, 19, 20, E, 15, E,
	                       E, 0, E, 11, 6, E, E,
	                       E, E, 0, 6, 9, E, 16,
	                       E, E, E, 0, 8, 8, 13,
	                       E, E, E, E, 0, 5, 15,
	                       E, E, E, E, E, 0, 14,
	                       E, E, E, E, E, E, 0 
	                       };
	                       
	
	//       1   2   3   4   5   6   7
	// ------------------------------------
	// x1:  -   7  19 20 % 15  %
	// x2: %   -   %  11  6  %   %
	// x3: %  %   -    6   9  %  16
	// x4: %  %  %   -    8   8  13
	// x5: %  %  %  %   -    5  15
	// x6: %  %  %  %  %    -   14
	// x7: %  %  %  %  %  %  % -
	
	PrintArr(W, Nodes);
	
	// Step 1
	//--------------
	printf("Start node: %d\n", S);
	printf("Terminate node: %d\n", T);
	// make nodes like array indexes
	S--;
	T--;
	
	// node's path can be temporary and permanent
	int Perm[Nodes]= {0};
	// made Start node permanent
	Perm[S] = 1;
	
	// Path array, input here only last or min path
	int Path[Nodes] = {0};
	// Start node path = 0, other nodes path = infinity , equals E
	for (int i = 0; i < Nodes; i++){
		Path[i] = E;
	}
	Path[S] = 0;
	
	// current node = start node
	C = S;
	DistC = Path[S];
	
	// print
	PrintPath(Path, Nodes);
	
	int Iter = 1;
	// iterations:
	// while is not terminate node
	while (C != T){
		printf("Iteration %d:\n", Iter++);
	//Step 2
	// what node has seen from Current
	int Temp = 0;
	for (int i = 0; i < Nodes; i++){
		// node is seen
		if (W[ C ][ i ] > 0 && W[ C ][ i ] < E){
			Temp = DistC + W[ C ][ i ];
			if (Temp < Path[ i ]) Path[ i ] = Temp;
		}
	}
	// new paths:
	PrintPath(Path, Nodes);
	
	// minimum distance from nodes with temporary paths:
	C = MinTempDist(Path, Perm, Nodes);
	// Path if current node became permanent
	Perm[C] = 1;
	// Path of Current node
	DistC = Path[ C ];
	
	/*
	cout << "Minimum distance have " << C+1 <<" node with temp path. It became current node and path become permanent." << endl;
	*/
	
	cout <<"Nodes with permanent path: ";
	for (int i = 0; i < Nodes; i++){
		if (Perm[ i ] == 1) cout << i+1<< " ";
	}
	cout << endl;
	
	// end of iteration
	cout << "------------------------------------" << endl;
	}
	
	printf("Shortest path from %d to %d node = %d\n",  S+1, T+1, Path[ T ] );
	
	return 0;
}

// find min path from existing nodes with temp distances
int MinTempDist(int Path[], int Perm[], int Nodes){
    int MinNode = -1;
    int MinDist = E;
	for (int i = 0; i < Nodes; i++)
	{
		if (Perm[ i ] == 0 && Path[ i ] > 0 && Path[ i ] < MinDist){
			MinDist = Path[ i ];
			MinNode = i;
		}
	}

	return MinNode;	
}

// print array of nodes's paths
void PrintPath(int Path[], int Nodes){
	cout << "Path of nodes:" << endl;
	for (int i = 0; i < Nodes; i++){
		printf("%4d", Path[i] );
	}
	cout << endl;
}

//print array 2 dims: Weight matrix
void PrintArr(int Arr[][Nodes], int Nodes ){
	cout << "Weight matrix:" << endl;
	for (int i = 0; i < Nodes; i++){
		for (int j = 0; j < Nodes; j++){
			printf("%4d", Arr[i][j] );
		}
		cout << endl;
	}
}