/*******************************************************************************
起始地址    占用空间                本地址数字的含义
00H	    4byte	    RIFF，资源交换文件标志。
04H	    4byte	    从下一个地址开始到文件尾的总字节数。高位字节在后面，这里就是001437ECH，
			        换成十进制是1325036byte，算上这之前的8byte就正好1325044byte了。
08H	    4byte	    WAVE，代表wav文件格式。
0CH	    4byte	    FMT ，波形格式标志
10H	    4byte	    00000010H，16PCM，我的理解是用16bit的数据表示一个量化结果。
14H	    2byte	    为1时表示线性PCM编码，大于1时表示有压缩的编码。这里是0001H。
16H	    2byte	    1为单声道，2为双声道，这里是0001H。
18H	    4byte	    采样频率，这里是00002B11H，也就是11025Hz。
1CH	    4byte	    Byte率=采样频率*音频通道数*每次采样得到的样本位数/8，00005622H，
			        也就是22050Byte/s=11025*1*16/2。
20H	    2byte	    块对齐=通道数*每次采样得到的样本位数/8，0002H，也就是2=1*16/8。
22H	    2byte	    样本数据位数，0010H即16，一个量化样本占2byte。
24H		2byte		附件数据，不一定存在。
26H	    4byte	    data，一个标志而已。
2AH	    4byte	    Wav文件实际音频数据所占的大小，这里是001437C8H即1325000，再加上2CH就正好
                    是1325044，整个文件的大小。
2EH	    不定	    量化数据
===================================================
PCM编码格式问题请参考
https://www.amobbs.com/thread-5652973-1-1.html?_dsign=8977581b
http://www.cnblogs.com/lidabo/p/3729615.html 
*******************************************************************************/ 
#include <stdio.h>
#include <stdlib.h>

/**定义数据类型*/
#define u8	unsigned char
#define u16	unsigned short
#define u32	unsigned long

/**选择音频采样深度*/
#define FILE_SCALE	 16	//音频文件质量 8或16	 
 
//WAV文件头格式。设置对齐方式为字节对齐。结构体共用46字节。
#pragma pack(1)
typedef struct {
	u8	riff_mark[4];		//0x00
	u32	file_size;			//0x04
	u8	wave_str[4];		//0x08
	u8	fmt_str[4];			//0x0C
	u32	pcm_bit_num;		//0x10
	u16	pcm_encode;			//0x14
	u16	sound_channel;		//0x16
	u32	pcm_sample_freq;	//0x18
	u32	byte_freq;			//0x1C
	u16	block_alin;			//0x20
	u16	sample_bits;		//0x22
	u16	reserved;			//0x24	是否存在附加信息
	u8	data_str[4];		//0x26
	u32	sound_size;			//0x2A - 0x2E
} WAV_Typedef;

/**对齐方式为默认*/
#pragma pack()

/**WAV文件头信息提取数组*/ 
WAV_Typedef WAVFile_Array;

/**申请内存空间指针*/
u16 *Sound_Data; 
u8 *Read_Sound_Data;
 
int main()
{
	FILE *fp,*fw;
	int i;
	int line_count=0;
	
	if((fp=fopen("test.wav","rb"))==NULL) {
		return 1;
	}	//打开操作不成功

	if((fw=fopen("wav_out.h","w"))==NULL) {
		return 1;
	}	//打开操作不成功
	
	/**读取文件头信息*/
	i = sizeof(WAVFile_Array);
	if(fread(&WAVFile_Array,48,1,fp)==1) {
		printf("wav file read ok!\n");
	}

	/**打印文件头信息*/
	printf("资源交换文件标志: %.4s\n",WAVFile_Array.riff_mark);
	printf("文件大小: %d\n",WAVFile_Array.file_size+8);
	printf("文件格式: %.4s\n",WAVFile_Array.wave_str);
	printf("波形格式: %.4s\n",WAVFile_Array.fmt_str);
	printf("PCM: %dbits\n",WAVFile_Array.pcm_bit_num);
	printf("声道: %s\n",WAVFile_Array.sound_channel==1?"单声道":"双声道");
	printf("采样速率: %d\n",WAVFile_Array.pcm_sample_freq);
	printf("码率: %d Bps\n",WAVFile_Array.byte_freq);
	printf("块对齐: %d\n",WAVFile_Array.block_alin);
	printf("采样位宽: %d\n",WAVFile_Array.sample_bits);	
	printf("Data标志: %.4s\n",WAVFile_Array.data_str);
	printf("SoundSize: %d\n",WAVFile_Array.sound_size);

	/**申请内存空间存放音频信息*/			
	Sound_Data=malloc(WAVFile_Array.sound_size);
	Read_Sound_Data=(u8 *)Sound_Data;
 
	/**申请内存失败*/
	if (Sound_Data==NULL) {
		printf("malloc failed!\n");	
		return 2;
	}
	
	/**偏移文件指针位置，跳过文件头信息部分，将指针指向Data部分。*/
	fseek(fp,sizeof(WAV_Typedef),SEEK_SET);

	/**将Data信息读取到Read_Sound_Data数组中*/
	for(i=0;i<WAVFile_Array.sound_size;i++) {
		Read_Sound_Data[i]=fgetc(fp);
	}
	
	/**打印输出头文件*/
	fprintf(fw,"#ifndef __SOUND_DATA_H__\n");
	fprintf(fw,"#define __SOUND_DATA_H__\n\n");
	fprintf(fw,"#define SOUND_LENGTH\t%d\n\n",WAVFile_Array.sound_size);
#if FILE_SCALE==16		
	fprintf(fw,"const unsigned short SOUND_DATA[SOUND_LENGTH] = {\n\t");
#else
	fprintf(fw,"const unsigned char SOUND_DATA[SOUND_LENGTH] = {\n\t");
#endif		
	
	/**以8个数据为一行对齐输出Data*/
	for (i=0;i<WAVFile_Array.sound_size;i++) {
#if FILE_SCALE==16 			
		fprintf(fw,"0x%04x, ",(Sound_Data[i])&0xffff);
#else	/**8位采样深度*/
		fprintf(fw,"0x%02x, ",((Sound_Data[i])&0xffff)>>8);
#endif
		/**记录每行数据个数，不应大于8个*/
		line_count++;
		if (line_count>8-1) {
			line_count=0;
			fprintf(fw,"\n\t");
		}
	}
	fprintf(fw,"\n};\n#endif\n");	
	printf("\n ***** 已转换成头文件 wav_out.h *****\n"); 
	
	/**Close the input file "fp" and output file "fw"*/
	if(fp!=NULL)
		fclose(fp);	
	if(fw!=NULL)
		fclose(fw);	
	
	return 0;	
}
