/*
*********************************************************************************************************
*                                                    LINUX-KERNEL
*                                        AllWinner Linux Platform Develop Kits
*                                                   Kernel Module
*
*                                    (c) Copyright 2006-2011, kevin.z China
*                                             All Rights Reserved
*
* File    : standby_clock.c
* By      : kevin.z
* Version : v1.0
* Date    : 2011-5-31 13:40
* Descript: ccmu process for platform standby;
* Update  : date                auther      ver     notes
*********************************************************************************************************
*/

#include "standby_i.h"


static __ccmu_reg_list_t   *CmuReg;;
static __u32    ccu_reg_back[7];
static __u32    cpu_freq;

//==============================================================================
// CLOCK SET FOR SYSTEM STANDBY
//==============================================================================




/*
*********************************************************************************************************
*                           standby_clk_init
*
*Description: ccu init for platform standby
*
*Arguments  : none
*
*Return     : result,
*
*Notes      :
*
*********************************************************************************************************
*/
__s32 standby_clk_init(void)
{
    CmuReg = (__ccmu_reg_list_t *)SW_VA_CCM_IO_BASE;

    /* backup pll registers */
    ccu_reg_back[0] = *(volatile __u32 *)&CmuReg->Pll1Ctl;
    ccu_reg_back[1] = *(volatile __u32 *)&CmuReg->Pll2Ctl;
    ccu_reg_back[2] = *(volatile __u32 *)&CmuReg->Pll3Ctl;
    ccu_reg_back[3] = *(volatile __u32 *)&CmuReg->Pll4Ctl;
    ccu_reg_back[4] = *(volatile __u32 *)&CmuReg->Pll5Ctl;
    ccu_reg_back[5] = *(volatile __u32 *)&CmuReg->Pll6Ctl;
    ccu_reg_back[6] = *(volatile __u32 *)&CmuReg->Pll7Ctl;

    return 0;
}


/*
*********************************************************************************************************
*                           standby_clk_exit
*
*Description: ccu exit for platform standby
*
*Arguments  : none
*
*Return     : result,
*
*Notes      :
*
*********************************************************************************************************
*/
__s32 standby_clk_exit(void)
{
    /* restore pll registers */
    *(volatile __u32 *)&CmuReg->Pll1Ctl = ccu_reg_back[0];
    *(volatile __u32 *)&CmuReg->Pll2Ctl = ccu_reg_back[1];
    *(volatile __u32 *)&CmuReg->Pll3Ctl = ccu_reg_back[2];
    *(volatile __u32 *)&CmuReg->Pll4Ctl = ccu_reg_back[3];
    *(volatile __u32 *)&CmuReg->Pll5Ctl = ccu_reg_back[4];
    *(volatile __u32 *)&CmuReg->Pll6Ctl = ccu_reg_back[5];
    *(volatile __u32 *)&CmuReg->Pll7Ctl = ccu_reg_back[6];

    return 0;
}


/*
*********************************************************************************************************
*                                     standby_clk_core2losc
*
* Description: switch core clock to 32k low osc.
*
* Arguments  : none
*
* Returns    : 0;
*********************************************************************************************************
*/
__s32 standby_clk_core2losc(void)
{
    CmuReg->SysClkDiv.AC328ClkSrc = 0;
    return 0;
}


/*
*********************************************************************************************************
*                                     standby_clk_core2hosc
*
* Description: switch core clock to 24M high osc.
*
* Arguments  : none
*
* Returns    : 0;
*********************************************************************************************************
*/
__s32 standby_clk_core2hosc(void)
{
    CmuReg->SysClkDiv.AC328ClkSrc = 1;
    return 0;
}


/*
*********************************************************************************************************
*                                     standby_clk_core2pll
*
* Description: switch core clock to core pll.
*
* Arguments  : none
*
* Returns    : 0;
*********************************************************************************************************
*/
__s32 standby_clk_core2pll(void)
{
    CmuReg->SysClkDiv.AC328ClkSrc = 2;
    return 0;
}


