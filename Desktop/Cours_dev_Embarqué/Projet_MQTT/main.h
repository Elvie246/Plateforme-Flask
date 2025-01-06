//empeche le fihier d'etre inclut plusieurs fois dans le même fichier source
// mqtt.h
#ifndef MQTT_H
#define MQTT_H

void on_connect(struct mosquitto *mosq, void *obj, int rc);
void on_message(struct mosquitto *mosq, void *obj, const struct mosquitto_message *msg);

#endif

