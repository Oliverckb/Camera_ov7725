#ifndef INF_PROCESS_H
#define INF_PROCESS_H


#include "COMMON.h"
#include "Users.h"

//边界中值滤波
#define BJMid_Filter();   if(i==3){L[0].x= MedFilter(L[0].x,L[1].x,L[2].x); R[0].x= MedFilter(R[0].x,R[1].x,R[2].x);\
								                   L[1].x= MedFilter(L[0].x,L[1].x,L[2].x); R[1].x= MedFilter(R[0].x,R[1].x,R[2].x);\
                                   L[2].x= MedFilter(L[1].x,L[2].x,L[3].x); R[2].x= MedFilter(R[1].x,R[2].x,R[3].x);}\
                        else if(i==6){L[3].x= MedFilter(L[2].x,L[3].x,L[4].x); R[3].x= MedFilter(R[2].x,R[3].x,R[4].x);\
                                      L[4].x= MedFilter(L[3].x,L[4].x,L[5].x); R[4].x= MedFilter(R[3].x,R[4].x,R[5].x);\
                                      L[5].x= MedFilter(L[4].x,L[5].x,L[6].x); R[5].x= MedFilter(R[4].x,R[5].x,R[6].x);}\
                        else if(i==9){L[6].x= MedFilter(L[5].x,L[6].x,L[7].x); R[5].x= MedFilter(R[5].x,R[6].x,R[7].x);\
                                      L[7].x= MedFilter(L[6].x,L[7].x,L[8].x); R[7].x= MedFilter(R[6].x,R[7].x,R[8].x);\
                                      L[8].x= MedFilter(L[7].x,L[8].x,L[9].x); R[8].x= MedFilter(R[7].x,R[8].x,R[9].x);}\
                        else if(i==12){L[9].x = MedFilter(L[8].x,L[9].x, L[10].x); R[9].x = MedFilter(R[8].x, R[9].x, R[10].x);\
                                       L[10].x= MedFilter(L[9].x,L[10].x,L[11].x); R[10].x= MedFilter(R[9].x, R[10].x,R[11].x);\
                                       L[11].x= MedFilter(L[10].x,L[11].x,L[12].x);R[11].x= MedFilter(R[10].x,R[11].x,R[12].x);}\
                        else if(i==15){L[12].x= MedFilter(L[11].x,L[12].x,L[13].x); R[12].x= MedFilter(R[11].x,R[12].x,R[13].x);\
                                       L[13].x= MedFilter(L[12].x,L[13].x,L[14].x); R[13].x= MedFilter(R[12].x,R[13].x,R[14].x);\
                                       L[14].x= MedFilter(L[13].x,L[14].x,L[15].x); R[14].x= MedFilter(R[13].x,R[14].x,R[15].x);}\
                        else if(i==18){L[15].x= MedFilter(L[14].x,L[15].x,L[16].x); R[15].x= MedFilter(R[14].x,R[15].x,R[16].x);\
                                       L[16].x= MedFilter(L[15].x,L[16].x,L[17].x); R[16].x= MedFilter(R[15].x,R[16].x,R[17].x);\
                                       L[17].x= MedFilter(L[16].x,L[17].x,L[18].x); R[17].x= MedFilter(R[16].x,R[17].x,R[18].x);}\
                        else if(i==21){L[18].x= MedFilter(L[17].x,L[18].x,L[19].x); R[18].x= MedFilter(R[17].x,R[18].x,R[19].x);\
                                       L[19].x= MedFilter(L[18].x,L[19].x,L[20].x); R[19].x= MedFilter(R[18].x,R[19].x,R[20].x);\
                                       L[20].x= MedFilter(L[19].x,L[20].x,L[21].x); R[20].x= MedFilter(R[19].x,R[20].x,R[21].x);}\
                        else if(i==24){L[21].x= MedFilter(L[20].x,L[21].x,L[22].x); R[21].x= MedFilter(R[20].x,R[21].x,R[22].x);\
                                       L[22].x= MedFilter(L[21].x,L[22].x,L[23].x); R[22].x= MedFilter(R[21].x,R[22].x,R[23].x);\
                                       L[23].x= MedFilter(L[22].x,L[23].x,L[24].x); R[23].x= MedFilter(R[22].x,R[23].x,R[24].x);}\
                        if(i==24){L[24].x = L[23].x + (L[23].x - L[22].x + 1); R[24].x = R[23].x + (R[23].x - R[22].x + 1);}
                  

/******************************************************************
功能描述：跳变识别以及中心线提取
******************************************************************/
void Black_Extract(void);







#endif