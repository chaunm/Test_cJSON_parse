/*
 * mqtt_json_parse.c
 *
 *  Created on: Jul 23, 2018
 *      Author: chaunm
 */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "mqtt_json_parse.h"
#include "mqtt_json_make.h"
#include "mqtt_json_type.h"
#include "cJSON.h"



/***********************************************************************************************************
 *                                        CONFIGURE MESSAGE PARSING                                        *
 ***********************************************************************************************************/
/* parse temperature threshold */
static mqtt_json_result_t mqtt_json_parse_conigure_temp_threshold(cJSON* jsonMessage)
{
	cJSON* tempThresJson;
	cJSON* tempJson;
	cJSON* indexJson;
	tempThresJson = cJSON_GetObjectItem(jsonMessage, "data");
	if (!cJSON_IsObject(tempThresJson))
		return MQTT_PARSE_DATA_ERROR;
	indexJson = cJSON_GetObjectItem(tempThresJson,  "index");
	if (!cJSON_IsNumber(indexJson))
		return MQTT_PARSE_DATA_ERROR;
	if ((indexJson->valueint > 4) || (indexJson->valueint < 1))
		return MQTT_PARSE_DATA_ERROR;
	tempJson = cJSON_GetObjectItem(tempThresJson,  "temperature");
	if (!cJSON_IsNumber(tempJson))
		return MQTT_PARSE_DATA_ERROR;
	printf("Temperature threshold index: %d, value %d\r\n", indexJson->valueint, tempJson->valueint);
	return MQTT_PARSE_SUCCESS;
}
/* Parse card ID configuration message */
static mqtt_json_result_t mqtt_json_parse_configure_card_id(cJSON* jsonMessage)
{
	cJSON* cardIdJson;
	cJSON* cardIdIndex;
	cJSON* cardId;
	cardIdJson = cJSON_GetObjectItem(jsonMessage, "data");
	if (!cJSON_IsObject(cardIdJson))
		return MQTT_PARSE_DATA_ERROR;
	cardIdIndex = cJSON_GetObjectItem(cardIdJson, "index");
	if (!cJSON_IsNumber(cardIdIndex))
		return MQTT_PARSE_DATA_ERROR;
	if ((cardIdIndex->valueint > 5) || (cardIdIndex->valueint < 1))
		return MQTT_PARSE_DATA_ERROR;
	cardId = cJSON_GetObjectItem(cardIdJson, "card_id");
	if ((!cJSON_IsString(cardId)) || (cardId->valuestring == NULL))
		return MQTT_PARSE_DATA_ERROR;
	if (strlen(cardId->valuestring) != 8)
		return MQTT_PARSE_DATA_ERROR;
	printf("Card Id index: %d, ID: %s\r\n", cardIdIndex->valueint, cardId->valuestring);
	return MQTT_PARSE_SUCCESS;
}

/* Parse battery threshold configuration message */
static mqtt_json_result_t mqtt_json_parse_configure_battery_threshold(cJSON* jsonMessage)
{
	cJSON* batteryThresJson;
	cJSON* indexJson;
	cJSON* batteryVoltJson;
	batteryThresJson = cJSON_GetObjectItem(jsonMessage, "data");
	if (!(cJSON_IsObject(batteryThresJson)))
		return MQTT_PARSE_DATA_ERROR;
	indexJson = cJSON_GetObjectItem(batteryThresJson, "index");
	if (!cJSON_IsNumber(indexJson))
		return MQTT_PARSE_DATA_ERROR;
	if ((indexJson->valueint > 4) || (indexJson->valueint < 1))
		return MQTT_PARSE_DATA_ERROR;
	batteryVoltJson = cJSON_GetObjectItem(batteryThresJson, "voltage");
	if (!cJSON_IsNumber(batteryVoltJson))
		return MQTT_PARSE_DATA_ERROR;
	printf("Battery threshold index: %d, threshold: %d\r\n", indexJson->valueint, batteryVoltJson->valueint);
	return MQTT_PARSE_SUCCESS;
}

