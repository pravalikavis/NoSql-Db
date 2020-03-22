#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int size = 20;
int sx, sx1;
struct ll
{
	char s[70];
	struct ll* next;
};

struct info
{
	int rollno;

	long int phone;
	char addr[30];
	char city[20];
	int pincode;
};
struct marks
{
	int rollno;
	char name[30];
	int m1, m2, m3, m4;
};
struct info** read_files1(char *s)
{
	struct info **i = (struct info **)calloc(2 * size, sizeof(struct info*));
	for (int j = 0; j < 2 * size; j++)
	{
		i[j] = (struct info *)calloc(1, sizeof(struct info));
	}

	FILE *p;
	int k = 0;
	fopen_s(&p, s, "r");
	if (p == NULL)
	{
		printf("\nunable to open file");
		return;
	}

	char st[40];
	fgets(st, 39, p);
	sx = 2;
	while (feof(p) == 0)
	{

		//	fscanf_s("%d%ld,%s,%s,%d", &i[0]->rollno, &i[0]->phone, i[0]->addr,10, i[0]->city,10, &i[0]->pincode);
		int su = fscanf_s(p, "%d,", &i[k]->rollno);
		if (su <= 0)
			break;
		fscanf_s(p, "%ld,", &i[k]->phone);
		fscanf_s(p, "%[^,],", i[k]->addr, 29);
		fscanf_s(p, "%[^,],", i[k]->city, 19);
		fscanf_s(p, "%d", &i[k]->pincode);

		k++;

		if (k == size*sx - 1)
		{
			sx++;
			i = (struct info **)realloc(i, sx*size*sizeof(struct info*));
			for (int g = (sx - 1)*size; g < sx*size; g++)
			{
				i[g] = (struct info*)calloc(1, sizeof(struct info));
			}

		}
	}
	return i;

}
struct marks** read_files2(char *s)
{

	struct marks **m = (struct marks **)calloc(size, sizeof(struct marks*));
	for (int j = 0; j < size; j++)
	{
		m[j] = (struct marks *)calloc(1, sizeof(struct marks));
	}
	FILE  *p1;

	fopen_s(&p1, s, "r");
	if (p1 == NULL)
	{
		printf("\nunable to open file");
		return;
	}
	int k = 0;
	char st[40];
	fgets(st, 39, p1);
	sx1 = 1;
	while (feof(p1) == 0)
	{
		int c;
		//	fscanf_s("%d%ld,%s,%s,%d", &i[0]->rollno, &i[0]->phone, i[0]->addr,10, i[0]->city,10, &i[0]->pincode);
		int su = fscanf_s(p1, "%d,", &m[k]->rollno);
		if (su <= 0)
		{
			break;
		}
		fscanf_s(p1, "%[^,],", m[k]->name, 19);
		fscanf_s(p1, "%d,", &m[k]->m1);
		fscanf_s(p1, "%d,", &m[k]->m2);
		fscanf_s(p1, "%d,", &m[k]->m3);
		fscanf_s(p1, "%d,", &m[k]->m4);
		k++;
		if (k == sx1*size - 1)
		{
			sx1++;
			m = (struct marks**)realloc(m, sx1*size*sizeof(struct marks*));
			for (int h = (sx1 - 1)*size; h < sx1*size; h++)
			{
				m[h] = (struct marks*)calloc(1, sizeof(struct marks));
			}
		}
	}

