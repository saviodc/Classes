#include <iostream>
#include "E101.h"
#include <string>

using namespace std;



#include <iostream>
#include "E101.h"
#include <string>
#define PORT 1024

#include <iostream>
#include "E101.h"
#include <string>

int gstate = 1;
string mstate = "GATE";


string left(){	return "LEFT";}

string right(){	return "RIGHT";}

string forward(){return "FORWARD";}

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

void gate(){
    char address[15] = "130.195.3.53";
	char message[24] = "Please";
	connect_to_server(address,PORT);
	send_to_server(message);
	receive_from_server(message);
	send_to_server(message);
	
}

class motor {	
	public:
		class MP1{
		public:
			int XC =  18;// clockwise
			int XAC =  17;// anti clockwise
			void fwd(double M){ // go foward at M intensity
				if (M < 0.1){
					M+=0.5;
				}
				set_motors(3,48-(XC*M));// clockwise
				set_motors(5,48+(XAC*M)); // anticlockwise
				hardware_exchange();
			}
			void back(double M){ // go backwards at M times power
				if (M < 0.1){
					M+=0.1;
				}
				set_motors(3,48+(XAC*M)); // anticlockwise
				set_motors(5,48-(XC*M)); // clockwise
				hardware_exchange();
					
			}
			void left(double M){ // turn left at M intensity
				if (M < 0.1){
					M+=0.1;
				}
				set_motors(3,48-(XC*M)); // go clockwise
				set_motors(5,48); // stop
				hardware_exchange();
			}
			void right(double M){ // turn right at M intensity
				if (M < 0.1){
					M+=0.1;
				}
				set_motors(3,48); // stop
				set_motors(5,48+(XAC*M)); // go anticlockwise
				hardware_exchange();
			}
			
			void adjust(double M){
				if(mstate == "FORWARD"){
				fwd(M); // move foward
				}
				if(mstate == "LEFT"){
					left(M); // adjust left
				}
				if (mstate == "RIGHT"){
					right(M); // adjust right
				}
			}
		};
		class MP2{
			private:
				int M = 9; // M is beteen 1-17
				double a = (M*1.0588)/18;
				double b = M/17;
			public:
				void set_camera(){
					set_motors(1,10);
					hardware_exchange();
				}

				void right(){ // turn right on spot
					set_motors(3,48-b);
					set_motors(5,48-b);
					hardware_exchange();
					sleep1(1000);
				}
				
				void left(){ // turn left on spot
					set_motors(3,48+a);
					set_motors(5,48+a);
					hardware_exchange();
					sleep1(1000);
				}

				void fwd(){ // move forward
					set_motors(3,48-a);
					set_motors(5,48+b);
					hardware_exchange();
					sleep1(500);
				}
				void state(string s){ // s for intersections
					if (s == "LEFT"){ // turn left
						left();
					}
					if (s == "RIGHT"){ // turn right
						right();
					}
					if(s == "RFORWARD"){ // move forward, ignore right turn
						fwd();
					}
				};	
		};
		class MP3 {
			private:
				int M = 9; // M is beteen 1-17
				double a = (M*1.0588)/18;
				double b = M/17;
			public:
				void set_camera(){
					set_motors(1,60);
					hardware_exchange();
				}
		};	
};

class camera {
private:
colours c;
motor::MP2 motP2;
public:

void changeP(){
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



int main(){
	
    init(0);
    open_screen_stream();
    take_picture();
    sleep1(100);
    bool stop = false;
    motor mot;
    camera cam;
    colours colour;
    motor::MP1 motP1;
    motor::MP2 motP2;
    camera::CP2 camP2; 
    //double M;
	while(true){
	take_picture();
	motor mot;
    double M = cam.camP1();

        if (gstate ==1){
            gate();
            motP1.adjust(M);
        }
        if (gstate == 2){
            string turn = camP2.intersect();
            motP2.state(turn);
            motP1.adjust(M);
        }

        /*if(gstate == THREE){
           // adjust camera to look up
        }*/
        
            // INSERT CODE HERE
        /*
        ORDER OF:
        - server connect to open gate
        - look for red square to change quadrants
        P1:
        - follow line
        P2:
        - intersections
        - follow line
        P3:
        - get close to pillars without touching
        - look up, find red ball, push off
    */
        cam.changeP();
        update_screen();
        if (stop == true){ // STOP MOTOR
            set_motors(5,48);
            set_motors(3,48);
            hardware_exchange();
            
        }
	}
		 close_screen_stream();
    }
   


