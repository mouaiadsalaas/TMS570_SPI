
/* USER CODE BEGIN (0) */
/* USER CODE END */

/* Include Files */

#include "sys_common.h"
#include "system.h"

/* USER CODE BEGIN (1) */
#include "spi.h"
/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */
//uint16 TX_Data_Master[16] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10 };
uint16 TX_Data_Master[16] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
uint16 TX_Data_Slave[16]  = { 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20 };
uint16 RX_Data_Master[16] = { 0 };
uint16 RX_Data_Slave[16]  = { 0 };
/* USER CODE END */

void main(void)
{
/* USER CODE BEGIN (3) */

    spiDAT1_t dataconfig1_t;

    dataconfig1_t.CS_HOLD = FALSE;
    dataconfig1_t.WDEL    = TRUE;

    dataconfig1_t.DFSEL   = SPI_FMT_0;//from here we can change clock mode
    dataconfig1_t.CSNR    = 0xFE;


    /* Enable CPU Interrupt through CPSR */
    _enable_IRQ();

    /* Initialize SPI Module Based on GUI configuration
     * SPI3 - Master ( SIMO, SOMI, CLK, CS0 )
     * SPI2 - Slave  ( SIMO, SOMI, CLK, CS0 )
     * */
    spiInit();

    //because we are using interrupt mode of spi recieve it is enough to write this for one time
    /* Initiate SPI2 Transmit and Receive through Interrupt Mode */
    spiSendAndGetData(spiREG2, &dataconfig1_t, 16, TX_Data_Slave, RX_Data_Slave);

    while(1){


        /* Initiate SPI1 Transmit and Receive through Polling Mode*/
        spiTransmitAndReceiveData(spiREG3, &dataconfig1_t, 16, TX_Data_Master, RX_Data_Master);
    }
/* USER CODE END */
}

/* USER CODE BEGIN (4) */
/* USER CODE END */
