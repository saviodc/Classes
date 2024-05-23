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
					set_mototrs(5,48+b);
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
		}	
};