	return m;
}
char ** define_grammer()
{
	char **buff = (char **)calloc(15, sizeof(char*));
	for (int i = 0; i < 15; i++)
	{
		buff[i] = (char *)calloc(10, sizeof(char));
	}
	buff[0] = "select";
	buff[1] = "{}";
	buff[2] = "from";
	buff[3] = "{}";
	buff[4] = "where";
	buff[5] = "{}";
	buff[6] = "{}";
	buff[7] = "{}";
	buff[8] = "load";
	buff[9] = "{}";
	buff[10] = "into";
	buff[11] = "{}";
	return buff;

}
int hash(char *key)
{
	int n = key[0]-97;
	int binaryNum[10] = { 0 };

	// counter for binary array
	int i = 0;
	while (n > 0) {

		// storing remainder in binary array
		binaryNum[i] = n % 2;
		n = n / 2;
		i++;
	}
	int num = binaryNum[4] *10+ binaryNum[3];
	int dec_value = 0;

	// Initializing base value to 1, i.e 2^0
	int base = 1;

	int temp = num;
	while (temp)
	{
		int last_digit = temp % 10;
		temp = temp / 10;

		dec_value += last_digit*base;

		base = base * 2;
	}
	
	if (dec_value == 2 && key[1] == 'y')
	{
		dec_value = 3;
	}
	return dec_value;
}
char * hashing_syntax(struct ll** hash_array, int put_or_get, char *key, char *value,int k)
{
	if (put_or_get == 1)
	{
		int i = hash(key);
		if (i == 2&&key[1]=='y')
		{
			i = 3;
		}
		if (hash_array[i]->s[0] == ' ')
		{
			int j;
			for (j = 0; value[j] != '\0'; j++)
			{
				hash_array[i]->s[j] = value[j];
			}
			hash_array[i]->s[j] = '\0';
		}
		else{
			struct ll* m_next = hash_array[i];
			while (m_next->next != NULL)
			{
				m_next = m_next->next;
			}
			struct ll* new1 = (struct ll *)calloc(1, sizeof(struct ll));

			int j;
			for (j = 0; value[j] != '\0'; j++)
			{
				new1->s[j] = value[j];
			}
			new1->s[j] = '\0';
			new1->next = NULL;
			m_next->next = new1;
		}
	}
	else
	{
		int i = hash(key);
		struct ll* m_next = hash_array[i];
		
			while (m_next->next != NULL&&k>1)
			{
				m_next = m_next->next;
				k--;

			}
			
		
	
		return m_next->s;

	}
}


char * l_analyzer(char *buff, int *i,int *j)
{

	char *buff1 = (char *)calloc(15, sizeof(char));
	if (strcmp(&buff[*i], "") == 0)
		return "";
	while (buff[*i] == ' ')
	{
		*i++;
	}

	while (buff[*i] != '\0' &&buff[*i] != '\n' && buff[*i] != ' ')
	{
		strncat(buff1, &buff[*i], 1);
		(*i)++;
	}
	*i = *i + 1;
	*j = *j + 1;
	return buff1;
}

int valid_grammer(char **check, char *input)
{
	int a = 0;
	struct hash_map **h_m = (struct hash_map**)calloc(4, sizeof(struct hash_map*));
	char *buff = (char *)calloc(200, sizeof(char));
	buff = input;
	int j = 0;
	int* p = &j;
	char *s = l_analyzer(buff, p, &a);
	if (strcmp(s, check[8]) == 0)
	{
		int i = 8;
		int c = 1;
		while (i < 11)
		{

			if (strcmp(check[i], "{}") != 0)
			{
				if (strcmp(check[i], s) != 0)
				{
					c = 0; break;
				}
			}
			i++;
			if (i < 11 && strcmp(&buff[*p], "") == 0)
			{
				c = 0;
				break;
			}
			if (i < 11)
				s = l_analyzer(buff, p, &a);
		}
		return c;
	}
	
	else{
		int i = 0;
		int c = 1;
		while (i < 8)
		{

			if (strcmp(check[i], "{}") != 0)
			{
				if (strcmp(check[i], s) != 0)
				{
					c = 0; break;
				}
			}
			else
			{
				while (strcmp(check[i + 1], s) != 0)
				{
					if (p > strlen(buff))
						return c;
					s = l_analyzer(buff, p, &a);

				}
			}
			i++;
			if (i < 7 && strcmp(&buff[*p], "") == 0)
			{
				c = 0;
				break;
			}
			if (i < 7)
				s = l_analyzer(buff, p, &a);
		}
		return c;
	}
}

