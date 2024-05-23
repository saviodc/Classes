#include <iostream>
#include "E101.h"
#include <string>
#include "MOTclass.cpp"

class camera {
private:
colours c;
motor::MP2 motP2;
public:

bool changeP(){
	int rcount = 0;
	for(int row = 200; row < 222;row++){ // check rows 200-222, middle of camera
		for(int col = 0; col < 320;col++){
			int r = (int)get_pixel(row,col,0);
			int g = (int)get_pixel(row,col,1);
			int b = (int)get_pixel(row,col,2);
			int intense = (int)get_pixel(row,col,3);
			if(c.isRed(r,g,b)){
				rcount++;
			}
		}
	}
	if(rcount > 50){
		gstate++;
		motP2.fwd();
	}
}

double camP1(){
	int totB;
	double totC;
	int centC;
	double dist;
	double grad = 0;
	for(int row = 200; row < 222;row++){ // check rows 200-222, middle of camera
		for(int col = 0; col < 320;col++){
			int intense = (int)get_pixel(row,col,3);
			if(c.isBlack(intense)){
				set_pixel(row,col,0,255,0); // make every black pixel green
				totB++;
				totC += col;
			}
		}}
		if(totB > 0){
			centC = totC / totB;	
			if (centC > 170){
				dist = centC-170;
				cout<<"RIGHT DIST: "<<dist<<endl;
				mstate = right(); // change current state to LEFT
			}
			else if (centC < 150){
				dist = 150 - centC;
				cout<<"LEFT DIST: "<<dist<<endl;
				mstate = left(); // change current state to RIGHT
			}
		}
		else if (totB == 0){
		mstate = forward();
		}
		grad = dist/150;
		cout<<"GRAD: "<<grad<<endl;
		return grad;
	}

class CP2{
private:
colours c;
bool isLeft(){  // returns true if left turn
	int count = 0;
	for(int row = 20;row<150;row++){
		for(int col = 20;col<24;col++){
			int intense = (int)get_pixel(row,col,3);
			if(c.isBlack(intense)){
				count++;
			}
		}
	}
	if (count > 20){
		return true;
		}
	else {
		return false;
	}
}

bool isRight(){ // returns true if right turn
	int count = 0;
	for(int row = 20;row<150;row++){
		for(int col = 296;col<300;col++){
			int intense = (int)get_pixel(row,col,3);
			if(c.isBlack(intense)){
				count++;
			}
		}
	}
	if (count > 20){
		return true;
		}
	else {
		return false;
	}
}

bool isFwd(){ // returns true if forward 
	int count = 0;
	for(int row =30;row<80;row++){
		for(int col = 100;col<220;col++){
			int intense = (int)get_pixel(row,col,3);
			if(c.isBlack(intense)){
				count++;
			}
		}
	}
	if (count > 20){
		return true;
		}
	else {
		return false;
	}
}
public:
string intersect(){
	if(isFwd() && !isLeft() && !isRight()){ // foward
		return "FORWARD";
	}
	if(!isFwd() && isLeft() && !isRight()){ // left turn
		return "LEFT";
	}
	if(!isFwd() && !isLeft() && isRight()){ // right turn
		return "RFORWARD";
	}
	if(!isFwd() && !isLeft() && !isRight()){ // nothing present
		return "RIGHT";
	}
	if(isFwd() && isLeft() && isRight()){ // all 3 present
		return "LEFT";
			}
} 

};
};