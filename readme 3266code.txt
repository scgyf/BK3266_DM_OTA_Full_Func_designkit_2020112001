BK3266_DM_OTA_Full_Func_Na：
R：svn上给国芯的全代码

BK3266_DM_OTA_Full_Func_Na_20190730_518.rar
BK3266_DM_OTA_Full_Func_Na_lib：
bk3266_dm_designkit_2020102401：
R：陈裕发过来的full、lib、sdk，用于国芯

BK3266_DM_OTA_Full_Func
BK3266_DM_Full_Func_lib_2020102101：
BK3266_DM_OTA_Full_Func_designkit_2020112001：
R：徐彪发过来的full、lib、sdk版本，用于佳祺通讯
T：先移植国芯底层，做到稳定的30ms
R1：移植le以外部分，编译通过，保留备份
BK3266_DM_Full_Func_lib_2020102101_1.rar

R2：移植、整合国芯蓝牙(ble+bt)程序，并测试2.5小时正常(8m距离转弯)
        形成lib、sdk
        保留备份，
        BK3266_DM_Full_Func_lib_2020102101_2.rar
        BK3266_DM_OTA_Full_Func_designkit_2020112001_2.rar

T:解决无moredata问题
R：开启moredata功能，收包不控制，推表盘128K数据并写flash，80s到90s的时间。
      保留备份BK3266_DM_Full_Func_lib_2020102101_3.rar ///201202 11:33

T:解决ancs长包丢数据问题(总长172bytes的数据，实际收到136bytes，末尾的数据丢了) ///201202 11:37
R:修改le_gatt.c "i"临时变量改动引起便宜出错；修改后，将le_gatt.c放到库里面
   保留备份BK3266_DM_Full_Func_lib_2020102101_4.rar ///201202 11:33

T：1、修复latency功能 
     2、解决安装手机send fail问题 
     3、增加moredata_enable功能
R： 1、将pkd时，latency强制设为0取消，修复latency问题
      2、连接16s后，设置latency；手机app增加打印，多次测试send fail没出现
      3、底层增加moredata_enable变量，控制是否开启MD功能，默认开启
           应用层增加MOREDATA_DISABLE
      保留备份BK3266_DM_Full_Func_lib_2020102101_5.rar 
      SDK备份BK3266_DM_OTA_Full_Func_designkit_2020112001_5.rar ；没发给客户

T：解决LEconnection_Disconnect() //le_connection.c L4239 //此处断开时，上层没有回调的问题
R：增加上层回调；同时查出上层调用此函数，没有清断开标志
R：修改ａｐｐ程序，解决回连不成功的问题 //201218 09:54

T：增加更新连接参数的回调功能　//201218 09:54
R:  OK，le_cts_app.c增加一函数

R：修改开始时handle=1，解决值变问题,发库给客户//201222 13:36
     保留备份BK3266_DM_Full_Func_lib_2020102101_6.rar 
                  BK3266_DM_OTA_Full_Func_designkit_2020112001_6.rar

T：客户反馈概率性问题，///210103 16:09
     1、推表盘容易断线，10s后真复位 
     2、应用过程中出现异常断线，然后不广播、连接不上等问题