struct ll** parser(char *input)
{ 
	struct ll** hash_arrays = (struct ll**)calloc(5, sizeof(struct ll*));
		for (int i = 0; i < 5; i++)
		{
			hash_arrays[i] = (struct ll*)calloc(1, sizeof(struct ll));
			hash_arrays[i]->next = NULL;
			hash_arrays[i]->s[0] = ' ';
		}
	char *parsers = (char *)calloc(20, sizeof(char));
	int i = 0;
	int *start = &i;
	int j = 0;
	int *no = &j;
	parsers=l_analyzer(input, start,no);
	while (strcmp(parsers, "") != 0)
	{
		if (j == 1)
		{
			hashing_syntax(hash_arrays, 1, "type", parsers, 0);
		}
		if (j == 2)
		{
			int start1 = *start;
			int no1 = *no;
			hashing_syntax(hash_arrays, 1, "columns", parsers, 0);
			parsers = l_analyzer(input, start, no);
			while (strcmp(parsers, "from"))
			{
				start1 = *start;
				
				hashing_syntax(hash_arrays, 1, "columns", parsers, 0);
				parsers = l_analyzer(input, start, no);
			}
			*no = no1;
			*start = start1;
		}
		if (j == 3)
		{
			
		}
		if (j == 4)
		{
			hashing_syntax(hash_arrays, 1, "table", parsers, 0);

		}
		if (j == 5)
		{

		}
		if (j == 6)
		{

		}
		if (j == 7)
		{
			hashing_syntax(hash_arrays, 1, "predicate", parsers, 0);
		}
		
		
		parsers = l_analyzer(input, start,no);

	}
	return hash_arrays;
}
struct info** hash_it1(struct info**x, struct info**h1)
{

