BK3266_DM_OTA_Full_Func_Na��
R��svn�ϸ���о��ȫ����

BK3266_DM_OTA_Full_Func_Na_20190730_518.rar
BK3266_DM_OTA_Full_Func_Na_lib��
bk3266_dm_designkit_2020102401��
R����ԣ��������full��lib��sdk�����ڹ�о

BK3266_DM_OTA_Full_Func
BK3266_DM_Full_Func_lib_2020102101��
BK3266_DM_OTA_Full_Func_designkit_2020112001��
R����뷢������full��lib��sdk�汾�����ڼ���ͨѶ
T������ֲ��о�ײ㣬�����ȶ���30ms
R1����ֲle���ⲿ�֣�����ͨ������������
BK3266_DM_Full_Func_lib_2020102101_1.rar

R2����ֲ�����Ϲ�о����(ble+bt)���򣬲�����2.5Сʱ����(8m����ת��)
        �γ�lib��sdk
        �������ݣ�
        BK3266_DM_Full_Func_lib_2020102101_2.rar
        BK3266_DM_OTA_Full_Func_designkit_2020112001_2.rar

T:�����moredata����
R������moredata���ܣ��հ������ƣ��Ʊ���128K���ݲ�дflash��80s��90s��ʱ�䡣
      ��������BK3266_DM_Full_Func_lib_2020102101_3.rar ///201202 11:33

T:���ancs��������������(�ܳ�172bytes�����ݣ�ʵ���յ�136bytes��ĩβ�����ݶ���) ///201202 11:37
R:�޸�le_gatt.c "i"��ʱ�����Ķ�������˳����޸ĺ󣬽�le_gatt.c�ŵ�������
   ��������BK3266_DM_Full_Func_lib_2020102101_4.rar ///201202 11:33

T��1���޸�latency���� 
     2�������װ�ֻ�send fail���� 
     3������moredata_enable����
R�� 1����pkdʱ��latencyǿ����Ϊ0ȡ�����޸�latency����
      2������16s������latency���ֻ�app���Ӵ�ӡ����β���send failû����
      3���ײ�����moredata_enable�����������Ƿ���MD���ܣ�Ĭ�Ͽ���
           Ӧ�ò�����MOREDATA_DISABLE
      ��������BK3266_DM_Full_Func_lib_2020102101_5.rar 
      SDK����BK3266_DM_OTA_Full_Func_designkit_2020112001_5.rar ��û�����ͻ�

T�����LEconnection_Disconnect() //le_connection.c L4239 //�˴��Ͽ�ʱ���ϲ�û�лص�������
R�������ϲ�ص���ͬʱ����ϲ���ô˺�����û����Ͽ���־
R���޸ģ�����򣬽���������ɹ������� //201218 09:54

T�����Ӹ������Ӳ����Ļص����ܡ�//201218 09:54
R:  OK��le_cts_app.c����һ����

R���޸Ŀ�ʼʱhandle=1�����ֵ������,������ͻ�//201222 13:36
     ��������BK3266_DM_Full_Func_lib_2020102101_6.rar 
                  BK3266_DM_OTA_Full_Func_designkit_2020112001_6.rar

T���ͻ��������������⣬///210103 16:09
     1���Ʊ������׶��ߣ�10s���渴λ 
     2��Ӧ�ù����г����쳣���ߣ�Ȼ�󲻹㲥�����Ӳ��ϵ�����
