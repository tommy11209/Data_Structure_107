#include <iostream>
#include <fstream>
#include <stack>

using namespace std;

char** read_maze(int* rows, int* cols);
void print_maze(char** maze, int rows, int cols);
void bruteForceMazeSolver(int i, int j);
int maze_search(char**, int, int);

struct Location {
   int row;
   int col;
};

struct maze
{
	int rows;
	int cols;
	char ** matrix;
};

maze myMaze;

class Queue {
   public:
   Queue(int maxlen);

   ~Queue();

   void add_to_back(Location loc);

   Location remove_from_front();

   bool is_empty();

   private:
   Location* contents; // ptr to dynamically-allocated array
   int tail;
   int head;
};

Queue::Queue(int maxlen) {
   contents = new Location[maxlen];
   head = 0;
   tail = 0;
}

Queue::~Queue() {
   delete[] contents;
}

void Queue::add_to_back(Location loc) {
   // FILL THIS IN
   contents[tail].row = loc.row;
   contents[tail].col = loc.col;
   tail++;
}

Location Queue::remove_from_front() {
   head++;
   return contents[head-1];
}

bool Queue::is_empty() {
   return head == tail;
}


int main(int argc, char** argv)
{
    char* input, *output, *output2;
    input = argv[1];
    output = argv[2];
    output2 = argv[3];
    std::fstream f(input , std::ios::in);
    std::fstream  out(output , std::ios::out);
    std::fstream  out2(output2 , std::ios::out);

    int rows, cols, result;
    int x=1, y=1;

    char** bfs_maze;

    f >> cols >> rows;

    bfs_maze = read_maze(&rows, &cols);
    myMaze.matrix = read_maze(&rows, &cols);

    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            f >> bfs_maze[i][j];
            }
    }
    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            myMaze.matrix[i][j] = bfs_maze[i][j];
            }
    }

    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            if(myMaze.matrix[i][j] == 'S')
            {
              x = j;
              y = i;
            }
      }

    }

    bruteForceMazeSolver(x,y);

    for(int i=0; i<rows; i++)
    {
      for(int j=0; j<cols; j++)
      {
         if(myMaze.matrix[i][j] == 'x')
         {
           myMaze.matrix[i][j] = '0';
         }
       }
    }

    for(int i=0; i<rows; i++){
      for(int j=0; j<cols; j++){
         out << myMaze.matrix[i][j] << " ";
      }
      out << endl;
    }

    if (bfs_maze == NULL) {
      cout << "Error, input format incorrect" << endl;
      return 1;
    }

    result = maze_search(bfs_maze, rows, cols);

    if (result == 1) { // path found!

      for(int i=0; i<rows; i++){
         for(int j=0; j<cols; j++){
            out2 << bfs_maze[i][j] << " ";
         }
         out2 << endl;
      }
    }
    else if (result == 0) { // no path :(
      cout << "No path could be found!" << endl;
    }
    else { // result == -1
      cout << "Invalid maze." << endl;
    }


    for(int i=0; i<rows; i++){
      delete [] bfs_maze[i];
      //delete [] myMaze[i];
    }
    delete [] bfs_maze;
    //////////////////////////////
    ///////////////////////////////

    for(int i=0; i<rows; i++){
      delete [] myMaze.matrix[i];
      //delete [] myMaze[i];
    }
    delete [] myMaze.matrix;

    return 0;
}

char** read_maze(int* rows, int* cols) {

   char** maze = new char*[*rows];
   for(int i=0; i<*rows; i++){

      maze[i] = new char[*cols];
   }
   return maze;
}

void bruteForceMazeSolver(int i, int j)
{

    int curr_x = j;
    int curr_y = i;
    int count = 0;
    int distance =0;
    stack<char> moves;

    while(myMaze.matrix[curr_x][curr_y] != 'E')
    {
        //try going right
        if(myMaze.matrix[curr_x][curr_y+1] == '0' || myMaze.matrix[curr_x][curr_y+1] == 'E' )
        {
            curr_y++;
            if(myMaze.matrix[curr_x][curr_y] == 'E'){
            break;
            }
            moves.push('r');
            myMaze.matrix[curr_x][curr_y] = '1';
        }

        //try going down
        else if(myMaze.matrix[curr_x+1][curr_y] == '0' || myMaze.matrix[curr_x+1][curr_y] == 'E')
        {
            curr_x++;
            if(myMaze.matrix[curr_x][curr_y] == 'E'){
            break;
            }
            moves.push('d');
            myMaze.matrix[curr_x][curr_y] = '1';
        }

        //try going left
        else if (myMaze.matrix[curr_x][curr_y-1] == '0' || myMaze.matrix[curr_x][curr_y-1] == 'E')
        {
            curr_y--;
            if(myMaze.matrix[curr_x][curr_y] == 'E'){
            break;
            }
            moves.push('l');
            myMaze.matrix[curr_x][curr_y] = '1';
        }

        //try going up
        else if(myMaze.matrix[curr_x-1][curr_y] == '0' || myMaze.matrix[curr_x-1][curr_y] == 'E')
        {
            curr_x--;
            if(myMaze.matrix[curr_x][curr_y] == 'E'){
            break;
            }
            moves.push('u');
            myMaze.matrix[curr_x][curr_y] = '1';
        }


        //try backtracking right
        else if (moves.top() == 'l'){
        	moves.pop();
        	if(myMaze.matrix[curr_x][curr_y] != 'S'){
        		myMaze.matrix[curr_x][curr_y] = 'x';
        	}
        	curr_y++;

        }

        //try backtracking down
        else if (moves.top() == 'u'){
        	moves.pop();
        	if(myMaze.matrix[curr_x][curr_y] != 'S'){
        		myMaze.matrix[curr_x][curr_y] = 'x';
        	}
        	curr_x++;

        }

        //try backtracking left
        else if (moves.top() == 'r'){
        	moves.pop();
        	if(myMaze.matrix[curr_x][curr_y] != 'S'){
        		myMaze.matrix[curr_x][curr_y] = 'x';
        	}
        	curr_y--;

        }

        //try backtracking up
        else if (moves.top() == 'd'){
        	moves.pop();
        	if(myMaze.matrix[curr_x][curr_y] != 'S'){
        		myMaze.matrix[curr_x][curr_y] = 'x';
        	}
        	curr_x--;
        }

        else{
        	cout << "Error: Maze Unsolvable" << endl;
        	break;
        }

    }

}

