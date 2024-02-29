/*
 * TWI_I2C.c
 *
 * Created: 20/02/2024 23:15:36
 *  Author: יוסי שלי
 */ 



void I2C::Init(long Scl,unsigned char Prescaler)
{
	TWBR = 0x02;
}
	
void I2C::Start()
{
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTA);
	WaitBussy()
		
	switch ((TWSR & 0xF8)) {
		case 0x08:
			return SUCCESS;
			break;
			
		default:
			return FAILED;
	}
}
	
void I2C::SendSLaveAddress(unsigned char adress)
{
	TWAR = adress;	
}
	
void I2C::WaitBussy()
{
	while (!(TWCR & (1 << TWINT)));
}
	
	