/* Parse aircon set temperature configuration message */
static mqtt_json_result_t mqtt_json_parse_configure_aircon_temperature(cJSON* jsonMessage)
{
	cJSON* acTempJson;
	cJSON* indexJson;
	cJSON* tempJson;
	acTempJson = cJSON_GetObjectItem(jsonMessage, "data");
	if (!(cJSON_IsObject(acTempJson)))
		return MQTT_PARSE_DATA_ERROR;
	indexJson = cJSON_GetObjectItem(acTempJson, "index");
	if (!cJSON_IsNumber(indexJson))
		return MQTT_PARSE_DATA_ERROR;
	if ((indexJson->valueint > 5) || (indexJson->valueint < 1))
		return MQTT_PARSE_DATA_ERROR;
	tempJson = cJSON_GetObjectItem(acTempJson, "temperature");
	if (!cJSON_IsNumber(tempJson))
		return MQTT_PARSE_DATA_ERROR;
	printf("aircon set temp index: %d, threshold: %d\r\n", indexJson->valueint, tempJson->valueint);
	return MQTT_PARSE_SUCCESS;
}

/* Parse configuration message */
static mqtt_json_result_t mqtt_json_parse_configure_message(cJSON* jsonMessage)
{
	cJSON *jsonParameter;
	cJSON *jsonMsgData;
	jsonParameter = cJSON_GetObjectItem(jsonMessage, "parameter");
	if (cJSON_IsString(jsonParameter) && (jsonParameter->valuestring != NULL))
	{
		if (!strcmp(jsonParameter->valuestring, "id"))
		{
			jsonMsgData = cJSON_GetObjectItem(jsonMessage, "data");
			if (cJSON_IsString(jsonMsgData) && (jsonMsgData->valuestring != NULL))
			{
				printf("Configure param: %s, value: %s\r\n", jsonParameter->valuestring, jsonMsgData->valuestring);
			}
		}
		else if (!strcmp(jsonParameter->valuestring, "temperature_threshold"))
		{
			return mqtt_json_parse_conigure_temp_threshold(jsonMessage);
		}
		else if (!strcmp(jsonParameter->valuestring, "card_id"))
		{
			return mqtt_json_parse_configure_card_id(jsonMessage);
		}
		else if (!strcmp(jsonParameter->valuestring, "phase_threshold_voltage"))
		{
			jsonMsgData = cJSON_GetObjectItem(jsonMessage, "data");
			if (cJSON_IsNumber(jsonMsgData))
			{
				printf("Configure param: %s, value: %d\r\n", jsonParameter->valuestring, jsonMsgData->valueint);
			}
		}
		else if (!strcmp(jsonParameter->valuestring, "battery_threshold"))
		{
			return mqtt_json_parse_configure_battery_threshold(jsonMessage);
		}
		else if (!strcmp(jsonParameter->valuestring, "aircon_temp"))
		{
			return mqtt_json_parse_configure_aircon_temperature(jsonMessage);
		}
		else if (!strcmp(jsonParameter->valuestring, "device_ip"))
		{
			jsonMsgData = cJSON_GetObjectItem(jsonMessage, "data");
			if (cJSON_IsString(jsonMsgData) && (jsonMsgData->valuestring != NULL))
			{
				printf("Configure param: %s, value: %s\r\n", jsonParameter->valuestring, jsonMsgData->valuestring);
			}
		}
		else if (!strcmp(jsonParameter->valuestring, "subnet_mask"))
		{
			jsonMsgData = cJSON_GetObjectItem(jsonMessage, "data");
			if (cJSON_IsString(jsonMsgData) && (jsonMsgData->valuestring != NULL))
			{
				printf("Configure param: %s, value: %s\r\n", jsonParameter->valuestring, jsonMsgData->valuestring);
			}
		}
		else if (!strcmp(jsonParameter->valuestring, "gateway"))
		{
			jsonMsgData = cJSON_GetObjectItem(jsonMessage, "data");
			if (cJSON_IsString(jsonMsgData) && (jsonMsgData->valuestring != NULL))
			{
				printf("Configure param: %s, value: %s\r\n", jsonParameter->valuestring, jsonMsgData->valuestring);
			}
		}
		else if (!strcmp(jsonParameter->valuestring, "server_ip"))
		{
			jsonMsgData = cJSON_GetObjectItem(jsonMessage, "data");
			if (cJSON_IsString(jsonMsgData) && (jsonMsgData->valuestring != NULL))
			{
				printf("Configure param: %s, value: %s\r\n", jsonParameter->valuestring, jsonMsgData->valuestring);
			}
		}
		else
			return MQTT_PARSE_PARAM_ERROR;
	}
	else
		return MQTT_PARSE_PARAM_ERROR;
	return MQTT_PARSE_SUCCESS;
}

/***********************************************************************************************************
 *                                        CONTROL MESSAGE PARSING                                          *
 ***********************************************************************************************************/
