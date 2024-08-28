#include "System.h"
#include "stm32wlxx.h"

#define Flash_Latency_0 0x00000000U
#define Calibration_Timing_0 0
#define ClockSource_MSI 0x00000000U

static void System_SetFlashLatency(uint32_t Latency);
static void System_SetVoltageScaling(uint32_t VoltageScaling);
static void System_SetClockMSI(uint32_t RangeMSI, uint32_t CalibrationTiming, uint32_t ClockSource);
static void System_InitBackupDomain(void);
static void System_InitPeriphClkSources(void);

void System_init(void)
{
    System_SetFlashLatency(Flash_Latency_0);
    System_SetVoltageScaling(PWR_CR1_VOS_1);
    System_SetClockMSI(RCC_CR_MSIRANGE_8, Calibration_Timing_0, ClockSource_MSI);

    System_InitBackupDomain();

    // Configure deep sleep mode (stop2)
    PWR->CR1 &= ~(PWR_CR1_LPMS_Msk);
    PWR->CR1 |= PWR_CR1_LPMS_1;

    //selecting MSI as a default clock after waking up
    RCC->CFGR &= ~(RCC_CFGR_STOPWUCK);

    //setting prescalers for APB1 and APB2 buses (not prescaled)
    RCC->CFGR &= ~(RCC_CFGR_PPRE1_Msk);
    RCC->CFGR &= ~(RCC_CFGR_PPRE2_Msk);


	System_InitPeriphClkSources();

    RCC->CIER |= RCC_CIER_HSERDYIE | RCC_CIER_MSIRDYIE; //enable interrupts from HSERDY and MSIRDY flags setting
    uint32_t priorityGroup = __NVIC_GetPriorityGrouping();
    NVIC_SetPriority(RCC_IRQn, NVIC_EncodePriority(priorityGroup, 0, 0));
    NVIC_EnableIRQ(RCC_IRQn);
}


static void System_SetFlashLatency(uint32_t Latency)
{
    MODIFY_REG(FLASH->ACR, FLASH_ACR_LATENCY, Latency);
    while(READ_BIT(FLASH->ACR, FLASH_ACR_LATENCY) != 0UL)
    {

    }
}

static void System_SetVoltageScaling(uint32_t VoltageScaling)
{
    MODIFY_REG(PWR->CR1, PWR_CR1_VOS, VoltageScaling);
    while((READ_BIT(PWR->SR2, PWR_SR2_VOSF) == (PWR_SR2_VOSF)) ? 1UL : 0UL)
    {

    }
}

static void System_SetClockMSI(uint32_t RangeMSI, uint32_t CalibrationTiming, uint32_t ClockSource)
{
    SET_BIT(RCC->CR, RCC_CR_MSION);
    while(((READ_BIT(RCC->CR, RCC_CR_MSIRDY) == (RCC_CR_MSIRDY)) ? 1UL : 0UL) != 1)
    {

    }
    SET_BIT(RCC->CR, RCC_CR_MSIRGSEL);
    MODIFY_REG(RCC->CR, RCC_CR_MSIRANGE, RangeMSI);
    MODIFY_REG(RCC->ICSCR, RCC_ICSCR_MSITRIM, CalibrationTiming << RCC_ICSCR_MSITRIM_Pos);
    MODIFY_REG(RCC->CFGR, RCC_CFGR_SW, ClockSource);
    while((READ_BIT(RCC->CFGR, RCC_CFGR_SWS)) != 0UL)
    {

    }
}

static void System_InitBackupDomain(void)
{

    //unlock write to RTC backup domain registers
    PWR->CR1 |= PWR_CR1_DBP;

	// If no RTC clock source has been selected, a backup domain reset must have occurred.
    if((RCC->BDCR & RCC_BDCR_BDRST_Msk) == 0 || (RCC->BDCR & RCC_BDCR_LSERDY) == 0)
	{
        //set LSE drive to low
        RCC->BDCR &= ~(RCC_BDCR_LSEDRV_Msk);

        //Enable LSE
        RCC->BDCR |= RCC_BDCR_LSEON;

        //wait for LSE to stabilise
		while (!(RCC->BDCR & RCC_BDCR_LSERDY))
		{
		}

        //select external LSE as source for RTC
        RCC->BDCR &= ~(RCC_BDCR_RTCSEL_Msk);
        RCC->BDCR |= RCC_BDCR_RTCSEL_0;

        //enable RTC
        RCC->BDCR |= RCC_BDCR_RTCEN;

        //enable RTC Buses for CPU1
        RCC->APB1ENR1 |= RCC_APB1ENR1_RTCAPBEN;

	}
}

static void System_InitPeriphClkSources(void)
{
	/* Selecting the system clock as the source for ADC */
	RCC->CCIPR &= ~(RCC_CCIPR_ADCSEL_Msk);
	RCC->CCIPR |= RCC_CCIPR_ADCSEL_Msk;

	//Selecting the system clock as the source clock for I2C
	RCC->CCIPR &= ~(RCC_CCIPR_I2C1SEL_Msk);
    RCC->CCIPR |= RCC_CCIPR_I2C1SEL_0;

	//Selecting the system clock as the source for LPUART
	RCC->CCIPR &= ~(RCC_CCIPR_LPUART1SEL_Msk);
	RCC->CCIPR |= RCC_CCIPR_LPUART1SEL_0;

	//Selecting the system clock as the source for UART
	RCC->CCIPR &= ~(RCC_CCIPR_USART2SEL_Msk);
	RCC->CCIPR |= RCC_CCIPR_USART2SEL_0;
}

void system_sleep(void)
{
    __WFI();
    return;
}