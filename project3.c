//Created bz Viktoryia Tomason
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
  int rows;
  int cols;
  unsigned char *cells;
} Map;


// Function that returns a map with a given number of rows and columns
Map Map_ctor(int rows, int cols)
{
	Map map;
	map.rows = rows;
	map.cols = cols;

	map.cells = malloc(map.rows * map.cols * sizeof(unsigned char));

	if (map.cells == NULL)
	{
		map.rows = 0;
		map.cols = 0;
	}
	return map;
	
}
// A function that, after receiving the number, translates into binary code and fills in the " field"
void map_kod(int x, char pole[])
{
	memset(pole, '0', 3);
	int pos = 0;
	while (x != 0)
	{
		if ((x % 2) == 0)
		{
			x = x / 2;
			pole[pos] = '0';
		}
		else if ((x % 2) != 0)
		{
			x = x / 2;
			pole[pos] = '1';
		}
		pos++;
	}
	pole[3] = '\0';
}

// The function gets a pointer to the map structure, the coordinate system, and the border marks the requested border of the shelf.The function returns true if there is a wall at the specified shelf boundary.
// Left border of answer 1, right border of answer 2 and upper or lower border of answer 3.
bool isborder(Map *map, int r, int c, int border)
{
	char hodnota[2];
	hodnota[0] = map->cells[r * map->cols + c];

	int par1 = 1;
	int par2 = 2;
	int par3 = 3;

	char pole[4];
	map_kod(atoi(hodnota), pole);

	if (border == par1)
	{
		if (pole[0] == '0')
			return false;
		else 
			return true;
	}

	if (border == par2)
	{
		//par2 == pole[1];
		if (pole[1] == '0')
			return false;
		else
			return true;
	}

	if (border == par3)
	{
		//par3 == pole[2];
		if (pole[2] == '0')
			return false;
		else 
			return true;
	}
 return 0;
}


// A function that returns the right direction
//Right hand rule answers number 22, left hand rule answers number 33.
int start_border(Map *map, int r, int c, int leftright)
{
	if (r > map->rows - 1 || c > map->cols - 1 || r < 0 || c < 0) return 0;

	if (c == 0)
	{
		if (!(isborder(map, r, c, 1)))
		{
			if (leftright == 22)
			{
				if (r % 2 == 0)
					return 1;

				else if (r % 2 == 1)
					return 1;
			}

			if (leftright == 33)
			{
				if (r % 2 == 0)
					return 1;

				else if (r % 2 == 1)
					return 1;

			}
		}
	}
	  if (c == map->cols - 1)
	 {
		 if (!(isborder(map, r, c, 2)))
		 {
			 if (leftright == 22)
			 {
				 if (r % 2 == 0)
				 return 2;

				 else if (r % 2 == 1)
				 return 2;
			 }

			 if (leftright == 33)
			 {
				 if (r % 2 == 0)
					 return 2;

				 else if (r % 2 == 1)
					 return 2;
			 }

		 }
	 }

	if (r == map->rows - 1)
	{
		if ((r * map->cols + c) % 2 == 1) 
		{
			if (!(isborder(map, r, c, 3)))
			{
				if (leftright == 22)
					return 3;
				if (leftright == 33)
					return 3;
			}
		}

	}
	
	if (r == 0)
	{
		if ((r * map->cols + c) % 2 == 0)
		{
			if (!isborder(map, r, c, 3))
			{
				if (leftright == 22)
					return 3;
				if (leftright == 33)
					return 3;
			}
		}
	}
	
	return 0;
}

