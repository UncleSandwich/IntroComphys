#include<iostream>
#include<fstream>
#include <vector>
#include <string>


using namespace std;

// The following function prints the lattice to file "output.ppm"
void Print_lattice (int *vlat, const int &vlx, const int &vly, const int &vwidth, const int &vheight, const char* vfilename="output.ppm")
{
	int const sizeOfCluster = 20000;
  int  i, j, k, l;
  int vw= vwidth/vlx, vh=vheight/vly;
  int r[sizeOfCluster], g[sizeOfCluster], b[sizeOfCluster];
  //r[0] = 255; g[0] = 255; b[0] = 255; //white  use 0 in your lattice if you want to color it white
  int counter = 1, index = 1;
  do {
	  g[counter] = index;
	  r[counter] = 255;
	  b[counter] = 255;
	  if (counter > index*double(sizeOfCluster) / 255) {
		  index++;
	  }
	  counter++;
  } while (counter<sizeOfCluster);
  
  /*int counter=1;
  for (i = 1; i < 1785; i++) {
	  g[i] = counter;
	  r[counter] = 255;
	  b[counter] = 0;
	  if (double(i)/1785.0-int(i/1785) ==  0) {
		  counter++;
	  }
  }*/
 
  /*
  r[1]=   0; g[1]= 255; b[1]=   0; //green  use 1 in your lattice if you want to color it green
  r[2]= 255; g[2]=   0; b[2]=   0; //red
  r[3]=   0; g[3]=   0; b[3]=   0; //black
  r[4]=   0; g[4]=   0; b[4]= 255; //blue
  */

  ofstream out (vfilename);

  out << "P3" << endl;
  out << vw*vlx << " " << vh*vly << endl;
  out << "255" << endl;

  for (i = vly - 1; i >= 0; i--)
	  for (j = 0; j<vh; j++)
		  for (k = 0; k<vlx; k++)
		  {
			  for (l = 0; l<vw; l++)
			  {
				 //Border colouring
				  /*if (vlat[k + i*vlx] == -1) {
					  out << 0 << " " << 0 << " " << 255 << " ";
				  }*/
				  /*else*/// if ((vlat[k + i*vlx] == 0) || (vlat[k+i*vlx] == -1)) {
					//  out << 255 << " " << 255 << " " << 255 << " ";
				  //}
				  //else {
					  //out << 0 << " " << 0 << " " << 0 << " ";
					  out << r[vlat[k + i*vlx]] << " " << g[vlat[k + i*vlx]] << " " << b[vlat[k + i*vlx]] << " ";
				  //}
			  }
		  }
  out << endl;

  out.close();
}