	if (h1 == NULL)
	{
		h1 = (struct info **)calloc(sx1*size, sizeof(struct info*));
	}
	for (int i = 0; i < sx*size; i++)
	{
		if (x[i] != NULL&&x[i]->rollno != 0)
		{
			int j = x[i]->rollno;
			h1[j] = x[i];
			h1[j] = h1[j];
		}
	}
	return h1;

}
struct marks** hash_it2(struct marks**x, struct marks**h2)
{
	if (h2 == NULL)
	{
		h2 = (struct marks **)calloc(sx1*size, sizeof(struct marks*));
	}
	for (int i = 0; i < sx1*size; i++)
	{
		if (x[i] != NULL&&x[i]->rollno != 0)
		{
			int j = x[i]->rollno;
			h2[j] = x[i];
		}
	}
	return h2;
}
int hash_table(int *i, int c, char *buff, int v)
{


	if (c == 1)
	{
		i[((int)buff[0] + (int)buff[1]) % 127] = v;
		return 0;

	}
	else
	{
		return i[((int)buff[0] + (int)buff[1]) % 127];
	}
}
void puts_hash(int *i)
{
	hash_table(i, 1, "*", 1);
	hash_table(i, 1, "m1", 2);
	hash_table(i, 1, "m2", 3);
	hash_table(i, 1, "m3", 4);
	hash_table(i, 1, "m4", 5);
	hash_table(i, 1, "name", 6);
	hash_table(i, 1, "add", 2);
	hash_table(i, 1, "city", 3);
	hash_table(i, 1, "pin", 4);
	hash_table(i, 1, "phone", 5);
	hash_table(i, 1, "info", 1);
	hash_table(i, 1, "marks", 2);
	hash_table(i, 1, ">", 2);
	hash_table(i, 1, "<", 3);
	hash_table(i, 1, "=", 1);
}
void projection(struct info**in, int start, int stop, struct marks**m, int u, int *x,int x1)
{
	int i = start;
	if (u == 1)
	{
		if (start == stop)
		{
			if (in[start] != NULL)
			{
				printf("\n%d ", in[i]->rollno);
				//printf("\n%d %d %s %s %d", in[start]->rollno, in[start]->phone, in[start]->addr, in[start]->city, in[start]->pincode);
				for (int p = 0; p < x1; p++)
				{
					switch (x[p])
					{
					case 5:printf("%d ", in[i]->phone);
						break;
					case 2:printf("%s ", in[i]->addr);
						break;
					case 3:printf("%s ", in[i]->city);
						break;
					case 4:printf("%d ", in[i]->pincode);
						break;
					case 1:printf(" %d %s %s %d", in[start]->phone, in[start]->addr, in[start]->city, in[start]->pincode);
						break;
					}
				}
			}
			else
				printf("\n record doent exist");

		}
		else
		{
			for (int i = start; i < stop; i++)
			{
				if (in[i] != NULL)
				{
					printf("\n%d ", in[i]->rollno);
					//printf("\n%d %d %s %s %d", in[start]->rollno, in[start]->phone, in[start]->addr, in[start]->city, in[start]->pincode);
					for (int p = 0; p < x1; p++)
					{
						switch (x[p])
						{
						case 5:printf("%d ", in[i]->phone);
							break;
						case 2:printf("%s ", in[i]->addr);
							break;
						case 3:printf("%s ", in[i]->city);
							break;
						case 4:printf("%d ", in[i]->pincode);
							break;
						case 1:printf(" %d %s %s %d", in[start]->phone, in[start]->addr, in[start]->city, in[start]->pincode);
							break;
						}
					}
				}
			}
		}
	}
	else
	{
		if (start == stop)
		{
			if (m[start] != NULL)
			{
				printf("\n%d ", m[i]->rollno);
				//printf("\n %d %s %d %d %d %d ", m[start]->rollno, m[start]->name, m[start]->m1, m[start]->m2, m[start]->m3, m[start]->m4);
				for (int p = 0; p < x1; p++)
				{
					switch (x[p])
					{
					case 6:printf("%s ", m[i]->name);
						break;
					case 2:printf("%d ", m[i]->m1);
						break;
					case 3:printf("%d ", m[i]->m2);
						break;
					case 4:printf("%d ", m[i]->m3);
						break;
					case 5:printf("%d ", m[i]->m4);
						break;
					case 1:printf("  %s %d %d %d %d ", m[start]->name, m[start]->m1, m[start]->m2, m[start]->m3, m[start]->m4);
						break;

					}
				}
			}
			else
				printf("\n record doent exist");

		}
		else
		{
			for (int i = start; i < stop; i++)
			{
				if (m[i] != NULL)
				{
					
						printf("\n%d ", m[i]->rollno);
						for (int p = 0; p < x1; p++)
						{
							switch (x[p])
							{
							case 6:printf("%s ", m[i]->name);
								break;
							case 2:printf("%d ", m[i]->m1);
								break;
							case 3:printf("%d ", m[i]->m2);
								break;
							case 4:printf("%d ", m[i]->m3);
								break;
							case 5:printf("%d ", m[i]->m4);
								break;
							case 1:printf("  %s %d %d %d %d ", m[start]->name, m[start]->m1, m[start]->m2, m[start]->m3, m[start]->m4);
								break;

							}
					}
				}
			}
		}
	}

}
void load_files(struct info**h1, struct marks**h2,char *buff,int u)
{
	
	if (u == 1)
	{
		struct info**in = read_files1(buff);
		h1 = hash_it1(in, h1);
	}
	else{
		struct marks**m = read_files2(buff);
		h2 = hash_it2(m, h2);
	}
}
void executer(struct ll**h, struct info **h1, struct marks **h2)
{
	int h_k = 0,t,p,k;
	int h_keys[127];
	puts_hash(h_keys);
	int *a = (int *)calloc(6, sizeof(int));
	int i = 1;
	char *s = hashing_syntax(h, 2, "type", "", 1);
	if (strcmp(s, "select") == 0)
	{
		char *s2 = "";
		char *s3 = "";
		char *s1 = hashing_syntax(h, 2, "column", "", i);
		//s2 = hashing_syntax(h, 2, "column", "", &i);
		a[h_k] = hash_table(h_keys, 2, s1, 0);
		h_k++;
		while (strcmp(s2, s1) != 0)
		{
			s3 = s2;
			
			i++;
			s2 = hashing_syntax(h, 2, "column", "", i);
			if (strcmp(s3, s2) == 0)
				break;
			a[h_k] = hash_table(h_keys, 2, s2, 0);
			h_k++;
			
		} 
		s = hashing_syntax(h, 2, "table", "", 1);
		t = hash_table(h_keys, 2, s, 0);
		s = hashing_syntax(h, 2, "predicate", "", 1);
		char s0[2];
		s0[0] = s[0];
		s0[1] = '\0';
		p = hash_table(h_keys, 2, &s0, 0);
		k = atoi(&s[1]);

		int k2 = p;
		if (t == 1)
		{

			int x1 = k;
			if (k2 == 1)
			{
				projection(h1, x1, x1, h2, t, a, h_k);

			}
			else if (k2 == 2)
			{
				projection(h1, x1, sx1*size, h2, t, a, h_k);
			}
			else
				projection(h1, 0, x1, h2, t, a, h_k);
		}
		else{

			int x1 = k;
			if (k2 == 1)
			{
				projection(h1, x1, x1, h2, t, a, h_k);

			}
			else if (k2 == 2)
			{
				projection(h1, x1, sx1*size, h2, t, a, h_k);
			}
			else
				projection(h1, 0, x1, h2, t, a, h_k);
		}
	}
	if (strcmp(s, "load") == 0)
	{
		s = hashing_syntax(h, 2, "column", "", 1);
		s = hashing_syntax(h, 2, "table", "", 1);
		t = hash_table(h_keys, 2, s, 0);
		load_files(h1, h2,s,t);
	}
}

