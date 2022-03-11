#ifndef __HTML__
#define __HTML__

#include "mbed.h"

//--------------------defining HTTP specific commands

#define Ip        "10.0.0.10"        // web browser access
#define Netmask   "255.0.0.0"
#define Gateway   "10.0.0.1"         // ethernet ip address

//#define HttpStatus "HTTP/1.0 200 OK"
//#define HttpHeader "Content-Type: text/html; charset=utf-8"
//#define HttpMsg ""                                   


#define HtmlStart 	    "<!DOCTYPE html>" "\r\n" "<html>" "\r\n"

#define HttpHead 	    "<head>" 
#define HttpHeadStop   	"</head>"

#define HttpBody	    "<body>"
#define HttpBodyStop    "</body>"

#define Header1         "<h1 align=\"center\">ELEC350: <i>\"Environmental Sensor\"</i></h1>"

#define BodyStyle	    "<body style= background-color:floralwhite;font-family:helvetica;>"

#define HtmlEnd 	    "</html>"

extern void Network_Respond();

#endif