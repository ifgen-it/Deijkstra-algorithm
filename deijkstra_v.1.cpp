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
// Route of the shortest path
int* Route = nullptr;
int RouteNodes = 1;

void PrintArr(int Arr[][Nodes], int Nodes);
void PrintPath(int Path[], int Nodes);
int MinTempDist(int Path[], int Perm[], int Nodes);
void AddNodeToRoute(int i);

int main(){
	
	printf("DEIJKSTRA algorithm\nSearching the shortest path in oriented graph\n");
	   	cout << "-----------------------------------------------" << endl;
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
	// Phase 1 Search value of the shortest path
	// Step 1
	//--------------
	printf("Start node: %d\n", S);
	printf("Terminate node: %d\n", T);
		cout << "-----------------------------------------------" << endl;
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
//	cout << "------------------------------------" << endl;
	}
	cout << "-----------------------------------------------" << endl;
	
	printf("Shortest path from %d to %d node = %d\n",  S+1, T+1, Path[ T ] );
	
//	cout << "Current: "<< C << endl;
	
	// Phase 2
	// Searching route of found path's value
	// Step 1
	int* Route = new int[ 1 ];
	// will find nodes from Terminate node to Start node
	Route[ 0 ] = T;
	// Current node is Term node now
// will build route from Term node to Start node	
	while ( C != S ){
for (int i = 0; i < Nodes; i++){
	if (W[ i ] [ C ] > 0 && W[ i ][ C ] < E){
		if (W[ i ][ C ] + Path[ i ] == Path[ C ] ){
		
			// create new array to put there new route node
	int* Temp = new int[ RouteNodes + 1];
	// copy 
	for (int i = 0; i < RouteNodes; i++){
		Temp[ i ] = Route[ i ];	
	}
	Temp[RouteNodes] = i;
	RouteNodes++;
	
	delete [ ] Route;
	Route = Temp;
	Temp = nullptr;
	//PrintPath(Route, RouteNodes);
	C = i;
	break;
			}	
		}	
  	}
	} // end of route building

	// reverse route array
	for (int i = 0; i < RouteNodes/2; i++){
		// swap
		int Temp = Route[ i ];
		Route[ i ] = Route[ RouteNodes-1-i];
		Route[RouteNodes-1-i] = Temp;	
	}
	
	
	//print route
	cout << "Shortest route:" << endl;
	for (int i = 0; i < RouteNodes; i++){
		printf("%d", Route[i] + 1);
		if (i == RouteNodes - 1) break;
		printf(" > ");
	}
	cout << endl;
	
	// clean memory
	delete[] Route;	
	
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