R： 1、实现容易复现步骤，推表盘时，苹果手机app每隔10s推送一条消息。(**可用于后续查找跟本原因，估计时间出问题**）
      2、断线后不走正常断开流程，增加异常断开流程，实现ble 6s回连，待客户测试确认。
      BK3266_DM_Full_Func_lib_2020102101_7.rar //保留备份
A、
3266 gattt收、发接口///2021 0105
1、获取接收到的数据
u_int8 GATTserver_Write_Command(u_int16 attrib_handle, u_int8* p_attrib_value,u_int16 length) ///le_gatt_server.c L1645
2、发送数据
t_GATT_error GATTserver_Characteristic_Write_Local_Value(u_int16 char_val_handle,u_int16 length, u_int8* p_attrib_value) ///le_gatt_server.c L1685

B、3266 Rf pin(Tx、Rx、Sync）///2021 0105 1347
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

T:整理，///210108 1501
1、解决看门狗复位，回连不上的问题（上层修改）
2、修改rx time out的interval参数
3、增加check RF，看门狗复位功能；取消底层其他位置喂狗
      LE_LL_Sleep()增加io口翻转
4、推表盘时切到classic bt
R:保留备份BK3266_DM_Full_Func_lib_2020102101_80.rar

R:1、增加lost_event_flag处理,解决latency断线问题
   2、底层也增加是否lacency判断，app_ble_latency_pass_enable()
   3、le_mode标志改为LC_Is_Tabasco_Asleep()写flash
R:保留备份BK3266_DM_Full_Func_lib_2020102101_81.rar
HW_set_rx_mode(0x03); //全扫描

R：调试库，加打印查找，搜服务时，不会服务信息的问题 ///210114 14:57
保留备份BK3266_DM_Full_Func_lib_2020102101_82.rar

/*200114 18:51*/
这几天iphone12 ios回连不上的问题，抓包分析是由于蓝牙模块不回服务信息引起的。
不回服务信息的原因是长包组包异常时，无法再正常解析数据。
已经针对修改，正测试验证。
保留备份BK3266_DM_Full_Func_lib_2020102101_83.rar

///200115 10:49
R：1、只留下组包continue_flag置1、清零的打印
     2、底层，针对sn出错，手机不发包引起断线进行修改
     3、上层，优化ancs、uuid服务交互数据的速度
保留备份BK3266_DM_Full_Func_lib_2020102101_84.rar

///210119 10:50
R：徐彪整合的lib，直接编译后，挂机13小时不断线
保留备份BK3266_DM_Full_Func_lib_2021011601.rar 

///
再次关机13小时不断线，苹果手机
BK3266_DM_Full_Func_lib_2021011601_2.rar

///210122 19:59
各位，这两天ble情况如下，
1、针对蓝牙连接状态显示不对问题，已进行修改，待复测
2、推送表盘功能大概率正常，会出现小概率断线，不好复现，需要继续分析确认问题
3、概率性反复断线回连问题，已针对修改，待测试确认
     A、latency时，discover数据、发送数据较慢，已修改
     B、发现苹果手机回连时，加密流程失败(smp pairing failed)，待加强测试后，再修改

R：1、缩减ble moredata
      2、推表盘时，取消sleep
不易断线，保留备份BK3266_DM_Full_Func_lib_2021011601_5.rar

///210202 16:29
A、升级表盘变慢问题
需要抓下蓝牙数据包，确认下是手机发数据慢了，还是蓝牙模块变慢了

T：按3288解决不广播问题，进行修改
R：D:\tech_prj_2020\20_1119_3266_佳琪\bk3266_dm_designkit_2020102401\bk3266_dm_designkit //修改上层

乃灿更改后发过来的lib： ///210208 10:26
BK3266_DM_Full_Func_lib_2021011601_7.rar
///210219 09:11
R：上次增加bt、ble切换反转，统计推表盘引起的5个问，并逐一分析对应解决
T:将对应更改整合到sdk上
1、ble连接成功后，sniffer模式推迟10s
 sniffmode_wakeup_dly = 1000; ///add 200219 

2、推表盘时，bt完全断开后，才和app交互数据
(bt_flag1_is_set( APP_FLAG_ACL_CONNECTION))

3、替换tws工程 rf校准文件，将校准时间改为200us
bk3000_rf.c
bk3266_calibration.c
#define CFG_CALIB_DELAY_US              (200)  ///change 210219

4、irq excepiton异常处理，增加打印、保持数据后，再重启
异常看门狗复位前，同时打开PRINT_BA22_EXCEPTION的打印
app_exception.c

T：整合sdk
R:
1、上层增加如下两个函数，编译通过
void ble_latency_disable_1s(void)
uint32 app_dial_updating(void)
app_get_best_offset() ///？？？
/********************************************************************************************************************************************************/
2、底层更改记录 ///210219
A、"updata_next_start_window"判断何时开启下一个窗口
if(p_connection->connection_bug_patch)  ///刚连接、更新连接间隔引起异常，
{
	///提前一个1.25ms
}
else
{
	///直接一个连接间隔或者提前一个1.25ms
}

B、debug_bit_cnt判断是否提前下一个窗口
if (BTtimer_Is_Expired_For_Time(p_connection->next_connect_event_start_time, current_clk - 4)) //超时时
case LE_NO_PKD //NO_PKD时

C、LEconnection_Set_Initial_Anchor_Point_Obtained(p_connection,1);
case LE_PKD :且crc_error为0时，置1

D、current_intra_slot = HW_get_intraslot_offset();
HW_get_intraslot_offset(void) { return mGetHWEntry32(JAL_INTRASLOT_OFFSET);  ///ceva dm.pdf P43页
 if (mGetHWEntry(JAL_LE_RX_RFU_DATA_HI) & 1)
/*LEconnection_Check_Intraslot_Offset()*/
/********************************************************************************************************************************************************/

R：压缩后改名为BK3266_DM_OTA_Full_Func_designkit_20210219.rar
发送给博芯张伟




 
