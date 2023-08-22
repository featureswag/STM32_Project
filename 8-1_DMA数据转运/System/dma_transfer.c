#include "stm32f10x.h"                  // Device header

uint16_t DMA_Size_Bank;
void DMA_TRANSFER_Init(uint32_t DMA_Address_A, uint32_t DMA_Address_B, uint16_t DMA_Size)
{
    DMA_Size_Bank = DMA_Size;
    /* *
     * 1. RCC Enable DMA1 Clock (DMA1_Channel1)
        use DMA1_Channel1 to transfer data from Data_A to Data_B
     */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);

    /* *
    * 2. Initialize DMA1_Channel1
     */
    DMA_InitTypeDef DMA_InitStructure;
    DMA_InitStructure.DMA_PeripheralBaseAddr = DMA_Address_A;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
    DMA_InitStructure.DMA_MemoryBaseAddr = DMA_Address_B;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize = DMA_Size;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Enable;
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
    DMA_Init(DMA1_Channel1,&DMA_InitStructure);

    /* *
     * 3. DISABLE DMA1_Channel1
     */
    DMA_Cmd(DMA1_Channel1,DISABLE);
}

void DMA_TRANSFER_Enable(void)
{
    DMA_Cmd(DMA1_Channel1,DISABLE);
    DMA_SetCurrDataCounter(DMA1_Channel1,DMA_Size_Bank);
    DMA_Cmd(DMA1_Channel1,ENABLE);

    // wait for DMA transfer complete
    while(DMA_GetFlagStatus(DMA1_FLAG_TC1)==RESET);
    // clear DMA transfer complete flag
    DMA_ClearFlag(DMA1_FLAG_TC1);
}
