/*
Image Component Labeling
Project 1
Haoran Zhi
2019/02/13

Purpose: the purpose of this program is to understand the difference between 
BFS and DFS.
*/
#include <iostream>
#include <cstdlib>
#include <array>
#include "arrayQueue.h"
#include "position.h"
#include "arrayStack.h"




using namespace std;

class Pixel
{
public:
//component of the class
  int **label;
  int **order ;
  int size;
  //function of this class
  Pixel (int a);//constructor
  void print ();
  friend void PopulateGrid (Pixel A, Pixel B, int Size);
  friend void applyBFS(Pixel gA);
  friend void applyDFS(Pixel gB);
};

/*the main function ask the user to 
input the size of the grid and show the two 
type of labeling methods: BFS and DFS
*/
int main (int argc, char const *argv[])
{

 int N;
  cout<<"Please enter the size of the Grid."<<endl;//prompt the user to enter the size they want
  cin>>N;
  N+=2;
  //create two Pixel objects
  Pixel gA (N), gB (N);
  //build the grid and apply two search method on them
  PopulateGrid (gA, gB, N);
  applyDFS(gA);
  applyBFS(gB);
  //show the result
  cout << "appying DFS:"<<endl;
  gA.print ();
  cout<<"applying BFS:"<<endl;
  gB.print();
 return 0;
}

//the constructor that takes a int value as input
//and inishallize the 2D-array
Pixel::Pixel (int a)
{
  size = a;
  label = new int *[a];
  order = new int *[a];
  for (int i = 0; i < size; i++){
  	label[i] = new int[a];
  	order[i] = new int[a];
  }
    


}





//the print function will print out the grid
void Pixel::print ()
{
  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++)
      if (j == size - 1)
	{
	  cout <<label[i][j]<< ","<<order[i][j]<< endl;
	}
      else
	{

	  cout << label[i][j] << "," << order[i][j] << " ";
	}
}


//the populaGrid function take two Pixel objects and a int as input 
//and will put random 1's in to the grid according to the density 
//get from the user.
void PopulateGrid (Pixel A, Pixel B, int Size)
{
  double density;
  //create a wall of 0's around.
  for (int i = 0; i < Size; i++)
    for (int j = 0; j < Size; j++){
      A.label[i][j] = B.label[i][j] = 0;
      A.order[i][j] = B.order[i][j] = 0;
    }

  cout << "please enter the density you want(0~1):" << endl;
  cin >> density;
  //draw random 1's on the grid
  for (int row = 1; row <= Size - 2; row++)
    for (int col = 1; col <= Size - 2; col++)
      {
	double r =( (double) rand () / (RAND_MAX));
	if (r <= density)
	  {
	    A.label[row][col] = B.label[row][col] = 1;
	  }
	else
	  {
	    A.label[row][col] = B.label[row][col] = 0;
	  }
	}
}






// the applyBFS function will take a Pixel object as input
//and will label the 1's in the grid using BFS.
void applyBFS(Pixel gA){

	position here;
	
	int numOfNbrs = 4;
	arrayQueue<position> q;
   	position nbr;
   	int Label = 2;
   	int Order;
   	//inistallizing offsets
	position offset[4];
	offset[0].row = 0; offset[0].col = 1; //right
	offset[1].row = 1; offset[1].col = 0; //down
	offset[2].row = 0; offset[2].col = -1;//left
	offset[3].row = -1; offset[3].col = 0;//up

   //loop through the grid
   for (int i = 1; i <= gA.size-2; i++)
   {
       for (int j = 1; j <= gA.size-2; j++)
       {	//find if there is a image
           if(gA.label[i][j] == 1)
           {
           	here.row = i;
			here.col = j;
			Order = 1;
			gA.label[here.row][here.col] = Label;
   			gA.order[here.row][here.col] = Order;

   			//scan the whole image out and label them
           	do 
   			{
   				
       			for (int k = 0; k < numOfNbrs; k++)
       			{
       				
          			nbr.row = here.row + offset[k].row;
          			nbr.col = here.col + offset[k].col;
          			if (gA.label[nbr.row][nbr.col] == 1)
          			{
          				Order+=1;
             			gA.label[nbr.row][nbr.col] = Label;
             			
             			gA.order[nbr.row][nbr.col] = Order;
             			
   	        			q.push(nbr);
          			}
       			}
      
      			if(q.empty()){
      				Label++;
      				break;
      			}
      			here = q.front();         // get next position
      			q.pop();
   			} while(true);
           	
           	
           }
       }
   }

}






// the applyDFS function will take a Pixel object as input
//and will label the 1's in the grid using DFS.
void applyDFS(Pixel gB){
	arrayStack<position>* image;
	image = new arrayStack<position>;
	int Label = 1;
	int Order;

   // initialize offsets
   position offset[4];
   offset[0].row = 0; offset[0].col = 1;   // right
   offset[1].row = 1; offset[1].col = 0;   // down
   offset[2].row = 0; offset[2].col = -1;  // left
   offset[3].row = -1; offset[3].col = 0;  // up

   position here;
   here.row = 1;
   here.col = 1;
   int option = 0; // next move
   int lastOption = 3;
   
   // search for a the image
    for (int i = 1; i <= gB.size-2; i++)
   {
       for (int j = 1; j <= gB.size-2; j++)
       {
           if(gB.label[i][j] == 1)
           {

           	 image = new arrayStack<position>;
           	 Label++;
           	 Order = 1;
           	 gB.order[i][j] = Order;

   			position here;
   			here.row = i;
   			here.col = j;
   			gB.label[i][j] = 0; // prevent return back 
   			int option = 0; 
   			int lastOption = 3;
   
   			// search for a image
   			while (true)
   			{
      			// find a neighbor to move to
      			int r, c;      
      			while (option <= lastOption) 
      			{
         			r = here.row + offset[option].row;
         			c = here.col + offset[option].col;
         			if (gB.label[r][c] == 1) {
         				Order++;
         				break;
         			}
         			option++; // next option
      			}

      			// was a neighbor found?
      			if (option <= lastOption)
      			{// move to image[r][c]
      				
      				gB.order[r][c] = Order;
         			image->push(here);
         			here.row = r;
         			here.col = c;
         			gB.label[r][c] = 0; // set to 0 to prevent revisit
         			option = 0;
      			}
      			else
      			{// no neighbor to move to, back up then label the image
         			if (image->empty()){
         				gB.label[i][j] = Label;
           			 break;   // no place to back up to
         			}
         			position next = image->top();
         			gB.label[here.row][here.col] = Label;
         			gB.label[next.row][next.col] = Label;
         			image->pop();
         			if (next.row == here.row)
            			option = 2 + next.col - here.col;
         			else option = 3 + next.row - here.row;
         			here = next;
      			}
   			}

           	
           	
           }
       }
   }
}
