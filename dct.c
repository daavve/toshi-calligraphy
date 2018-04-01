#include "header.h"
#include <stdio.h>
#include <opencv2/highgui/highgui_c.h>

// div = input cmd-line, Goes through and sets certain pixels to a brightness value of 0
// div I think means the search space to determine how likely we are to get a brightness value of 0
void reduceHigherFreq(CvMat *cm, int div){
	int x, y;
	
    const float x_frac = -(cm->rows / cm->cols);
    const float y_frac = 2*cm->rows/div;
	for(y = 0; y < cm->rows; y++){
		for(x = 0; x < cm->cols; x++){
			if(y >= x_frac * x + y_frac ){
				cvmSet(cm, y, x, 0);
			}
		}
	}
	
	//for print out purpose only
	if(0){
		printf("print array\n");
		for(y=0; y < cm->rows; y++){
			for(x=0; x < cm->cols; x++){
				//printf("%d", a[i][j]%10);
				int temp = ((int)cvmGet(cm, y, x))%10;
				if(temp < 0){
					temp *= -1;
				}
				printf("%d", temp);
			}
			putchar('\n');
		}
	}
}

    //dct-level is input from cmd line
void makeIdctImage(CvMat *dct, CvMat *idct, IplImage *invImage, int g_dct_level){
	int x, y;
    
    cvDCT( dct, dct, CV_DXT_FORWARD);
	
	reduceHigherFreq(dct, g_dct_level);
	//reduceHigherFreqInSquare(dct, g_dct_level);
	
	//IDCT
	cvDCT( dct, idct, CV_DXT_INVERSE);
	//逆変換用画像にデータをコピー # Copy data to reverse conversion image
	for(y=0; y<invImage->height; y++){
		for(x=0; x<invImage->width; x++){
			invImage->imageData[invImage->widthStep * y + x] = (unsigned char)cvmGet(idct,y,x);
		}
	}
    cvSaveImage("idct_out.bmp", invImage, 0); //This blury image represents the image after running through the dft
}