R�� 1��ʵ�����׸��ֲ��裬�Ʊ���ʱ��ƻ���ֻ�appÿ��10s����һ����Ϣ��(**�����ں������Ҹ���ԭ�򣬹���ʱ�������**��
      2�����ߺ��������Ͽ����̣������쳣�Ͽ����̣�ʵ��ble 6s���������ͻ�����ȷ�ϡ�
      BK3266_DM_Full_Func_lib_2020102101_7.rar //��������
A��
3266 gattt�ա����ӿ�///2021 0105
1����ȡ���յ�������
u_int8 GATTserver_Write_Command(u_int16 attrib_handle, u_int8* p_attrib_value,u_int16 length) ///le_gatt_server.c L1645
2����������
t_GATT_error GATTserver_Characteristic_Write_Local_Value(u_int16 char_val_handle,u_int16 length, u_int8* p_attrib_value) ///le_gatt_server.c L1685

B��3266 Rf pin(Tx��Rx��Sync��///2021 0105 1347
void BK3000_GPIO_Initial (void) //driver_icu.c L970
{
   ...
   #if 1//def BEKEN_DEBUG
    BK3000_GPIO_6_CONFIG  = 1<<sft_GPIO_FUNCTION_ENABLE; // baseband rx bit (IC GPIO2)
    BK3000_GPIO_7_CONFIG  = 1<<sft_GPIO_FUNCTION_ENABLE; // baseband tx bit (IC GPIO3)

    BK3000_GPIO_20_CONFIG = 1<<sft_GPIO_FUNCTION_ENABLE; //sync find(IC GPIO13) ==(JTAG_TDI)
   
    BK3000_GPIO_GPIODCON |= 0x7f3f0;                    /// one bit for one gpio(test function)
    BK3000_GPIO_GPIODCON |= (1 << 6) | (1 << 7);   ///enable rf tr,rx //201125
    BK3000_GPIO_GPIODCON |= (1 << 20); //sync	
   #endif
   ...
}

T:����///210108 1501
1��������Ź���λ���������ϵ����⣨�ϲ��޸ģ�
2���޸�rx time out��interval����
3������check RF�����Ź���λ���ܣ�ȡ���ײ�����λ��ι��
      LE_LL_Sleep()����io�ڷ�ת
4���Ʊ���ʱ�е�classic bt
R:��������BK3266_DM_Full_Func_lib_2020102101_80.rar

R:1������lost_event_flag����,���latency��������
   2���ײ�Ҳ�����Ƿ�lacency�жϣ�app_ble_latency_pass_enable()
   3��le_mode��־��ΪLC_Is_Tabasco_Asleep()дflash
R:��������BK3266_DM_Full_Func_lib_2020102101_81.rar
HW_set_rx_mode(0x03); //ȫɨ��

R�����Կ⣬�Ӵ�ӡ���ң��ѷ���ʱ�����������Ϣ������ ///210114 14:57
��������BK3266_DM_Full_Func_lib_2020102101_82.rar

/*200114 18:51*/
�⼸��iphone12 ios�������ϵ����⣬ץ����������������ģ�鲻�ط�����Ϣ����ġ�
���ط�����Ϣ��ԭ���ǳ�������쳣ʱ���޷��������������ݡ�
�Ѿ�����޸ģ���������֤��
��������BK3266_DM_Full_Func_lib_2020102101_83.rar

///200115 10:49
R��1��ֻ�������continue_flag��1������Ĵ�ӡ
     2���ײ㣬���sn�����ֻ�������������߽����޸�
     3���ϲ㣬�Ż�ancs��uuid���񽻻����ݵ��ٶ�
��������BK3266_DM_Full_Func_lib_2020102101_84.rar

///210119 10:50
R��������ϵ�lib��ֱ�ӱ���󣬹һ�13Сʱ������
��������BK3266_DM_Full_Func_lib_2021011601.rar 

///
�ٴιػ�13Сʱ�����ߣ�ƻ���ֻ�
BK3266_DM_Full_Func_lib_2021011601_2.rar

///210122 19:59
��λ��������ble������£�
1�������������״̬��ʾ�������⣬�ѽ����޸ģ�������
2�����ͱ��̹��ܴ���������������С���ʶ��ߣ����ø��֣���Ҫ��������ȷ������
3�������Է������߻������⣬������޸ģ�������ȷ��
     A��latencyʱ��discover���ݡ��������ݽ��������޸�
     B������ƻ���ֻ�����ʱ����������ʧ��(smp pairing failed)������ǿ���Ժ����޸�

R��1������ble moredata
      2���Ʊ���ʱ��ȡ��sleep
���׶��ߣ���������BK3266_DM_Full_Func_lib_2021011601_5.rar

///210202 16:29
A���������̱�������
��Ҫץ���������ݰ���ȷ�������ֻ����������ˣ���������ģ�������

T����3288������㲥���⣬�����޸�
R��D:\tech_prj_2020\20_1119_3266_����\bk3266_dm_designkit_2020102401\bk3266_dm_designkit //�޸��ϲ�

�˲Ӹ��ĺ󷢹�����lib�� ///210208 10:26
BK3266_DM_Full_Func_lib_2021011601_7.rar
///210219 09:11
R���ϴ�����bt��ble�л���ת��ͳ���Ʊ��������5���ʣ�����һ������Ӧ���
T:����Ӧ�������ϵ�sdk��
1��ble���ӳɹ���snifferģʽ�Ƴ�10s
 sniffmode_wakeup_dly = 1000; ///add 200219 

2���Ʊ���ʱ��bt��ȫ�Ͽ��󣬲ź�app��������
(bt_flag1_is_set( APP_FLAG_ACL_CONNECTION))

3���滻tws���� rfУ׼�ļ�����У׼ʱ���Ϊ200us
bk3000_rf.c
bk3266_calibration.c
#define CFG_CALIB_DELAY_US              (200)  ///change 210219

4��irq excepiton�쳣�������Ӵ�ӡ���������ݺ�������
�쳣���Ź���λǰ��ͬʱ��PRINT_BA22_EXCEPTION�Ĵ�ӡ
app_exception.c

T������sdk
R:
1���ϲ�����������������������ͨ��
void ble_latency_disable_1s(void)
uint32 app_dial_updating(void)
app_get_best_offset() ///������
/********************************************************************************************************************************************************/
2���ײ���ļ�¼ ///210219
A��"updata_next_start_window"�жϺ�ʱ������һ������
if(p_connection->connection_bug_patch)  ///�����ӡ��������Ӽ�������쳣��
{
	///��ǰһ��1.25ms
}
else
{
	///ֱ��һ�����Ӽ��������ǰһ��1.25ms
}

B��debug_bit_cnt�ж��Ƿ���ǰ��һ������
if (BTtimer_Is_Expired_For_Time(p_connection->next_connect_event_start_time, current_clk - 4)) //��ʱʱ
case LE_NO_PKD //NO_PKDʱ

C��LEconnection_Set_Initial_Anchor_Point_Obtained(p_connection,1);
case LE_PKD :��crc_errorΪ0ʱ����1

D��current_intra_slot = HW_get_intraslot_offset();
HW_get_intraslot_offset(void) { return mGetHWEntry32(JAL_INTRASLOT_OFFSET);  ///ceva dm.pdf P43ҳ
 if (mGetHWEntry(JAL_LE_RX_RFU_DATA_HI) & 1)
/*LEconnection_Check_Intraslot_Offset()*/
/********************************************************************************************************************************************************/

R��ѹ�������ΪBK3266_DM_OTA_Full_Func_designkit_20210219.rar
���͸���о��ΰ




 