/* Parse control door data */
static mqtt_json_result_t mqtt_json_parse_control_door(char* data)
{
	if (!strcmp(data, "open"))
	{
		printf("door open command succeed\r\n");
	}
	else if (!strcmp(data, "close"))
	{
		printf("door close command succeed\r\n");
	}
	else
		return MQTT_PARSE_DATA_ERROR;
	return MQTT_PARSE_SUCCESS;
}

/* Parse control alarm data */
static mqtt_json_result_t mqtt_json_parse_control_alarm(char* data)
{
	if (!strcmp(data, "on"))
	{
		printf("alarm on command succeed\r\n");
	}
	else if (!strcmp(data, "off"))
	{
		printf("alarm off command succeed\r\n");
	}
	else
		return MQTT_PARSE_DATA_ERROR;
	return MQTT_PARSE_SUCCESS;
}

/* Parse control fan data */
static mqtt_json_result_t mqtt_json_parse_control_fan(char* parameter, char* data)
{
	if (!strcmp(data, "on"))
	{
		printf("fan %s on command succeed\r\n", parameter);
	}
	else if (!strcmp(data, "off"))
	{
		printf("fan %s off command succeed\r\n", parameter);
	}
	else
		return MQTT_PARSE_DATA_ERROR;
	return MQTT_PARSE_SUCCESS;
}

/* Parse aircon control message */
static mqtt_json_result_t mqtt_json_parse_control_aircon(cJSON* jsonMessage)
{
	cJSON* airconCtrlJson;
	cJSON* powerJson;
	cJSON* temperatureJson;
	cJSON* indexJson;
	airconCtrlJson = cJSON_GetObjectItem(jsonMessage, "data");
	if (!(cJSON_IsObject(airconCtrlJson)))
		return MQTT_PARSE_DATA_ERROR;
	indexJson = cJSON_GetObjectItem(airconCtrlJson, "index");
	if (!cJSON_IsNumber(indexJson))
		return MQTT_PARSE_DATA_ERROR;
	if ((indexJson->valueint > 2) || (indexJson->valueint < 1))
		return MQTT_PARSE_DATA_ERROR;
	powerJson = cJSON_GetObjectItem(airconCtrlJson, "power");
	if (!cJSON_IsString(powerJson))
		return MQTT_PARSE_DATA_ERROR;
	if ((strcmp(powerJson->valuestring, "on") && strcmp(powerJson->valuestring, "off")))
		return MQTT_PARSE_DATA_ERROR;
	temperatureJson = cJSON_GetObjectItem(airconCtrlJson, "temperature");
	if (!cJSON_IsNumber(temperatureJson))
		return MQTT_PARSE_DATA_ERROR;
	printf("Aircon control index: %d\r\n", indexJson->valueint);
	printf("Power: %s, temperature: %d\r\n", powerJson->valuestring, temperatureJson->valueint);
	return MQTT_PARSE_SUCCESS;
}

/* parse control message */
static mqtt_json_result_t mqtt_json_parse_control_message(cJSON* jsonMessage)
{
	cJSON *jsonParameter;
	cJSON *jsonMsgData;
	jsonParameter = cJSON_GetObjectItem(jsonMessage, "parameter");
	if (cJSON_IsString(jsonParameter) && (jsonParameter->valuestring != NULL))
	{
		if (!strcmp(jsonParameter->valuestring, "door"))
		{
			jsonMsgData = cJSON_GetObjectItem(jsonMessage, "data");
			if (cJSON_IsString(jsonMsgData) && (jsonMsgData->valuestring != NULL))
			{
				printf("Control param: %s, value: %s\r\n", jsonParameter->valuestring, jsonMsgData->valuestring);
				return mqtt_json_parse_control_door(jsonMsgData->valuestring);
			}
			else
				return MQTT_PARSE_DATA_ERROR;
		}
		else if (!strcmp(jsonParameter->valuestring, "alarm"))
		{
			jsonMsgData = cJSON_GetObjectItem(jsonMessage, "data");
			if (cJSON_IsString(jsonMsgData) && (jsonMsgData->valuestring != NULL))
			{
				printf("Control param: %s, value: %s\r\n", jsonParameter->valuestring, jsonMsgData->valuestring);
				return mqtt_json_parse_control_alarm(jsonMsgData->valuestring);
			}
			else
				return MQTT_PARSE_DATA_ERROR;
		}
		else if (!strcmp(jsonParameter->valuestring, "fan_1"))
		{
			jsonMsgData = cJSON_GetObjectItem(jsonMessage, "data");
			if (cJSON_IsString(jsonMsgData) && (jsonMsgData->valuestring != NULL))
			{
				printf("Control param: %s, value: %s\r\n", jsonParameter->valuestring, jsonMsgData->valuestring);
				return mqtt_json_parse_control_fan(jsonParameter->valuestring, jsonMsgData->valuestring);
			}
			else
				return MQTT_PARSE_DATA_ERROR;
		}
		else if (!strcmp(jsonParameter->valuestring, "fan_2"))
		{
			jsonMsgData = cJSON_GetObjectItem(jsonMessage, "data");
			if (cJSON_IsString(jsonMsgData) && (jsonMsgData->valuestring != NULL))
			{
				printf("Control param: %s, value: %s\r\n", jsonParameter->valuestring, jsonMsgData->valuestring);
				return mqtt_json_parse_control_fan(jsonParameter->valuestring, jsonMsgData->valuestring);
			}
			else
				return MQTT_PARSE_DATA_ERROR;
		}
		else if (!strcmp(jsonParameter->valuestring, "aircon"))
		{
			return mqtt_json_parse_control_aircon(jsonMessage);
		}
		else
			return MQTT_PARSE_PARAM_ERROR;
	}
	else
		return MQTT_PARSE_PARAM_ERROR;
	return MQTT_PARSE_SUCCESS;
}