/**************************************************

 *************************************************/
int maze_search(char** maze, int rows, int cols)
{

    //Creating the visited grid
    int** visited = new int*[rows];
    for(int i=0; i<rows; i++){
    visited[i] = new int[cols];
       for(int j=0; j<cols; j++){
          visited[i][j] = 0; //initilze all to 0
       }
    }
    //Creating the predecessor grid
    Location** predecessor = new Location*[rows];
    for(int i=0; i<rows; i++){
    predecessor[i] = new Location[cols];
    }
    //Creating a queue
    Queue q(rows*cols);

    // Check if there is start and end point
    int start = 0;
    int end = 0;
    Location startpoint;

    for(int i=0; i<rows; i++){
    for(int j=0; j<cols; j++){
       if(maze[i][j] == 'S'){
          start++;
          startpoint.row = i;
          startpoint.col = j;
          q.add_to_back(startpoint);
       }
       if(maze[i][j] == 'E'){
          end++;
       }
    }
    }

    //Check if it is a valid maze
    if(start != 1 || end !=1){
    for(int i=0; i<rows; i++){
       delete [] visited[i];
    }
    delete[] visited;

    for(int i=0; i<rows; i++){
       delete [] predecessor[i];
    }
    delete [] predecessor;

    return -1;
    }

    Location curr; // current location
    // initialize north, west, south and east
    Location north, west, south, east;
    //TO check if path is found
    bool found = false;

    while(!(q.is_empty())){
    curr = q.remove_from_front();
    visited[curr.row][curr.col] = 1;

    //For searching north
    north.row = curr.row - 1;
    north.col = curr.col;
    //make sure inside the maze
    if(north.row>=0 && north.row<rows &&
       north.col>=0 && north.col<cols){
       if(maze[north.row][north.col] == 'E'){
          found = true;
          break;
       }
       //check if it is a valid path
       else if(maze[north.row][north.col] == '0' &&
              visited[north.row][north.col] != 1){

              q.add_to_back(north);
              visited[north.row][north.col] = 1;
              predecessor[north.row][north.col] = curr;
       }
    }

    //For searching west
    west.row = curr.row;
    west.col = curr.col - 1;
    //make sure inside the maze
    if(west.row>=0 && west.row<rows &&
       west.col>=0 && west.col<cols){
       if(maze[west.row][west.col] == 'E'){
          found = true;
          break;
       }
       //check if it is a valid path
       else if(maze[west.row][west.col] == '0' &&
              visited[west.row][west.col] != 1){

              q.add_to_back(west);
              visited[west.row][west.col] = 1;
              predecessor[west.row][west.col] = curr;
       }
    }
    //For searching south
    south.row = curr.row + 1;
    south.col = curr.col;
    //make sure inside the maze
    if(south.row>=0 && south.row<rows && south.col>=0 &&
       south.col<cols){
       if(maze[south.row][south.col] == 'E'){
          found = true;
          break;
       }
       //check if it is a valid path
       else if(maze[south.row][south.col] == '0' &&
               visited[south.row][south.col] != 1){

               q.add_to_back(south);
               visited[south.row][south.col] = 1;
               predecessor[south.row][south.col] = curr;
       }
    }
    //For searching east
    east.row = curr.row;
    east.col = curr.col + 1;
    //make sure inside the maze
    if(east.row>=0 && east.row<rows && east.col>=0 &&
       east.col<cols){
       if(maze[east.row][east.col] == 'E'){
          found = true;
          break;
       }
       //check if it is a valid path
       else if(maze[east.row][east.col] == '0' &&
               visited[east.row][east.col] != 1){

               q.add_to_back(east);
               visited[east.row][east.col] = 1;
               predecessor[east.row][east.col] = curr;
       }
    }
    }
    //delete the visited array allocation since it is no longer used
    for(int i=0; i<rows; i++){
    delete [] visited[i];
    }
    delete[] visited;

    //situation when no path exist
    if(!found){
    //delete the predecessor array that have been allocated
    for(int i=0; i<rows; i++){
    delete [] predecessor[i];
    }
    delete [] predecessor;

    return 0;
    }

    // situation when path find
    else{

    while(maze[curr.row][curr.col] != 'S'){
        maze[curr.row][curr.col] = '1';
        curr = predecessor[curr.row][curr.col];
    }

    for(int i=0; i<rows; i++){
       delete [] predecessor[i];
    }
       delete [] predecessor;

    return 1;
    }


}