// Direction from left side of answer 1, direction from right side of ANSWER 2 and direction from top or bottom of Answer 3
// Goes through the map and prints every step 
int bludiste(Map map, int r, int c, int par, int leftright)
{	
	if (r > map.rows - 1 || c > map.cols - 1 || r < 0 || c < 0) return 1;

	if (leftright == 33) {
	
	if ((r * map.cols + c) % 2 == 1)
	{
		if (par == 1)
		{
			if (!(isborder(&map, r, c, 2)))
			{
				c++;
				if (r > map.rows - 1 || c > map.cols - 1 || r < 0 || c < 0) return 1;
				printf("%d,%d\n", r + 1, c + 1);
			}
			else par = 2;
		}


		else if (par == 2)
		{

			if (!(isborder(&map, r, c, 3)))
			{
				par = 3;
				r++;
				if (r > map.rows - 1 || c > map.cols - 1 || r < 0 || c < 0) return 1;
				printf("%d,%d\n", r + 1, c + 1);
			}
			else par = 3;
		}

		else if (par == 3)
		{
			if (!(isborder(&map, r, c, 1)))
			{
				par = 2;
				c--;
				if (r > map.rows - 1 || c > map.cols - 1 || r < 0 || c < 0) return 1;
				printf("%d,%d\n", r + 1, c + 1);
			}
			else par = 1;
		}
	}
		else if ((r * map.cols + c) % 2 == 0)
		{
			if (par == 1)
			{
				if (!(isborder(&map, r, c, 3)))
				{
					par = 3;
					r--;
					if (r > map.rows - 1 || c > map.cols - 1 || r < 0 || c < 0) return 1;
					printf("%d,%d\n", r + 1, c + 1);
				}
				else par = 3;
			}

			else if (par == 2)
			{
				if (!(isborder(&map, r, c, 1)))
				{
					c--;
					if (r > map.rows - 1 || c > map.cols - 1 || r < 0 || c < 0) return 1;
					printf("%d,%d\n", r + 1, c + 1);
				}
				else par = 1;
			}

			else if (par == 3)
			{

				if (!(isborder(&map, r, c, 2)))
				{
					par = 1;
					c++;
					if (r > map.rows - 1 || c > map.cols - 1 || r < 0 || c < 0) return 1;
					printf("%d,%d\n", r + 1, c + 1);
				}
				else par = 2;
			}

		}
	}

	else if (leftright == 22) {
		if ((r * map.cols + c) % 2 == 0)
	{
	if (par == 1)
		{
			if (!(isborder(&map, r, c, 2)))
			{
				c++;
				if (r > map.rows - 1 || c > map.cols - 1 || r < 0 || c < 0) return 1;
		        printf ("%d,%d\n", r + 1, c + 1);
			}
			else par = 2;
		}
		else if (par == 2)
		{
			if (!(isborder(&map, r, c, 3)))
			{
				par = 3;
				r--;
				if (r > map.rows - 1 || c > map.cols - 1 || r < 0 || c < 0) return 1;
		        printf ("%d,%d\n", r + 1, c + 1);
			}
			else par = 3;
		}		
		else if (par == 3)
		{
			if (!(isborder(&map, r, c, 1)))
			{
				par = 2;
				c--;
				if (r > map.rows - 1 || c > map.cols - 1 || r < 0 || c < 0) return 1;
		        printf ("%d,%d\n", r + 1, c + 1);
			}
			else par = 1;
		}
	}
	  else if ((r * map.cols + c) % 2 == 1)
	  	{
			if (par == 1)
		{
			if (!(isborder(&map, r, c, 3)))
			{
				par = 3;
				r++;
				if (r > map.rows - 1 || c > map.cols - 1 || r < 0 || c < 0) return 1;
		        printf ("%d,%d\n", r + 1, c + 1);
			}
			else par = 3;
		}
			
		else if (par == 2)
		{
			
			if (!(isborder(&map, r, c, 1)))
			{
				
				c--;
				if (r > map.rows - 1 || c > map.cols - 1 || r < 0 || c < 0) return 1;
		        printf ("%d,%d\n", r + 1, c + 1);
			}
			else 
				par = 1;
			
		}

		else if (par == 3)
		{
			if (!(isborder(&map, r, c, 2)))
			{
				par = 1;
				c++;
				if (r > map.rows - 1 || c > map.cols - 1 || r < 0 || c < 0) return 1;
		        printf ("%d,%d\n", r + 1, c + 1);
			}
			else par = 2;
		}
	}		
	}

	bludiste(map, r, c, par, leftright);
	return 0;
}

// Releases all memory in the map
void Map_dtor(Map *map)
{
	if (map->cells != NULL)
	 {
    	free(map->cells);
		map->cells = NULL;
		map->rows = 0;
		map->cols = 0;
	}
}

