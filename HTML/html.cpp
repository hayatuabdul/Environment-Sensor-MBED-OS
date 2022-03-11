#include "mbed.h"
#include "EthernetInterface.h"		//mbed library for ehternet comms
#include "mbed_mktime.h"		    //mbed library for GMT
#include "time.h"			        //mbed library for set and format time
#include "stdio.h"			        //mbed input output
#include "TCPSocket.h"
#include "html.h"

#include <iostream>
#include <string>

#include "Measurements.h"

extern double n;
extern double n1;
extern double n2;

Measurements DataForEthernet;

EthernetInterface Interface;		//setting up the ethernet connection        

void Network_Respond()  //ethernet function, this is what will be contained in one of the threads in main
{
    Interface.set_network(Ip, Netmask, Gateway);
    Interface.connect();
    
    SocketAddress BaseAddress;  		//setting up address of coming data
    Interface.get_ip_address(&BaseAddress);
    
    TCPSocket Socket;      		        //setting up socket
    Socket.open(&Interface);			//opening socket and adding it to stack
    Socket.bind(80);                    //connect http to TCP 80

    int err = Socket.listen(5);
    if (err==0){
        printf("HTML Initialised!\n\r");
    }
    else{
        printf("Error: %d\n\r",err);
    }
    
    time_t seconds = time(NULL);	//returns time in seconds since Jan 1 1970
    
	string Head;
	string Body;
	string Message;

    while (true) {
        //using namespace std;				//wait on recieved connection
        
        TCPSocket* Soc = Socket.accept();
//-----------------concatenating string for header
		Head += HttpHead;
		Head += "<title align=\"center\">ELEC350 Environmental Sensor</title>";
		Head += HttpHeadStop;
//-----------------concatenating string for body
		//Body += HttpBody;
		Body += BodyStyle;
		Body += Header1;
		Body += "<b><p><PRE>| Index |    date    | time  | T |  H  |  P   |  L  |</PRE></p></b>";
        Body += "<b><p><PRE>|  (#)  |(dd/mm/yyyy)|(hh:mm)|(C)| (%) |(mbar)| (#) |</PRE></p></b>";
		//for loop for all data points for a given date
        
        int i;
        for (i=0;i<1;i++)
        {
            Body += to_string(i);
            //Body += ", 14/01/2021, 00:11, 27.5C, 77%, 1000mbar, 8<br>";
            //Body += ", " + to_string(DataForEthernet.Temperature()) + ", " + to_string(DataForEthernet.Pressure()) + ", " + to_string(DataForEthernet.Humidity()) + ", " + to_string(DataForEthernet.LightLevel()) + "<br>";
            Body += ", " + to_string(n) + ", " + to_string(n1) + ", " + to_string(n2) + "<br>";
        }
		//ctime(&seconds)
		Body += HttpBodyStop;
//-----------------concatenating all code
		Message += HtmlStart;
		Message += Head;
		Message += Body;
        Message += HtmlEnd;
//-----------------sending html code as string

        nsapi_size_or_error_t error = Soc->send(Message.c_str(), Message.size());
        Soc->close();
        printf("Socket closed\n\r");
    }
}
