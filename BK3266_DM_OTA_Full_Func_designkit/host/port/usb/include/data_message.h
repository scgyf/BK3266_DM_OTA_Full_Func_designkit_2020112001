/****************************************************************************
* ���ƣ����ݽṹ����
* ���ܣ�
****************************************************************************/
//#define __PACKED_PRE__
//#define __PACKED_POST__
//#define __PACKED_POST__  __attribute__((packed))

typedef struct
{
	unsigned char		int_mode;
	unsigned char		rw_mode;
	unsigned char		addr10_flag;
	unsigned short int	send_addr;
	unsigned char		remain_data_cnt;
	unsigned char		addr_idx;
	unsigned char		addr_tx_done;
	unsigned char		trans_done;
	unsigned char		repeat_start;	
	unsigned char		ack_check;	
} i2c_message;

typedef struct
{
 	unsigned char		txint_mode;
	unsigned char		rxint_mode;
   	unsigned char		tx_remain_data_cnt;
	unsigned char		rx_remain_data_cnt;
	unsigned char		master;
	unsigned char		nssmd;
	unsigned char		trans_done;
} spi_message;

typedef struct
{
	unsigned char	rxfifo_level;
	unsigned char	txfifo0_level;
	unsigned char	txfifo1_level;
	unsigned char	txfifo2_level;
	unsigned char	trans_done;
	int  		remain_data_cnt;
} i2s_message;



