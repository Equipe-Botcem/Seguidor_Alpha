#ifndef _SEGUIDOR_
#define _SEGUIDOR_

#include "Driver.h"
#include "motor_drive.h"
#include "Sensor.h"
#include "BluetoothSerial.h"
#include "Controlador.h"
#include "Sensor_linha.h"


class Seguidor{

public:

	// Constrtutores
	Seguidor();

	// Configs e inits
	void Config_led_esq(unsigned char pin);
	void Config_led_dir(unsigned char pin);
	void Config_motors(unsigned char *pins_dir, unsigned char *pins_esq);
	void Config_sensor_linha(unsigned char *pins);
	void Config_sensor_esq(unsigned char pin);
	void Config_sensor_dir(unsigned char pin);
	void Config_pins();
	void initBluetooth();
	void Init();

	// Sets parametros
	void set_handler();

	// Other functions 
	void Behavior();
	void Stop();
	void Run();
	void Enable_motors_drives();
	void Disable_motors_drives();
	void calibration();
	void controle();
	void comunica_serial();
	bool Check_stop();
	bool Check_latEsq();
	bool isEnd();
	bool isStart();
	void stopRoutine();


	void teste();
	void mapeamento();


	String command = "";
	BluetoothSerial SerialBT;

private:

	enum Comando {SET = 0, STOP, RUN, CALIBRACAO};

	//-----------Atributos-----------//

	bool end = false;
	bool start = false;

	// Timers 
	unsigned long startTime = 0;
	unsigned long stopTime = 0;
	unsigned long samplingTime = 0;
	unsigned long latEsqTime = 0;


	//-----------Objetos-----------//
	Driver driver;
	Sensor_linha sensor_linha;
	Sensor sensor_esq;
	Sensor sensor_dir;
	Controlador controlador;
	

	//-----------Pinos-----------//
	// Motor 2
	unsigned char pins_motor_drive_esq[4] = {2,15,18,21};
	unsigned char led_dir = 12;

	// Motor 1
	unsigned char pins_motor_drive_dir[4] = {22,5,4,19};
	unsigned char led_esq = 23;

	// Sensores 
	unsigned char pins_sensor_linha[8] = {39,35,36,14,25,26,27,32};
	unsigned char pin_sensor_esq = 13;
	unsigned char pin_sensor_dir = 33;

	// Outros
	unsigned char bateria = 34;
	unsigned char led1 = 23;
	unsigned char led2 = 12;

	

};

#endif