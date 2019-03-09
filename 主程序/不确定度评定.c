/*********************************************************************
 This is a small program to calculate uncertainty,
 the current Version No.1.1.190303_alpha,
 its function is:
 1) Calculate the combined uncertainty & relative uncertainty
    of the direct measurement amount(no valid number can be retained);
 2) Detect bad value and prompt the user to re-experiment;
 3) Calculate the combined uncertainty of the indirect measurement amount.
 
 Next version: Continue to improve the function of calculating the 
               combined uncertainty of the indirect measurement amount.
*********************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <math.h> 

double ur() 
{
	unsigned int n, i=0, j;			//n is the number of measurements
	double tp, UB, delta, C, UC, Ur, sigma;
	double a[40];
	double aver=0, SE, sum=0, UA;
	/*aver = the best estimate of the measured results
	UA = uncertainty of A-class standard, SE = Systematic Error*/


	printf("Enter the number of experiments:\n");
	scanf("%d",&n);
	if( n == 1 )
	{
		printf("Enter experimental data:\n");
		scanf("%lf",&a[0]);
		printf("Enter error tolerance delta:\n");
		scanf("%lf", &delta );
		printf("1) uniform distribution or 2) normal distribution ? [Enter \'1\' or \'2\']\n");
		scanf("%d",&j);
		if(j==1)
		{
			C=sqrt(3);
		}
		else
		{
			C=3;
		}
		UA = 0;
		UB = delta/C;
		UC = UB;
		Ur = UC/a[0]*100;
		printf("Ua = %f\tUb = %f",UA,UB);
		printf("\nX = %f ¡À %f£¨unit£©\nUr = %f %%\np = 0.683\n\n",a[0],UC,Ur);
		return (Ur/100);
	}
	else
	{
		switch ( n-1 )		//Tp values corresponding to different n£¨confidence probability 0.683£©
		{
			case 1:
				tp=1.84;
				break;
			case 2:
				tp=1.32;
				break;
			case 3:
				tp=1.20;
				break;
			case 4:
				tp=1.14;
				break;
			case 5:
				tp=1.11;
				break;
			case 6:
				tp=1.09;
				break;
			case 7:
				tp=1.08;
				break;
			case 8:
				tp=1.07;
				break;
			case 9:
				tp=1.06;
				break;
			case 10:
				tp=1.05;
				break;
			case 15:
			case 20:
				tp=1.03;
				break;
			case 30:
				tp=1.02;
				break;
			case 40:
				tp=1.01;
				break;
		}
		printf("Enter experimental data:\n");
		while ( i < n )
		{
			scanf("%lf", &a[i] );
			i++;
		}
		printf("Enter systematic error:\n");
		scanf("%lf",&SE);
		printf("Enter error tolerance delta:\n");
		scanf("%lf", &delta );
		printf("1) uniform distribution or 2) normal distribution ? [Enter \'1\' or \'2\']\n");
		scanf("%d",&j);
		i=0;								////Re-assignment for i
		for( ; i<n ;)						//Jump out of the loop when Correct all values
		{
			aver=0;
			for( i = 0 ; i < n ; i++ )
			{
				aver += a[i];
			}
			aver = aver / n ;
			aver = aver - SE;				//Re-assignment for aver
			sum=0;
			for( i = 0 ; i < n ; i++ )
			{
				sum += pow( (a[i] - aver) , 2 );
			}
			sigma = tp * sqrt( sum/(n-1) );
			sum = sum/(n*(n-1));			//Re-assignment for sigma & sum
			UA = tp * sqrt(sum);

			/*The above is the calculation result of uncertainty of A-class standard*/

			if(j==1)
			{
				C=sqrt(3);
			}
			else
			{
				C=3;								//3-sigma' rule test
				if( n > 5 )
				{
					for( i = 0 ; i < n ; i++ )
					{
						if( fabs(a[i] - aver) > 3*sigma )
						{
							printf("%f is a bad value!\nCorrect it:\n",a[i]);
							scanf("%lf",&a[i]);
							break;
						}
					}
				}
			}
		}
		UB = delta/C;

		/*The above is the calculation result of uncertainty of B-class standard*/

		UC = sqrt( pow( UA , 2 ) + pow( UB , 2 ) );
		Ur = (UC/aver)*100;
		//The Ur value is 100 times the normal value and is used as the output before the percent sign
		printf("Ua = %f\tUb = %f",UA,UB);
		printf("\n\nX = %f ¡À %f£¨unit£©\nUr = %f %%\np = 0.683\n\n",aver,UC,Ur);
		return (Ur/100);
	}
}

double URN()
{
	int i, n, m;
	//n is the number of direct measurements, m is the power of the parameter
	double uri, sum=0, Ur_N=0;
	printf("Enter the number of direct measurement amount:\n");
	scanf("%d",&n);
	printf("OKay,Let\'s focus on one of these quantities.\n");
	for( i = 0 ; i < n ; i++ )
	{
		uri = ur();
		printf("Enter the idempotent:\n");
		scanf("%d",&m);
		uri = pow( m*uri , 2 );
		sum = sum + uri;
		if(i < n-1 )
		{
			printf("OKay,Let\'s focus on another quantity.\n");
		}
		else
		{
			break;
		}
	}
	Ur_N = sqrt(sum);
	return Ur_N;
}
int main()
{
	int i;
	double Ur_N;
	printf("Function Type?\n1)N=x/y or N=x*y\n2)N=x¡Ày\n3)N=kx(k is constant)\t[choose 1,2 or 3]\n");
	scanf("%d",&i);
	switch ( i )
	{
		case 1: Ur_N = URN();break;
		case 2:
		case 3: printf("I haven\'t get ready!");break;
	}
	Ur_N = Ur_N*100;
	printf("\n\nUr_N = %.2f%%\n",Ur_N);
	system("pause");
	return 0;
}
