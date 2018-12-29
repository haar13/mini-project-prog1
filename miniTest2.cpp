#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include<stdlib.h>
#include<time.h>
#include<math.h>
using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////////////////////
double randvel(){
  double vel=0;
  vel=(1+rand()%(151-50))*0.01;
  return vel;
}
////////////////////////////////////////////////////////////////////////
int rotdirection(){
  int dir = 0;
  dir = 1+rand()%(3-1);
  return dir;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

double randrot2(){
  double rot = 0;
  rot = ((1+rand()%(61))-30)*0.1;
  //rot = (1+rand()%(7))-3;
  return rot;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

void complete(){

      double angle=0;
      double realangle=0;
      double posx=0;
      double posy=0;
      double ahead=0;
      double realposx=0;
      double realposy=0;
      int direction=0;
      int rep=0;
      cout<<"How many repetitions should i do?"<<endl;
      cin>>rep;
      ros::NodeHandle nh;
      ros::Publisher cmd_vel_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel_mux/input/navi", 100);
      for (int i=0;i<rep;i++){
        ros::Duration(1.0).sleep();
        geometry_msgs::Twist msg;
        msg.linear.x = 0.0;
        if(rotdirection()==1){
          angle=1.57079633;
        }
        else{
          angle=-1.57079633;
        }
        //angle=1.57;//randrot2();
        realangle=realangle+(angle);//
        msg.angular.z = angle*2.2;
        cmd_vel_pub.publish(msg);

        ros::Duration(1.0).sleep();
        ahead = randvel();
        posx=ahead*cos(realangle);
        posy=ahead*sin(realangle);
        if (realposx+posx<1.5&&realposx+posx>(-1.5)) {          //  ##   ##
          if (realposy+posy<1.5&&realposy+posy>(-1.5)) {        //  _________
        realposx=realposx+posx;
        realposy=realposy+posy;
        cout<<"Position en X: "<<realposx<<" Position en Y: "<<realposy<<endl;

        //nh.advertise<geometry_msgs::Twist>("/cmd_vel_mux/input/navi", 10); no tiene sentido esto
       ros::Duration(1.0).sleep();
       for(int i=0;i<((ahead*20)+1);i++){
         geometry_msgs::Twist msg;
         msg.linear.x = 0.5;
         msg.angular.z = 0.0;
         cmd_vel_pub.publish(msg);
         ros::Duration(0.1).sleep();
       }

      }
      else {
        cout<<"The position in Y would be: "<<realposy+posy<<", limit is -+1.5"<<endl;
      }
      }
      else {
        cout<<"The position in X would be: "<<realposx+posx<<", limit is -+1.5"<< endl;
      }
    }
}

void rotation(){
  double valueDeg = 0;
  double valueRad = 0;
  cout<<"How many degree would you like me to turn? " << endl;
  cin >> valueDeg;
  valueRad = valueDeg *(M_PI/180);
  cout <<"you selected: " << valueRad <<"radians"<<endl;
  ros::NodeHandle nh;
  ros::Publisher cmd_vel_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel_mux/input/navi", 10);
  ros::Duration(1.0).sleep();
  for(int i=0;i<(valueRad*10)+1;i++){
    geometry_msgs::Twist msg;
    msg.linear.x = 0.0;
    msg.angular.z = 1.0;
    cmd_vel_pub.publish(msg);
    ros::Duration(0.1).sleep();
  }
  cout<<"Done rotating "<< valueDeg<< "°/"<< valueRad<< "rad.     Good job me!"<<endl;
}

void linearVelocity(){
  cout<<"How many meters Mister Turtle should go:"<<endl;
  double meters = 0;
  cin>>meters;
  ros::NodeHandle nh;
  ros::Publisher cmd_vel_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel_mux/input/navi", 10);
  ros::Duration(1.0).sleep();
  for(int i=0;i<((meters*20));i++){
    geometry_msgs::Twist msg;
    msg.linear.x = 0.5;
    msg.angular.z = 0.0;
    cmd_vel_pub.publish(msg);
    ros::Duration(0.1).sleep();
  }
  cout<<"Mister turtle went "<< meters << "m"<<endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[]) {
  bool bExit = false;
  int method=0;
  srand(time(NULL));
  ros::init(argc, argv, "move_turtlesim");
  cout<<"Welcome, please try me."<<endl;
  cout<<"Which working method do you prefer? 1. both Ways or 2. Rotation or 3. Linear."<<endl;

do {

  cin>>method;
  switch (method) {
    case 1:
      complete();
      break;

    case 2:
      rotation();
      break;

    case 3:
      linearVelocity();
      break;

    case 'e':
      cout << "You chose to exit the program." << endl;
      bExit = true;
      cout << "SEE YOU SOON AGAIN!" << endl;
      break;

    default:                            //\t\t\t\t = 4 tabs
      cout << "You typed in a invalid number, try: " << endl;
      cout << "\t\t\t\t1 -> random drive in a square;" <<endl;
      cout << "\t\t\t\t2 -> I will rotate in a given angle." <<endl;
      cout << "\t\t\t\t3 -> I will drive forwart to a given distance." <<endl;
      cout << "\t\t\t\te -> to exit the program." <<endl;
      break;
}
} while (!bExit);

  ros::spin();
  return 0;
}
