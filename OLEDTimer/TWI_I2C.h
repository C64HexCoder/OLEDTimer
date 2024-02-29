/*
 * TWI_I2C.h
 *
 * Created: 20/02/2024 23:16:00
 *  Author: יוסי שלי
 */ 


#ifndef TWI_I2C_H_
#define TWI_I2C_H_

#define SUCCESS 1
#define FAILED  0

class I2C 
{
	public:
		void I2C::Init();
		void I2C::Start();
		void I2C::Stop();
		void I2C::WaitBussy();
		void I2C::SendSLaveAddress();
}

#endif /* TWI_I2C_H_ */