/*
*********************************************************************************************************
*                                     standby_clk_plldisable
*
* Description: disable dram pll.
*
* Arguments  : none
*
* Returns    : 0;
*********************************************************************************************************
*/
__s32 standby_clk_plldisable(void)
{
    CmuReg->Pll1Ctl.PLLEn = 0;
    CmuReg->Pll2Ctl.PLLEn = 0;
    CmuReg->Pll3Ctl.PLLEn = 0;
    CmuReg->Pll4Ctl.PLLEn = 0;
    #if 0
    CmuReg->Pll5Ctl.PLLEn = 0;
    #endif
    CmuReg->Pll6Ctl.PLLEn = 0;
    CmuReg->Pll7Ctl.PLLEn = 0;

    return 0;
}


/*
*********************************************************************************************************
*                                     standby_clk_pllenable
*
* Description: enable dram pll.
*
* Arguments  : none
*
* Returns    : 0;
*********************************************************************************************************
*/
__s32 standby_clk_pllenable(void)
{
    CmuReg->Pll1Ctl.PLLEn = 1;
    CmuReg->Pll2Ctl.PLLEn = 1;
    CmuReg->Pll3Ctl.PLLEn = 1;
    CmuReg->Pll4Ctl.PLLEn = 1;
    #if 0
    CmuReg->Pll5Ctl.PLLEn = 1;
    #endif
    CmuReg->Pll6Ctl.PLLEn = 1;
    CmuReg->Pll7Ctl.PLLEn = 1;

    return 0;
}


/*
*********************************************************************************************************
*                                     standby_clk_hoscdisable
*
* Description: disable HOSC.
*
* Arguments  : none
*
* Returns    : 0;
*********************************************************************************************************
*/
__s32 standby_clk_hoscdisable(void)
{
    CmuReg->HoscCtl.OSC24MEn = 0;
    return 0;
}


/*
*********************************************************************************************************
*                                     standby_clk_hoscenable
*
* Description: enable HOSC.
*
* Arguments  : none
*
* Returns    : 0;
*********************************************************************************************************
*/
__s32 standby_clk_hoscenable(void)
{
    CmuReg->HoscCtl.OSC24MEn = 1;
    return 0;
}


/*
*********************************************************************************************************
*                                     standby_clk_ldodisable
*
* Description: disable LDO.
*
* Arguments  : none
*
* Returns    : 0;
*********************************************************************************************************
*/
__s32 standby_clk_ldodisable(void)
{
    __u32   tmpReg;

    tmpReg = *(volatile __u32 *)&CmuReg->HoscCtl;
    tmpReg &= ~(1<<16);
    *(volatile __u32 *)&CmuReg->HoscCtl = tmpReg | (0xa7<<24) ;

    return 0;
}


/*
*********************************************************************************************************
*                                     standby_clk_ldoenable
*
* Description: enable LDO.
*
* Arguments  : none
*
* Returns    : 0;
*********************************************************************************************************
*/
__s32 standby_clk_ldoenable(void)
{
    __u32   tmpReg;

    tmpReg = *(volatile __u32 *)&CmuReg->HoscCtl;
    tmpReg |= (1<<16);
    *(volatile __u32 *)&CmuReg->HoscCtl = tmpReg | (0xa7<<24) ;

    return 0;
}


/*
*********************************************************************************************************
*                                     standby_clk_setdiv
*
* Description: switch core clock to 32k low osc.
*
* Arguments  : none
*
* Returns    : 0;
*********************************************************************************************************
*/
__s32 standby_clk_setdiv(struct sun4i_clk_div_t  *clk_div)
{
    if(!clk_div)
    {
        return -1;
    }

    CmuReg->SysClkDiv.AXIClkDiv = clk_div->axi_div;
    CmuReg->SysClkDiv.AHBClkDiv = clk_div->ahb_div;
    CmuReg->SysClkDiv.APB0ClkDiv = clk_div->apb_div;

    return 0;
}


/*
*********************************************************************************************************
*                                     standby_clk_getdiv
*
* Description: switch core clock to 32k low osc.
*
* Arguments  : none
*
* Returns    : 0;
*********************************************************************************************************
*/
__s32 standby_clk_getdiv(struct sun4i_clk_div_t  *clk_div)
{
    if(!clk_div)
    {
        return -1;
    }

    clk_div->axi_div = CmuReg->SysClkDiv.AXIClkDiv;
    clk_div->ahb_div = CmuReg->SysClkDiv.AHBClkDiv;
    clk_div->apb_div = CmuReg->SysClkDiv.APB0ClkDiv;

    return 0;
}