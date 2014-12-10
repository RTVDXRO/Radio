///
/// \file RDSParser.h
/// \brief RDS Parser class definition.
///
/// \author Matthias Hertel, http://www.mathertel.de
/// \copyright Copyright (c) 2014 by Matthias Hertel.\n
/// This work is licensed under a BSD style license.\n
/// See http://www.mathertel.de/License.aspx
/// 
/// \details
///
/// More documentation and source code is available at http://www.mathertel.de/Arduino
///
/// History:
/// --------
/// * 01.09.2014 created and RDS sender name working.
/// * 01.11.2014 RDS time added.


#ifndef __RDSPARSER_H__
#define __RDSPARSER_H__

#include <arduino.h>

/// callback function for passing a ServicenName 
extern "C" {
  typedef void (*receiveServicenNameFunction)(char *name);
  typedef void (*receiveTimeFunction)(uint8_t hour, uint8_t minute);
}


/// Library for parsing RDS data values and extracting information.
class RDSParser
{
public:
  RDSParser(); ///< create a new object from this class.

  /// Initialize internal variables before starting or after a change to another channel.
  void init();
  
  /// Pass all available RDS data through this function.
  void processData(uint16_t block1, uint16_t block2, uint16_t block3, uint16_t block4);
  
  void attachServicenNameCallback(receiveServicenNameFunction newFunction); ///< Register function for displaying a new Service Name.
  void attachTimeCallback(receiveTimeFunction newFunction); ///< Register function for displaying a new time

private:
  // ----- actual RDS values
  uint8_t rdsGroupType, rdsTP, rdsPTY;

  // Program Service Name
  char _PSName1[10]; // including trailing '\00' character.
  char _PSName2[10]; // including trailing '\00' character.
  char programServiceName[10];    // found station name or empty. Is max. 8 character long.
  
  receiveServicenNameFunction _sendServiceName; ///< Registered ServiceName function.

  receiveTimeFunction _sendTime; ///< Registered Time function.
  uint16_t _lastRDSMinutes; ///< last RDS time send to callback.

  char _RDSText[64+2];

}; //RDSParser

#endif //__RDSPARSER_H__