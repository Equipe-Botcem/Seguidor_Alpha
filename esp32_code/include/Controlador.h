#ifndef _CONTROLADOR_
#define _CONTROLADOR_

#include "motor_drive.h"
#include "Sensor.h"
#include "Encoder.h"
#include "BluetoothSerial.h"


class Controlador{

public:

	// Constrtutores
	Controlador();

    void setControlador(float kp, float kd, float ki);

    void setKp(float kp);
    void setKd(float kd);
    void setKi(float ki);

    int calcRot(float erro);
    double I, erro_antigo;
    
private:
	
    float Kp;
	float Kd;
    float Ki;


};

#endif