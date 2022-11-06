#include "Controlador/Controlador.h"

Controlador::Controlador()
{
}

Controlador::Controlador(double kp, double ki, double kd)
{
	_kp = kp;
	_ki = ki;
	_kd = kd;
}

//! testar criaçao de objeto
void Controlador::Config_motor_esq(unsigned char *pins)
{
	motor_esq = Motor_drive(pins[0], pins[1], pins[2], pins[3]);
}

//! testar criaçao de objeto
void Controlador::Config_motor_dir(unsigned char *pins)
{
	motor_dir = Motor_drive(pins[0], pins[1], pins[2], pins[3]);
}

void Controlador::Config_encoder_esq(unsigned char pin_interrupt)
{
	encoder_esq = Encoder(pin_interrupt);
}

void Controlador::Config_encoder_dir(unsigned char pin_interrupt)
{
	encoder_dir = Encoder(pin_interrupt);
}

//! testar criaçao de objeto
void Controlador::Config_sensor_linha(unsigned char *pins)
{
	sensor_linha = Sensor_linha(pins);
}

//! testar criaçao de objeto
void Controlador::Config_sensor_esq(unsigned char pin)
{
	sensor_esq = Sensor_esq(pin);
}

//! testar criaçao de objeto
void Controlador::Config_sensor_dir(unsigned char pin)
{
	sensor_dir = Sensor_dir(pin);
}

void Controlador::Init()
{
	motor_dir.Init();
	motor_esq.Init();
	encoder_esq.Init();
	encoder_dir.Init();
	sensor_linha.Init();
	sensor_esq.Init();
	sensor_dir.Init();

}

void Controlador::Set_kp(double kp)
{
	_kp = kp;
}

void Controlador::Set_ki(double ki)
{
	_ki = ki;
}

void Controlador::Set_kd(double kd)
{
	_kd = kd;
}

void Controlador::Enable_motors_drives()
{
	motor_esq.Enable_drive();
	motor_dir.Enable_drive();
}

void Controlador::Disable_motors_drives()
{
	motor_esq.Disable_drive();
	motor_dir.Disable_drive();
}

//! estudar para implementar
void Controlador::Detec_motors_drives_fault()
{
}

void Controlador::Set_direction_forward()
{
	motor_esq.Set_motor_forward();
	motor_dir.Set_motor_forward();
}

void Controlador::Set_direction_reverse()
{
	motor_esq.Set_motor_reverse();
	motor_dir.Set_motor_reverse();
}

void Controlador::Set_motor_esq_speed(int speed)
{
	motor_esq.Set_speed(speed);
}

void Controlador::Set_motor_dir_speed(int speed)
{
	motor_dir.Set_speed(speed);
}

void Controlador::Check_current_motors_drives()
{

	double current_M_esq = motor_esq.Get_current_milliamps();
	double current_M_dir = motor_dir.Get_current_milliamps();

	//! definir valor de parada por corrente
	if (current_M_dir || current_M_esq >= 7)
	{
		Disable_motors_drives();
	}
}

double Controlador::calc_erro()
{
	double erro = 0;
	//? é possivel retirar o * para pegar uma cópia sem ferar a memoria?
	double *Leituras = sensor_linha.Read_line();
	for (unsigned int i = 0; i < 8; i++)
	{
		erro += Leituras[i] * pesos[i];
	}
	return erro;
}

void Controlador::calibration(){

	// Seguidor no preto
	int v_min_esq = sensor_esq.find_min();
	int v_min_dir = sensor_dir.find_min();

	Enable_motors_drives();
	Set_direction_forward();
	
	// Joga para o branco em relação a ponta do seguidor
	//TODO ajustar o tempo e velocidade
	Set_motor_esq_speed(100);
	Set_motor_dir_speed(100);
	delay(300);
	Disable_motors_drives();
	

	// Seguidor no branco
	int v_max_esq = sensor_esq.find_max();
	int v_max_dir = sensor_dir.find_max();

	// Acha val médio

	double v_med_esq = (v_max_esq - v_min_esq) / 2;
	double v_med_dir = (v_max_dir - v_min_dir) / 2;


	Sensor_esq.setValorMed(v_med_esq);	
	Sensor_dir.setValorMed(v_med_dir);
}