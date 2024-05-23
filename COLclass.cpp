#include <iostream>
#include "E101.h"
#include <string>

class colours{
	/*
 CHECKS for specific colours 
 in format:
 isCol(row,col,R,G,B)
 or
 isBlack(row,col,intense)
 
 **/
	public:
bool isBlack(int intense){
	if (intense < 60){
		return true;
	}
	else{ return false;}
}

bool isRed(int R, int G, int B){
	if (R/G > 1.4 || R/B > 1.4){
		return true;
	}
	else {return false;}
}

bool isGreen(int R, int G, int B){
	if (G/R > 1.4 || G/B > 1.4){
		return true;
	}
 else {return false;}
}

bool isBlue(int R, int B, int G){
	if (B/G > 1.4 || B/R > 1.4){
		return true;
	}
 else {return false;}
}};