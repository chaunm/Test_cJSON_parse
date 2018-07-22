/*
 ============================================================================
 Name        : MqttParser.c
 Author      : Chaunm
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mqtt_json_parse.h"

char* sampleConfigMessage = "{\n"\
		"\"id\": \"BOX0001\",\n"\
		"\"message_id\": 1864,\n"\
		"\"type\": \"config\",\n"\
		"\"parameter\": \"server_ip\",\n"\
		"\"data\": \"192.168.1.23\"\n"\
		"}";

char* sampleControlMessage = "{\n"\
		"\"id\": \"BOX0001\",\n"\
		"\"message_id\": 1865,\n"\
		"\"type\": \"control\",\n"\
		"\"parameter\": \"alarm\",\n"\
		"\"data\": \"off\"\n"\
		"}";

int main(void) {
	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
	puts(sampleConfigMessage);
	mqtt_json_parse_message(sampleConfigMessage, strlen(sampleConfigMessage));
	puts(sampleControlMessage);
	mqtt_json_parse_message(sampleControlMessage, strlen(sampleControlMessage));
	return EXIT_SUCCESS;
}