int main(int argc, char*argv[])
{
	if (argc < 2) {
		fprintf(stderr, "Chyba: chybi argumenty\n");
		return 1;
	}
	if (strcmp(argv[1], "--help") == 0)
		 {
		printf("\nTo je program, ktery v danem bludisti a jeho vstupu najde pruchod ven\n\n"); 
		printf("--help vytiskne tuto zpravu\n\n");
		printf("--test  zkontroluje, ze soubor spravny a vytiskne Valid. V opacnem pripade program tiskne Invalid\n\n");
		printf("--rpath hleda pruchod pomoci pravidla prave ruky\n\n");
		printf("--lpath hleda pruchod pomoci pravidla leve ruky\n\n");
		
		return 0;
	}

	else if (strcmp(argv[1], "--test") == 0)
	{

//Open file
	FILE*fl;

	fl = fopen(argv[2], "r+b");
	 if (!fl){
        fprintf(stderr,"Nelze otevrit soubor %s \n", argv[2]);
        return 1;
    }
	if (fl != NULL)
	{
		//Number of rows
		char rows[5];
		fscanf(fl, "%s", rows); 

		//Correct format
		for (unsigned p = 0; p < strlen(rows); p++)
		 {
			 if ((rows[p] >= 'A' && rows[p] <= 'Z') || (rows[p] >= 'a' && rows[p] <= 'z')) 
			 {
				fprintf(stderr,"Invalid\n");
				fclose(fl);
				return 1;

			 }
		}
		//Number of cols
		char cols[5];
		fscanf(fl, "%s", cols);

		//Correct format
		for (unsigned p = 0; p < strlen(cols); p++)
		 {
			 if ((cols[p] >= 'A' && cols[p] <= 'Z') || (cols[p] >= 'a' && cols[p] <= 'z')) 
			 {
				printf("Invalid\n");
				fclose(fl);
				return 1;
			 }
		}

	Map map;
		map = Map_ctor(atoi(rows), atoi(cols));
    int hodnota;
        for (int i = 0; i < map.rows; i++){
            for (int j = 0; j < map.cols; j++){
                if (fscanf(fl, "%d", &hodnota) == 1 && hodnota>=0 && hodnota <8)
		{
                    map.cells[ i*map.cols + j]= hodnota;
                }
                else {
                    printf("Invalid\n");
                    fclose(fl);
		Map_dtor(&map);
                    return 1;
                }
            }
        }
	printf("Valid\n");
        fclose(fl);
        Map_dtor(&map);
	}
	}

	
	else if (strcmp(argv[1], "--rpath") == 0)
	{
		if (argc != 5)
                {
			fprintf(stderr, "Chyba: neplatny pocet argumentu \n");
			return 1;
		}

	FILE*fl;

	fl = fopen(argv[4], "r+b");
	if ((fl = fopen(argv[4], "r+b")) == NULL) {
			fprintf(stderr, "Chyba: soubor neexistuje %s\n", argv[4]);
			return 1;
		}
		char rows[5];
		fscanf(fl, "%s", rows);
		char cols[5];
		fscanf(fl, "%s", cols);
		
		Map map;

		map = Map_ctor(atoi(rows), atoi(cols));

		unsigned char k[2];

		for (int i = 0; fscanf(fl, "%s", k) != -1; i++)
		{
			if (i > map.rows * map.cols)
			{
				fprintf(stderr,"Chyba: neplatny pocet argumentu \n");
				fclose(fl);
				Map_dtor(&map);
				return 1;
			}
			map.cells[i] = k[0];
		}

		int startBorder = start_border(&map, (atoi(argv[2]) - 1), (atoi(argv[3]) - 1), 22);
		if (startBorder == 0) {
			fprintf(stderr, "Nelze vstoupit\n");
			fclose(fl);
			Map_dtor(&map);
			return 1;
		}

		printf("%d,%d\n", atoi(argv[2]), atoi(argv[3]));
		
		bludiste(map, (atoi(argv[2]) - 1), (atoi(argv[3]) - 1), startBorder, 22); 
		Map_dtor(&map);
		fclose(fl);
		
	}


	else if (strcmp(argv[1], "--lpath") == 0)
	{
		if (argc != 5){
			fprintf(stderr, "Chyba: neplatny pocet argumentu \n");
			return 1;
		}
			FILE*fl;

	fl = fopen(argv[4], "r+b");
	if ((fl = fopen(argv[4], "r+b")) == NULL) {
			fprintf(stderr, "Chyba: soubor neexistuje %s \n", argv[4]);
			return 1;
		}
		char rows[5];
		fscanf(fl, "%s", rows);
		char cols[5];
		fscanf(fl, "%s", cols);
		
		Map map;

		map = Map_ctor(atoi(rows), atoi(cols));

		unsigned char k[2];

		for (int i = 0; fscanf(fl, "%s", k) != -1; i++)
		{
			if (i > map.rows * map.cols)
			{
				fprintf(stderr,"Chyba: neplatny pocet argumentu \n");
				Map_dtor(&map);
				fclose(fl);
				return 1;
			}
			map.cells[i] = k[0];
		}

		
		
		int startBorder = start_border(&map, (atoi(argv[2]) - 1), (atoi(argv[3]) - 1), 33);
		if (startBorder == 0) {
			fprintf(stderr, "Nelze vstoupit\n");
			Map_dtor(&map);
			fclose(fl);
			return 1;
		}
		printf("%d,%d\n", atoi(argv[2]), atoi(argv[3]));
		bludiste(map, (atoi(argv[2]) - 1), (atoi(argv[3]) - 1), startBorder, 33);
		Map_dtor(&map);
		fclose(fl);

		}
		return 0;
	}

		
	