/* Parse message receive from MQTT input topic */
void mqtt_json_parse_message(char* message, unsigned int length)
{
	cJSON *jsonMessage;
	cJSON *jsonBoxId;
	cJSON *jsonMsgId;
	cJSON *jsonMsgType;
	mqtt_json_result_t result = MQTT_PARSE_SUCCESS;
	printf("Parse message with length: %d\r\n", length);

	char* responseMessage;
	if ((message == NULL) || (length == 0))
		return;
	char* procBuffer = (char*)malloc(length + 1);
	memcpy(procBuffer, message, length);
	procBuffer[length] = 0;
	jsonMessage = cJSON_Parse(procBuffer);
	if (jsonMessage == NULL)
	{
		result = MQTT_PARSE_MESSAGE_ERROR;
		goto END_PARSE;
	}
	jsonBoxId = cJSON_GetObjectItem(jsonMessage, "id");
	if(cJSON_IsString(jsonBoxId) && (jsonBoxId->valuestring != NULL))
	{
		printf("BOX ID: %s\r\n", jsonBoxId->valuestring);
	}
	else
	{
		result = MQTT_PARSE_BOXID_ERROR;
		goto END_PARSE;
	}
	jsonMsgId = cJSON_GetObjectItem(jsonMessage, "message_id");
	if(cJSON_IsNumber(jsonMsgId))
	{
		printf("Message ID: %d\r\n", jsonMsgId->valueint);
	}
	else
	{
		result = MQTT_PARSE_MSGID_ERROR;
		goto END_PARSE;
	}
	jsonMsgType = cJSON_GetObjectItem(jsonMessage, "type");
	if (cJSON_IsString(jsonMsgType) && (jsonMsgType->valuestring != NULL))
	{
		printf("Message Type: %s\r\n", jsonMsgType->valuestring);
	}
	else
	{
		result = MQTT_PARSE_TYPE_ERROR;
		goto END_PARSE;
	}
	if (!strcmp(jsonMsgType->valuestring, "config"))
	{
		printf("Parse configuration message\r\n");
		result = mqtt_json_parse_configure_message(jsonMessage);
	}
	else if (!strcmp(jsonMsgType->valuestring, "control"))
	{
		printf("Parse control message \r\n");
		result = mqtt_json_parse_control_message(jsonMessage);
	}
	else if (!strcmp(jsonMsgType->valuestring, "reset"))
	{
		printf("Resetting ...\r\n");
	}
	else
		result = MQTT_PARSE_TYPE_ERROR;

	END_PARSE:
	if ((result != MQTT_PARSE_MESSAGE_ERROR) && (result != MQTT_PARSE_BOXID_ERROR) && (result != MQTT_PARSE_MSGID_ERROR))
	{
		if (result == MQTT_PARSE_SUCCESS)
			responseMessage = mqtt_json_make_response(jsonBoxId->valuestring, jsonMsgId->valueint, result);
		else
			responseMessage = mqtt_json_make_response(jsonBoxId->valuestring, jsonMsgId->valueint, result);
		if (responseMessage != NULL)
		{
			printf ("response:\n%s\r\n", responseMessage);
			free(responseMessage);
		}
	}
	cJSON_Delete(jsonMessage);
	free(procBuffer);
}
