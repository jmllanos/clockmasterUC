#ifndef _CONTROLLER_COMMANDS_H_INCLUDED
#define _CONTROLLER_COMMANDS_H_INCLUDED

#include <Arduino.h>
#include <string.h>
#include <ArduinoHttpServer.h>
#include <tiva_configuration.h>
#include <clock_master_registers.h>
#include <read_write_registers.h>
#include <ArduinoJson.h>
#include <Base64.h>
#include <network_commands.h>
#include "WatchdogMan.h"
#include <pps_divider.h>

enum user_request
{
  Status,
  Reset,
  Start,
  Stop,
  Setdate,
  Setpps,
  Read,
  Write,
  ChangeIP,
  Error
};

user_request str2request (String request);

class clock_master
{
    private:
        pps_divider pps_divider_0;
        pps_divider pps_divider_1;
        pps_divider pps_divider_2;
        pps_divider pps_divider_3;

    public:

};

void clock_master_reset (ArduinoHttpServer::StreamHttpReply& httpReply, long& rc_ram_usage, bool& free_running);

void clock_master_stop (ArduinoHttpServer::StreamHttpReply& httpReply);

void clock_master_start (ArduinoHttpServer::StreamHttpReply& httpReply);

void clock_master_read (ArduinoHttpServer::StreamHttpReply& httpReply, char* data);

void  clock_master_get_status(ArduinoHttpServer::StreamHttpReply& httpReply, long& rc_ram_usage);

void clock_master_write (ArduinoHttpServer::StreamHttpReply& httpReply, char* data, long data_length, long& rc_ram_usage, bool& free_running);

bool clock_master_changeip(ArduinoHttpServer::StreamHttpReply& httpReply, char* data);

#endif
