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
		"\"parameter\": \"temperature_threshold\",\n"\
		"\"data\":\n"\
		"{\n"\
		"\"index\": 2,\n"\
		"\"temperature\": 25\n"\
		"}\n"\
		"}";

char* sampleControlMessage = "{\n"\
		"\"id\": \"BOX0001\",\n"\
		"\"message_id\": 1865,\n"\
		"\"type\": \"control\",\n"\
		"\"parameter\": \"aircon\",\n"\
		"\"data\":\n"\
		"{\n"\
		"\"index\": 2,\n"\
		"\"power\": \"on\",\n"\
		"\"temperature\": 25\n"\
		"}\n"\
		"}";

int main(void) {
	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
	puts(sampleConfigMessage);
	mqtt_json_parse_message(sampleConfigMessage, strlen(sampleConfigMessage));
	puts(sampleControlMessage);
	mqtt_json_parse_message(sampleControlMessage, strlen(sampleControlMessage));
	return EXIT_SUCCESS;
}
