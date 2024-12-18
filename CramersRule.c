#include <stdio.h>

void cramerRule(float matrix[4][4], float vector[4]);
float determinant(float matrix[4][4], int n);
void displayDet(float matrix[4][4]);

int main() {
    int i, j;
	//Coefficient matrix
    float coefficient[4][4] = {{3, 5, 6, 3},{7, 1, 3, 2},{3, 8, 2, 1},{9, 2, 3, 3}};

    //Constants matrix
    float constant[4] = {143, 93, 102, 119};

    //Dsiplay System of Equation
    printf("\nFrom the data given, four system of equation are formed.\n\n");
    printf("\t3a + 5b + 6c + 3d = 143\n");
    printf("\t7a +  b + 3c + 2d = 93\n");
    printf("\t3a + 8b + 2c +  d = 102\n");
    printf("\t9a + 2b + 3c + 3d = 119\n");

    //Display Coefficient matrix
    printf("\nCoeficient matrix (Number of deliveries):\n");
    printf("\n");
    for(i=0; i<4;i++)
    {   
        printf("\t{");
        for(j=0; j<4;j++)
        {
        printf(" %.f ",coefficient[i][j]); 
        }
        printf("}\n");
    }

    //Display Constant Vector
    printf("\nConstant Vector (Total fuel consumed):\n\n");
    for(i=0; i<4 ; i++)
    {     
        printf("\t    {");
        printf(" %-3.f ",constant[i]); 
        printf("}\n");
    }
    printf("\n");

    //Function call to solve the equations
    cramerRule(coefficient, constant);

}

// Cramer's Rule solution (use in main function)
void cramerRule(float matrix[4][4], float vector[4]) {
    int i ,j, k , r; 
    float solution[4];
    float tempMatrix[4][4];
    float ansDet[4];

    //determine the det of A
    float det = determinant(matrix, 4);
    printf("Determinant of D:\n");
    displayDet(matrix);
    printf("\n\tdet(D): %.f\n",det);

    printf("\nReplace each column in Determinant D with constant vector to get Da, Db, Dc and Dd.\n");
    //Loop for ColumnReplacement and GettingSolution
    for (k = 0; k < 4; k++) {

        //Loop for Row for temMatrix
        for (i = 0; i < 4; i++) {
            //Loop for Column for temMartix
            for (j = 0; j < 4; j++) {
                tempMatrix[i][j] = matrix[i][j];
            }
        }

        //Formation of Da, Db, Dc ,Dd
        for (r = 0; r < 4; r++) 
        {
            tempMatrix[r][k] = vector[r];
        }

        //Display Determinants
        printf("\nDeterminant of D%c:\n", 'a' + k);
        displayDet(tempMatrix);
        
        //Display Answer of Determinants
        ansDet[k]= determinant(tempMatrix, 4);
        printf("\n\tdet(D%c) = %.f\n", 'a' + k, ansDet[k]);
        
        //Solution a, b, c, d
        solution[k] = ansDet[k] / det;
    }
    printf("\n");

    //Display Formula
    printf("Given the Formula:\n");
    printf("x = det(Dx)/det(D)\n\n");
    //Display Solution
    printf("Hence,\n");
    for(i=0; i<4;i++)
    {
        printf("%c = det(D%c)/det(D) = %.f/%.f = %.f\n",'a'+i ,'a'+i , ansDet[i] , det , solution[i]);
    }
    printf("\n");
    //Display Conclusion
    for (i = 0; i < 4; i++) 
    {
        printf("Fuel consumed by truck per delivery to City %c = %.f liters\n", 'A' + i, solution[i]);
    }
}

// Calculate the determinant of a matrix
float determinant(float matrix[4][4], int n) {
    int h, i ,j, k, p ;
	float det = 0;
    float tempMatrix[4][4];

    //For 1x1 matrix
    if (n == 1) {
        return matrix[0][0];
    }
    //For 2x2 matrix
    if (n == 2) {
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    }

    for (p = 0; p < n; p++) 
    {
        h = 0, k = 0;           //h for temp row; k for temp column
        //Loop for Column of temp
        for (i = 1; i < n; i++) 
        {
            //Loop for Row of temp
            for (j = 0; j < n; j++) 
            {
                if (j != p) 
                { 
                	tempMatrix[h][k++] = matrix[i][j];
                    if (k == n - 1) 
                    {
                    	k = 0;
                    	h++;
                	}
            	}
            }
        }
        //Calculation of Determinant (sign * value of first row * determinant)
        det += (p % 2 == 0 ? 1 : -1) * matrix[0][p] * determinant(tempMatrix, n - 1);
    }
    return det;
}

void displayDet(float matrix[4][4])
{
    int i, j;
	printf("\n");
    //Loop for Row
    for(i=0; i<4;i++)
    {   
        printf("\t|");
        //Loop for Column
        for(j=0; j<4;j++)
        {
            printf(" %.f ",matrix[i][j]); 
        }
        printf("|\n");
    }
}


