/*******************************************************************************
 * 文件名：ADC_Filter.c
 * 内容摘要：
 * 其他说明：
 * 当前版本：
 * 作者：YiYANZtY
 *******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "ADC_Filter.h"

/* Private includes ----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/*********************************************************/
/**
 * @brief 均值滤波
 * @param  pData 数据
 * @param  xSize 长度
 * @retval uint16_t 结果
 */
uint16_t xAvgFilter(uint16_t *pData, uint32_t xSize) {
	uint32_t xResutl = 0;
	uint16_t xMax = 0;
	uint16_t xMin = 0xFFFF;

	if (xSize < 4) {
		return *pData;
	}
	for (int i = 0; i < xSize; i++) {
		if (*pData > xMax) {
			xMax = *pData;
		}
		if (*pData < xMin) {
			xMin = *pData;
		}
		xResutl += *pData++;
	}

	xResutl -= xMax;
	xResutl -= xMin;
	xResutl /= (xSize - 2);

	return xResutl;
}

/*****************************************************/
/**
 *卡尔曼滤波器
 *@param KFP *kfp 卡尔曼结构体参数
 *   float input 需要滤波的参数的测量值（即传感器的采集值）
 *@return 滤波后的参数（最优值）
 */
float kalmanFilter(KFP* kfp, float input)
{
    //预测协方差方程：k时刻系统估算协方差 = k-1时刻的系统协方差 + 过程噪声协方差
    kfp->Now_P = kfp->LastP + kfp->Q;
    //卡尔曼增益方程：卡尔曼增益 = k时刻系统估算协方差 / （k时刻系统估算协方差 + 观测噪声协方差）
    kfp->Kg = kfp->Now_P / (kfp->Now_P + kfp->R);
    //更新最优值方程：k时刻状态变量的最优值 = 状态变量的预测值 + 卡尔曼增益 * （测量值 - 状态变量的预测值）
    kfp->out = kfp->out + kfp->Kg * (input - kfp->out);//因为这一次的预测值就是上一次的输出值
    //更新协方差方程: 本次的系统协方差付给 kfp->LastP 威下一次运算准备。
    kfp->LastP = (1 - kfp->Kg) * kfp->Now_P;
    return kfp->out;
}

/******************************************/
#define SUM_WIN_SIZE  6

int history[SUM_WIN_SIZE];    //历史值，其中history[SUM_WIN_SIZE-1]为最近的记录

int buff_init = 0;    //前SUM_WIN_SIZE-1次填充后才能开始输出
int iSlidHisIdx = 0;    //环形数组可放数据的位置

int factor[SUM_WIN_SIZE] = {1, 2, 3, 4, 5, 6 };    //加权系数
int K = 21;    //1+2+3+4+5+6

int iSlidingFilter(int current)
{
    int i, j;
    int sum = 0;

    if (buff_init == 0)
    {
        history[iSlidHisIdx] = current;
        iSlidHisIdx++;
        if (iSlidHisIdx >= (SUM_WIN_SIZE - 1))
        {
            buff_init = 1;    //iSlidHisIdx有效范围是0-5，前面缓存5个，下一个就可以输出
        }
        return 0xFFFF;    //当前无法输出，做个特殊标记区分
    }
    else
    {
        history[iSlidHisIdx] = current;
        iSlidHisIdx++;
        if (iSlidHisIdx >= SUM_WIN_SIZE)
        {
            iSlidHisIdx = 0;    //iSlidHisIdx有效最大5,下次再从0开始循环覆盖
        }

        j = iSlidHisIdx;
        for (i = 0; i < SUM_WIN_SIZE; i++)
        {
            //注意[0]的值并不是最早的值,即将覆盖写入得[j]才是
            sum += history[j] * factor[i];    //注意防止数据溢出
            j++;
            if (j == SUM_WIN_SIZE)
            {
                j = 0;
            }
        }
        return sum / K;
    }
}

/***************************************************/
//气泡排序 size 为数组的length
void bubbleSort(int array[], int size)
{

    //外循环 ： 循环总次数为 (size -1) ：  step = 0 to size -2
    for (int otter = 0; otter < size - 1; ++otter)
    {
        // 内循环 - 总次数为 （size-1-step） ： i = 0 to size - 2 - step
        for (int inner = 0; inner < size - 1 - otter; ++inner)
        {
            // 比较数组中当前数值和下一个的数值
            // 如果当前数值大，则交换位置
            if (array[inner] > array[inner + 1])
            {
                int temp = array[inner];
                array[inner] = array[inner + 1];
                array[inner + 1] = temp;
            }
        }
    }
}

//气泡排序，去掉最小的，去掉最大的，然后平均
int iAvgFilter2(int array[], int size)
{
    bubbleSort(array, size); //气泡排序

    //对于array size小于3个的数组，选择全部数据
    int arrayBegin = 0;
    int arrayEnd = size - 1;

    //对于array size 大于3个的数据，
    //去掉最小和最大，然后选择中间的30%数据
    if (size > 3)
    {
        arrayBegin = size * 0.3;
        arrayEnd = size * 0.7;
    }

    int readingSum = 0;
    for (int i = arrayBegin; i < arrayEnd; i++)
    {
        readingSum += array[i];
    }
    int readingAvg = readingSum / (arrayEnd - arrayBegin);

    return readingAvg;
}

/* Private application code --------------------------------------------------*/
/**************ADC_Filter.c*************************************END OF FILE****/
