// 此題目不會有走不到終點的情形

#include<iostream>
#include<fstream>
#include<stack>
#include<queue>
#include<vector>
using namespace std;

//#####################################################################

// For method 1
enum Direction{Right, Down, Left, Up, Finish};

Direction goBackOne(char*, stack<Direction>&, int&, int&);
void goForwardOne(char*, stack<Direction>&, int&, Direction, int&);
void changeDir(Direction&);
int getPosition(int, Direction, int);

//#####################################################################

int main(int argc, char* argv[]){
	int column;
	int row;
	int START;
	int END;
	int now;
	
	ifstream in(argv[1]);
	ofstream out1(argv[2]);
	ofstream out2(argv[3]);
	
// read file
	in >> column >> row;
	
	char* map = new char[row*column];
	char* map2 = new char[row*column];
	for(int i = 0; i < row*column; i++)
	{
		in >> map[i];
		map2[i] = map[i];
		if(map[i] == 'S')
			START = i;
		if(map[i] == 'E')
			END = i;
	}
	
// method 1
	stack<Direction> last_directions;
	
	Direction next_direction = Right;
	bool flag = false;					// reach 'E'
	now = START;
	int next_position;
	
	while(!flag)
	{
		next_position = getPosition(now, next_direction, column);
		
		if((map[next_position] == '1' || map[next_position] == '2') && next_direction != Finish)
			changeDir(next_direction);
		else
		{
			if(next_direction == Finish && now == START)
			{
				cout << "Method 1: There is no path to goal!" << endl;	
				break;
			}
			
			if(next_direction == Finish)
				next_direction = goBackOne(map, last_directions, now, column);
			else
			{
				goForwardOne(map, last_directions, now, next_direction, column);
				next_direction = Right;
			}
			
			if(now == END)
			{
				flag = true;
				map[END] = 'E';
			}				
		}
	}
	
// method 2	
	bool flag2 = false;					// find 'E'
	int P, d;
	int* step_map = new int[row*column];
	queue<int> spread;					// the queue in method 2 example

	
	for(int i = 0; i < row*column; i++)
	{
		step_map[i] = -1;
		
		if(map2[i] == 'S')
		{
			step_map[i] = 0;
			spread.push(i);
		}
	}

	while(!flag2)
	{
		P = spread.front();
		d = step_map[P];
		if(map2[P+1] != '2' && step_map[P+1] == -1)						// right
		{
			step_map[P+1] = d+1;
			spread.push(P+1);
			
			if(map2[P+1] == 'E')
				flag2 = true;
		}
		if(map2[P+column] != '2' && step_map[P+column] == -1)			// down
		{
			step_map[P+column] = d+1;
			spread.push(P+column);
			
			if(map2[P+column] == 'E')
				flag2 = true;
		}
		if(map2[P-1] != '2' && step_map[P-1] == -1)						// left
		{
			step_map[P-1] = d+1;
			spread.push(P-1);
			
			if(map2[P-1] == 'E')
				flag2 = true;
		}
		if(map2[P-column] != '2' && step_map[P-column] == -1)			// up
		{
			step_map[P-column] = d+1;
			spread.push(P-column);
			
			if(map2[P-column] == 'E')
				flag2 = true;
		}
		spread.pop();
	}
	
	P = END;
	d = step_map[END];
	
	while(d != 1)
	{
		if(step_map[P+1] == d-1)						// right
		{
			map2[P+1] = '1';
			P = P+1;
		}
		else if(step_map[P+column] == d-1)				// down
		{
			map2[P+column] = '1';
			P = P+column;
		}
		else if(step_map[P-1] == d-1)					// left
		{
			map2[P-1] = '1';
			P = P-1;
		}
		else if(step_map[P-column] == d-1)				// up
		{
			map2[P-column] = '1';
			P = P-column;
		}
	
		
		d--;
	}
	
	
// print map
	for(int i = 0; i < row*column; i++)
	{
		out1 << map[i] << " ";
		out2 << map2[i] << " ";
		if( i % column == column - 1 )
		{
			out1 << endl;
			out2 << endl;
		}
	}

	
	delete[] map;
	delete[] map2;
	delete[] step_map;
	
	return 0;

}

//#####################################################################

// Go back for one step, and return the next direction.
Direction goBackOne(char* map, stack<Direction>& last_directions, int& now, int& column)
{
	if(map[now] == '1')
		map[now] = '0';
	
	Direction last_step = last_directions.top();
	switch(last_step)
	{
		case Right:
			now--;
			last_directions.pop();
			return Down;
			break;
		case Down:
			now-=column;
			last_directions.pop();
			return Left;
			break;
		case Left:
			now++;
			last_directions.pop();
			return Up;
			break;
		case Up:
			now+=column;
			last_directions.pop();
			return Finish;
			break;
	}		
}


// Go forward for one step, and set now as '1'.
void goForwardOne(char* map, stack<Direction>& last_directions, int& now, Direction next_direction, int& column)
{
	switch(next_direction)
	{
		case Right:
			now++;
			last_directions.push(next_direction);
			map[now] = '1';
			break;
		case Down:
			now+=column;
			last_directions.push(next_direction);
			map[now] = '1';
			break;
		case Left:
			now--;
			last_directions.push(next_direction);
			map[now] = '1';
			break;
		case Up:
			now-=column;
			last_directions.push(next_direction);
			map[now] = '1';
			break;
	}
}


void changeDir(Direction& dir)
{
	Direction next;
	switch(dir)
	{
		case Right:
			dir = Down;
			break;
		case Down:
			dir = Left;
			break;
		case Left:
			dir = Up;
			break;
		case Up:
			dir = Finish;
			break;
	}
}


int getPosition(int now, Direction next_direction, int column)
{
	switch(next_direction)
	{
		case Right:
			return (now + 1);
			break;
		case Down:
			return (now + column);
			break;
		case Left:
			return (now - 1);
			break;
		case Up:
			return (now - column);
			break;
		default:
			return 0;
			break;
	}
}