void joins(struct info **x, struct marks **y)
{
	printf("\n\n\nJOINS:\n\n\n");
	for (int i = 1; i < sx*size; i++)
	{
		for (int j = 0; j < sx1*size; j++)
		{
			if (x[i] != NULL&&y[j] != NULL&&x[i]->rollno == y[j]->rollno)
			{
				printf("%d %s %d %d %d %d %ld %s %s %d\n ", x[i]->rollno, y[i]->name, y[i]->m1, y[i]->m2, y[i]->m3, y[i]->m4, x[i]->phone, x[i]->addr, x[i]->city, x[i]->pincode);

				break;
			}
			if (x[i] != NULL && (j == sx1*size - 1))
			{
				printf("%d %s %d %d %d %d \n ", x[i]->rollno, y[i]->name, y[i]->m1, y[i]->m2, y[i]->m3, y[i]->m4);

			}

		}
	}
	
}

void main()
{
	printf("\n\nenter close to exit");
	printf("\n\nsyntax: select<space>{columns, * for all columns}from<space>where<space>{table:info or marks}rollno<space>{= or < or >}{search_value}");
	printf("\nex:select * from info where rollno =20");
	printf("\n\nsyntax:load<space>{path of file name}<space>into{table}");
	printf("\nex:load info1.txt into info");
	printf("\n\nenter joins to print left joins");
	printf("\n\npress enter to proceed");
	getchar();
	system("cls");
	struct info **in = read_files1("C:/Users/lakshmi/Downloads/studentinfolist.csv");
	struct marks **m = read_files2("C:/Users/lakshmi/Downloads/studentmarkslist.csv");

	struct info **h1 = hash_it1(in, NULL);
	struct marks **h2 = hash_it2(m, NULL);
	printf("\n>>");
	char *input_string = (char *)calloc(100, sizeof(char));
	fgets(input_string, 199, stdin);

	while (strcmp(input_string, "close\n") != 0)
	{
		if (strcmp(input_string, "joins\n") == 0)
		{
			joins(h1, h2);
		}
		else
		{
			char **check = define_grammer();

			if (valid_grammer(check, input_string) == 0)
			{
				printf("\ninvalid syntax");
				printf("\nsyntax: select<space>{columns, * for all columns}from<space>where<space>{table:info or marks}rollno<space>{= or < or >}{search_value}");
				printf("\nex:select * from info where rollno =20");
				printf("\nsyntax:load<space>{path of file name}<space>into{table}");
				printf("\nex:load info1.txt into info");
			}
			else
			{

				executer(parser(input_string), h1, h2);
				
			}
		}
		printf("\n>>");
		fgets(input_string, 199, stdin);
	}
}