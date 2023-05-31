#ifndef _ENCODER_
#define _ENCODER_

class Encoder
{
private:
	unsigned char pin_a;
	static volatile int contador_a;

public:
	Encoder();
	Encoder(unsigned char a);
	~Encoder();

	void Init();
	static void Rotina();

	int Get_contador();
	void Reset();
};

#endif